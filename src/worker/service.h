#ifndef _APP_SRC_WORKER_SERVICE_H_
#define _APP_SRC_WORKER_SERVICE_H_

#include <string>
#include "include/proxy.h"

using std::string;

class WorkerService : public WorkerIf {
public:
    void StartTask(const TaskInfo& task_info);
};

#endif


