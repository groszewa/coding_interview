//////////////////////////////////////
// Name         : cacheLine.h
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache line with LRU
//////////////////////////////////////
#ifndef CACHE_LINE_H
#define CACHE_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <deque>

#include "cacheWay.h"

class cacheLine {
 private:
  unsigned int ways_per_line;
  unsigned int bytes_per_way;
  cacheWay** ways;
  //std::deque<int> lru;
  int lru; //FIXME - make generic
 public:
  cacheLine();
  cacheLine(unsigned int DUMMY);
  cacheLine(unsigned int WAYS_PER_LINE, unsigned int BYTES_PER_WAY);
  ~cacheLine();
  int isHit(unsigned int tag);
  void writeLineByte(unsigned int way, unsigned int offset, uint8_t writeData, bool setDirty);
  uint8_t readLineByte(unsigned int way,unsigned int offset);
  void writeLineTag(unsigned int way, unsigned int tag);
  void dumpLine();
  unsigned int getTagWay(unsigned int way);
  ////getters and setters
  unsigned int getWaysPerLine() {return ways_per_line;}
  unsigned int getBytesPerWay() {return bytes_per_way;}
  bool         getWayDirty(unsigned int way);
  bool         getWayValid(unsigned int way);
  
  unsigned int getLRU();
  void printLRU();
  void updateLRU(unsigned int way);
  void resetLRU();
  void clearDirty(unsigned int way);
  
};

#endif //CACHE_LINE_H
