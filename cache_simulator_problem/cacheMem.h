//////////////////////////////////////
// Name         : cacheMem.h
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache Memory base class 
//////////////////////////////////////
#ifndef CACHE_MEM_H
#define CACHE_MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cacheLine.h"

class cacheMem {
 private:
  unsigned int sets_per_cache;
  unsigned int ways_per_set;
  unsigned int bytes_per_way;
  cacheLine**  lines;
 public:
  cacheMem();
  cacheMem(unsigned int DUMMY);
  cacheMem(unsigned int DUMMY1, unsigned int DUMMY2);  
  cacheMem(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY);
  ~cacheMem();

  unsigned int getAddressTag(unsigned int addr);
  unsigned int getAddressIndex(unsigned int addr);
  unsigned int getAddressOffset(unsigned int addr);
  int getLineLRU(unsigned int index);
  bool getWayNeedsWB(unsigned int index, unsigned int way);
  bool getWayValid(unsigned int index,unsigned int way);
  int isTagHit(unsigned int tag, unsigned int index); //if tag is in cache, return which way otherwise return -1
  void writeTag(unsigned int tag,unsigned int index,unsigned int way);
  void writeCacheByte(unsigned int index, unsigned int way, unsigned int offset, uint8_t wrData, bool setDirty);
  uint8_t readCacheByte(unsigned int index, unsigned int way, unsigned int offset);
  void dumpCache();
  void initCache();
  
  
  ////getters and setters
  unsigned int getSetsPerCache() {return sets_per_cache;}  
  unsigned int getWaysPerSet()    {return ways_per_set;}
  unsigned int getBytesPerWay()    {return bytes_per_way;}
  unsigned int getTag(unsigned int index, unsigned int way);
  void clearDirty(unsigned int index, unsigned int way);
  
};

class cacheMem2Way : public cacheMem {
public:
  unsigned int getAddressOffset(unsigned int addr)    {return addr & 0x03;}
  unsigned int getAddressIndex(unsigned int addr)  {return (addr & 0x3c) >> 2;}
  unsigned int getAddressTag(unsigned int addr) {return (addr & 0xc0) >> 6;}
  cacheMem2Way(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY) : cacheMem(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY) {
    printf("Created %d byte cacheMem2Way : %d cacheLines per cacheMem : %d cacheWays per cacheLine : %d bytes per cacheWay\n",SETS_PER_CACHE*WAYS_PER_SET*BYTES_PER_WAY,SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY);    
  }
};

class cacheMem4Way : public cacheMem {
public:
  unsigned int getAddressOffset(unsigned int addr)    {return addr & 0x03;}
  unsigned int getAddressIndex(unsigned int addr)  {return (addr & 0x1c) >> 2;}
  unsigned int getAddressTag(unsigned int addr) {return (addr & 0xe0) >> 5;}
  cacheMem4Way(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY) : cacheMem(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY) {
    printf("Created %d byte cacheMem4Way : %d cacheLines per cacheMem : %d cacheWays per cacheLine : %d bytes per cacheWay\n",SETS_PER_CACHE*WAYS_PER_SET*BYTES_PER_WAY,SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY);    
  }
  
};


#endif //CACHE_MEM_H
