#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "master/machine_pool.h"

using lynn::ReadLocker;
using lynn::WriteLocker;

using log4cplus::Logger;
static Logger logger = Logger::getInstance("master");

void MachinePool::Insert(const MachinePtr& machine) {
    string endpoint = machine->GetEndpoint();
    WriteLocker locker(m_lock);
    m_machine_pool[endpoint] = machine;
}

void MachinePool::Delete(const string& endpoint) {
    m_machine_pool.erase(endpoint);
}

vector<string> MachinePool::GetAllMachineEndpoint() {
    ReadLocker locker(m_lock);
    vector<string> rtn;
    for(map<string, MachinePtr>::iterator it = m_machine_pool.begin();
        it != m_machine_pool.end(); ++it) {
        rtn.push_back(it->first);
    }
    return rtn;
}
