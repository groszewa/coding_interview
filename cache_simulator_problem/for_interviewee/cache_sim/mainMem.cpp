//////////////////////////////////////
// Name         : mainMem.cpp
// Author       : Alex Groszewski
// Date         : 5/15/2020
// Description  : physical memory model for CPU, assume flat (no paging)
//////////////////////////////////////


#include "mainMem.h"


mainMem::mainMem() {
  printf("ERROR : Cannot create mainMemory of size 0 bytes!\n");
  exit(1);
}

mainMem::mainMem(unsigned int SIZE) {
  mem.resize(SIZE);
  printf("Created new mainMemory of size %d bytes!\n",mem.size());
}

mainMem::~mainMem() {
}

uint8_t mainMem::read(unsigned int addr) {
  assert(addr < mem.size());
  return mem[addr];
}

void mainMem::write(unsigned int addr, uint8_t data) {
  assert(addr < mem.size());
  mem[addr] = data;
}

void mainMem::initIncreasing() {
  for(auto i=0;i<getSize();i++) {
    write(i,i);
  }
}

void mainMem::dumpMem() {
  for(auto i=0;i<getSize();i++) {
    printf("mem[%3d] = 0x%x\n",i,read(i));
  }
}


//int main() {
//  printf("hello mainMem!\n");
//  mainMem mem_inst(256);
//  printf("Created mem of size %d\n", mem_inst.getSize());
//  mem_inst.write(0,1);
//  mem_inst.write(1,2);
//  printf("mem[0] = 0x%x\n",mem_inst.read(0));
//  printf("mem[1] = 0x%x\n",mem_inst.read(1));
//  printf("mem[3] = 0x%x\n",mem_inst.read(3));
//  //mem_inst.read(256); //error
//  //mem_inst.write(256,0xf); //error
//  mem_inst.initIncreasing();
//  //mem_inst.dumpMem();
//  return 0;
//}
