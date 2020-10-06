//////////////////////////////////////
// Name         : cacheSim.h
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache Memory base class, 
//////////////////////////////////////
#ifndef CACHE_SIM_H
#define CACHE_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cacheMem.h"
#include "mainMem.h"

class cacheSim {
 private:
  cacheMem2Way *cache;
  mainMem      *mem;
  unsigned int transactionCount;
  unsigned int hitCount;
  
 public:
  cacheSim(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY, unsigned int MAIN_MEM_SIZE);
  ~cacheSim();
  
  void writeTransaction(unsigned int addr, uint8_t wrData, bool debug);
  uint8_t readTransaction(unsigned int addr, bool debug);
  double getHitRate();
  void dumpCache();
  void dumpMem();
  void readTest(bool debug);
  void writeTest(bool debug);
  
  ////getters and setters
  unsigned int getTransactionCount() {return transactionCount;}  
  unsigned int getHitCount()         {return hitCount;}
  void incrTransactionCount()        {transactionCount++;}
  void incrHitCount()                {hitCount++;}
  
};

#endif //CACHE_SIM_H
