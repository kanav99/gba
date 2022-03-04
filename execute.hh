#include "defines.hh"
#include "registers.hh"
#include "instructions.hh"
#include "mmap.hh"

template <std::size_t N,  const program_t<N> program, std::size_t instr_ptr = 0>
inline constexpr void execute(mmap_t* mmap, registers_t &reg)
{
    if constexpr (instr_ptr < N)
    {
        constexpr auto instr = (op_t) program.code[instr_ptr];
        if constexpr (instr == op_t::nop) {
            // pass
        }
        else if constexpr (instr == op_t::ld_bc_d16) {
            reg.bc = * (uint16_t *) (program.code + instr_ptr + 1);
        }
        else if constexpr (instr == op_t::ld_mbc_a) {
            mmap->setByte(reg.bc, reg.a);
        }
        else if constexpr (instr == op_t::inc_bc) {
            reg.bc++;
        }
        else if constexpr (instr == op_t::inc_b) {
            reg.b++;
            // TODO: set appropriate flags
        }
        else if constexpr (instr == op_t::dec_b) {
            reg.b--;
            // TODO: set appropriate flags
        }
        else if constexpr (instr == op_t::ld_b_d8) {
            reg.b = program.code[instr_ptr + 1];
        }
        else if constexpr (instr == op_t::rlca) {
            reg.a = reg.a << 1 | reg.a >> 7;
            reg.flag_c = (reg.a >> 7);
        }
        else {
            std::cout << "Unknown instruction: " << (int) instr << std::endl;
        }
        execute<N, program, instr_ptr + 1>(mmap, reg);
    }
}
