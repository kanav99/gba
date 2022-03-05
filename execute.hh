#include "defines.hh"
#include "registers.hh"
#include "instructions.hh"
#include "mmap.hh"

template <std::size_t N, address instr_ptr = 0>
constexpr instruction_t get_instr()
{
    if constexpr (program.code[instr_ptr] == 0xCB) {
        return instruction_t{static_cast<op_t>(program.code[instr_ptr + 1] + 256), instruction_sizes[program.code[instr_ptr + 1] + 256]};
    } else {
        return instruction_t{static_cast<op_t>(program.code[instr_ptr]), instruction_sizes[program.code[instr_ptr]]};
    }
}

template <std::size_t N,  address instr_ptr = 0, std::size_t end_ptr = N>
__attribute__((always_inline)) inline constexpr void execute();

template <std::size_t N, address func_ptr = 0>
__attribute__((noinline)) constexpr void func_call()
{
    try {
        execute<N, func_ptr>();
    }
    catch (int x) {
        return;
    }
}

template <std::size_t N,  address instr_ptr, std::size_t end_ptr>
__attribute__((always_inline)) inline constexpr void execute()
{
    // std::cout << end_ptr << std::endl;
    if constexpr (instr_ptr < end_ptr)
    {
        constexpr auto instr = get_instr<N, instr_ptr>();
        if constexpr (instr.op == op_t::nop) {
            // pass
        }
        else if constexpr (instr.op == op_t::ld_bc_d16) {
            reg.bc = *(u16 *) (program.code + instr_ptr + 1);
        }
        else if constexpr (instr.op == op_t::ld_mbc_a) {
            mmap.setByte(reg.bc, reg.a);
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
            flags.c = (reg.a & 1);
        }
        else if constexpr (instr.op == op_t::ld_ma16_sp) {
            mmap.setWord(*(u16 *)(program.code + instr_ptr + 1), sp);
        }
        else if constexpr (instr.op == op_t::add_hl_bc) {
            reg.hl += reg.bc;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::ld_a_mbc) {
            reg.a = mmap.getByte(reg.bc);
        }
        else if constexpr (instr.op == op_t::dec_bc) {
            reg.bc--;
        }
        else if constexpr (instr.op == op_t::inc_c) {
            reg.c++;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::dec_c) {
            reg.c--;
            // TODO: set appropriate flags
        }
        else if constexpr (instr.op == op_t::ld_c_d8) {
            reg.c = program.code[instr_ptr + 1];
        }
        else if constexpr (instr.op == op_t::rrca) {
            flags.c = (reg.a & 1);
            reg.a = reg.a >> 1 | reg.a << 7;
        }
        else if constexpr (instr.op == op_t::ld_de_d16) {
            reg.de = *(u16 *) (program.code + instr_ptr + 1);
        }
        else if constexpr (instr.op == op_t::ld_a_mde) {
            reg.a = mmap.getByte(reg.de);
        }
        else if constexpr (instr.op == op_t::jp_nz_s8) {
            constexpr address addr = instr_ptr + instr.size + static_cast<s16>(static_cast<s8>(program.code[instr_ptr + 1]));
            // risky code
            if constexpr (addr < instr_ptr) {
                // loop
                while(!flags.z) {
                    execute<N, addr, instr_ptr>();
                }
                return execute<N, instr_ptr + instr.size, end_ptr>();
            }
            else {
                // ifelse
                if (flags.z) {
                    execute<N, instr_ptr + instr.size, addr>();
                }
                return execute<N, addr>();
            }
        }
        else if constexpr (instr.op == op_t::ld_hl_d16) {
            reg.hl = *(u16 *)(program.code + instr_ptr + 1);
        }
        else if constexpr (instr.op == op_t::ld_sp_d16) {
            sp = *(u16 *)(program.code + instr_ptr + 1);
        }
        else if constexpr (instr.op == op_t::ld_mhldec_a) {
            mmap.setByte(reg.hl--, reg.a);
        }
        else if constexpr (instr.op == op_t::ld_a_d8) {
            reg.a = program.code[instr_ptr + 1];
        }
        else if constexpr (instr.op == op_t::hlt) {
            std::exit(0);
        }
        else if constexpr (instr.op == op_t::ld_mhl_a) {
            mmap.setByte(reg.hl, reg.a);
        }
        else if constexpr (instr.op == op_t::xor_a) {
            reg.a = 0;
            flags.c = 0;
            flags.h = 0;
            flags.n = 0;
            flags.z = 1;
        }
        else if constexpr (instr.op == op_t::ret) {
            throw 69;
        }
        else if constexpr (instr.op == op_t::call_a16) {
            constexpr address addr = program.code[instr_ptr + 1] | program.code[instr_ptr + 2] << 8;
            func_call<N, addr>();
        }
        else if constexpr (instr.op == op_t::ld_mc_a) {
            mmap.setByte(static_cast<address>(0xff00) | static_cast<address>(reg.c), reg.a);
        }
        else if constexpr (instr.op == op_t::ld_ma8_a) {
            mmap.setByte(static_cast<address>(0xff00) | static_cast<address>(program.code[instr_ptr + 1]), reg.a);
        }
        else if constexpr (instr.op == op_t::bit_7_h) {
            flags.z = !(reg.h & 0x80);
            flags.n = 1;
            flags.h = 1;
        }
        else if constexpr (instr.op == op_t::print_hi) {
            std::cout << "hi" << std::endl;
        }
        else {
            // std::cout << "Unknown instruction 0x" << std::hex << (u16)instr.op << " at address 0x" << instr_ptr  << std::endl;
            return;
        }
        return execute<N, instr_ptr + instr.size, end_ptr>();
    }
}
