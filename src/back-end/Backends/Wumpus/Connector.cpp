#include <Pluma/Connector.hpp>
#include "WumpusBackend.h"

PLUMA_CONNECTOR
bool connect(pluma::Host& host){
    host.add(new yagi::execution::WumpusBackendProvider() );
    return true;
}
