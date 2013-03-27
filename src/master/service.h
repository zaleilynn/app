#ifndef _APP_SRC_MASTER_SERVICE_H_
#define _APP_SRC_MASTER_SERVICE_H_

#include <string>
#include "include/proxy.h"

using std::string;

class MasterService : public MasterIf {
public:
    void RegistMachine(const MachineInfo& machine_info);
};

#endif

