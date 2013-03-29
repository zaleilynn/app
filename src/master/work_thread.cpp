#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <boost/thread.hpp>

#include "include/rpc.h"
#include "master/task.h"
#include "master/machine_pool.h"
#include "master/request.h"

using log4cplus::Logger;
using boost::thread;

static Logger logger = Logger::getInstance("master");

void* RequestGenerator() {
    while(true) {
        float interval = RequestI::Instance()->GetInterval();
        if(interval == 0) {
            LOG4CPLUS_INFO(logger, "request thread ends");
            break;
        }
//        LOG4CPLUS_INFO(logger, "interval " << interval);
        usleep(1000000 * interval);
        TaskInfo info;
        //混合型应用
        //其实在worker里面被忽略了 
        info.app = "mixed";
        //LOG4CPLUS_INFO(logger, "a new task interval:" << interval);
        TaskPtr task(new Task(info));
        //防止请求太快来不及处理
        TaskBufferI::Instance()->PushBack(task);
    }
    return NULL;
}


void* SchedulerProcessor() {
    bool flag = true;
    while(true) {
        vector<string> machines = MachinePoolI::Instance()->GetAllMachineEndpoint();
        if(machines.size() == 0) {
            //没有机器,不能一直查询
            //LOG4CPLUS_INFO(logger, "no machine right now...");
            sleep(1);
        } else { 
            if(flag) {
                LOG4CPLUS_INFO(logger, "begin to generate request");
                //有机器再启动线请求程,只能启动一次
                thread request_generator_t(RequestGenerator);
                //这个线程主要修改rate
                RequestI::Instance()->Start();
                flag = false;
            }
 
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
