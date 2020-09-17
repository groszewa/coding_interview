//////////////////////////////////////
// Name         : cacheWay.cpp
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Single set of a cache line
//////////////////////////////////////

#include "cacheWay.h"

cacheWay::cacheWay() {
  printf("ERROR : Cannot create a cacheWay with size 0 bytes!\n");
  exit(1);
}

cacheWay::cacheWay(unsigned int BYTES_PER_WAY) {
  bytes_per_way = BYTES_PER_WAY;
  data = new uint8_t[bytes_per_way];
  valid = false;
  dirty = false;
  //printf("Created cacheWay of size %d bytes\n",bytes_per_way);
}

cacheWay::~cacheWay() {
  //printf("Calling cacheWay destructor!\n");
  delete [] data;
  //printf("cacheWay data has been destroyed!\n");
}


uint8_t cacheWay::readWay(unsigned int offset) {
  if(offset>(getBytesPerWay()-1)) {
    printf("ERROR : cacheWay : read : offset 0x%x is out of range!\n",offset);
    exit(1);
  }
  valid = true;
  return data[offset];
}

void cacheWay::writeWay(unsigned int offset, uint8_t writeData) {
  if(offset>(getBytesPerWay()-1)) {
    printf("ERROR : cacheWay : write : offset 0x%x is out of range!\n",offset);
    exit(1);
  }
  //printf("cacheWay : writeWay : data[%d] = 0x%x\n",offset,writeData);
  valid = true;
  dirty = true;
  data[offset] = writeData;
  
}

void cacheWay::dumpWay() {
  printf("dumpWay ");
  for(int i=0;i<getBytesPerWay();i++) {
    printf(": [%d]=0x%x ");
  }
  printf("\n");
}

//int main() {
//  printf("Hello, cacheWay!\n");
//  cacheWay way(4);
//
//  for(int i=0;i<4;i++) {
//    printf("way[%d] = 0x%x\n",i,way.readWay(i));
//  }
//  
//  way.writeWay(0,0);
//  way.writeWay(1,1);
//  way.writeWay(2,2);
//  way.writeWay(3,3);
//  for(int i=0;i<4;i++) {
//    printf("way[%d] = 0x%d\n",i,way.readWay(i));
//  }
//  printf("way valid : %d\n",way.getValid());
//  way.setValid();
//  printf("way valid : %d\n",way.getValid());
//  way.clearValid();
//  printf("way valid : %d\n",way.getValid());
//
//  printf("way tag : 0x%x\n",way.getTag());
//  way.setTag(0x3);
//  printf("way tag : 0x%x\n",way.getTag());
//  way.setTag(0x1);
//  printf("way tag : 0x%x\n",way.getTag());
//  
//  
//  return 0;
//}
