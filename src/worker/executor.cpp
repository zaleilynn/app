#include <time.h>

#include "worker/executor.h"

void Executor::Do(){
   //计算/内存密集型
   long sum = 0;
   for(int i = 0; i < 2000; i++) {
       for(int j = 0; j < 2500; j++) {
           sum += i*j;
      }
   }
}
