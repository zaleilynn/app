#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <boost/thread.hpp>

#include <boost/thread.hpp>
#include "worker/executor.h"

using log4cplus::Logger;
using boost::thread;

static Logger logger = Logger::getInstance("worker");

void* ExecutorWorker(const ExecutorPtr& job) {
    job->Do();
    return NULL;
}

void* SchedulerProcessor() {
    while(true) {
        ExecutorPtr executor;
        ExecutorBufferI::Instance()->PopFront(&executor);
        //LOG4CPLUS_INFO(logger, "a new task");
        //一个任务一个线程
        // thread executor_worker_t(ExecutorWorker, executor);
        // 单进程处理吧
        executor->Do();
    }
    return NULL;
}
