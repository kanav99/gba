#pragma once

enum class op_t {
    nop = 0,
    ld_bc_d16 = 1,
    ld_mbc_a = 2,
    inc_bc = 3,
    inc_b = 4,
    dec_b = 5,
    ld_b_d8 = 6,
    rlca = 7,
    ld_ma16_sp = 8,
    add_hl_bc = 9,
    ld_a_mbc = 10,
    dec_bc = 11,
    inc_c = 12,
    dec_c = 13,
    ld_c_d8 = 14,
    rrca = 15,
    ld_sp_d16 = 49,
};

constexpr std::size_t instruction_sizes[512] = {
    1, 3, 1, 1, 1, 1, 2, 1,
    3, 1, 1, 1, 1, 1, 2, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 3,
};

constexpr int instruction_cycles[512] = {
   1, 3, 2, 2, 1, 1, 2, 1,
   5, 2, 2, 2, 1, 1, 2, 1,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 3,
};

struct instruction_t {
    op_t op;
    std::size_t size;
};
