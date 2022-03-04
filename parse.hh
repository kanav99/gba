#pragma once
#include <cstdint>
#include <iostream>
#include "defines.hh"

template <std::size_t N>
constexpr auto parse(const u8 (&str)[N]) {
    program_t<N> program = {{}};
    for(int i = 0; i < N; i++) {
        program.code[i] = str[i];
    }
    return program;
}
