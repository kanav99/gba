#include "defines.hh"
#include "registers.hh"
#include "instructions.hh"
#include "mmap.hh"

template <std::size_t N,  const program_t<N> program, std::size_t instr_ptr = 0>
constexpr instruction_t get_instr()
{
    if constexpr (program.code[instr_ptr] == 0xCB) {
        return instruction_t{static_cast<op_t>(program.code[instr_ptr + 1] + 256), instructionSizes[program.code[instr_ptr + 1] + 256]};
    } else {
        return instruction_t{static_cast<op_t>(program.code[instr_ptr]), instructionSizes[program.code[instr_ptr]]};
    }
}

template <std::size_t N,  const program_t<N> program, std::size_t instr_ptr = 0>
inline constexpr void execute(mmap_t* mmap, registers_t &reg)
{
    if constexpr (instr_ptr < N)
    {
        constexpr auto instr = get_instr<N, program, instr_ptr>();
        if constexpr (instr.op == op_t::nop) {
            // pass
        }
        else if constexpr (instr.op == op_t::ld_bc_d16) {
            reg.bc = *(u16 *) (program.code + instr_ptr + 1);
        }
        else if constexpr (instr.op == op_t::ld_mbc_a) {
            mmap->setByte(reg.bc, reg.a);
        }
        else if constexpr (instr.op == op_t::inc_bc) {
            reg.bc++;
        }
        else if constexpr (instr.op == op_t::inc_b) {
            reg.b++;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::dec_b) {
            reg.b--;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::ld_b_d8) {
            reg.b = program.code[instr_ptr + 1];
        }
        else if constexpr (instr.op == op_t::rlca) {
            reg.a = reg.a << 1 | reg.a >> 7;
            reg.flag_c = (reg.a >> 7);
        }
        else if constexpr (instr.op == op_t::ld_ma16_sp) {
            mmap->setWord(*(u16 *)(program.code + instr_ptr + 1), reg.sp);
        }
        else {
            std::cout << "Unknown instruction: " << (int) instr << std::endl;
        }
        execute<N, program, instr_ptr + instr.size>(mmap, reg);
    }
}
