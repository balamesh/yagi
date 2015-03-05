
/***************************************************************************
 *  yagi_protobuf.cpp - protobuf network communication for YAGI
 *
 *  Created: Tue Feb 24 13:17:36 2015 (based on OpenPRS and CLIPS versions)
 *  Copyright  2013-2015  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/*  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the authors nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "yagi_protobuf.h"

#include <core/threading/mutex_locker.h>
#include <core/exception.h>
#include <core/exceptions/system.h>
#include <utils/misc/string_split.h>
#include <protobuf_comm/client.h>
#include <protobuf_comm/server.h>
#include <protobuf_comm/peer.h>

#include <google/protobuf/descriptor.h>

#include <algorithm>

using namespace google::protobuf;
using namespace protobuf_comm;

namespace yagi_protobuf {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif

/** @class YAGIProtobuf "yagi_protobuf.h"
 * YAGI protobuf integration class.
 * This class adds functionality related to protobuf to YAGI.
 * It supports the creation of communication channels through protobuf_comm.
 * An instance maintains its own message register shared among server, peer,
 * and clients.
 * @author Tim Niemueller
 */

/** Constructor.
 * @param proto_path proto path passed to a newly instantiated message register
 */
YAGIProtobuf::YAGIProtobuf(std::vector<std::string> &proto_path)
  : server_(NULL), next_client_id_(0)
{
  message_register_ = new MessageRegister(proto_path);
}


/** Destructor. */
YAGIProtobuf::~YAGIProtobuf()
{
  for (auto c : clients_) {
    delete c.second;
  }
  clients_.clear();

  delete message_register_;
  delete server_;
}


/** Enable protobuf stream server.
 * @param port TCP port to listen on for connections
 */
void
YAGIProtobuf::yagi_pb_enable_server(int port)
{
  if ((port > 0) && ! server_) {
    server_ = new protobuf_comm::ProtobufStreamServer(port, message_register_);

    server_->signal_connected()
      .connect(boost::bind(&YAGIProtobuf::handle_server_client_connected, this, _1, _2));
    server_->signal_disconnected()
      .connect(boost::bind(&YAGIProtobuf::handle_server_client_disconnected, this, _1, _2));
    server_->signal_received()
      .connect(boost::bind(&YAGIProtobuf::handle_server_client_msg, this, _1, _2, _3, _4));
    server_->signal_receive_failed()
      .connect(boost::bind(&YAGIProtobuf::handle_server_client_fail, this, _1, _2, _3, _4));
  }

}


/** Disable protobuf stream server. */
void
YAGIProtobuf::yagi_pb_disable_server()
{
  delete server_;
  server_ = NULL;
}


/** Enable protobuf peer.
 * @param address IP address to send messages to
 * @param send_port UDP port to send messages to
 * @param recv_port UDP port to receive messages on, 0 to use the same as the @p send_port
 * @param crypto_key encryption key
 * @param cipher cipher suite, see BufferEncryptor for supported types
 * @return peer identifier
 */
long int
YAGIProtobuf::yagi_pb_peer_create_local_crypto(std::string address, int send_port, int recv_port,
						  std::string crypto_key, std::string cipher)
{
  if (recv_port <= 0)  recv_port = send_port;

  if (send_port > 0) {
    protobuf_comm::ProtobufBroadcastPeer *peer =
      new protobuf_comm::ProtobufBroadcastPeer(address, send_port, recv_port,
					       message_register_, crypto_key, cipher);

    long int peer_id;
    {
      fawkes::MutexLocker lock(&map_mutex_);
      peer_id = ++next_client_id_;
      peers_[peer_id] = peer;
    }

    peer->signal_received()
      .connect(boost::bind(&YAGIProtobuf::handle_peer_msg, this, peer_id, _1, _2, _3, _4));
    peer->signal_recv_error()
      .connect(boost::bind(&YAGIProtobuf::handle_peer_recv_error, this, peer_id, _1, _2));
    peer->signal_send_error()
      .connect(boost::bind(&YAGIProtobuf::handle_peer_send_error, this, peer_id, _1));

    return peer_id;
  } else {
    return 0;
  }
}

/** Enable protobuf peer.
 * @param address IP address to send messages to
 * @param port UDP port to send and receive messages
 * @param crypto_key encryption key
 * @param cipher cipher suite, see BufferEncryptor for supported types
 * @return peer identifier
 */
long int
YAGIProtobuf::yagi_pb_peer_create_crypto(std::string address, int port,
						       std::string crypto_key, std::string cipher)
{
  return yagi_pb_peer_create_local_crypto(address, port, port, crypto_key, cipher);
}

/** Enable protobuf peer.
 * @param address IP address to send messages to
 * @param port UDP port to send and receive messages
 * @return peer identifier
 */
long int
YAGIProtobuf::yagi_pb_peer_create(std::string address, int port)
{
  return yagi_pb_peer_create_local_crypto(address, port, port);
}

/** Enable protobuf peer.
 * @param address IP address to send messages to
 * @param send_port UDP port to send messages to
 * @param recv_port UDP port to receive messages on, 0 to use the same as the @p send_port
 * @return peer identifier
 */
