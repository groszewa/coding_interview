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

#include "mainMem.h"

class cacheSim {
 private:
  //TODO - add pointer to your cache simulator here
  mainMem      *mem;
  unsigned int transactionCount;
  unsigned int hitCount;
  
 public:
  cacheSim(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY, unsigned int MAIN_MEM_SIZE);
  ~cacheSim();
  
  void writeTransaction(unsigned int addr, uint8_t wrData, bool debug);
  uint8_t readTransaction(unsigned int addr, bool debug);
  double getHitRate();

  //Feel free to add any functions you may need here
  
  ////getters and setters - any you may need can be added here
  
};

#endif //CACHE_SIM_H
