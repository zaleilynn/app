#ifndef _APP_MASTER_MACHINE_H_
#define _APP_MASTER_MACHINE_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include "include/proxy.h"

using boost::shared_ptr;
using std::string;

class Machine {
public:
    explicit Machine(const MachineInfo& info) : m_machine_info(info) {};
    string GetEndpoint(){
        return m_machine_info.endpoint;
    }
private:
    MachineInfo m_machine_info;
};

typedef shared_ptr<Machine> MachinePtr;
#endif