long int
YAGIProtobuf::yagi_pb_peer_create_local(std::string address, int send_port,
						      int recv_port)
{
  return yagi_pb_peer_create_local_crypto(address, send_port, recv_port);
}


/** Disable peer.
 * @param peer_id ID of the peer to destroy
 */
void
YAGIProtobuf::yagi_pb_peer_destroy(long int peer_id)
{
  if (peers_.find(peer_id) != peers_.end()) {
    delete peers_[peer_id];
    peers_.erase(peer_id);
  }
}


/** Setup crypto for peer. 
 * @param peer_id ID of the peer to destroy
 * @param crypto_key encryption key
 * @param cipher cipher suite, see BufferEncryptor for supported types
 */
void
YAGIProtobuf::yagi_pb_peer_setup_crypto(long int peer_id,
						      std::string crypto_key, std::string cipher)
{
  if (peers_.find(peer_id) != peers_.end()) {
    peers_[peer_id]->setup_crypto(crypto_key, cipher);
  }
}


/** Register a new message type.
 * @param full_name full name of type to register
 * @return true if the type was successfully registered, false otherwise
 */
bool
YAGIProtobuf::yagi_pb_register_type(std::string full_name)
{
  try {
    message_register_->add_message_type(full_name);
    return true;
  } catch (std::runtime_error &e) {
    //logger_->log_error("RefBox", "Registering type %s failed: %s", full_name.c_str(), e.what());
    return false;
  }
}



/** Create a new message of given type.
 * @param full_name name of message type (fully qualified, i.e. including package name)
 * @return shared pointer to new mesage
 * @exception std::runtime_error thrown if creating the message failed
 */
std::shared_ptr<google::protobuf::Message> *
YAGIProtobuf::yagi_create_msg(std::string full_name)
{
  std::shared_ptr<google::protobuf::Message> m =
    message_register_->new_message_for(full_name);
  return new std::shared_ptr<google::protobuf::Message>(m);
}


/** Create new reference to message.
 * @param msgptr message to create reference for
 * @return new message reference pointing to the very same message as @p msgptr
 */
std::shared_ptr<google::protobuf::Message> *
YAGIProtobuf::yagi_pb_ref(void *msgptr)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return new std::shared_ptr<google::protobuf::Message>();

  return new std::shared_ptr<google::protobuf::Message>(*m);
}


/** Destroy given message (reference).
 * This will decrement the reference count to the message and delete it.
 * The message itself is deleted if the reference counter reaches zero.
 * @param msgptr message (reference) to delete, any access to this message
 * afterwards is illegal.
 * @return T
 */
std::string
YAGIProtobuf::yagi_pb_destroy(void *msgptr)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return "false";

  delete m;
  return "true";
}


/** Get field names of message.
 * @param msgptr user pointer to message
 * @return term containing lisp list of field names
 */
std::string
YAGIProtobuf::yagi_pb_field_names(void *msgptr)
{
  std::list<std::string> tl;

  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return "";


  const Descriptor *desc = (*m)->GetDescriptor();
  const int field_count  = desc->field_count();
  for (int i = 0; i < field_count; ++i) {
    tl.push_back(desc->field(i)->name());
  }
  return fawkes::str_join(tl, ",");
}


/** Get type if a specific field.
 * @param msgptr message for which to get the field type
 * @param field_name name of the field
 * @return term with a symbol for the type
 */
std::string
YAGIProtobuf::yagi_pb_field_type(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return "INVALID-MESSAGE";

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field) {
    return "DOES-NOT-EXIST";
  }
  switch (field->type()) {
  case FieldDescriptor::TYPE_DOUBLE:   return "DOUBLE";
  case FieldDescriptor::TYPE_FLOAT:    return "FLOAT";
  case FieldDescriptor::TYPE_INT64:    return "INT64";
  case FieldDescriptor::TYPE_UINT64:   return "UINT64";
  case FieldDescriptor::TYPE_INT32:    return "INT32";
  case FieldDescriptor::TYPE_FIXED64:  return "FIXED64";
  case FieldDescriptor::TYPE_FIXED32:  return "FIXED32";
  case FieldDescriptor::TYPE_BOOL:     return "BOOL";
  case FieldDescriptor::TYPE_STRING:   return "STRING";
  case FieldDescriptor::TYPE_MESSAGE:  return "MESSAGE";
  case FieldDescriptor::TYPE_BYTES:    return "BYTES";
  case FieldDescriptor::TYPE_UINT32:   return "UINT32";
  case FieldDescriptor::TYPE_ENUM:     return "ENUM";
  case FieldDescriptor::TYPE_SFIXED32: return "SFIXED32";
  case FieldDescriptor::TYPE_SFIXED64: return "SFIXED64";
  case FieldDescriptor::TYPE_SINT32:   return "SINT32";
  case FieldDescriptor::TYPE_SINT64:   return "SINT64";
  default:  return "UNKNOWN";
  }
}


