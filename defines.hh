#pragma once

#include <cstdint>

#define KB 1024
typedef unsigned char byte;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef uint16_t address;

template <std::size_t N>
struct program_t {
    u8 code[N];
};
