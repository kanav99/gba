#pragma once

#include <cstdint>

template<std::size_t N, class T>
constexpr std::size_t countof(T(&)[N]) { return N; }

#define KB 1024
typedef unsigned char byte;
typedef uint32_t u32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

typedef uint16_t address;

template <std::size_t N>
struct program_t {
    u8 code[N];
};
