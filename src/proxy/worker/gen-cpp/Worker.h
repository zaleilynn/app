/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Worker_H
#define Worker_H

#include <thrift/TDispatchProcessor.h>
#include "worker_types.h"



class WorkerIf {
 public:
  virtual ~WorkerIf() {}
  virtual void StartTask(const  ::TaskInfo& info) = 0;
};

class WorkerIfFactory {
 public:
  typedef WorkerIf Handler;

  virtual ~WorkerIfFactory() {}

  virtual WorkerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(WorkerIf* /* handler */) = 0;
};

class WorkerIfSingletonFactory : virtual public WorkerIfFactory {
 public:
  WorkerIfSingletonFactory(const boost::shared_ptr<WorkerIf>& iface) : iface_(iface) {}
  virtual ~WorkerIfSingletonFactory() {}

  virtual WorkerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(WorkerIf* /* handler */) {}

 protected:
  boost::shared_ptr<WorkerIf> iface_;
};

class WorkerNull : virtual public WorkerIf {
 public:
  virtual ~WorkerNull() {}
  void StartTask(const  ::TaskInfo& /* info */) {
    return;
  }
};

typedef struct _Worker_StartTask_args__isset {
  _Worker_StartTask_args__isset() : info(false) {}
  bool info;
} _Worker_StartTask_args__isset;

class Worker_StartTask_args {
 public:

  Worker_StartTask_args() {
  }

  virtual ~Worker_StartTask_args() throw() {}

   ::TaskInfo info;

  _Worker_StartTask_args__isset __isset;

  void __set_info(const  ::TaskInfo& val) {
    info = val;
  }

  bool operator == (const Worker_StartTask_args & rhs) const
  {
    if (!(info == rhs.info))
      return false;
    return true;
  }
  bool operator != (const Worker_StartTask_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Worker_StartTask_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Worker_StartTask_pargs {
 public:


  virtual ~Worker_StartTask_pargs() throw() {}

  const  ::TaskInfo* info;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Worker_StartTask_result {
 public:

  Worker_StartTask_result() {
  }

  virtual ~Worker_StartTask_result() throw() {}


  bool operator == (const Worker_StartTask_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Worker_StartTask_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Worker_StartTask_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Worker_StartTask_presult {
 public:


  virtual ~Worker_StartTask_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class WorkerClient : virtual public WorkerIf {
 public:
  WorkerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  WorkerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void StartTask(const  ::TaskInfo& info);
  void send_StartTask(const  ::TaskInfo& info);
  void recv_StartTask();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class WorkerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<WorkerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (WorkerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_StartTask(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  WorkerProcessor(boost::shared_ptr<WorkerIf> iface) :
    iface_(iface) {
    processMap_["StartTask"] = &WorkerProcessor::process_StartTask;
  }

  virtual ~WorkerProcessor() {}
};

class WorkerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  WorkerProcessorFactory(const ::boost::shared_ptr< WorkerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< WorkerIfFactory > handlerFactory_;
};

class WorkerMultiface : virtual public WorkerIf {
 public:
  WorkerMultiface(std::vector<boost::shared_ptr<WorkerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~WorkerMultiface() {}
 protected:
  std::vector<boost::shared_ptr<WorkerIf> > ifaces_;
  WorkerMultiface() {}
  void add(boost::shared_ptr<WorkerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void StartTask(const  ::TaskInfo& info) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->StartTask(info);
    }
    ifaces_[i]->StartTask(info);
  }

};



#endif
