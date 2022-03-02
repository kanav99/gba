#pragma once
#include <cstdint>
#include "instructions.hh"

const int num_instructions = 2;
struct instruction_t {
    op_t op;
    int size;
    void (*func)(unsigned char *);
}; 

constexpr instruction_t instructions[num_instructions] = {
    {op_t::nop, 1, instruction_00_nop},
    {op_t::ld, 3, instruction_01_ld}
};

template <std::size_t N>
constexpr auto numInstr(const char (&str)[N]) {
    std::size_t count = 0;
    for (int i = 0; i < N;) {
        i = i + instructions[str[i]].size;
        count++;
    }
    return count;
}


template <std::size_t N, std::size_t M>
struct program {
    op_t instructions[M];
};

template <std::size_t N, std::size_t M>
constexpr auto parse(const char (&str)[N]) {
    program<N, M> result = {{}};

    for (int i = 0, j = 0; i < N; j++)
    {
        result.instructions[j] = instructions[str[i]].op;
        i += instructions[str[i]].size;
    }

    return result;
}

template <std::size_t N, std::size_t M, const program<N, M> Program, std::size_t instr_ptr = 0>
inline constexpr void execute(unsigned char* data_ptr)
{
    if constexpr (instr_ptr < M)
    {
        constexpr auto instr = Program.instructions[instr_ptr];
        instructions[static_cast<int>(instr)].func(data_ptr);
        execute<N, M, Program, instr_ptr + 1>(data_ptr);
    }
}