/** Check if message has a specific field.
 * This is relevant in particular for optional fields.
 * @param msgptr message
 * @param field_name name of the field
 * @return true if the field is present, false otherwise
 */
bool
YAGIProtobuf::yagi_pb_has_field(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return false;

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field)  return false;

  const Reflection *refl       = (*m)->GetReflection();

  if (field->is_repeated()) {
    return (refl->FieldSize(**m, field) > 0);
  } else {
    return refl->HasField(**m, field);
  }
}


/** Get a fields label.
 * @param msgptr message for which to get the field type
 * @param field_name name of the field
 * @return Term with Symbol, one of INVALID-MESSAGE, DOES-NOT-EXIST, OPTIONAL, REPEATED, UNKNOWN
 */
std::string
YAGIProtobuf::yagi_pb_field_label(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return "INVALID-MESSAGE";

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field)  return "DOES-NOT-EXIST";
  switch (field->label()) {
  case FieldDescriptor::LABEL_OPTIONAL: return "OPTIONAL";
  case FieldDescriptor::LABEL_REQUIRED: return "REQUIRED";
  case FieldDescriptor::LABEL_REPEATED: return "REPEATED";
  default:                              return "UNKNOWN";
  }
}

/** Get properly typed field value.
 * @param msgptr message for which to get the field type
 * @param field_name name of the field
 * @return Term with value of proper type
 */
std::string
YAGIProtobuf::yagi_pb_field_value(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return "INVALID-MESSAGE";

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field)  return "DOES-NOT-EXIST";
  const Reflection *refl       = (*m)->GetReflection();
  if (field->type() != FieldDescriptor::TYPE_MESSAGE && ! refl->HasField(**m, field)) {
    //logger_->log_warn("RefBox", "Field %s of %s not set",
    //	   field_name.c_str(), (*m)->GetTypeName().c_str());
    return "NOT-SET";
  }
  switch (field->type()) {
  case FieldDescriptor::TYPE_DOUBLE:   return std::to_string(refl->GetDouble(**m, field));
  case FieldDescriptor::TYPE_FLOAT:    return std::to_string(refl->GetFloat(**m, field));
  case FieldDescriptor::TYPE_INT64:    return std::to_string(refl->GetInt64(**m, field));
  case FieldDescriptor::TYPE_UINT64:
    return std::to_string((long int)refl->GetUInt64(**m, field));
  case FieldDescriptor::TYPE_INT32:    return std::to_string(refl->GetInt32(**m, field));
  case FieldDescriptor::TYPE_FIXED64:
    return std::to_string((long int)refl->GetUInt64(**m, field));
  case FieldDescriptor::TYPE_FIXED32:  return std::to_string(refl->GetUInt32(**m, field));
  case FieldDescriptor::TYPE_BOOL:     return refl->GetBool(**m, field) ? "true" : "false";
  case FieldDescriptor::TYPE_STRING:   return refl->GetString(**m, field);
  case FieldDescriptor::TYPE_MESSAGE:
    {
      const google::protobuf::Message &mfield = refl->GetMessage(**m, field);
      google::protobuf::Message *mcopy = mfield.New();
      mcopy->CopyFrom(mfield);
      void *ptr = new std::shared_ptr<google::protobuf::Message>(mcopy);
      return build_pointer(ptr);
    }
  case FieldDescriptor::TYPE_BYTES:    return "bytes";
  case FieldDescriptor::TYPE_UINT32:   return std::to_string(refl->GetUInt32(**m, field));
  case FieldDescriptor::TYPE_ENUM:
    return refl->GetEnum(**m, field)->name();
  case FieldDescriptor::TYPE_SFIXED32: return std::to_string(refl->GetInt32(**m, field));
  case FieldDescriptor::TYPE_SFIXED64: return std::to_string(refl->GetInt64(**m, field));
  case FieldDescriptor::TYPE_SINT32:   return std::to_string(refl->GetInt32(**m, field));
  case FieldDescriptor::TYPE_SINT64:   return std::to_string(refl->GetInt64(**m, field));
  default:
    throw std::logic_error("Unknown protobuf field type encountered");
  }
}


/** Set a field.
 * @param msgptr message for which to get the field type
 * @param field_name name of the field
 * @param value term which must contain a single properly typed value.
 */
