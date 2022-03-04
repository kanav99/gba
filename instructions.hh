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
};

constexpr int instructionSizes[] = {
    1, 3, 1, 1, 1, 1, 2, 1,
    3,
};

struct instruction_t {
    op_t op;
    std::size_t size;
};
