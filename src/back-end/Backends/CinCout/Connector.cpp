#include <Pluma/Connector.hpp>
#include "CinCoutBackend.h"

PLUMA_CONNECTOR
bool connect(pluma::Host& host){
    host.add(new yagi::execution::CinCoutBackendProvider() );
    return true;
}
