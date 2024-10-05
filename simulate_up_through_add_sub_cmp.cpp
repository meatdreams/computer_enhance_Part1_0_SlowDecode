// This is all headers and main.cpp globbed together. Enjoy. Or not.

#ifndef MR_HEADER
#define MR_HEADER

#include <cstdint>
#include <iostream>
#include <bitset>
#include <string.h>

#define array_size(mr_array) (sizeof(mr_array) / sizeof(mr_array[0]))

typedef uint8_t u8;
typedef uint16_t u16;

enum byte_2_through_6_contents {
    MOD_REG_RM,
    DATA_8,
    DATA_16,
    DATA_LO,
    DATA_HI,
    DISP_LO,
    DISP_HI,
    DATA_SX,
    MOD_GGG_RM,
    ADDR_LO,
    ADDR_HI,
    ADDR_8,
};

enum the_MOD_GGG_RM_cases {
    MOD_000_RM,
    MOD_101_RM,
};

enum instruction_categories {
    ADD_to_from_register_memory = 0,
    ADD_immediate_register_memory = 1,
    ADD_immediate_to_accumulator = 2,
    SUB_to_from_register_memory = 3,
    SUB_immediate_register_memory = 4,
    SUB_immediate_to_accumulator = 5,
    CMP_to_from_register_memory = 6,
    CMP_immediate_register_memory = 7,
    CMP_immediate_with_accumulator = 8,
    MOV_to_from_register_memory = 9,
    MOV_immediate_register_memory = 10,
    MOV_immediate_to_register = 11,
    MOV_memory_to_accumulator = 12,
    MOV_accumulator_to_memory = 13,
    MOV_register_memory_to_seg_reg = 14,
    MOV_seg_reg_to_register_memory = 15,
    GGG_TBD_MIDDLE_THREE_WOWEE = 16,
    JUMP = 17,
    LOOP_JCXZ = 18,
};

enum instruction_format_chunks {
    MOV,
    ADD,
    SUB,
    CMP,
    REG8_MEM8,
    REG8,
    MEM8,
    REG16_MEM16,
    REG16,
    MEM16,
    IMMED8,
    IMMED16,
    AL,
    CL,
    DL,
    BL,
    AH,
    CH,
    DH,
    BH,
    AX,
    CX,
    DX,
    BX,
    SP,
    BP,
    SI,
    DI,
    GGG,
};

enum d_ { NO_D, YES_D, NA_D };

enum w_ { NO_W = 0, YES_W = 1, NA_W = 0 };

enum s_ { NO_S, YES_S, NA_S };

struct byte_whisperer {
    instruction_categories mr_category;
    byte_2_through_6_contents second_byte;
    byte_2_through_6_contents bytes_3_through_6[4];
    instruction_format_chunks instruction_format[3];
    d_ d_flag;
    w_ w_flag;
    s_ s_flag;
};

