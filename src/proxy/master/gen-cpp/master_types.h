/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef master_TYPES_H
#define master_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>





typedef struct _MachineInfo__isset {
  _MachineInfo__isset() : endpoint(false) {}
  bool endpoint;
} _MachineInfo__isset;

class MachineInfo {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  MachineInfo() : endpoint() {
  }

  virtual ~MachineInfo() throw() {}

  std::string endpoint;

  _MachineInfo__isset __isset;

  void __set_endpoint(const std::string& val) {
    endpoint = val;
  }

  bool operator == (const MachineInfo & rhs) const
  {
    if (!(endpoint == rhs.endpoint))
      return false;
    return true;
  }
  bool operator != (const MachineInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MachineInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(MachineInfo &a, MachineInfo &b);

typedef struct _TaskInfo__isset {
  _TaskInfo__isset() : app(false) {}
  bool app;
} _TaskInfo__isset;

class TaskInfo {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  TaskInfo() : app() {
  }

  virtual ~TaskInfo() throw() {}

  std::string app;

  _TaskInfo__isset __isset;

  void __set_app(const std::string& val) {
    app = val;
  }

  bool operator == (const TaskInfo & rhs) const
  {
    if (!(app == rhs.app))
      return false;
    return true;
  }
  bool operator != (const TaskInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TaskInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TaskInfo &a, TaskInfo &b);



#endif
