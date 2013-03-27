#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <boost/thread.hpp>

#include "include/rpc.h"
#include "master/task.h"
#include "master/machine_pool.h"
#include "master/request.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("master");

void* SchedulerProcessor() {
    while(true) {
        vector<string> machines = MachinePoolI::Instance()->GetAllMachineEndpoint();
        if(machines.size() == 0) {
            //没有机器,不能一直查询
            LOG4CPLUS_INFO(logger, "no machine right now...");
            sleep(1);
        } else {
            
            for(vector<string>::iterator it = machines.begin(); it != machines.end(); it++) {
                TaskPtr task;
                TaskBufferI::Instance()->PopFront(&task);
                try {
                    Proxy<WorkerClient> proxy = Rpc<WorkerClient, WorkerClient>::GetProxy(*it);
                    proxy().StartTask(task->GetTaskInfo());
                } catch (TException &tx) {
                    LOG4CPLUS_WARN(logger, "machine " << *it << " is down");
                    MachinePoolI::Instance()->Delete(*it);
                }
            }
        } 
    }
    return NULL;
}

void* RequestGenerator() {
    while(true) {
        float interval = RequestI::Instance()->GetInterval();
        usleep(1000000 * interval);
        TaskInfo info;
        //混合型应用 
        info.app = "mixed";
        //LOG4CPLUS_INFO(logger, "a new task interval:" << interval);
        TaskPtr task(new Task(info)); 
        //防止请求太快来不及处理
        TaskBufferI::Instance()->PushBack(task);
    }
    return NULL;
}
