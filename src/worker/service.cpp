#include "include/proxy.h"

#include "worker/service.h"
#include "worker/executor.h"

void WorkerService::StartTask(const TaskInfo& task){
    ExecutorPtr ptr(new Executor(task));
    ExecutorBufferI::Instance()->PushBack(ptr);    
}
