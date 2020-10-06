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
  cache   = new cacheMem2Way(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY);
  //initialize memory
  mem->initIncreasing();
}

cacheSim::~cacheSim() {
  delete cache;
  delete mem;
}

uint8_t cacheSim::readTransaction(unsigned int addr, bool debug) {
  incrTransactionCount();
  unsigned int tag = cache->getAddressTag(addr);
  unsigned int index = cache->getAddressIndex(addr);
  unsigned int offset = cache->getAddressOffset(addr);
  int way = cache->isTagHit(tag,index);
  //printf("debug : tag = 0x%02x index = 0x%02x : way = 0x%02x : valid = %d\n",tag,index,way,cache->getWayValid(index,way));
  if(way>=0 && cache->getWayValid(index,way)) {
    printf("READ TXN  : Reading data from 0x%02x : HIT  : readData = 0x%02x\n",addr,cache->readCacheByte(index,way,offset));
    incrHitCount();
    return cache->readCacheByte(index,way,offset);
  } else {
    //need to fill cache line 
    unsigned int addrAligned = addr & 0xfc;
    //use LRU to find which way to write to
    unsigned int wayFromLRU = cache->getLineLRU(index);
    //if way is valid and dirty, need to write back to memory before flushing
    if(cache->getWayNeedsWB(index,wayFromLRU)) {
      unsigned int tagWB = cache->getTag(index,wayFromLRU);
      if(debug) {
        printf("READ TXN  : cache line 0x%02x way 0x%02x is dirty and needs to be written back to memory!\n",index,wayFromLRU);
      }
      for(unsigned int i = addrAligned;i<(cache->getBytesPerWay()+addrAligned);i++) {
        unsigned int indexWB = cache->getAddressIndex(i);
        unsigned int offsetWB = cache->getAddressOffset(i);
        unsigned int newAddr = (tagWB << 6) | (indexWB << 4) | (0x3 & i);
        
        uint8_t wbCacheData = cache->readCacheByte(indexWB,wayFromLRU,offsetWB);
        if(debug) {
          printf("READ TXN  : Writing back data 0x%x to mainMem[0x%02x]\n", wbCacheData,newAddr);
        }
        
        mem->write(newAddr,wbCacheData);
      }
    } else {
      if(debug) {
        printf("READ TXN  : cache index 0x%02x way 0x%02x does not need to be written back because it is not dirty\n",index,wayFromLRU);
      }
    }
    //fill the cache line
    if(debug) {
      printf("READ TXN  : Filling cache line starting at aligned address 0x%02x\n",addrAligned);
    }
    for(unsigned int i = addrAligned;i<(addrAligned+cache->getBytesPerWay());i++) {
      uint8_t writeData = mem->read(i);
      unsigned int tagNew = cache->getAddressTag(i);
      unsigned int indexNew = cache->getAddressIndex(i);
      unsigned int offsetNew = cache->getAddressOffset(i);
      cache->writeCacheByte(indexNew,wayFromLRU,offsetNew,writeData,false);
      cache->writeTag(tagNew,indexNew,wayFromLRU);
    }
    cache->clearDirty(index,wayFromLRU);
    if(debug) {
      printf("READ TXN  : Clearing dirty bit\n");
    }
    uint8_t readData = cache->readCacheByte(index,wayFromLRU,offset);
    printf("READ TXN  : Reading data from 0x%02x : MISS : readData = 0x%02x\n",addr,readData);
    
    return readData;

  }
}