void
YAGIProtobuf::yagi_pb_set_field(void *msgptr, std::string field_name, std::string &value)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!*m) return;

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field) {
    //logger_->log_warn("RefBox", "Could not find field %s", field_name.c_str());
    return;
  }
  const Reflection *refl       = (*m)->GetReflection();

  try {
    switch (field->type()) {
    case FieldDescriptor::TYPE_DOUBLE:
      refl->SetDouble(m->get(), field, std::stod(value));
      break;
    case FieldDescriptor::TYPE_FLOAT: 
      refl->SetFloat(m->get(), field, std::stof(value));
      break;
    case FieldDescriptor::TYPE_SFIXED64:
    case FieldDescriptor::TYPE_SINT64:
    case FieldDescriptor::TYPE_INT64:
      refl->SetInt64(m->get(), field, std::stol(value));
      break;
    case FieldDescriptor::TYPE_FIXED64:
    case FieldDescriptor::TYPE_UINT64:
      refl->SetUInt64(m->get(), field, std::stol(value));
      break;
    case FieldDescriptor::TYPE_SFIXED32:
    case FieldDescriptor::TYPE_SINT32:
    case FieldDescriptor::TYPE_INT32:
      refl->SetInt32(m->get(), field, std::stoi(value));
      break;
    case FieldDescriptor::TYPE_BOOL:
      refl->SetBool(m->get(), field, (value == "true"));
      break;
    case FieldDescriptor::TYPE_STRING:
      refl->SetString(m->get(), field, value);
      break;
    case FieldDescriptor::TYPE_MESSAGE:
      {
	std::shared_ptr<google::protobuf::Message> *mfrom =
	  static_cast<std::shared_ptr<google::protobuf::Message> *>(parse_pointer(value));
	if (mfrom) {
	  Message *mut_msg = refl->MutableMessage(m->get(), field);
	  mut_msg->CopyFrom(**mfrom);
	  delete mfrom;
	}
      }
      break;
    case FieldDescriptor::TYPE_BYTES:    break;
    case FieldDescriptor::TYPE_FIXED32:
    case FieldDescriptor::TYPE_UINT32:
      refl->SetUInt32(m->get(), field, std::stol(value));
      break;
    case FieldDescriptor::TYPE_ENUM:
      {
	const std::string &sym_name = value;

	const EnumDescriptor *enumdesc = field->enum_type();
	const EnumValueDescriptor *enumval = enumdesc->FindValueByName(sym_name);
	if (enumval) {
	  refl->SetEnum(m->get(), field, enumval);
	} else {
	  std::string sym_str(sym_name);
	  std::transform(sym_str.begin(), sym_str.end(), sym_str.begin(), std::ptr_fun<int, int>(std::toupper));

	  const EnumValueDescriptor *enumval = enumdesc->FindValueByName(sym_str);

	  if (enumval) {
	    refl->SetEnum(m->get(), field, enumval);
	  } else {
	    fprintf(stderr, "%s: cannot set invalid enum value '%s' (neither '%s') on '%s'",
		    (*m)->GetTypeName().c_str(), sym_name.c_str(), sym_str.c_str(), field_name.c_str());
	  }
	}
      }
      break;

    default:
      throw std::logic_error("Unknown protobuf field type encountered");
    }
  } catch (std::logic_error &e) {
    //logger_->log_warn("RefBox", "Failed to set field %s of %s: %s", field_name.c_str(),
    //	   (*m)->GetTypeName().c_str(), e.what());
  }
}


/** Add value to a repeated field.
 * @param msgptr message
 * @param field_name name of the field
 * @param value term which must contain a single properly typed value.
 */
void
YAGIProtobuf::yagi_pb_add_list(void *msgptr, std::string field_name, std::string &value)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!(m || *m)) return;

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field) {
    //logger_->log_warn("RefBox", "Could not find field %s", field_name.c_str());
    return;
  }
  const Reflection *refl       = (*m)->GetReflection();

  try {
    switch (field->type()) {
    case FieldDescriptor::TYPE_DOUBLE:
      refl->AddDouble(m->get(), field, std::stod(value));
      break;
    case FieldDescriptor::TYPE_FLOAT: 
      refl->AddFloat(m->get(), field, std::stof(value));
      break;

    case FieldDescriptor::TYPE_SFIXED64:
    case FieldDescriptor::TYPE_SINT64:
    case FieldDescriptor::TYPE_INT64:
      refl->AddInt64(m->get(), field, std::stol(value));
      break;

    case FieldDescriptor::TYPE_SFIXED32:
    case FieldDescriptor::TYPE_SINT32:
    case FieldDescriptor::TYPE_INT32:
      refl->AddInt32(m->get(), field, std::stoi(value));
      break;
    case FieldDescriptor::TYPE_BOOL:
      refl->AddBool(m->get(), field, (value == "true"));
      break;
    case FieldDescriptor::TYPE_STRING:
      refl->AddString(m->get(), field, value);
      break;
    case FieldDescriptor::TYPE_MESSAGE:
      {
	std::shared_ptr<google::protobuf::Message> *mfrom =
	  static_cast<std::shared_ptr<google::protobuf::Message> *>(parse_pointer(value));
	if (mfrom) {
	  Message *mut_msg = refl->AddMessage(m->get(), field);
	  mut_msg->CopyFrom(**mfrom);
	  delete mfrom;
	} else {
	  throw std::logic_error(std::string("Invalid pointer, required user pointer for ") +
				 (*m)->GetTypeName() + field_name);
	}
      }
      break;

    case FieldDescriptor::TYPE_BYTES:    break;

    case FieldDescriptor::TYPE_FIXED32:
    case FieldDescriptor::TYPE_UINT32:
      refl->AddUInt32(m->get(), field, std::stol(value));
      break;

    case FieldDescriptor::TYPE_ENUM:
      {
	const std::string &sym_name = value;

	const EnumDescriptor *enumdesc = field->enum_type();
	const EnumValueDescriptor *enumval = enumdesc->FindValueByName(sym_name);
	if (enumval) {
	  refl->AddEnum(m->get(), field, enumval);
	} else {
	  //logger_->log_warn("RefBox", "%s: cannot set invalid enum value '%s' on '%s'",
	  //	 (*m)->GetTypeName().c_str(), value.as_string().c_str(), field_name.c_str());
	}
      }
      break;

    default:
      throw std::logic_error("Unknown protobuf field type encountered");
    }
  } catch (std::logic_error &e) {
    //logger_->log_warn("RefBox", "Failed to add field %s of %s: %s", field_name.c_str(),
    //	   (*m)->GetTypeName().c_str(), e.what());
  }
}


