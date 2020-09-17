//////////////////////////////////////
// Name         : mainMem.h
// Author       : Alex Groszewski
// Date         : 5/15/2020
// Description  : physical memory model for CPU, assume flat (no paging)
//////////////////////////////////////

#ifndef MAIN_MEM_H
#define MAIN_MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <vector>

class mainMem {
 private:
  unsigned int size;
  //uint8_t* mem;
  std::vector<uint8_t> mem;
 public:
  mainMem();
  mainMem(unsigned int SIZE);
  ~mainMem();
  uint8_t  read(unsigned int addr);
  void    write(unsigned int addr, uint8_t data);
  unsigned int getSize() {return mem.size();}
  void initIncreasing();
  void dumpMem();
};

#endif //MAIN_MEM_H
