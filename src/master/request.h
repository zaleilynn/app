#ifndef _LYNN_MASTER_REQUEST_H_
#define _LYNN_MASTER_REQUEST_H_

#include <vector>
#include <string>
#include "include/rwlock.h"
#include "include/singleton.h"
#include "include/thread.h"

using lynn::RWLock;
using std::vector;
using std::string;

class Request {
public:
   ~Request();
   int Init(const string& pattern);
   void Entry();
   void Start();
   float GetInterval();
private:
   void SetRate(int rate);
   int GetRate();
   float GetPoissonValue(float r);
   RWLock m_lock;
   lynn::Thread* m_thread;
   int m_cur_rate;
   vector<int> m_pattern;
};

typedef Singleton<Request> RequestI;
#endif
