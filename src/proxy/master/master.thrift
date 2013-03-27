struct MachineInfo {
    1: string endpoint,
}

struct TaskInfo {
    1: string app,
}

service Master {
    void RegistMachine(1: MachineInfo info),
}
