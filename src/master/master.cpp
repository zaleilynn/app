#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <boost/thread.hpp>
#include <google/gflags.h>

#include "include/rpc.h"
#include "master/service.h"
#include "master/request.h"

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;
using std::auto_ptr;
using std::string;
using boost::thread;

DEFINE_int32(port, 10000, "master rpc port");
DEFINE_string(pattern, "/root/pattern1", "request pattern file");

extern void* SchedulerProcessor();

int main(int argc, char ** argv){
    //先不要配置文件了
    if(argc > 1) {
        google::ParseCommandLineFlags(&argc, &argv, true);
    }
    //初始化日志
    SharedObjectPtr<Appender> append(new ConsoleAppender());
    append->setName(LOG4CPLUS_TEXT("append for app master"));
    auto_ptr<Layout> layout(new PatternLayout(LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S} %p %l:%m %n")));
    append->setLayout(layout);
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("master"));
    logger.addAppender(append);
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
  
    if(RequestI::Instance()->Init(FLAGS_pattern) != 0) {
        LOG4CPLUS_ERROR(logger, "cannot init request sender");
        return 1;
    }

    thread scheduler_processor_t(SchedulerProcessor);

    Rpc<MasterService, MasterProcessor>::Listen(FLAGS_port);
    return 0;
}
