#include "gtest/gtest.h"


MemoryMap setup_mem_map(uint16_t PC, uint16_t value) {
    MemoryMap mem_map;
    
    mem_map.write(PC, (value & 0xFF));
    mem_map.write(PC + 1, (value >> 8));

    EXPECT_EQ((value & 0xFF), mem_map.read(PC));
    EXPECT_EQ((value >> 8), mem_map.read(PC + 1));

    return mem_map;
}


TEST(CPU_JUMP, JP_NN) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC3;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_NZ_NN_False) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_NZ_NN_True) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_Z_NN_False) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xCA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_Z_NN_True) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xCA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_NC_NN_False) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xD2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_NC_NN_True) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xD2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_C_NN_False) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xDA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_C_NN_True) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xDA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JP_HL) {
    uint16_t PC = 0xFF80;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xE9;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_HL, value);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_Postive) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    int value_signed = 112;
    uint16_t result_PC = PC + value_signed + 1;
    uint8_t opcode = 0x18;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_Negative) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0xAB;
    int value_signed = -85;
    uint8_t opcode = 0x18;
    uint16_t result_PC = PC + value_signed + 1;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_NZ_False) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint16_t result_PC = PC + value + 1;
    uint8_t opcode = 0x20;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_NZ_True) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint8_t opcode = 0x20;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_Z_False) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint8_t opcode = 0x28;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_Z_True) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint16_t result_PC = PC + value + 1;
    uint8_t opcode = 0x28;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_NC_False) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint16_t result_PC = PC + value + 1;
    uint8_t opcode = 0x30;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_FALSE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_NC_True) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint8_t opcode = 0x30;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_C_False) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint8_t opcode = 0x38;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register(REG_PC));
}

TEST(CPU_JUMP, JR_C_True) {
    uint16_t PC = 0xFF80;
    uint8_t value = 0x70;
    uint16_t result_PC = PC + value + 1;
    uint8_t opcode = 0x38;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(result_PC, cpu.read_register(REG_PC));
}

// RST 10
TEST(CPU_RST, RST) {
    uint8_t opcode = 0xD7;
    uint16_t PC = 0xFF80;
    uint16_t SP = 0xFFF0;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(PC & 0xFF, cpu.read_memory(REG_HL));
}

// CALL nn
TEST(CPU_CALL, CALL_NN) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    EXPECT_EQ(val, cpu.read_register(REG_PC));
}

// CALL cc, nn
TEST(CPU_CALL, CALL_CC_NN_NoFlags) {
    uint8_t opcode = 0xDC;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.set_flag_register(CARRY_FLAG, false);

    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(next_PC, cpu.read_register(REG_PC));
}

// CALL cc, nn
TEST(CPU_CALL, CALL_CC_NN_Carry) {
    uint8_t opcode = 0xDC;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.set_flag_register(CARRY_FLAG, true);

    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    EXPECT_EQ(val, cpu.read_register(REG_PC));
}

// RET
TEST(CPU_RETURNS, RET) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    // CALL nn
    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    // RET
    opcode = 0xC9;
    cpu.decode_op(opcode);

    EXPECT_EQ(SP, cpu.read_register(REG_SP));
    EXPECT_EQ(next_PC, cpu.read_register(REG_PC));
}

// RET cc
TEST(CPU_RETURNS, RET_CC_NoFlags) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    // CALL nn
    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    // RET cc
    cpu.set_flag_register(CARRY_FLAG, false);

    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    opcode = 0xD8;
    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));
    EXPECT_EQ(val, cpu.read_register(REG_PC));
}

// RET cc
TEST(CPU_RETURNS, RET_CC_Carry) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    // CALL nn
    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    // RET cc
    cpu.set_flag_register(CARRY_FLAG, true);

    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    opcode = 0xD8;
    cpu.decode_op(opcode);

    EXPECT_EQ(SP, cpu.read_register(REG_SP));
    EXPECT_EQ(next_PC, cpu.read_register(REG_PC));
}

// RETI
TEST(CPU_RETURNS, RETI) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xFF80;
    uint16_t next_PC = 0xFF82;
    uint16_t SP = 0xFFF0;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    // CALL nn
    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(next_PC >> 8, cpu.read_memory(REG_DE));
    EXPECT_EQ(next_PC & 0xFF, cpu.read_memory(REG_HL));

    // RETI
    opcode = 0xD9;
    cpu.decode_op(opcode);

    EXPECT_EQ(SP, cpu.read_register(REG_SP));
    EXPECT_EQ(next_PC, cpu.read_register(REG_PC));

    // Check if interrupts are enabled
    EXPECT_TRUE(cpu.interrupts_enabled());
}
