#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <boost/thread.hpp>
#include <google/gflags.h>

#include "include/rpc.h"
#include "include/proxy.h"
#include "worker/service.h"
#include "worker/resource_manager.h"

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;
using std::auto_ptr;
using std::string;
using boost::thread;

DEFINE_int32(port, 9998, "worker rpc port");
DEFINE_string(master_endpoint, "127.0.0.1:9999", "master rpc endpoint");
DEFINE_string(interface, "br0", "interface for communicating");

extern void* SchedulerProcessor();

int main(int argc, char ** argv){
    //先不要配置文件了
    if(argc > 1) {
        google::ParseCommandLineFlags(&argc, &argv, true);
    }
    

    //初始化日志
    SharedObjectPtr<Appender> append(new ConsoleAppender());
    append->setName(LOG4CPLUS_TEXT("append for app worker"));
    auto_ptr<Layout> layout(new PatternLayout(LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S} %p %l:%m %n")));
    append->setLayout(layout);
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("worker"));
    logger.addAppender(append);
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
   
    if(ResourceManagerI::Instance()->Init() !=0 ) {
        LOG4CPLUS_ERROR(logger, "cannot initialize resource manager\n");
        return 1;
    }
 
    MachineInfo info;
    info.endpoint = ResourceManagerI::Instance()->GetMachineEndpoint();
    try {
        Proxy<MasterClient> proxy = Rpc<MasterClient, MasterClient>::GetProxy(FLAGS_master_endpoint);
        proxy().RegistMachine(info);
    } catch (TException &tx) {
        LOG4CPLUS_ERROR(logger, "regist machine error: " << tx.what());
        return 1;
    }

    thread scheduler_processor_t(SchedulerProcessor);
 
    Rpc<WorkerService, WorkerProcessor>::Listen(FLAGS_port);
    return 0;
}