inline void *set_up_mr_whisperer(byte_whisperer *mr_whisperer) {
    mr_whisperer[0b00000000] = {ADD_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {ADD, REG8_MEM8, REG8},
                                NO_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00000001] = {ADD_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {ADD, REG16_MEM16, REG16},
                                NO_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00000010] = {ADD_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {ADD, REG8, REG8_MEM8},
                                YES_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00000011] = {ADD_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {ADD, REG16, REG16_MEM16},
                                YES_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00000100] = {ADD_immediate_to_accumulator,
                                DATA_8,
                                {/*here to take up space*/},
                                {ADD, AL, IMMED8},
                                NA_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00000101] = {ADD_immediate_to_accumulator,
                                DATA_LO,
                                /*here to take up space*/
                                {DATA_HI},
                                {ADD, AX, IMMED16},
                                NA_D,
                                YES_W,
                                NA_S};

    mr_whisperer[0b00101000] = {SUB_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {SUB, REG8_MEM8, REG8},
                                NO_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00101001] = {SUB_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {SUB, REG16_MEM16, REG16},
                                NO_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00101010] = {SUB_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {SUB, REG8, REG8_MEM8},
                                YES_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00101011] = {SUB_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {SUB, REG16, REG16_MEM16},
                                YES_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00101100] = {SUB_immediate_to_accumulator,
                                DATA_8,
                                {/*here to take up space*/},
                                {SUB, AL, IMMED8},
                                NA_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00101101] = {SUB_immediate_to_accumulator,
                                DATA_LO,
                                /*here to take up space*/
                                {DATA_HI},
                                {SUB, AX, IMMED16},
                                NA_D,
                                YES_W,
                                NA_S};


    mr_whisperer[0b00111000] = {CMP_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {CMP, REG8_MEM8, REG8},
                                NO_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00111001] = {CMP_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {CMP, REG16_MEM16, REG16},
                                NO_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00111010] = {CMP_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {CMP, REG8, REG8_MEM8},
                                YES_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00111011] = {CMP_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {CMP, REG16, REG16_MEM16},
                                YES_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b00111100] = {CMP_immediate_with_accumulator,
                                DATA_8,
                                {/*here to take up space*/},
                                {CMP, AL, IMMED8},
                                NA_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b00111101] = {CMP_immediate_with_accumulator,
                                DATA_LO,
                                /*here to take up space*/
                                {DATA_HI},
                                {CMP, AX, IMMED16},
                                NA_D,
                                YES_W,
                                NA_S};

    printf("dicks\n");
    u8 i = 0b01110000;
    u8 j = 0b10000000;
    u8 k = 0b00000001;
    for (; i < j; i += k) {
        mr_whisperer[i] = {JUMP};
    }

    i = 0b11100000;
    j = 0b11100100;
    for (; i < j; i += k) {
        mr_whisperer[i] = {LOOP_JCXZ};
    }

    // s = 0, w = 0
    mr_whisperer[0b10000000] = {GGG_TBD_MIDDLE_THREE_WOWEE,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_8},
                                {GGG, REG8_MEM8, IMMED8},
                                NA_D,
                                NO_W,
                                NO_S};
    // s = 0, w = 1
    mr_whisperer[0b10000001] = {GGG_TBD_MIDDLE_THREE_WOWEE,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_LO, DATA_HI},
                                {GGG, REG16_MEM16, IMMED16},
                                NA_D,
                                YES_W,
                                NO_S};
    // s = 1, w = 0
    mr_whisperer[0b10000010] = {GGG_TBD_MIDDLE_THREE_WOWEE,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_8},
                                {GGG, REG8_MEM8, IMMED8},
                                NA_D,
                                NO_W,
                                YES_S};
    // s = 1, w = 1
    mr_whisperer[0b10000011] = {GGG_TBD_MIDDLE_THREE_WOWEE,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_SX},
                                {GGG, REG8_MEM8, IMMED8},
                                NA_D,
                                YES_W,
                                YES_S};


    mr_whisperer[0b10001000] = {MOV_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {MOV, REG8_MEM8, REG8},
                                NO_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b10001001] = {MOV_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {MOV, REG16_MEM16, REG16},
                                NO_D,
                                YES_W,
                                NA_S};
    mr_whisperer[0b10001010] = {MOV_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {MOV, REG8, REG8_MEM8},
                                YES_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b10001011] = {MOV_to_from_register_memory,
                                MOD_REG_RM,
                                {DISP_LO, DISP_HI},
                                {MOV, REG16, REG16_MEM16},
                                YES_D,
                                YES_W,
                                NA_S};
    // I'm not going to worry about the SEGREG MOV stuff right now
    mr_whisperer[0b10100000] = {
        MOV_memory_to_accumulator, ADDR_LO, {ADDR_HI}, {MOV, AL, MEM8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10100001] = {
        MOV_memory_to_accumulator, ADDR_LO, {ADDR_HI}, {MOV, AX, MEM16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10100010] = {
        MOV_accumulator_to_memory, ADDR_LO, {ADDR_HI}, {MOV, MEM8, AL}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10100011] = {
        MOV_accumulator_to_memory, ADDR_LO, {ADDR_HI}, {MOV, MEM16, AX}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10110000] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, AL, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110001] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, CL, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110010] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, DL, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110011] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, BL, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110100] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, AH, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110101] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, CH, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110110] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, DH, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10110111] = {
        MOV_immediate_to_register, DATA_8, {}, {MOV, BH, IMMED8}, NA_D, NO_W, NA_S};
    mr_whisperer[0b10111000] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, AX, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111001] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, CX, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111010] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, DX, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111011] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, BX, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111100] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, SP, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111101] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, BP, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111110] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, SI, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b10111111] = {
        MOV_immediate_to_register, DATA_LO, {DATA_HI}, {MOV, DI, IMMED16}, NA_D, YES_W, NA_S};
    mr_whisperer[0b11000110] = {MOV_immediate_register_memory,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_8},
                                {REG8_MEM8, IMMED8},
                                NA_D,
                                NO_W,
                                NA_S};
    mr_whisperer[0b11000111] = {MOV_immediate_register_memory,
                                MOD_GGG_RM,
                                {DISP_LO, DISP_HI, DATA_LO, DATA_HI},
                                {REG16_MEM16, IMMED16},
                                NA_D,
                                YES_W,
                                NA_S};
    return mr_whisperer;
}

#endif // MR_HEADER

#include "mr_header.h"

inline void REG_figure_outer(w_ w_flag, u8 REG_bits) {
    // printf("in REG figure outer\n");
    char reggies[][2][3] = {{"al", "ax"}, {"cl", "cx"}, {"dl", "dx"}, {"bl", "bx"},
                            {"ah", "sp"}, {"ch", "bp"}, {"dh", "si"}, {"bh", "di"}};
    printf("%s", reggies[REG_bits][w_flag]);
}

inline void effective_address_figure_outer(u8 MOD_bits, u8 RM_bits, u8 *mr_index) {
    // printf("in effective address figure outer\n");
    char effective_address[][8] = {"bx + si", "bx + di", "bp + si", "bp + di",
                                   "si",      "di",      "bp",      "bx"};
    switch (MOD_bits) {
    case 0b00000000:
        // printf("MOD = 00\n");
        printf("[%s]", effective_address[RM_bits]);
        break;
    case 0b00000001:
        // printf("MOD = 01\n");
        printf("[%s + %d]", effective_address[RM_bits], *mr_index);
        break;
    case 0b00000010: {
        // printf("MOD = 10\n");
        int big_ol_word = *mr_index + (int)(*(mr_index + 1) << 8);
        printf("[%s + %d]", effective_address[RM_bits], big_ol_word);
    } break;
    default:
        printf("\nfell through effective address switch\n");
        break;
    }
    // printf("\nreturning from effective address figure outer\n");
}

