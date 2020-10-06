//////////////////////////////////////
// Name         : cacheWay.h
// Author       : Alex Groszewski
// Date         : 5/16/2020
// Description  : Single set of a cache line
//////////////////////////////////////
#ifndef CACHE_WAY_H
#define CACHE_WAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class cacheWay {
 private:
  unsigned int bytes_per_way;
  unsigned int tag;
  uint8_t* data;
  bool     valid;
  bool     dirty;
 public:
  cacheWay();
  cacheWay(unsigned int BYTES_PER_WAY);
  ~cacheWay();
  uint8_t readWay(unsigned int offset);
  void    writeWay(unsigned int offset,uint8_t writeData);
  void    dumpWay();
  
  //getters and setters
  unsigned int getBytesPerWay(){return bytes_per_way;}
  void setValid() {valid = true;}
  void setDirty() {dirty = true;}
  void clearValid() {valid = false;}
  void clearDirty() {dirty = false;}
  bool getValid() {return valid;}
  bool getDirty() {return dirty;}
  unsigned int getTag() {return tag;}
  void setTag(unsigned int newTag) {tag = newTag;}
};

#endif //CACHE_WAY_H
