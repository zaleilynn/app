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
    file >> tmp;
    LOG4CPLUS_INFO(logger, "set rate to " << tmp);
    //设置第一个值
    m_cur_rate = tmp;

    while(!file.eof()) {
        file >> tmp;
        //防止重复读最后一个数据
        if(file.fail()) {
            break;
        }
        //除第一个值，其余的存起来
        m_pattern.push_back(tmp);
    }
    return 0;
}

//按照pattern修改当前的任务率
void Request::Entry(){
    for(vector<int>::iterator it =  m_pattern.begin(); it != m_pattern.end(); it++) {
        //按照pattern每一分钟修改一次速率
        sleep(1);
        LOG4CPLUS_INFO(logger, "set rate to " << *it); 
        SetRate(*it);
    }
    sleep(1);
    //模拟结束了
    SetRate(0);
    LOG4CPLUS_INFO(logger, "requset thread ends");
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
    if(r == 0) {
        return 0;
    }
    float randpr = (float)rand()/RAND_MAX;
    return -(1/r) * (float)log(1-randpr);
}