inline u8 *RM_to_from_REG_figure_outer_CASE1(const byte_whisperer *mr_whisperer, u8 *mr_index) {
    // printf("in RM to from REG figure outer CASE1\n");
    u8 mod_reg_rm_bit = *(mr_index + 1);
    u8 MOD_bits = mod_reg_rm_bit >> 6;
    u8 REG_bits = (mod_reg_rm_bit & 0b00111000) >> 3;
    u8 RM_bits = (mod_reg_rm_bit & 0b00000111);
    w_ w_flag = mr_whisperer[*mr_index].w_flag;

    // 10000011 11000110
    if (MOD_bits == 0b00000011) {
        // printf("MOD = 11\n");
        switch (mr_whisperer[*mr_index].instruction_format[1]) {
        case REG8:
        case REG16: {
            // printf("REG first\n");
            REG_figure_outer(w_flag, REG_bits);
            printf(", ");
            REG_figure_outer(w_flag, RM_bits);
            printf("\n");
        }; break;
        case REG8_MEM8:
        case REG16_MEM16: {
            // printf("RM first\n");
            REG_figure_outer(w_flag, RM_bits);
            printf(", ");
            REG_figure_outer(w_flag, REG_bits);
            printf("\n");
        }; break;
        default:
            printf("fell through MOD == 11 switch\n");
            break;
        }
        // printf("mr_index += 2\n");
        // printf("returning from CASE 1 -> MOD 11 path\n");
        return mr_index += 2;
    } else {
        // printf("MOD != 11\n");
        switch (mr_whisperer[*mr_index].instruction_format[1]) {
        case REG8:
        case REG16: {
            // printf("REG first\n");
            REG_figure_outer(w_flag, REG_bits);
            printf(", ");
            effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
            printf("\n");
        }; break;
        case REG8_MEM8:
        case REG16_MEM16: {
            // printf("RM first\n");
            effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
            printf(", ");
            REG_figure_outer(w_flag, REG_bits);
            printf("\n");
        }; break;
        default:
            printf("\nfell through 2nd half of to_from reg function\n");
            break;
        }
        switch (MOD_bits) {
        case 0b00000010: {
            mr_index += 4;
            // printf("mr_index += 4\n");
        }; break;
        case 0b00000001: {
            mr_index += 3;
            // printf("mr_index += 3\n");
        }; break;
        case 0b00000000: {
            mr_index += 2;
            // printf("mr_index += 2\n");
        }; break;
        default:
            printf("\nfell through switch at end of to from reg function\n");
            break;
        }
        // printf("\nreturning from to_from figure outer\n");
        return mr_index;
    }
}

inline u8 *immediate_to_with_from_REG_CASE3(const byte_whisperer *mr_whisperer, u8 *mr_index) {
    // printf("in immediate to with from REG CASE3\n");
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    u8 REG_bits;
    switch (mr_whisperer[*mr_index].instruction_format[0]) {
    case MOV: {
        REG_bits = (*mr_index) & 0b00000111;
    }; break;
    case ADD:
    case SUB:
    case CMP: {
        REG_bits = 0b00000000;
    }; break;
    default: {
        printf("fell through MOV_immediate_to_REG_CASE3 switch\n");
    }; break;
    }
    REG_figure_outer(w_flag, REG_bits);
    // printf("\nw_flag: %d\n", w_flag);
    // printf("\nbyte 1: %d\n", *(mr_index));
    // printf("\nbyte 2: %d\n", *(mr_index + 1));
    // printf("\nbyte 3: %d\n", *(mr_index + 2));
    int mr_data = *(mr_index + 1) + (int)(w_flag * (*(mr_index + 2) << 8));
    printf(", %d\n", mr_data);
    // printf("\nthis one moved mr_index %d bits forward\n", (mr_index + 2 + w_flag) - mr_index);
    // printf("\nreturning from mov immediate figure outer\n");
    // printf("w_flag = %d\n", w_flag);
    return mr_index += (2 + w_flag);
}

inline u8 *immediate_to_with_from_RM_CASE2(const byte_whisperer *mr_whisperer, u8 *mr_index) {
    // printf("in immediate to with from RM CASE2\n");
    s_ s_flag = mr_whisperer[*mr_index].s_flag;
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    u8 MOD_GGG_RM_bit = *(mr_index + 1);
    u8 MOD_bits = MOD_GGG_RM_bit >> 6;
    u8 GGG_bits = (MOD_GGG_RM_bit & 0b00111000) >> 3;
    u8 RM_bits = (MOD_GGG_RM_bit & 0b00000111);

    if (mr_whisperer[*mr_index].mr_category == MOV_immediate_register_memory) {
        printf("mov ");
    } else {
        // printf("\nin first ggg switch\n");
        switch (GGG_bits) {
        case 0b00000000: {
            printf("add ");
        }; break;
        case 0b00000101: {
            printf("sub ");
        }; break;
        case 0b00000111: {
            printf("cmp ");
        }; break;
        default: {
            printf("fell through ggg switch\n");
        }
        }
    }
    if (MOD_bits == 0b00000011) {
        // printf("\nMOD = 11\n");
        REG_figure_outer(w_flag, RM_bits);
    } else {
        // printf("\nMOD != 11\n");
        if (w_flag == YES_W)
            printf("word ");
        else
            printf("byte ");
        effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
    }
    printf(", ");

    switch (MOD_bits) {
    case 0b00000011:
    case 0b00000000: {
        // printf("mr_index += 2\n");
        mr_index += 2;
    }; break;
    case 0b00000001: {
        // printf("mr_index += 3\n");
        mr_index += 3;
    }; break;
    case 0b00000010: {
        // printf("mr_index += 4\n");
        mr_index += 4;
    }; break;
    default: {
        printf("fell through switch at end of CASE2");
    }; break;
    }

    int16_t mr_data = *(mr_index++);
    // printf("mr_index += 1");
    if (w_flag == YES_W) {
        if (s_flag == YES_S) {
            if (GGG_bits == 0b00000111) {
                // mr_data += *(mr_index++) << 8;
                ++mr_index;
                ++mr_index;
            }
            int16_t sign_extend_mr_data = mr_data & 0b0000000010000000;
            sign_extend_mr_data <<= 8;
            mr_data ^= sign_extend_mr_data;
        } else {
            mr_data += *(mr_index++) << 8;
        }
    }
    printf("%d\n", mr_data);

    return mr_index; // some number between 2 and 6
}

