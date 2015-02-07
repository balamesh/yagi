#include <Pluma/Connector.hpp>
#include "AsraelBackend.h"

PLUMA_CONNECTOR
bool connect(pluma::Host& host){
    host.add(new yagi::execution::AsraelBackendProvider() );
    return true;
}
