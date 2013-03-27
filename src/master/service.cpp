#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "master/service.h"
#include "master/machine_pool.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("master");

void MasterService::RegistMachine(const MachineInfo& info) {
    MachinePtr ptr(new Machine(info));
    MachinePoolI::Instance()->Insert(ptr);
}