inline u8 *jump_and_loop_figure_outer(const byte_whisperer *mr_whisperer, u8 *mr_index) {
    u8 mr_byte = *mr_index;
    u8 jump_lo = 0b01110000;
    u8 jump_hi = 0b01111111;
    u8 loop_lo = 0b11100000;
    u8 loop_hi = 0b11100011;
    u8 mr_increment = 0b00000001;

    // std::cout << std::bitset<8>(*mr_index) << ' ' << std::bitset<8>(*(mr_index + 1)) << '\n';
    // std::cout << mr_index << ' ' << mr_index + 1 << '\n';

    if ((mr_byte >= jump_lo) && (mr_byte <= jump_hi)) {
        char jump_types[][4]{"jo", "jno", "jb", "jnb", "je", "jne", "jbe", "ja",
                             "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jg"};
        printf("%s 0x%08x\n", jump_types[mr_byte - jump_lo], *(mr_index + 1));
    } else if ((mr_byte >= loop_lo) && (mr_byte <= loop_hi)) {
        char loop_types[][7]{"loopnz", "loopz", "loop", "jcxz"};
        printf("%s 0x%08x\n", loop_types[mr_byte - loop_lo], *(mr_index + 1));
    }
    return mr_index += 2;
}

inline u8 *deasm(const byte_whisperer *mr_whisperer, u8 *mr_index) {
    instruction_categories mr_category = mr_whisperer[*mr_index].mr_category;
    // printf("mr_category: %d\n", mr_category);
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    // printf("instruction enum: %u\n", mr_category);
    // printf("\nbyte: %d\n", *mr_index);
    // std::cout << '\n'
    //           << std::bitset<8>(*mr_index) << ' ' << std::bitset<8>(*(mr_index + 1)) << '\n';
    switch (mr_category) {
    case MOV_to_from_register_memory: {
        printf("mov ");
        mr_index = RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index);
    }; break;
    case MOV_immediate_register_memory: {
        printf("mov ");
        mr_index = immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index);
    }; break;
    case MOV_immediate_to_register: {
        printf("mov ");
        mr_index = immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index);
    }; break;
    case ADD_to_from_register_memory: {
        printf("add ");
        mr_index = RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index);
    }; break;
    case ADD_immediate_register_memory: {
        printf("add ");
        mr_index = immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index);
    }; break;
    case ADD_immediate_to_accumulator: { // needed - will be AL or AX... i think
        printf("dd ");
        mr_index = immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index);
    }; break;
    case SUB_to_from_register_memory: {
        printf("sub ");
        mr_index = RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index);
    }; break;
    case SUB_immediate_register_memory: {
        printf("sub ");
        mr_index = immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index);
    }; break;
    case SUB_immediate_to_accumulator: { // needed - same
        printf("sub ");
        mr_index = immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index);
    }; break;
    case CMP_to_from_register_memory: {
        printf("cmp ");
        mr_index = RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index);
    }; break;
    case CMP_immediate_register_memory: { // needed - same
        printf("cmp ");
        mr_index = immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index);
    }; break;
    case CMP_immediate_with_accumulator: {
        printf("cmp "); // this is the one where data is in the 2nd byte
        mr_index = immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index);
    }; break;
    case GGG_TBD_MIDDLE_THREE_WOWEE: {
        // printf("12GGG MIDDLE THREE\n");
        mr_index = immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index);
    }; break;
    case JUMP:
    case LOOP_JCXZ: {
        mr_index = jump_and_loop_figure_outer(mr_whisperer, mr_index);
    }; break;
    default: {
        printf("fell through deasm switch\n");
        mr_index += 1024;
    } break;
    }
    return mr_index;
}

#include "mr_header.h"
#include <cstdint>
#include <inttypes.h>

typedef int16_t s16;
typedef int8_t s8;

enum full_register_name {
    _AX,
    _CX,
    _DX,
    _BX,
    _SP,
    _BP,
    _SI,
    _DI,
    num_of_registers,
};

enum h_l_register_name {
    _AL,
    _CL,
    _DL,
    _BL,
    _AH,
    _CH,
    _DH,
    _BH,
    num_h_l_reggies,
};

enum X_L_or_H {
    _X,
    _L,
    _H,
    num_X_L_or_H,
};

