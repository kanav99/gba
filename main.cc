#include "parse.hh"
#include "execute.hh"
#include "mmap.hh"

static constexpr u8 rom[] = {
#include "roms/dmg_rom.txt"
};

const std::size_t N = countof(rom);

// dont want no shit inside main disassembly
template <class T>
__attribute__((noinline)) void debug_print(T x) {
    std::cout << x << std::endl;
}

int main() {
    struct registers_t reg;
    constexpr auto program = parse<N>(rom);
    auto mmap = new mmap_t();
    execute<N, program>(mmap, reg);
}