#include "parse.hh"
#include "execute.hh"
#include "mmap.hh"

const std::size_t N = 1;
static constexpr char rom[N] = {0};

int main() {
    struct registers_t reg;
    constexpr auto program = parse<N>(rom);
    auto mmap = new mmap_t();
    execute<N, program>(mmap, reg);
}