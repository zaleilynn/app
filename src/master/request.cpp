#include <math.h>
#include <fstream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "master/request.h"

using std::ifstream;
using std::tr1::bind;
using log4cplus::Logger;
using lynn::ReadLocker;
using lynn::WriteLocker;

static Logger logger = Logger::getInstance("master");

Request::~Request() {
    delete m_thread;
}

int Request::Init(const string& pattern){
    ifstream file(pattern.c_str());
    if(!file) {
        LOG4CPLUS_ERROR(logger, "cannot read pattern file");
        return 1;
    }
    int tmp;
    for(int i = 0; i <= 24; i++) {
        file >> tmp;
        m_pattern.push_back(tmp);
    }
    return 0;
}

//按照pattern修改当前的任务率
void Request::Entry(){
    for(vector<int>::iterator it =  m_pattern.begin(); it != m_pattern.end(); it++) {
        //按照pattern每一分钟修改一次速率
        sleep(60);
        SetRate(*it);
    }
}

void Request::SetRate(int rate) {
    WriteLocker locker(m_lock);
    m_cur_rate = rate;
}

int Request::GetRate() {
    ReadLocker locker(m_lock);   
    return m_cur_rate; 
}

float Request::GetInterval() {
   ReadLocker locker(m_lock);
   return GetPoissonValue(m_cur_rate); 
}

void Request::Start(){
    lynn::Thread::ThreadFunc func = bind(&Request::Entry, this);
    m_thread =  new lynn::Thread(func);
    m_thread->Start();
}

float Request::GetPoissonValue(float r) {
    float randpr = (float)rand()/RAND_MAX;
    return -(1/r) * (float)log(1-randpr);
}
