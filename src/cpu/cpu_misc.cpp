#include "cpu.h"


void CPU::swap(const std::string &reg) {
    uint8_t val;
    
    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    uint8_t lower = val & 0x0F;
    uint8_t upper = val & 0xF0;
    uint8_t result = (lower << 4) | (upper >> 4);

    this->reset_flag_register();

    std::cout << "SWAP " << reg << std::endl;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

void CPU::complement() {
    uint8_t val = this->read_register("A");
    uint8_t result = ~val;

    std::cout << "CPL" << std::endl;

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(HALF_CARRY_FLAG, true);

    this->write_register("A", result);
}

void CPU::complement_carry() {
    bool carry = this->read_flag_register(CARRY_FLAG);

    std::cout << "CCF" << std::endl;

    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);
    
    this->set_flag_register(CARRY_FLAG, !carry);
}

void CPU::set_carry() {
    std::cout << "SCF" << std::endl;

    this->set_flag_register(CARRY_FLAG, true);
}