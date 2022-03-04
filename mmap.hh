#pragma once
#include "defines.hh"
#define RAM_SIZE 0x10000

class mmap_t {
  u8 *ram;
public:
  mmap_t() {
    ram = new u8[RAM_SIZE];
  }

  u8 getByte(address addr) {
    return ram[addr];
  }

  void setByte(address addr, u8 value) {
    ram[addr] = value;
    // std::cout << "set ram[" << addr << "] = " << (int)value << std::endl;
  }

  u16 getWord(address addr) {
    return *(u16 *) (ram + addr);
  }

  void setWord(address addr, u16 value) {
    *(u16 *) (ram + addr) = value;
  }
};
