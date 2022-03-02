#include "registers.hh"
#include <cstdint>

registers_t registers;

void set_memory(uint16_t address, unsigned char* data, int size) {
    // TODO
}

void instruction_00_nop(unsigned char *instruction) {
    registers.pc++;
}

void instruction_01_ld(unsigned char *instruction) {
    registers.bc = * (uint16_t *) (instruction + 1);
    registers.pc += 3;
}