struct Mr_register {
    Mr_register()
      : ax_cx_bx_dx{}, sign_flag{}, zero_flag{} {
        // ax_cx_bx_dx[_BX] = 1;
        h_and_l_pointers[_AL] = (u8 *)(&ax_cx_bx_dx[_AX]);
        h_and_l_pointers[_AH] = (u8 *)(&ax_cx_bx_dx[_AX]) + 1;
        h_and_l_pointers[_CL] = (u8 *)(&ax_cx_bx_dx[_CX]);
        h_and_l_pointers[_CH] = (u8 *)(&ax_cx_bx_dx[_CX]) + 1;
        h_and_l_pointers[_DL] = (u8 *)(&ax_cx_bx_dx[_DX]);
        h_and_l_pointers[_DH] = (u8 *)(&ax_cx_bx_dx[_DX]) + 1;
        h_and_l_pointers[_BL] = (u8 *)(&ax_cx_bx_dx[_BX]);
        h_and_l_pointers[_BH] = (u8 *)(&ax_cx_bx_dx[_BX]) + 1;

        // for (int i{}; i < 4; ++i) {
        //     printf("%s: 0x%x\n%s: 0x%x\n%s: 0x%x\n\n", x_names[i], &ax_cx_bx_dx[i], h_l_names[i],
        //            h_and_l_pointers[i], h_l_names[i + 4], h_and_l_pointers[i + 4]);
        // }
    }

