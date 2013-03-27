#ifndef _APP_MASTER_TASK_H_
#define _APP_MASTER_TASK_H_

#include <boost/shared_ptr.hpp>

#include "include/block_queue.h"
#include "include/singleton.h"
#include "include/proxy.h"

using boost::shared_ptr;
using lynn::BlockQueue;

class Task {
public:
    Task(const TaskInfo& task_info) : m_task_info(task_info) {};
    TaskInfo GetTaskInfo() {
        return m_task_info;
    }
private:
    TaskInfo m_task_info;
};

typedef shared_ptr<Task> TaskPtr;
typedef Singleton< BlockQueue<TaskPtr> > TaskBufferI;

#endif
