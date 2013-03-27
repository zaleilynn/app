#include <sstream>
#include <google/gflags.h>
#include "include/system.h"
#include "worker/resource_manager.h"

using std::stringstream;

DECLARE_string(interface);
DECLARE_int32(port);

int ResourceManager::Init() {
    stringstream buffer;
    buffer << FLAGS_port;
    m_endpoint = System::GetIP(FLAGS_interface) + ":" + buffer.str();
    return 0; 
}
