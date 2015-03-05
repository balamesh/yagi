
/***************************************************************************
 *  yagi_protobuf.h - protobuf network communication for OpenPRS
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

#ifndef __FAWKES_BACKEND_YAGI_PROTOBUF_H_
#define __FAWKES_BACKEND_YAGI_PROTOBUF_H_

#include <list>
#include <map>

#include <protobuf_comm/server.h>
#include <core/threading/mutex.h>
#include <core/utils/lock_queue.h>

namespace protobuf_comm {
  class ProtobufStreamClient;
  class ProtobufBroadcastPeer;
}

namespace yagi_protobuf {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif

class YAGIProtobuf
{
 public:
  typedef enum {
    CT_SERVER, CT_CLIENT, CT_PEER
  } ClientType;

  typedef struct {
    std::string endpoint_host;
    unsigned short endpoint_port;
    uint16_t comp_id;
    uint16_t msg_type;
    std::shared_ptr<google::protobuf::Message> msg;
    ClientType ct;
    unsigned int client_id;
  } MessageData;

 public:
  YAGIProtobuf(std::vector<std::string> &proto_path);
  ~YAGIProtobuf();

  /** Get Protobuf server.
   * @return protobuf server */
  protobuf_comm::ProtobufStreamServer *  server() const
  { return server_; }

  /** Get protobuf_comm peers.
   * @return protobuf_comm peer */
  const std::map<long int, protobuf_comm::ProtobufBroadcastPeer *> &
  peers() const
  { return peers_; }

  /** Get the communicator's message register.
   * @return message register */
  protobuf_comm::MessageRegister &  message_register()
  { return *message_register_; }

  /** Signal invoked for a message that has been sent to a server client.
   * @return signal
   */
  boost::signals2::signal<void (protobuf_comm::ProtobufStreamServer::ClientID,
				std::shared_ptr<google::protobuf::Message>)> &
    signal_server_sent() { return sig_server_sent_; }

  /** Signal invoked for a message that has been sent to a client.
   * @return signal
   */
  boost::signals2::signal<void (std::string, unsigned short,
				std::shared_ptr<google::protobuf::Message>)> &
    signal_client_sent() { return sig_client_sent_; }

  /** Signal invoked for a message that has been sent via broadcast.
   * @return signal
   */
  boost::signals2::signal<void (long int, std::shared_ptr<google::protobuf::Message>)> &
    signal_peer_sent() { return sig_peer_sent_; }

  bool          yagi_pb_register_type(std::string full_name);
  std::string   yagi_pb_field_names(void *msgptr);
  bool          yagi_pb_has_field(void *msgptr, std::string field_name);
  std::string   yagi_pb_field_value(void *msgptr, std::string field_name);
  std::string   yagi_pb_field_type(void *msgptr, std::string field_name);
  std::string   yagi_pb_field_label(void *msgptr, std::string field_name);
  std::string   yagi_pb_field_list(void *msgptr, std::string field_name);
  bool          yagi_pb_field_is_list(void *msgptr, std::string field_name);
  std::shared_ptr<google::protobuf::Message> *  yagi_create_msg(std::string full_name);
  std::shared_ptr<google::protobuf::Message> *  yagi_pb_ref(void *msgptr);
  std::string   yagi_pb_destroy(void *msgptr);
  void          yagi_pb_set_field(void *msgptr, std::string field_name, std::string &value);
  void          yagi_pb_add_list(void *msgptr, std::string field_name, std::string &value);
  void          yagi_pb_send(long int client_id, void *msgptr);
  std::string   yagi_pb_client_connect(std::string host, int port);
  void          yagi_pb_disconnect(long int client_id);
  void          yagi_pb_broadcast(long int peer_id, void *msgptr);
  void          yagi_pb_enable_server(int port);
  void          yagi_pb_disable_server();

  long int      yagi_pb_peer_create(std::string host, int port);
  long int      yagi_pb_peer_create_local(std::string host,
					  int send_port, int recv_port);
  long int      yagi_pb_peer_create_crypto(std::string host, int port,
					   std::string crypto_key = "", std::string cipher = "");
  long int      yagi_pb_peer_create_local_crypto(std::string host,
						 int send_port, int recv_port,
						 std::string crypto_key = "", std::string cipher = "");
  void          yagi_pb_peer_destroy(long int peer_id);
  void          yagi_pb_peer_setup_crypto(long int peer_id,
					  std::string crypto_key, std::string cipher);
  
  bool          yagi_pb_events_pending();
  std::list<MessageData>  yagi_pb_process();

  std::string   build_pointer(void *p);
  void *        parse_pointer(std::string &p);

  void          set_peer_name(const std::string &name, long int client_id);
  long int      get_peer_name(const std::string &name);

 private:
  void clips_assert_message(std::pair<std::string, unsigned short> &endpoint,
			    uint16_t comp_id, uint16_t msg_type,
			    std::shared_ptr<google::protobuf::Message> &msg,
			    ClientType ct, unsigned int client_id = 0);
  void handle_server_client_connected(protobuf_comm::ProtobufStreamServer::ClientID client,
				      boost::asio::ip::tcp::endpoint &endpoint);
  void handle_server_client_disconnected(protobuf_comm::ProtobufStreamServer::ClientID client,
					 const boost::system::error_code &error);

  void handle_server_client_msg(protobuf_comm::ProtobufStreamServer::ClientID client,
				uint16_t component_id, uint16_t msg_type,
				std::shared_ptr<google::protobuf::Message> msg);

  void handle_server_client_fail(protobuf_comm::ProtobufStreamServer::ClientID client,
				 uint16_t component_id, uint16_t msg_type,
				 std::string msg);

  void handle_peer_msg(long int peer_id,
		       boost::asio::ip::udp::endpoint &endpoint,
		       uint16_t component_id, uint16_t msg_type,
		       std::shared_ptr<google::protobuf::Message> msg);
  void handle_peer_recv_error(long int peer_id, boost::asio::ip::udp::endpoint &endpoint, std::string msg);
  void handle_peer_send_error(long int peer_id, std::string msg);

  void handle_client_connected(long int client_id);
  void handle_client_disconnected(long int client_id,
				    const boost::system::error_code &error);
  void handle_client_msg(long int client_id,
			 uint16_t comp_id, uint16_t msg_type,
			 std::shared_ptr<google::protobuf::Message> msg);
  void handle_client_receive_fail(long int client_id,
				  uint16_t comp_id, uint16_t msg_type, std::string msg);
  void yagi_assert_message(std::string &endpoint_host, unsigned short endpoint_port,
			   uint16_t comp_id, uint16_t msg_type,
			   std::shared_ptr<google::protobuf::Message> &msg,
			   YAGIProtobuf::ClientType ct,
			   unsigned int client_id);
  void yagi_assert_server_client_event(long int client_id,
				       std::string &host, unsigned short port, bool connect);
  void yagi_assert_client_event(long int client_id, bool connect);

 private:
  protobuf_comm::MessageRegister       *message_register_;
  protobuf_comm::ProtobufStreamServer  *server_;

  boost::signals2::signal<void (protobuf_comm::ProtobufStreamServer::ClientID,
				std::shared_ptr<google::protobuf::Message>)> sig_server_sent_;
  boost::signals2::signal<void (std::string, unsigned short,
				std::shared_ptr<google::protobuf::Message>)> sig_client_sent_;
  boost::signals2::signal<void (long int, std::shared_ptr<google::protobuf::Message>)> sig_peer_sent_;
  
  fawkes::Mutex map_mutex_;
  long int next_client_id_;


  std::map<long int, protobuf_comm::ProtobufStreamServer::ClientID> server_clients_;
  typedef std::map<protobuf_comm::ProtobufStreamServer::ClientID, long int> RevServerClientMap;
  RevServerClientMap rev_server_clients_;
  std::map<long int, protobuf_comm::ProtobufStreamClient *>  clients_;
  std::map<long int, protobuf_comm::ProtobufBroadcastPeer *> peers_;

  std::map<long int, std::pair<std::string, unsigned short>> client_endpoints_;

  fawkes::LockQueue<
    std::tuple<std::string, unsigned short, uint16_t, uint16_t,
               std::shared_ptr<google::protobuf::Message>, ClientType, unsigned int>> q_msgs_;
  fawkes::LockQueue<std::tuple<long int, std::string, unsigned short, bool>> q_server_client_;
  fawkes::LockQueue<std::tuple<long int, bool>> q_client_;


  std::map<std::string, long int> client_names_;
};

} // end namespace protobuf_clips

#endif
