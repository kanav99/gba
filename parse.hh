#pragma once
#include <cstdint>
#include <iostream>
#include "defines.hh"

template <std::size_t N>
constexpr auto parse(const char (&str)[N]) {
    program_t<N> program = {{}};
    for(int i = 0; i < N; i++) {
        program.code[i] = str[i];
    }
    return program;
}
