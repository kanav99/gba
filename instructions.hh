#pragma once

enum class op_t {
    nop,
    ld_bc_d16,
    ld_mbc_a,
    inc_bc,
    inc_b,
    dec_b,
    ld_b_d8,
    rlca,
    ld_ma16_sp,
    add_hl_bc,
    ld_a_mbc,
    dec_bc,
    inc_c,
    dec_c,
    ld_c_d8,
    rrca,
};

constexpr std::size_t instruction_sizes[512] = {
    1, 3, 1, 1, 1, 1, 2, 1,
    3, 1, 1, 1, 1, 1, 2, 1,
};

constexpr int instruction_cycles[512] = {
   1, 3, 2, 2, 1, 1, 2, 1,
   5, 2, 2, 2, 1, 1, 2, 1,
};

struct instruction_t {
    op_t op;
    std::size_t size;
};
