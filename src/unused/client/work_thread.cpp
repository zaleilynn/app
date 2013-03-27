#include "include/rpc.h"
#include "include/proxy.h"

void* RequestGenerator() {
    while(true) {
        float interval = GetInterval();
        usleep(1000000 * interval);
        TaskInfo info;
        info.app = "mixed";
    }
    return NULL;
}
