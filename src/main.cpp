#include <fstream>
#include <iostream>

#include "display/display.h"
#include "file_parser/file_parser.h"
#include "memory/memory_map.h"
#include "memory/memory.h"
#include "cpu/cpu.h"


int main(int argc, char** argv) {
    int rom_size = 32*1024;

    std::string rom_file = "roms/Tetris.gb";
    
    if (argc > 1) {
        rom_file = argv[1];
    }

    FileParser file_parser(rom_size);
    file_parser.load_rom(rom_file);
    
    MemoryMap memory_map;
    memory_map.init_memory_map(file_parser.get_buffer_ptr());

    CPU cpu(memory_map);

    std::string rom_name = file_parser.get_rom_name();
    cartridge_type_t cartridge_type = file_parser.get_cartridge_type();

    Display main_display(rom_name);

    std::cout << "Title: " << rom_name << std::endl;
    std::cout << "Cartridge Type: " << cartridge_type << std::endl << std::endl;

    main_display.init_display();
    
    while (main_display.is_display_open()) {
        uint8_t opcode =  cpu.fetch_op();

        cpu.decode_op(opcode);

        main_display.poll_events();
        main_display.render();
    }

    return 0;
}