/** Connect as a client to the given server.
 * Note that this will perform an asynchronous connect. A
 * (protobuf-client-connected) or (protobuf-client-disconnected) fact
 * is asserted during (pb-process) in the case of success or failure.
 * @param host host to connect to
 * @param port TCP port to connect to
 * @return Term with a long long of the client ID
 */
std::string
YAGIProtobuf::yagi_pb_client_connect(std::string host, int port)
{
  if (port <= 0) return "false";

  ProtobufStreamClient *client = new ProtobufStreamClient(message_register_);

  long int client_id;
  {
    fawkes::MutexLocker lock(&map_mutex_);
    client_id = ++next_client_id_;
    clients_[client_id] = client;
  }

  client->signal_connected().connect(
    boost::bind(&YAGIProtobuf::handle_client_connected, this, client_id));
  client->signal_disconnected().connect(
    boost::bind(&YAGIProtobuf::handle_client_disconnected,
		this, client_id, boost::asio::placeholders::error));
  client->signal_received().connect(
    boost::bind(&YAGIProtobuf::handle_client_msg, this, client_id, _1, _2, _3));
  client->signal_receive_failed().connect(
    boost::bind(&YAGIProtobuf::handle_client_receive_fail, this, client_id, _1, _2, _3));

  client->async_connect(host.c_str(), port);
  return std::to_string(client_id);
}


/** Send message to a specific client.
 * @param client_id ID of the client, this can be a server client ID, a client
 * ID, or a peer ID (message will then be broadcasted).
 * @param msgptr message to send
 */
void
YAGIProtobuf::yagi_pb_send(long int client_id, void *msgptr)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!(m || *m)) {
    //logger_->log_warn("RefBox", "Cannot send to %li: invalid message", client_id);
    return;
  }

  try {
    fawkes::MutexLocker lock(&map_mutex_);

    if (server_ && server_clients_.find(client_id) != server_clients_.end()) {
      //printf("***** SENDING via SERVER\n");
      server_->send(server_clients_[client_id], *m);
      sig_server_sent_(server_clients_[client_id], *m);
    } else if (clients_.find(client_id) != clients_.end()) {
      //printf("***** SENDING via CLIENT\n");
      clients_[client_id]->send(*m);
      std::pair<std::string, unsigned short> &client_endpoint = client_endpoints_[client_id];
      sig_client_sent_(client_endpoint.first, client_endpoint.second, *m);
    } else if (peers_.find(client_id) != peers_.end()) {
      //printf("***** SENDING via CLIENT\n");
      peers_[client_id]->send(*m);
      sig_peer_sent_(client_id, *m);
    } else {
      //printf("Client ID %li is unknown, cannot send message of type %s\n",
      //     client_id, (*m)->GetTypeName().c_str());
    }
  } catch (google::protobuf::FatalException &e) {
    //logger_->log_warn("RefBox", "Failed to send message of type %s: %s",
    //     (*m)->GetTypeName().c_str(), e.what());
  } catch (std::runtime_error &e) {
    //logger_->log_warn("RefBox", "Failed to send message of type %s: %s",
    //     (*m)->GetTypeName().c_str(), e.what());
  }
}


/** Broadcast a message through a peer.
 * @param peer_id ID broadcast peer to send through
 * @param msgptr message to send
 */
void
YAGIProtobuf::yagi_pb_broadcast(long int peer_id, void *msgptr)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!(m || *m)) {
    fprintf(stderr, "Cannot send broadcast: invalid message");
    return;
  }

  fawkes::MutexLocker lock(&map_mutex_);
  if (peers_.find(peer_id) == peers_.end())  return;

  try {
    peers_[peer_id]->send(*m);
  } catch (google::protobuf::FatalException &e) {
    fprintf(stderr, "pb-broadcast: failed to broadcast message of type %s: %s\n",
	    (*m)->GetTypeName().c_str(), e.what());
  }

  sig_peer_sent_(peer_id, *m);
}


/** Disconnect a given client.
 * @param client_id ID of client to disconnect, can be a server client ID or a client ID
 */