    u16 ax_cx_bx_dx[num_of_registers] /*{1001, 2002, 3003, 4004, 5005, 6006, 7007, 8008}*/;
    u8 *h_and_l_pointers[num_h_l_reggies];
    char x_names[num_of_registers][3]{"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
    char h_l_names[num_h_l_reggies][3]{"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};
    bool sign_flag{};
    bool zero_flag{};
};

inline void register_value_printer(Mr_register *mr_register) {
    // printf("\n");
    for (int i{}; i < num_of_registers; ++i) {
        printf("%s: %d\n", mr_register->x_names[i], mr_register->ax_cx_bx_dx[i]);
    }
    printf("\n");
    for (int i{}; i < num_h_l_reggies; ++i) {
        printf("%s: %u\n", mr_register->h_l_names[i], (u8)(*mr_register->h_and_l_pointers[i]));
    }
    printf("\n");
}

inline void flag_figure_outer(u8 *lvalue_byte, u16 *lvalue_word, Mr_register *mr_register) {
    bool prev_sign_flag = mr_register->sign_flag;
    bool prev_zero_flag = mr_register->zero_flag;
    u16 mr_lvalue{};
    if (lvalue_word == nullptr) {
        mr_lvalue = *lvalue_byte & 0b0000000011111111;
        if (mr_lvalue & 0b0000000010000000) {
            mr_lvalue &= 0b1111111101111111;
            mr_lvalue ^= 0b1000000000000000;
        }
    } else if (lvalue_byte == nullptr) {
        mr_lvalue = *lvalue_word;
    } else {
        printf("pointers are borked lol\n");
    }

    mr_register->zero_flag = (mr_lvalue == 0);
    mr_register->sign_flag = (mr_lvalue & 0b1000000000000000);
         
    if (prev_zero_flag != mr_register->zero_flag) {
        printf("Z: %1x -> %1x\n", prev_zero_flag, mr_register->zero_flag);
    }
    if (prev_sign_flag != mr_register->sign_flag) {
        printf("S: %1x -> %1x\n", prev_sign_flag, mr_register->sign_flag);
    }
    printf("\n");
}

inline void SIM_effective_address_figure_outer(u8 MOD_bits, u8 RM_bits, u8 *mr_index) {
    // printf("in effective address figure outer\n");
    char effective_address[][8] = {"bx + si", "bx + di", "bp + si", "bp + di",
                                   "si",      "di",      "bp",      "bx"};
    switch (MOD_bits) {
    case 0b00000000:
        // printf("MOD = 00\n");
        printf("[%s]", effective_address[RM_bits]);
        break;
    case 0b00000001:
        // printf("MOD = 01\n");
        printf("[%s + %d]", effective_address[RM_bits], *mr_index);
        break;
    case 0b00000010: {
        // printf("MOD = 10\n");
        int big_ol_word = *mr_index + (int)(*(mr_index + 1) << 8);
        printf("[%s + %d]", effective_address[RM_bits], big_ol_word);
    } break;
    default:
        printf("\nfell through effective address switch\n");
        break;
    }
    // printf("\nreturning from effective address figure outer\n");
}

inline u8 *SIM_RM_to_from_REG_figure_outer_CASE1(const byte_whisperer *mr_whisperer, u8 *mr_index,
                                                 Mr_register *mr_register) {
    // printf("in RM to from REG figure outer CASE1\n");
    u8 mod_reg_rm_bit = *(mr_index + 1);
    u8 MOD_bits = mod_reg_rm_bit >> 6;
    u8 REG_bits = (mod_reg_rm_bit & 0b00111000) >> 3;
    u8 RM_bits = (mod_reg_rm_bit & 0b00000111);
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    instruction_format_chunks instruction = mr_whisperer[*mr_index].instruction_format[0];

    u8 *lvalue_byte{nullptr};
    u8 *rvalue_byte{nullptr};
    u8 cmp_result_byte{};

    u16 *lvalue_word{nullptr};
    u16 *rvalue_word{nullptr};
    u16 cmp_result_word{};

    if (MOD_bits == 0b00000011) {
        if (w_flag == NO_W) {
            switch (mr_whisperer[*mr_index].instruction_format[1]) {
            case REG8: {
                lvalue_byte = mr_register->h_and_l_pointers[REG_bits];
                rvalue_byte = mr_register->h_and_l_pointers[RM_bits];
            }; break;
            case REG8_MEM8: {
                lvalue_byte = mr_register->h_and_l_pointers[RM_bits];
                rvalue_byte = mr_register->h_and_l_pointers[REG_bits];
            }; break;
            default: {
                printf("fell through mod 11 NO_W switch #1\n");
            };
            }
            switch (instruction) {
            case MOV: {
                *lvalue_byte = *rvalue_byte;
            }; break;
            case ADD: {
                *lvalue_byte += *rvalue_byte;
            }; break;
            case SUB: {
                *lvalue_byte -= *rvalue_byte;
            }; break;
            case CMP: {
                cmp_result_byte = *lvalue_byte - *rvalue_byte;
                lvalue_byte = &cmp_result_byte;
            }; break;
            default: {
                printf("fell through mod 11 NO_W switch #2\n");
            }
            }
        } else if (w_flag == YES_W) {
            switch (mr_whisperer[*mr_index].instruction_format[1]) {
            case REG16: {
                lvalue_word = &mr_register->ax_cx_bx_dx[REG_bits];
                rvalue_word = &mr_register->ax_cx_bx_dx[RM_bits];
            }; break;
            case REG16_MEM16: {
                lvalue_word = &mr_register->ax_cx_bx_dx[RM_bits];
                rvalue_word = &mr_register->ax_cx_bx_dx[REG_bits];
            }; break;
            default: {

                printf("fell through mod 11 YES_W switch #1\n");
            }; break;
            }
            switch (instruction) {
            case MOV: {
                *lvalue_word = *rvalue_word;
            }; break;
            case ADD: {
                *lvalue_word += *rvalue_word;
            }; break;
            case SUB: {
                *lvalue_word -= *rvalue_word;
            }; break;
            case CMP: {
                cmp_result_word = *lvalue_word - *rvalue_word;
                lvalue_word = &cmp_result_word;
            }; break;
            default: {
                printf("fell through mod 11 NO_W switch #2\n");
            }
            }
        }
        mr_index += 2;
    } else { //                                THIS SHOULDN'T HAPPEN YET
        // printf("MOD != 11\n");
        switch (mr_whisperer[*mr_index].instruction_format[1]) {
        case REG8:
        case REG16: {
            // printf("REG first\n");
            // SIM_REG_bus_lol(w_flag, REG_bits);
            printf(", ");
            SIM_effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
            printf("\n");
        }; break;
        case REG8_MEM8:
        case REG16_MEM16: {
            // printf("RM first\n");
            SIM_effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
            printf(", ");
            // SIM_REG_bus_lol(w_flag, REG_bits);
            printf("\n");
        }; break;
        default:
            printf("\nfell through 2nd half of to_from reg function\n");
            break;
        }
        switch (MOD_bits) {
        case 0b00000010: {
            mr_index += 4;
            // printf("mr_index += 4\n");
        }; break;
        case 0b00000001: {
            mr_index += 3;
            // printf("mr_index += 3\n");
        }; break;
        case 0b00000000: {
            mr_index += 2;
            // printf("mr_index += 2\n");
        }; break;
        default:
            printf("\nfell through switch at end of to from reg function\n");
            break;
        }
        // printf("\nreturning from to_from figure outer\n");
    }
    register_value_printer(mr_register);
    if (instruction != MOV) {
        flag_figure_outer(lvalue_byte, lvalue_word, mr_register);
    }
    return mr_index;
}

inline u8 *SIM_immediate_to_with_from_RM_CASE2(const byte_whisperer *mr_whisperer, u8 *mr_index,
                                               Mr_register *mr_register) {
    // printf("in immediate to with from RM CASE2\n");
    s_ s_flag = mr_whisperer[*mr_index].s_flag;
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    u8 MOD_GGG_RM_bit = *(mr_index + 1);
    u8 MOD_bits = MOD_GGG_RM_bit >> 6;
    u8 GGG_bits = (MOD_GGG_RM_bit & 0b00111000) >> 3;
    u8 RM_bits = (MOD_GGG_RM_bit & 0b00000111);

    instruction_format_chunks instruction = mr_whisperer[*mr_index].instruction_format[0];

    u8 *lvalue_byte{nullptr};
    u8 cmp_result_byte{};

    u16 *lvalue_word{nullptr};
    u16 cmp_result_word{};


    switch (MOD_bits) {
    case 0b00000011: {
        if (w_flag == YES_W) {
            lvalue_word = &mr_register->ax_cx_bx_dx[RM_bits];
        } else {
            lvalue_byte = mr_register->h_and_l_pointers[RM_bits];
        }
        mr_index += 2;
    }; break;
    case 0b00000000: { // none of these should happen yet
        SIM_effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
        mr_index += 2;
    }; break;
    case 0b00000001: {
        SIM_effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
        mr_index += 3;
    }; break;
    case 0b00000010: {
        SIM_effective_address_figure_outer(MOD_bits, RM_bits, mr_index + 2);
        mr_index += 4;
    }; break;
    default: {
        printf("fell through CASE2 lvalue switch");
    }; break;
    }

    // printf("mr_index += 1");
    if (w_flag == YES_W) {
        u16 mr_data = *(mr_index++);
        if (s_flag == YES_S) {
            // if (instruction == CMP) { // i don't think this is correct - see 4-30 & 4-31
            //     // mr_data += *(mr_index++) << 8;
            //     ++mr_index; // with CMP, data is 2 bytes regardless
            //     ++mr_index; // this 2nd one was here b/c trial and error.
            // }
            int16_t sign_extend_mr_data = mr_data & 0b0000000010000000;
            sign_extend_mr_data <<= 8;
            mr_data ^= sign_extend_mr_data;
        } else {
            mr_data += *(mr_index++) << 8;
        }
        if (mr_whisperer[*mr_index].mr_category == MOV_immediate_register_memory) { // MOV
            *lvalue_word = mr_data;
        } else {
            // printf("\nin first ggg switch\n");
            switch (GGG_bits) {
            case 0b00000000: { // ADD
                *lvalue_word += mr_data;
            }; break;
            case 0b00000101: { // SUB
                *lvalue_word -= mr_data;
            }; break;
            case 0b00000111: { // CMP
                cmp_result_word = *lvalue_word;
                cmp_result_word -= mr_data;
                lvalue_word = &cmp_result_word;
            }; break;
            default: {
                printf("fell through CASE2 YES_W switch\n");
            }
            }
        }
    } else {
        u8 mr_data = *(mr_index++);
        if (mr_whisperer[*mr_index].mr_category == MOV_immediate_register_memory) { // MOV
            *lvalue_byte = mr_data;
        } else {
            // printf("\nin first ggg switch\n");
            switch (GGG_bits) {
            case 0b00000000: { // ADD
                *lvalue_byte += mr_data;
            }; break;
            case 0b00000101: { // SUB
                *lvalue_byte -= mr_data;
            }; break;
            case 0b00000111: { // CMP
                cmp_result_byte = *lvalue_byte;
                cmp_result_byte -= mr_data;
                lvalue_byte = &cmp_result_byte;
            }; break;
            default: {
                printf("fell through CASE2 YES_W switch\n");
            }
            }
        }
    }

    register_value_printer(mr_register);
    flag_figure_outer(lvalue_byte, lvalue_word, mr_register);

    return mr_index; // some number between 2 and 6
}

inline u8 *SIM_immediate_to_with_from_REG_CASE3(const byte_whisperer *mr_whisperer, u8 *mr_index,
                                                Mr_register *mr_register) {
    // printf("in immediate to with from REG CASE3\n");
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    u8 REG_bits;
    instruction_format_chunks mr_instruction = mr_whisperer[*mr_index].instruction_format[0];

    u8 *lvalue_byte{nullptr};
    u16 *lvalue_word{nullptr};

    switch (mr_instruction) {
    case MOV: {
        REG_bits = (*mr_index) & 0b00000111;
        if (w_flag == NO_W) {
            lvalue_byte = mr_register->h_and_l_pointers[REG_bits];
            *lvalue_byte = *(mr_index + 1);
        } else if (w_flag == YES_W) {
            lvalue_word = &mr_register->ax_cx_bx_dx[REG_bits];
            *lvalue_word = *(mr_index + 1) + (*(mr_index + 2) << 8);
        }
        register_value_printer(mr_register);
    }; break;
    case ADD:
    case SUB:
    case CMP: {
        printf("find out why CASE3 is getting non MOV instructions\n");
        flag_figure_outer(lvalue_byte, lvalue_word, mr_register);
    }; break;
    default: {
        printf("fell through MOV_immediate_to_REG_CASE3 switch\n");
    }; break;
    }


    // switch (mr_whisperer[*mr_index].instruction_format[2]) {
    // case IMMED8: {
    //     *lvalue_byte = *(mr_index + 1);
    // }; break;
    // case IMMED16: {
    //     *lvalue_word = *(mr_index + 1) + (*(mr_index + 2) << 8);
    // }; break;
    // default:
    //     printf("fell through immediate switch #2\n");
    //     break;
    // }
    return mr_index += (2 + w_flag);
}

inline u8 *SIM_jump_and_loop_figure_outer(const byte_whisperer *mr_whisperer, u8 *mr_index,
                                          Mr_register *mr_register) {
    u8 mr_byte = *mr_index;
    u8 jump_lo = 0b01110000;
    u8 jump_hi = 0b01111111;
    u8 loop_lo = 0b11100000;
    u8 loop_hi = 0b11100011;
    u8 mr_increment = 0b00000001;

    // std::cout << std::bitset<8>(*mr_index) << ' ' << std::bitset<8>(*(mr_index + 1)) << '\n';
    // std::cout << mr_index << ' ' << mr_index + 1 << '\n';

    if ((mr_byte >= jump_lo) && (mr_byte <= jump_hi)) {
        char jump_types[][4]{"jo", "jno", "jb", "jnb", "je", "jne", "jbe", "ja",
                             "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jg"};
        printf("%s 0x%08x\n", jump_types[mr_byte - jump_lo], *(mr_index + 1));
    } else if ((mr_byte >= loop_lo) && (mr_byte <= loop_hi)) {
        char loop_types[][7]{"loopnz", "loopz", "loop", "jcxz"};
        printf("%s 0x%08x\n", loop_types[mr_byte - loop_lo], *(mr_index + 1));
    }
    return mr_index += 2;
}

inline u8 *its_sim_time(const byte_whisperer *mr_whisperer, u8 *mr_index,
                        Mr_register *mr_register) {
    instruction_categories mr_category = mr_whisperer[*mr_index].mr_category;
    // printf("mr_category: %d\n", mr_category);
    w_ w_flag = mr_whisperer[*mr_index].w_flag;
    // printf("instruction enum: %u\n", mr_category);
    // printf("\nbyte: %d\n", *mr_index);
    // std::cout << '\n'
    //           << std::bitset<8>(*mr_index) << ' ' << std::bitset<8>(*(mr_index + 1)) << '\n';
    switch (mr_category) {
    case MOV_to_from_register_memory: {
        mr_index = SIM_RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index, mr_register);
    }; break;
    case MOV_immediate_register_memory: {
        mr_index = SIM_immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index, mr_register);
    }; break;
    case MOV_immediate_to_register: {
        mr_index = SIM_immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index, mr_register);
    }; break;
    case ADD_to_from_register_memory: {
        mr_index = SIM_RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index, mr_register);
    }; break;
    case ADD_immediate_register_memory: {
        mr_index = SIM_immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index, mr_register);
    }; break;
    case ADD_immediate_to_accumulator: { // needed - will be AL or AX... i think
        mr_index = SIM_immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index, mr_register);
    }; break;
    case SUB_to_from_register_memory: {
        mr_index = SIM_RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index, mr_register);
    }; break;
    case SUB_immediate_register_memory: {
        mr_index = SIM_immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index, mr_register);
    }; break;
    case SUB_immediate_to_accumulator: { // needed - same
        mr_index = SIM_immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index, mr_register);
    }; break;
    case CMP_to_from_register_memory: {
        mr_index = SIM_RM_to_from_REG_figure_outer_CASE1(mr_whisperer, mr_index, mr_register);
    }; break;
    case CMP_immediate_register_memory: { // needed - same
        mr_index = SIM_immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index, mr_register);
    }; break;
    case CMP_immediate_with_accumulator: {
        // this is the one where data is in the 2nd byte
        mr_index = SIM_immediate_to_with_from_REG_CASE3(mr_whisperer, mr_index, mr_register);
    }; break;
    case GGG_TBD_MIDDLE_THREE_WOWEE: {
        mr_index = SIM_immediate_to_with_from_RM_CASE2(mr_whisperer, mr_index, mr_register);
    }; break;
    case JUMP:
    case LOOP_JCXZ: {
        mr_index = SIM_jump_and_loop_figure_outer(mr_whisperer, mr_index, mr_register);
    }; break;
    default: {
        printf("fell through deasm switch\n");
        mr_index += 1024;
    } break;
    }
    return mr_index;
}

