#ifndef _APP_WORKER_RESOURCE_MANAGER_H_
#define _APP_WORKER_RESOURCE_MANAGER_H_

#include <string>
#include "include/singleton.h"
 
using std::string;

class ResourceManager {
public:
    int Init();
    string GetMachineEndpoint(){
        return m_endpoint;
    }
private:
    string m_endpoint;
};

typedef Singleton<ResourceManager> ResourceManagerI;
#endif