void
YAGIProtobuf::yagi_pb_disconnect(long int client_id)
{
  //logger_->log_info("RefBox", "Disconnecting client %li", client_id);

  try {
    fawkes::MutexLocker lock(&map_mutex_);

    if (server_clients_.find(client_id) != server_clients_.end()) {
      protobuf_comm::ProtobufStreamServer::ClientID srv_client = server_clients_[client_id];
      server_->disconnect(srv_client);
      server_clients_.erase(client_id);
      rev_server_clients_.erase(srv_client);
    } else if (clients_.find(client_id) != clients_.end()) {
      delete clients_[client_id];
      clients_.erase(client_id);
    }
  } catch (std::runtime_error &e) {
    throw fawkes::Exception("Failed to disconnect from client %li: %s", client_id, e.what());
  }
}


/** Get list of values of a given message field.
 * @param msgptr message
 * @param field_name field to retrieve
 * @return term which contains a Lisp list with properly typed values, or a symbol in
 * case of an error
 */
std::string
YAGIProtobuf::yagi_pb_field_list(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!(m || *m)) return "INVALID-MESSAGE";

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field)  return "DOES-NOT-EXIST";

  std::list<std::string> tl;

  if (field->label() == FieldDescriptor::LABEL_REQUIRED ||
      field->label() == FieldDescriptor::LABEL_OPTIONAL)
  {
    tl.push_back(yagi_pb_field_value(msgptr, field_name));
    return fawkes::str_join(tl, ",");
  }

  const Reflection *refl       = (*m)->GetReflection();
  int field_size = refl->FieldSize(**m, field);
  for (int i = 0; i < field_size; ++i) {
    switch (field->type()) {
    case FieldDescriptor::TYPE_DOUBLE:
      tl.push_back(std::to_string(refl->GetRepeatedDouble(**m, field, i)));
      break;
    case FieldDescriptor::TYPE_FLOAT:
      tl.push_back(std::to_string(refl->GetRepeatedFloat(**m, field, i)));
      break;
      break;
    case FieldDescriptor::TYPE_UINT64:
    case FieldDescriptor::TYPE_FIXED64:
      tl.push_back(std::to_string(refl->GetRepeatedUInt64(**m, field, i)));
      break;
    case FieldDescriptor::TYPE_UINT32:
    case FieldDescriptor::TYPE_FIXED32:
      tl.push_back(std::to_string(refl->GetRepeatedUInt32(**m, field, i)));
      break;
    case FieldDescriptor::TYPE_BOOL:
      tl.push_back(refl->GetRepeatedBool(**m, field, i) ? "true" : "false");
      break;
    case FieldDescriptor::TYPE_STRING:
      tl.push_back(refl->GetRepeatedString(**m, field, i).c_str());
      break;
    case FieldDescriptor::TYPE_MESSAGE:
      {
	const google::protobuf::Message &msg = refl->GetRepeatedMessage(**m, field, i);
	google::protobuf::Message *mcopy = msg.New();
	mcopy->CopyFrom(msg);
	void *ptr = new std::shared_ptr<google::protobuf::Message>(mcopy);
	tl.push_back(build_pointer(ptr));
      }
      break;
    case FieldDescriptor::TYPE_BYTES:
      tl.push_back((char *)"bytes");
      break;
    case FieldDescriptor::TYPE_ENUM:
      tl.push_back(refl->GetRepeatedEnum(**m, field, i)->name());
      break;
    case FieldDescriptor::TYPE_SFIXED32:
    case FieldDescriptor::TYPE_INT32:
    case FieldDescriptor::TYPE_SINT32:
      tl.push_back(std::to_string(refl->GetRepeatedInt32(**m, field, i)));
      break;
    case FieldDescriptor::TYPE_SFIXED64:
    case FieldDescriptor::TYPE_SINT64:
    case FieldDescriptor::TYPE_INT64:
      tl.push_back(std::to_string(refl->GetRepeatedInt64(**m, field, i)));
      break;
    default:
      throw std::logic_error("Unknown protobuf field type encountered");
    }
  }

  return fawkes::str_join(tl, ",");
}


/** Check if a given field is a list (repeated field).
 * @param msgptr message
 * @param field_name name of the field
 * @return true if the field is a list, false otherwise
 */
bool
YAGIProtobuf::yagi_pb_field_is_list(void *msgptr, std::string field_name)
{
  std::shared_ptr<google::protobuf::Message> *m =
    static_cast<std::shared_ptr<google::protobuf::Message> *>(msgptr);
  if (!(m || *m)) return false;

  const Descriptor *desc       = (*m)->GetDescriptor();
  const FieldDescriptor *field = desc->FindFieldByName(field_name);
  if (! field) {
    return false;
  }
  return (field->label() == FieldDescriptor::LABEL_REPEATED);
}


/** Process all pending events.
 * This will process events and assert appropriate facts.
 */
