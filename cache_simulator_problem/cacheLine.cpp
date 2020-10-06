//////////////////////////////////////
// Name         : cacheLine.cpp
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Cache line with LRU
//////////////////////////////////////

#include "cacheLine.h"

cacheLine::cacheLine() {
  printf("ERROR : Need to specify 2 arguments i.e. cacheLine(WAYS_PER_LINE,BYTES_PER_WAY)!\n");
  exit(1);
}

cacheLine::cacheLine(unsigned int DUMMY) {
  printf("ERROR : Need to specify 2 arguments i.e. cacheLine(WAYS_PER_LINE,BYTES_PER_WAY)! Only supplied one : %d\n",DUMMY);
  exit(1);
}


cacheLine::cacheLine(unsigned int WAYS_PER_LINE, unsigned int BYTES_PER_WAY) {
  bytes_per_way = BYTES_PER_WAY;
  ways_per_line = WAYS_PER_LINE;

  ways = new cacheWay *[WAYS_PER_LINE];
  for(int i=0;i<WAYS_PER_LINE;i++) {
    ways[i] = new cacheWay(BYTES_PER_WAY);
    ways[i]->clearValid();
    ways[i]->clearDirty();
    //lru.push_back(i); //fixme
  }
  lru = 0;
  //printf("Created cacheLine with %d cacheWays of size %d bytes each\n",ways_per_line,bytes_per_way);
}

cacheLine::~cacheLine() {
  for(int i=0;i<ways_per_line;i++) {
    delete ways[i];
  }
  //delete [] lru;
}

int cacheLine::isHit(unsigned int tag) {
  for(int i=0;i<ways_per_line;i++) {
    if(ways[i]->getTag()==tag) return i;
  }
  return -1;
}

unsigned int cacheLine::getTagWay(unsigned int way) {
  return ways[way]->getTag();
}

void cacheLine::writeLineByte(unsigned int way, unsigned int offset, uint8_t writeData, bool setDirty) {
  ways[way]->writeWay(offset,writeData);
  if(setDirty) {
    ways[way]->setDirty();
  }
  ways[way]->setValid();
  updateLRU(way);
}

uint8_t cacheLine::readLineByte(unsigned int way, unsigned int offset) {
  ways[way]->setValid();
  updateLRU(way);
  return ways[way]->readWay(offset);
}

void cacheLine::writeLineTag(unsigned int way,unsigned int tag) {
  ways[way]->setTag(tag);
  //resetLRU();
  updateLRU(way);
}

void cacheLine::dumpLine() {
    printf("dumpLine\n");
    for(int way=0;way<getWaysPerLine();way++) {
      printf("Way %d : tag=0x%x ",way,ways[way]->getTag());
      for(int byte=0;byte<getBytesPerWay();byte++) {
        printf(": byte[%d]=0x%x ",byte,readLineByte(way,byte));
      }
      printf("\n");
    }
}

//fixme
unsigned int cacheLine::getLRU() {
  //return lru.back();
  return lru;
}

bool cacheLine::getWayDirty(unsigned int way) {
  return ways[way]->getDirty();
}

bool cacheLine::getWayValid(unsigned int way) {
  return ways[way]->getValid();
}

//fixme
void cacheLine::printLRU() {
  //printf("LRU ");
  //for(std::deque<int>::iterator it = lru.begin();it!=lru.end();++it) {
  //  printf(": %d ", *it);
  //}
  //printf("\n");
}

//fixme
void cacheLine::updateLRU(unsigned int way) {
  //printf("updateLRU : Current LRU = %d\n",lru.back());
  //printf("updateLRU : Current MRU = %d\n",lru.front());
  //printf("updateLRU : New access  = %d\n",way);
  //if(way==lru.front()) {
  //  printf("updateLRU : Accessing MRU element, not doing anything\n");
  //  return;
  //}
  //int temp = lru[way];
  ////printf("updateLRU : Deleting element %d at %d\n",temp,way);
  ////lru.erase(lru.begin() + way);
  //for(std::deque<int>::iterator it = lru.begin();it!=lru.end();++it) {
  //  //if(*it==way) lru.erase(lru.begin() + (it-lru.begin()));
  //  if(*it==way) printf("it =  0x%x\n",it-lru.begin);
  //}
  //printLRU();
  //lru.push_front(temp);
  //printf("updateLRU : New LRU = %d\n",lru.back());
  //printf("updateLRU : New MRU = %d\n",lru.front());
  if(lru==way) lru ^= 1;
}

void cacheLine::resetLRU() {
  lru = 0;
}

void cacheLine::clearDirty(unsigned int way) {
  ways[way]->clearDirty();
}

//int main() {
//  printf("Hello, cacheLine!\n");
//  unsigned int NUM_WAYS  = 2;
//  unsigned int NUM_BYTES = 4;
//  cacheLine line(NUM_WAYS,NUM_BYTES);
//
//  //read_write_byte_test
//  for(int way=0;way<NUM_WAYS;way++) {
//    for(int byte=0;byte<NUM_BYTES;byte++) {
//      line.writeLineByte(way,byte,way+byte);
//      printf("cacheLine : read_write_byte_test : Writing way[%d][%d] = 0x%x\n",way,byte,way+byte);
//      printf("LRU = %d\n",line.getLRU());
//      //line.printLRU();
//    }
//  }
//  printf("\n");
//  for(int way=0;way<NUM_WAYS;way++) {
//    for(int byte=0;byte<NUM_BYTES;byte++) {
//      printf("cacheLine : read_write_byte_test : Reading way[%d][%d] = 0x%x\n",way,byte,line.readLineByte(way,byte));
//      printf("LRU = %d\n",line.getLRU());
//      //line.printLRU();
//    }
//  }
//
//  //tag check
//  printf("Writing tag 0x2 to way 0\n");
//  printf("LRU before = %d\n",line.getLRU());
//  line.writeLineTag(0,2);
//  printf("LRU after = %d\n",line.getLRU());
//  printf("Writing tag 0x3 to way 1\n");
//  printf("LRU before = %d\n",line.getLRU());
//  line.writeLineTag(1,3);
//  printf("LRU after = %d\n",line.getLRU());  
//  printf("Line contains tag 0 in way %d (-1 means not found)\n",line.isHit(0));
//  printf("Line contains tag 1 in way %d (-1 means not found)\n",line.isHit(1));
//  printf("Line contains tag 2 in way %d (-1 means not found)\n",line.isHit(2));
//  printf("Line contains tag 3 in way %d (-1 means not found)\n",line.isHit(3));
//  line.dumpLine();
//  
//  
//  
//  return 0;
//}