#include <string.h>
// #define debug

int main(int argc, char **argv) {
    byte_whisperer mr_whisperer[256];
    set_up_mr_whisperer(mr_whisperer);
    FILE *mr_file;
    bool do_exec;
    Mr_register mr_register{};

#ifdef debug
    do_exec = true;
    char listing[50]{"listing_0046_add_sub_cmp"};
    mr_file = fopen(listing, "rb");
    if (mr_file == NULL) {
        printf("file open failed\n");
        return -1;
    }
    u8 mr_buffer[1024];
    mr_buffer[1023] = 0b11111111;
    u8 *mr_deasm_index = mr_buffer;
    size_t bytes_read = fread(mr_buffer, sizeof(u8), array_size(mr_buffer), mr_file);
    // fread(mr_buffer, sizeof(u8), 64, mr_file);

    printf("bytes read %d\n", (int)bytes_read);

    if (do_exec) {
        u8 *mr_sim_index = mr_buffer;
        register_value_printer(&mr_register);
        while (mr_deasm_index < &mr_buffer[bytes_read - 1]) {
            mr_sim_index = its_sim_time(mr_whisperer, mr_sim_index, &mr_register);
            mr_deasm_index = deasm(mr_whisperer, mr_deasm_index);
            register_value_printer(&mr_register);
        }
    } else {
        printf("else\n");
        while (mr_deasm_index < &mr_buffer[bytes_read - 1]) {
            printf("test lol\n");
            mr_deasm_index = deasm(mr_whisperer, mr_deasm_index);
        }
    }
    fclose(mr_file);
}
#endif // debug
#ifndef debug
    if (argc > 2) {
        if (strcmp(argv[1], "-exec") == 0) {
            do_exec = true;
            mr_file = fopen(argv[2], "rb");
        } else {
            do_exec = false;
            mr_file = fopen(argv[1], "rb");
        }
    }
    if (mr_file == NULL) {
        printf("file open failed\n");
        return -1;
    }
    u8 mr_buffer[1024];
    mr_buffer[1023] = 0b11111111;
    u8 *mr_deasm_index = mr_buffer;
    size_t bytes_read = fread(mr_buffer, sizeof(u8), array_size(mr_buffer), mr_file);
    // fread(mr_buffer, sizeof(u8), 64, mr_file);

    printf("bytes read %d\n", (int)bytes_read);

    if (do_exec) {
        u8 *mr_sim_index = mr_buffer;
	printf("\nInitial state:\n");
        register_value_printer(&mr_register);
        while (mr_deasm_index < &mr_buffer[bytes_read - 1]) {
            mr_deasm_index = deasm(mr_whisperer, mr_deasm_index);
	    printf("\n");
            mr_sim_index = its_sim_time(mr_whisperer, mr_sim_index, &mr_register);
        }
    } else {
        printf("else\n");
        while (mr_deasm_index < &mr_buffer[bytes_read - 1]) {
            printf("test lol\n");
            mr_deasm_index = deasm(mr_whisperer, mr_deasm_index);
        }
    }
    fclose(mr_file);
}
#endif // debug