std::list<YAGIProtobuf::MessageData>
YAGIProtobuf::yagi_pb_process()
{
  /*
  { fawkes::MutexLocker lock(q_server_client_.mutex());
    while (! q_server_client_.empty()) {
      auto &sc = q_server_client_.front();
      yagi_assert_server_client_event(std::get<0>(sc), std::get<1>(sc),
				      std::get<2>(sc), std::get<3>(sc));
      q_server_client_.pop();
    }
  }
  */

  /*
  { fawkes::MutexLocker lock(q_client_.mutex());
    while (! q_client_.empty()) {
      auto &c = q_client_.front();
      yagi_assert_client_event(std::get<0>(c), std::get<1>(c));
      q_client_.pop();
    }
  }
  */

  std::list<MessageData> msgs;
  { fawkes::MutexLocker lock(q_msgs_.mutex());
    while (! q_msgs_.empty()) {
      auto &m = q_msgs_.front();
      msgs.push_back(
	{std::get<0>(m), std::get<1>(m), std::get<2>(m),
         std::get<3>(m), std::get<4>(m), std::get<5>(m), std::get<6>(m)});
      q_msgs_.pop();
    }
  }

    return msgs;
}


/** Check if there are pending events.
 * @return true if there are pending events, false otherwise
 */
bool
YAGIProtobuf::yagi_pb_events_pending()
{
  fawkes::MutexLocker lock1(q_server_client_.mutex());
  fawkes::MutexLocker lock2(q_client_.mutex());
  fawkes::MutexLocker lock3(q_msgs_.mutex());

  return (! (q_server_client_.empty() && q_client_.empty() && q_msgs_.empty()));
}


void
YAGIProtobuf::yagi_assert_server_client_event(long int client_id,
					      std::string &host, unsigned short port, bool connect)
{
  /*
  TermList tl = sl_make_slist();
  tl = build_term_list(tl, std::to_string(client_id));
  if (connect) {
    tl = build_term_list(tl, host.c_str());
    tl = build_term_list(tl, std::to_string(port));
    add_external_fact((char *)"protobuf-server-client-connected", tl);
  } else {
    add_external_fact((char *)"protobuf-server-client-disconnected", tl);
  }
  */
}


void
YAGIProtobuf::yagi_assert_client_event(long int client_id, bool connect)
{
  /*
  TermList tl = sl_make_slist();
  tl = build_term_list(tl, std::to_string(client_id));
  if (connect) {
    add_external_fact((char *)"protobuf-client-connected", tl);
  } else {
    add_external_fact((char *)"protobuf-client-disconnected", tl);
  }
  */
}

void
YAGIProtobuf::yagi_assert_message(std::string &endpoint_host, unsigned short endpoint_port,
				     uint16_t comp_id, uint16_t msg_type,
				     std::shared_ptr<google::protobuf::Message> &msg,
				     YAGIProtobuf::ClientType ct,
				     unsigned int client_id)
{
  /*
  TermList tl = sl_make_slist();

  struct timeval tv;
  gettimeofday(&tv, 0);
  void *ptr = new std::shared_ptr<google::protobuf::Message>(msg);
  //tl = build_term_list(tl, (char *)"type"));
  tl = build_term_list(tl, msg->GetTypeName().c_str()));
  //tl = build_term_list(tl, (char *)"comp-id"));
  tl = build_term_list(tl, std::to_string(comp_id));
  //tl = build_term_list(tl, (char *)"msg-type"));
  tl = build_term_list(tl, std::to_string(msg_type));
  //tl = build_term_list(tl, (char *)"rcvd-via"));
  tl = build_term_list(tl, (client_id == 0) ? "BROADCAST" : "STREAM"));
  //tl = build_term_list(tl, (char *)"rcvd-at"));
  tl = build_term_list(tl, std::to_string(tv.tv_sec));
  tl = build_term_list(tl, std::to_string(tv.tv_usec));
  //tl = build_term_list(tl, (char *)"rcvd-from"));
  tl = build_term_list(tl, endpoint_host.c_str()));
  tl = build_term_list(tl, std::to_string(endpoint_port));
  //tl = build_term_list(tl, (char *)"client-type"));
  tl = build_term_list(tl, ct == CT_CLIENT ? "CLIENT" :
					(ct == CT_SERVER ? "SERVER" : "PEER")));
  //tl = build_term_list(tl, (char *)"client-id"));
  tl = build_term_list(tl, std::to_string(client_id));
  //tl = build_term_list(tl, (char *)"ptr"));
  tl = build_term_list(tl, build_pointer(ptr));

  add_external_fact((char *)"protobuf-msg", tl);
  */
}


std::string
YAGIProtobuf::build_pointer(void *p)
{
  std::string rv;
  char *tmp;
  if (asprintf(&tmp, "%p", p) == -1) {
    throw fawkes::OutOfMemoryException("Failed to allocate pointer string");
  }
  rv = tmp;
  free(tmp);
  return rv;
}


void *
YAGIProtobuf::parse_pointer(std::string &p)
{
  long long pl = std::stoll(p);
  return (void *)pl;
}


void
YAGIProtobuf::set_peer_name(const std::string &name, long int client_id)
{
  client_names_[name] = client_id;
}


long int
YAGIProtobuf::get_peer_name(const std::string &name)
{
  std::map<std::string, long int>::const_iterator c =
    client_names_.find(name);
  if (c == client_names_.end()) {
    return 0;
  } else {
    return c->second;
  }
}

