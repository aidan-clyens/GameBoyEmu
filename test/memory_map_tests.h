#include "gtest/gtest.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"


TEST(MemoryMap, Init) {
    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(nullptr));
}

TEST(MemoryMap, GetIndexes) {
    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(nullptr));

    uint16_t addresses[12] = {
        0x1000,
        0x5000,
        0x9000,
        0xB000,
        0xD000,
        0xF000,
        0xFE0A,
        0xFEFF,
        0xFF0F,
        0xFF50,
        0xFF90,
        0xFFFF
    };

    for (int i=0; i<12; i++) {
        EXPECT_EQ(i, mem_map.get_index(addresses[i]));
    }
}

TEST(MemoryMap, GetIndexesBoundaries) {
    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(nullptr));

    uint16_t addresses[12] = {
        0x0000,
        0x4000,
        0x8000,
        0xA000,
        0xC000,
        0xE000,
        0xFE00,
        0xFEA0,
        0xFF00,
        0xFF4C,
        0xFF80,
        0xFFFF
    };

    for (int i=0; i<12; i++) {
        EXPECT_EQ(i, mem_map.get_index(addresses[i]));
    }
}

TEST(MemoryMap, WriteSwitchableRAM) {
    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(nullptr));

    uint16_t address = 0xA100;
    uint16_t mem_address = address - 0xA000;
    uint8_t data = 0x1F;

    EXPECT_EQ(3, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(mem_address, mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}

TEST(MemoryMap, WriteInternalRAM) {
    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(nullptr));

    uint16_t address =0xC100;
    uint16_t mem_address = address - 0xC000;
    uint8_t data = 0x1F;

    EXPECT_EQ(4, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(mem_address, mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}

TEST(MemoryMap, ReadRom) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);

    EXPECT_EQ(buffer_size, file_parser.get_buffer_size());
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(file_parser.get_buffer_ptr()));

    uint16_t address_1 = 0x134;
    uint8_t data_1 = 0x54;

    EXPECT_EQ(0, mem_map.get_index(address_1));
    EXPECT_EQ(data_1, mem_map.read(address_1));
}

TEST(MemoryMap, WriteToRom) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);

    EXPECT_EQ(buffer_size, file_parser.get_buffer_size());
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    EXPECT_TRUE(mem_map.init_memory_map(file_parser.get_buffer_ptr()));

    uint16_t address_1 = 0x134;
    uint8_t data_1 = 0xFF;

    EXPECT_EQ(0, mem_map.get_index(address_1));
    EXPECT_ANY_THROW(mem_map.write(address_1, data_1));
}