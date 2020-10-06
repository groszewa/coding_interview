//////////////////////////////////////
// Name         : cacheMem.cpp
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache memory base class
//////////////////////////////////////

#include "cacheMem.h"

cacheMem::cacheMem() {
  printf("ERROR : Need to specify 3 arguments i.e. cacheMem(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY)!\n");
  exit(1);
}

cacheMem::cacheMem(unsigned int DUMMY) {
  printf("ERROR : Need to specify 3 arguments i.e. cacheMem(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY)! Only supplied one : %d\n",DUMMY);
  exit(1);
}

cacheMem::cacheMem(unsigned int DUMMY1, unsigned int DUMMY2) {
  printf("ERROR : Need to specify 3 arguments i.e. cacheMem(SETS_PER_CACHE,WAYS_PER_SET,BYTES_PER_WAY)! Only supplied two : %d : %d\n",DUMMY1,DUMMY2);
  exit(1);
}

cacheMem::cacheMem(unsigned int SETS_PER_CACHE, unsigned int WAYS_PER_SET, unsigned int BYTES_PER_WAY) {
  sets_per_cache = SETS_PER_CACHE;
  bytes_per_way   = BYTES_PER_WAY;
  ways_per_set   = WAYS_PER_SET;

  lines = new cacheLine *[sets_per_cache];
  for(int i=0;i<sets_per_cache;i++) {
    lines[i] = new cacheLine(WAYS_PER_SET,BYTES_PER_WAY);
  }
  //printf("Created cacheMem : %d cacheLines per cacheMem : %d cacheWays per cacheLine : %d bytes per cacheWay\n",sets_per_cache,ways_per_line,bytes_per_way);
}

cacheMem::~cacheMem() {
  for(int i=0;i<sets_per_cache;i++) {
    delete lines[i];
  }
}

int cacheMem::isTagHit(unsigned int tag, unsigned int index) {
  return lines[index]->isHit(tag);
}

void cacheMem::writeTag(unsigned int tag, unsigned int index, unsigned int way) {
  lines[index]->writeLineTag(way,tag);
}


void cacheMem::writeCacheByte(unsigned int index, unsigned int way, unsigned int offset, uint8_t wrData, bool setDirty) {
  lines[index]->writeLineByte(way,offset,wrData,setDirty);
}

uint8_t cacheMem::readCacheByte(unsigned int index, unsigned int way, unsigned int offset) {
  return lines[index]->readLineByte(way,offset);
}

unsigned int cacheMem::getTag(unsigned int index, unsigned int way) {
  return lines[index]->getTagWay(way);
}

void cacheMem::dumpCache() {
  printf("dumpCache\n");
  for(int line=0;line<getSetsPerCache();line++) {
    printf("[Line %2d] ",line);
    for(int way=0;way<getWaysPerSet();way++) {
      printf(" [Way %d] tag=0x%02x ",way,lines[line]->getTagWay(way));
      for(int byte=0;byte<getBytesPerWay();byte++) {
        printf(": byte[%d]=0x%02x ",byte,lines[line]->readLineByte(way,byte));
      }
    }
    printf("\n");
  }
}

void cacheMem::initCache() {
  for(int line=0;line<getSetsPerCache();line++) {
    for(int way=0;way<getWaysPerSet();way++) {
      lines[line]->writeLineTag(way,line+way);
      for(int byte=0;byte<getBytesPerWay();byte++) {
        lines[line]->writeLineByte(way,byte,line+way+byte,false);
      }
    }
  }
}

int cacheMem::getLineLRU(unsigned int index) {
  return lines[index]->getLRU();
}

bool cacheMem::getWayNeedsWB(unsigned int index, unsigned int way) {
  return lines[index]->getWayDirty(way) && lines[index]->getWayValid(way);
}

bool cacheMem::getWayValid(unsigned int index, unsigned int way) {
  return lines[index]->getWayValid(way);
}

void cacheMem::clearDirty(unsigned int index, unsigned int way) {
  lines[index]->clearDirty(way);
}


//int main() {
//  printf("Hello, cacheMem!\n");
//  unsigned int NUM_LINES = 16;
//  unsigned int NUM_WAYS  = 2;
//  unsigned int NUM_BYTES = 4;
//  cacheMem2Way cache(NUM_LINES,NUM_WAYS,NUM_BYTES);
//  //cacheMem4Way cache(8,4,NUM_BYTES);
//  cache.initCache();
//  cache.dumpCache();
//  return 0;
//}
