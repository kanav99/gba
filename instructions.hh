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
};

constexpr int instructionSizes[] = {
    1, 3, 1, 1, 1, 1, 2, 1,
};
