include "../master/master.thrift"

service Worker {
    void StartTask(1: master.TaskInfo info),
}
