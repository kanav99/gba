#pragma once
#include <cstdint>
#include <iostream>
#include "instructions.hh"
#include "registers.hh"

struct instruction_t {
    op_t op;
    int size;
    char operands[2];
}; 

constexpr int instructionSizes[] = {
    1, 3, 1, 1, 1, 1, 2, 1,
};

#define FLAG_Z(x) (x & 0x80)
#define FLAG_N(x) (x & 0x40)
#define FLAG_H(x) (x & 0x20)
#define FLAG_C(x) (x & 0x10)

template <std::size_t N>
constexpr auto numInstr(const char (&str)[N]) {
    std::size_t count = 0;
    for (int i = 0; i < N;) {
        if (str[i] == 0xCB) {
            i = i + instructionSizes[256+str[i+1]];
        }
        else {
            i = i + instructionSizes[str[i]];
        }
        count++;
    }
    return count;
}


template <std::size_t N, std::size_t M>
struct program {
    instruction_t instructions[M];
};

template <std::size_t N, std::size_t M>
constexpr auto parse(const char (&str)[N]) {
    program<N, M> result = {{}};

    for (int i = 0, j = 0; i < N; j++)
    {
        if (str[i] == 0xCB) {
            result.instructions[j].op = (op_t) (256 + str[i+1]);
            const auto size = instructionSizes[256 + str[i+1]];
            if (size == 3) {
                result.instructions[j].operands[0] = str[i+2];
            }
            else if (size == 4) {
                result.instructions[j].operands[0] = str[i+2];
                result.instructions[j].operands[1] = str[i+3];
            }
            i += size;
        }
        else {
            result.instructions[j].op = (op_t) str[i];
            const auto size = instructionSizes[str[i]];
            if (size == 2) {
                result.instructions[j].operands[0] = str[i+1];
            }
            else if (size == 3) {
                result.instructions[j].operands[0] = str[i+1];
                result.instructions[j].operands[1] = str[i+2];
            }
            i += size;
        }
    }

    return result;
}

template <std::size_t N, std::size_t M, const program<N, M> Program, std::size_t instr_ptr = 0>
inline constexpr void execute(unsigned char* data_ptr, registers_t &reg)
{
    if constexpr (instr_ptr < M)
    {
        constexpr auto instr = Program.instructions[instr_ptr];
        if constexpr (instr.op == op_t::nop) {
            // pass
        }
        else if constexpr (instr.op == op_t::ld_bc_d16) {
            reg.bc = * (uint16_t *) (instr.operands);
        }
        else if constexpr (instr.op == op_t::ld_mbc_a) {
            data_ptr[reg.bc] = reg.a;
        }
        else if constexpr (instr.op == op_t::inc_bc) {
            reg.bc++;
        }
        else if constexpr (instr.op == op_t::inc_b) {
            reg.b++;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::dec_b) {
            reg.b--;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::ld_b_d8) {
            reg.b = instr.operands[0];
        }
        else if constexpr (instr.op == op_t::rlca) {
            reg.a = reg.a << 1 | reg.a >> 7;
            reg.f = (reg.a >> 7) << 4;
        }
        else {
            std::cout << "Unknown instruction: " << (int) instr.op << std::endl;
        }
        execute<N, M, Program, instr_ptr + 1>(data_ptr, reg);
    }
}
