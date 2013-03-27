#ifndef _APP_MASTER_MACHINE_POOL_H_
#define _APP_MASTER_MACHINE_POOL_H_

#include <map>
#include <string>
#include <vector>

#include "include/rwlock.h"
#include "include/singleton.h"
#include "master/machine.h"

using std::map;
using std::string;
using std::vector;
using lynn::RWLock;

class MachinePool {
public:
    void Insert(const MachinePtr& machine_ptr);
    vector<string> GetAllMachineEndpoint();
    void Delete(const string& endpoint);
private: 
    RWLock m_lock;
    map<string, MachinePtr> m_machine_pool;
};

typedef Singleton<MachinePool> MachinePoolI;
#endif
