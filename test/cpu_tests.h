#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"


TEST(CPU, InitCPU) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_register("AF"));
    EXPECT_EQ(0x0, cpu.read_register("BC"));
    EXPECT_EQ(0x0, cpu.read_register("DE"));
    EXPECT_EQ(0x0, cpu.read_register("HL"));
    EXPECT_EQ(0x0, cpu.read_register("SP"));
    EXPECT_EQ(0x100, cpu.read_register("PC"));
}

TEST(CPU, ReadInvalidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_ANY_THROW(cpu.read_register("ABC"));
}

TEST(CPU, WriteValidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu.write_register("AF", data));
    EXPECT_EQ(data, cpu.read_register("AF"));
}

TEST(CPU, WriteInvalidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    uint16_t data = 0xABCD;

    EXPECT_ANY_THROW(cpu.write_register("ABC", data));
}

TEST(CPU, FetchOpcodeFromRom) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map.init_memory_map(file_parser.get_buffer_ptr());
    CPU cpu(mem_map);

    EXPECT_EQ(0x100, cpu.read_register("PC"));
    EXPECT_EQ(file_parser.get_byte(0x100), cpu.fetch_op());
    EXPECT_EQ(file_parser.get_byte(0x101), cpu.fetch_op());
}