void cacheSim::writeTransaction(unsigned int addr, uint8_t wrData, bool debug) {
  incrTransactionCount();
  unsigned int tag = cache->getAddressTag(addr);
  unsigned int index = cache->getAddressIndex(addr);
  unsigned int offset = cache->getAddressOffset(addr);
  int way = cache->isTagHit(tag,index);
  if(way>=0 && cache->getWayValid(index,way)) {
    printf("WRITE TXN : Writing data to   0x%02x : HIT  : writeData = 0x%02x\n",addr,wrData);
    cache->writeCacheByte(index,way,offset,wrData,true);
    incrHitCount();
  } else {
    //need to fill cache line 
    unsigned int addrAligned = addr & 0xfc;
    //use LRU to find which way to write to
    unsigned int wayFromLRU = cache->getLineLRU(index);
    //if way is valid and dirty, need to write back to memory before flushing
    if(cache->getWayNeedsWB(index,wayFromLRU)) {
      unsigned int tagWB = cache->getTag(index,wayFromLRU);
      if(debug) {
        printf("WRITE TXN : cache line 0x%02x way 0x%02x is dirty and needs to be written back to memory!\n",index,wayFromLRU);
      }
      
      for(unsigned int i = addrAligned;i<(cache->getBytesPerWay()+addrAligned);i++) {
        //unsigned int tagWB = cache->getAddressTag(i);
        unsigned int indexWB = cache->getAddressIndex(i);
        unsigned int offsetWB = cache->getAddressOffset(i);
        unsigned int newAddr = (tagWB << 6) | (indexWB << 4) | (0x3 & i);
        
        uint8_t wbCacheData = cache->readCacheByte(indexWB,wayFromLRU,offsetWB);
        if(debug) {
          printf("WRITE TXN : Writing back data 0x%x to mainMem[0x%02x]\n", wbCacheData,newAddr);
        }
        
        mem->write(newAddr,wbCacheData);
      }
      //printf("Clearing dirty bit on index 0x%02x way 0x%02x\n",index,wayFromLRU);
      //cache->clearDirty(index,wayFromLRU);
    } else {
      if(debug) {
        printf("WRITE TXN : cache index 0x%02x way 0x%02x does not need to be written back because it is not dirty\n",index,wayFromLRU);
      }
    }
    //fill the cache line
    if(debug) {
      printf("WRITE TXN : Filling cache line starting at aligned address 0x%02x\n",addrAligned);
    }
    for(unsigned int i = addrAligned;i<(addrAligned+cache->getBytesPerWay());i++) {
      uint8_t writeData = mem->read(i);
      unsigned int tagNew = cache->getAddressTag(i);
      unsigned int indexNew = cache->getAddressIndex(i);
      unsigned int offsetNew = cache->getAddressOffset(i);
      cache->writeCacheByte(indexNew,wayFromLRU,offsetNew,writeData,false);
      cache->writeTag(tagNew,indexNew,wayFromLRU);
    }
    cache->clearDirty(index,wayFromLRU);
    if(debug) {
      printf("WRITE TXN : Clearing dirty bit\n");
    }
    cache->writeCacheByte(index,wayFromLRU,offset,wrData,true);
    printf("WRITE TXN : Writing data to 0x%02x : MISS : writeData = 0x%02x\n",addr,wrData); //FIXME


  }
}

double cacheSim::getHitRate() {
  return 100*(double)getHitCount()/(double)getTransactionCount();
}

void cacheSim::dumpCache() {
  cache->dumpCache();
}

void cacheSim::dumpMem() {
  return mem->dumpMem();
}

void cacheSim::readTest(bool debug) {
  //dumpCache();
  readTransaction(0x0,debug); //miss
  //dumpCache();
  readTransaction(0x1,debug); //hit
  readTransaction(0x2,debug); //hit
  readTransaction(0x3,debug); //hit
  writeTransaction(0x0,0xf,debug); //hit
  readTransaction(0x4,debug); //miss
  readTransaction(0x5,debug); //hit
  readTransaction(0x6,debug); //hit
  readTransaction(0x7,debug); //hit
 
  //dumpCache();

  //write to way 1 in line 0 (way 0 already filled)
  readTransaction(0x40,debug); //miss, fill line 0 way 1
  //dumpMem();
  readTransaction(0x80,debug); //miss, evict line 0 way 0 back to memory, fill line 0 way 0
  readTransaction(0x83,debug); //hit
  readTransaction(0xc0,debug); //miss, fill line 0 way 1 but not dirty so dont WB
  readTransaction(0xc0,debug); //hit
  
  readTransaction(0xc1,debug); //hit
  
  dumpCache();
  //dumpMem();

}

void cacheSim::writeTest(bool debug) {
  writeTransaction(0x00,0xa,debug); //MISS, fill line 0 way 0, write 0xa to byte 0
  writeTransaction(0x02,0xb,debug); //HIT,  write 0xb to line 0, way 0, byte 2
  writeTransaction(0x40,0xc,debug); //MISS, fill line 0, way 1, write 0xc to byte 0
  writeTransaction(0x43,0xd,debug); //HIT,  write 0xd to line 0, way 1, byte 3 
  writeTransaction(0x81,0xe,debug); //MISS, need to flush line 0, way 0 which gets written back to memory, fill line 0, way 0, write 0xe to byte 1
  writeTransaction(0x80,0xf,debug); //HIT,  write 0xf to line 0, way 0, byte 0
  dumpCache();
  //dumpMem();
}


int main() {
  printf("Starting Cache Simulator!\n");
  unsigned int NUM_LINES     = 16;
  unsigned int NUM_WAYS      = 2;
  unsigned int NUM_BYTES     = 4;
  unsigned int MAIN_MEM_SIZE = 256;

  cacheSim sim(NUM_LINES,NUM_WAYS,NUM_BYTES,MAIN_MEM_SIZE);

  bool debug = false;

  //sim.readTest(debug);
  sim.writeTest(debug);

  printf("Statistics : Total Transactions = %3d : Total Cache Hits = %3d : Hit Rate = %f\%\n",sim.getTransactionCount(),sim.getHitCount(),sim.getHitRate());
  return 0;
}
