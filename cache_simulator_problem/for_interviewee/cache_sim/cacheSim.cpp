//////////////////////////////////////
// Name         : cacheSim.cpp
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache memory base class
//////////////////////////////////////

#include "cacheSim.h"


cacheSim::cacheSim(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY, unsigned int MAIN_MEM_SIZE) {
  transactionCount = 0;
  hitCount         = 0;
  mem     = new mainMem(MAIN_MEM_SIZE);
  //TODO - initialize cache
  //initialize memory
  mem->initIncreasing();
}

cacheSim::~cacheSim() {
  delete mem;
  //TODO - cleanup any pointers used in cache creation
}

uint8_t cacheSim::readTransaction(unsigned int addr, bool debug) {
  //TODO
}

void cacheSim::writeTransaction(unsigned int addr, uint8_t wrData, bool debug) {
  //TODO
}

double cacheSim::getHitRate() {
  //TODO
}




int main() {
  printf("Starting Cache Simulator!\n");
  unsigned int NUM_SETS      = 16;
  unsigned int NUM_WAYS      = 2;
  unsigned int NUM_BYTES     = 4;
  unsigned int MAIN_MEM_SIZE = 256;

  cacheSim sim(NUM_SETS,NUM_WAYS,NUM_BYTES,MAIN_MEM_SIZE);

  //TODO run test here

  //TODO print stats here

  return 0;
}
