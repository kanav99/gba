#include "parse.hh"
#include <iostream>

const std::size_t N = 5;
static constexpr char rom[N] = {0, 1, 5, 0, 2};

int main() {
    struct registers_t reg;
    static constexpr auto M = numInstr(rom);
    static_assert(M == 3);
    std::cout << M << std::endl;
    constexpr auto program = parse<5, M>(rom);
    unsigned char* ram = new unsigned char[1000];
    execute<N, M, program>(ram, reg);
    std::cout << reg.bc << std::endl;
}