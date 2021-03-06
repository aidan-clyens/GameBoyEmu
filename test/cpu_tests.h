#include "gtest/gtest.h"


TEST(CPU, InitCPU) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);
}

TEST(CPU, FetchOpcodeFromRom) {
    std::vector<char> contents;
    contents.resize(BUFFER_SIZE);
    std::fill(contents.begin(), contents.end(), 0);

    contents[0x100] = 0xAB;
    contents[0x101] = 0xCD;

    ROMOnly *cartridge = new ROMOnly(contents, 2);
    EXPECT_EQ(ROM_ONLY, cartridge->get_cartridge_type());

    MemoryMap mem_map;
    mem_map. load_rom(cartridge);
    CPU cpu(mem_map);

    EXPECT_EQ(0x100, cpu.read_register(REG_PC));
    EXPECT_EQ(0xAB, cpu.fetch_op());
    EXPECT_EQ(0xCD, cpu.fetch_op());
}

TEST(CPU, InitialFlagRegister) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_TRUE(cpu.read_flag_register(ZERO_FLAG));
    EXPECT_FALSE(cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_TRUE(cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, WriteZeroFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
}

TEST(CPU, WriteSubtractFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
}

TEST(CPU, WriteHalfCarryFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU, WriteCarryFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, SetMultipleFlags) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));
    
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, false));

    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, ResetFlagRegister) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));

    cpu.reset_flag_register();

    EXPECT_EQ(0, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, WriteMemoryHL) {
    uint16_t HL = 0xFF80;
    uint8_t val = 0xAB;
    
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_HL, HL);
    EXPECT_EQ(HL, cpu.read_register(REG_HL));

    cpu.write_memory(val);

    EXPECT_EQ(val, cpu.read_memory());
    EXPECT_EQ(val, cpu.read_memory(REG_HL));
}

TEST(CPU, WriteMemory) {
    uint16_t BC = 0xFF80;
    uint8_t val = 0xAB;
    
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_BC, BC);
    EXPECT_EQ(BC, cpu.read_register(REG_BC));

    cpu.write_memory(REG_BC, val);

    EXPECT_EQ(val, cpu.read_memory(REG_BC));
}