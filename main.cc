#include "parse.hh"
#include "mmap.hh"
#include "registers.hh"

static constexpr u8 rom[] = {
#include "roms/dmg_rom.txt"
};

const std::size_t N = countof(rom);
constexpr auto program = parse<N>(rom);

mmap_t mmap;
registers_t reg;

#include "execute.hh"

// dont want no shit inside main disassembly
template <class T>
__attribute__((noinline)) void debug_print(T x) {
    std::cout << x << std::endl;
}

int main() {
    execute<N, 0>();
}