void
YAGIProtobuf::handle_server_client_connected(ProtobufStreamServer::ClientID client,
						boost::asio::ip::tcp::endpoint &endpoint)
{

  long int client_id = -1;
  {
    fawkes::MutexLocker lock(&map_mutex_);
    client_id = ++next_client_id_;
    client_endpoints_[client_id] =
      std::make_pair(endpoint.address().to_string(), endpoint.port());
    server_clients_[client_id] = client;
    rev_server_clients_[client] = client_id;
  }

  q_server_client_.push_locked(
    std::make_tuple(client_id, endpoint.address().to_string(), endpoint.port(), true));
}


void
YAGIProtobuf::handle_server_client_disconnected(ProtobufStreamServer::ClientID client,
						   const boost::system::error_code &error)
{
  long int client_id = -1;
  {
    fawkes::MutexLocker lock(&map_mutex_);
    RevServerClientMap::iterator c;
    if ((c = rev_server_clients_.find(client)) != rev_server_clients_.end()) {
      client_id = c->second;
      rev_server_clients_.erase(c);
      server_clients_.erase(client_id);
    }
  }

  if (client_id >= 0) {
    q_server_client_.push_locked(std::make_tuple(client_id, "", 0, false));
  }
}


/** Handle message that came from a client.
 * @param client client ID
 * @param component_id component the message was addressed to
 * @param msg_type type of the message
 * @param msg the message
 */
void
YAGIProtobuf::handle_server_client_msg(ProtobufStreamServer::ClientID client,
						    uint16_t component_id, uint16_t msg_type,
						    std::shared_ptr<google::protobuf::Message> msg)
{
  fawkes::MutexLocker lock(&map_mutex_);
  RevServerClientMap::iterator c;
  if ((c = rev_server_clients_.find(client)) != rev_server_clients_.end()) {
    q_msgs_.push_locked(std::make_tuple(client_endpoints_[c->second].first,
					client_endpoints_[c->second].second,
					component_id, msg_type, msg, CT_SERVER, c->second));
  }
}

/** Handle server reception failure
 * @param client client ID
 * @param component_id component the message was addressed to
 * @param msg_type type of the message
 * @param msg the message string
 */
void
YAGIProtobuf::handle_server_client_fail(ProtobufStreamServer::ClientID client,
						     uint16_t component_id, uint16_t msg_type,
						     std::string msg)
{
  fawkes::MutexLocker lock(&map_mutex_);
  RevServerClientMap::iterator c;
  if ((c = rev_server_clients_.find(client)) != rev_server_clients_.end()) {
    /*
    fawkes::MutexLocker lock(&yagi_mutex_);
    yagi_->assert_fact_f("(protobuf-server-receive-failed (comp-id %u) (msg-type %u) "
			  "(rcvd-via STREAM) (client-id %li) (message \"%s\") "
			  "(rcvd-from (\"%s\" %u)))",
			  component_id, msg_type, c->second, msg.c_str(),
			  client_endpoints_[c->second].first.c_str(),
			  client_endpoints_[c->second].second);
    */
  }
}


/** Handle message that came from a peer/robot
 * @param endpoint the endpoint from which the message was received
 * @param component_id component the message was addressed to
 * @param msg_type type of the message
 * @param msg the message
 */
void
YAGIProtobuf::handle_peer_msg(long int peer_id,
					   boost::asio::ip::udp::endpoint &endpoint,
					   uint16_t component_id, uint16_t msg_type,
					   std::shared_ptr<google::protobuf::Message> msg)
{
  q_msgs_.push_locked(std::make_tuple(endpoint.address().to_string(), endpoint.port(),
				      component_id, msg_type, msg, CT_PEER, peer_id));
}


/** Handle error during peer message processing.
 * @param endpoint endpoint of incoming message
 * @param msg error message
 */
void
YAGIProtobuf::handle_peer_recv_error(long int peer_id,
					boost::asio::ip::udp::endpoint &endpoint, std::string msg)
{
  fprintf(stderr, "Failed to receive peer message from %s:%u: %s\n",
	  endpoint.address().to_string().c_str(), endpoint.port(), msg.c_str());
}

/** Handle error during peer message processing.
 * @param msg error message
 */
void
YAGIProtobuf::handle_peer_send_error(long int peer_id, std::string msg)
{
  //logger_->log_warn("RefBox", "Failed to send peer message: %s", msg.c_str());
}


void
YAGIProtobuf::handle_client_connected(long int client_id)
{
  q_client_.push_locked(std::make_tuple(client_id, true));
}

void
YAGIProtobuf::handle_client_disconnected(long int client_id,
					    const boost::system::error_code &error)
{
  q_client_.push_locked(std::make_tuple(client_id, false));
}

void
YAGIProtobuf::handle_client_msg(long int client_id,
				   uint16_t comp_id, uint16_t msg_type,
				   std::shared_ptr<google::protobuf::Message> msg)
{
  q_msgs_.push_locked(std::make_tuple("", 0, comp_id, msg_type, msg, CT_CLIENT, client_id));
}


void
YAGIProtobuf::handle_client_receive_fail(long int client_id,
						      uint16_t comp_id, uint16_t msg_type, std::string msg)
{
}

} // end namespace protobuf_clips
