#include "parse.hh"
#include <iostream>

const std::size_t N = 5;
static constexpr char rom[N] = {0, 1, 0, 0, 0};

int main() {
    static constexpr auto M = numInstr(rom);
    static_assert(M == 3);
    std::cout << M << std::endl;
    constexpr auto program = parse<5, M>(rom);
    unsigned char* ram = new unsigned char[1000];
    execute<N, M, program>(ram);
}