#ifndef _APP_WORKER_EXECUTOR_H_
#define _APP_WORKER_EXECUTOR_H_

#include <boost/shared_ptr.hpp>
#include "include/proxy.h"
#include "include/block_queue.h"
#include "include/singleton.h"

using boost::shared_ptr;
using lynn::BlockQueue;

class Executor {
public:
    explicit Executor(const TaskInfo& info) : m_task_info(info) {}
    void Do();
private:
    TaskInfo m_task_info;
};

typedef shared_ptr<Executor> ExecutorPtr;
typedef Singleton< BlockQueue<ExecutorPtr> > ExecutorBufferI;
#endif
