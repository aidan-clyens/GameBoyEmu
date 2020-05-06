#include "io.h"


IO::IO():
m_P1(0xFF),
m_DIV(0x0),
m_TIMA(0x0),
m_TMA(0x0),
m_TAC(0x0),
m_LCDC(0x91),
m_SCY(0x0),
m_SCX(0x0),
m_LY(0x0),
m_LYC(0x0),
m_BGP(0xFC),
m_OBP0(0xFF),
m_OBP1(0xFF),
m_WY(0x0),
m_WX(0x0),
m_IE(0x0),
m_IF(0x0)
{

}

IO::~IO() {

}

uint8_t IO::read(IORegisters_t address) {
    if (address >= 0xFF30 && address <= 0xFF3F) {
        #ifdef IO_DEBUG
        std::cerr << "Wave Pattern RAM unusable" << std::endl;
        #endif

        return 0;
    }

    switch (address) {
        case P1:
            #ifdef IO_DEBUG
            std::cout << "IO read: P1" << std::endl;
            #endif

            return m_P1;
        case SB:
            #ifdef IO_DEBUG
            std::cerr << "SB not implemented" << std::endl;
            #endif

            return 0;
        case SC:
            #ifdef IO_DEBUG
            std::cerr << "SB not implemented" << std::endl;
            #endif

            return 0;
        case DIV:
            #ifdef IO_DEBUG
            std::cout << "IO read: DIV" << std::endl;
            #endif

            return m_DIV;
        case TIMA:
            #ifdef IO_DEBUG
            std::cout << "IO read: TIMA" << std::endl;
            #endif

            return m_TIMA;
        case TMA:
            #ifdef IO_DEBUG
            std::cout << "IO read: TMA" << std::endl;
            #endif

            return m_TMA;
        case TAC:
            #ifdef IO_DEBUG
            std::cout << "IO read: TAC" << std::endl;
            #endif

            return m_TAC;
        case IF:
            #ifdef IO_DEBUG
            std::cout << "IO read: IF" << std::endl;
            #endif

            return m_IF;
        case NR10:
        case NR11:
        case NR12:
        case NR13:
        case NR14:
        case NR21:
        case NR22:
        case NR23:
        case NR24:
        case NR30:
        case NR31:
        case NR32:
        case NR33:
        case NR34:
        case NR41:
        case NR42:
        case NR43:
        case NR44:
        case NR50:
        case NR51:
        case NR52:
            #ifdef IO_DEBUG
            std::cerr << "NR5* not implemented" << std::endl;
            #endif

            return 0;
        case LCDC:
            #ifdef IO_DEBUG
            std::cout << "IO read: LCDC" << std::endl;
            #endif

            return m_LCDC;
        case STAT:
            #ifdef IO_DEBUG
            std::cout << "IO read: STAT" << std::endl;
            #endif

            return m_STAT;
        case SCY:
            #ifdef IO_DEBUG
            std::cout << "IO read: SCY" << std::endl;
            #endif

            return m_SCY;
        case SCX:
            #ifdef IO_DEBUG
            std::cout << "IO read: SCX" << std::endl;
            #endif

            return m_SCX;
        case LY:
            #ifdef IO_DEBUG
            std::cout << "IO read: LY" << std::endl;
            #endif

            return m_LY;
        case LYC:
            #ifdef IO_DEBUG
            std::cout << "IO read: LYC" << std::endl;
            #endif

            return m_LYC;
        case DMA:
            #ifdef IO_DEBUG
            std::cout << "IO read: DMA" << std::endl;
            #endif

            return m_DMA;
        case BGP:
            #ifdef IO_DEBUG
            std::cout << "IO read: BGP" << std::endl;
            #endif

            return m_BGP;
        case OBP0:
            #ifdef IO_DEBUG
            std::cout << "IO read: OBP0" << std::endl;
            #endif

            return m_OBP0;
        case OBP1:
            #ifdef IO_DEBUG
            std::cout << "IO read: OBP1" << std::endl;
            #endif

            return m_OBP1;
        case WY:
            #ifdef IO_DEBUG
            std::cout << "IO read: WY" << std::endl;
            #endif

            return m_WY;
        case WX:
            #ifdef IO_DEBUG
            std::cout << "IO read: WX" << std::endl;
            #endif

            return m_WX;
        case IE:
            #ifdef IO_DEBUG
            std::cout << "IO read: IE" << std::endl;
            #endif

            return m_IE;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            // throw new std::exception;
            break;
    }
}

uint16_t IO::write(IORegisters_t address, uint8_t data) {
    if (address >= 0xFF30 && address <= 0xFF3F) {
        #ifdef IO_DEBUG
        std::cerr << "Wave Pattern RAM unusable" << std::endl;
        #endif

        return 0;
    }

    switch (address) {
        case P1:
            #ifdef IO_DEBUG
            std::cout << "IO write: P1" << std::endl;
            #endif

            m_P1 = data;
            break;
        case SB:
            #ifdef IO_DEBUG
            std::cerr << "SB not implemented" << std::endl;
            #endif

            break;
        case SC:
            #ifdef IO_DEBUG
            std::cerr << "SB not implemented" << std::endl;
            #endif

            break;
        case DIV:
            #ifdef IO_DEBUG
            std::cout << "IO write: DIV" << std::endl;
            #endif

            m_DIV = data;
            break;
        case TIMA:
            #ifdef IO_DEBUG
            std::cout << "IO write: TIMA" << std::endl;
            #endif

            m_TIMA = data;
            break;
        case TMA:
            #ifdef IO_DEBUG
            std::cout << "IO write: TMA" << std::endl;
            #endif

            m_TMA = data;
            break;
        case TAC:
            #ifdef IO_DEBUG
            std::cout << "IO write: TAC" << std::endl;
            #endif

            m_TAC = data;
            break;
        case IF:
            #ifdef IO_DEBUG
            std::cout << "IO write: IF" << std::endl;
            #endif

            m_IF = data;
            break;
        case NR10:
        case NR11:
        case NR12:
        case NR13:
        case NR14:
        case NR21:
        case NR22:
        case NR23:
        case NR24:
        case NR30:
        case NR31:
        case NR32:
        case NR33:
        case NR34:
        case NR41:
        case NR42:
        case NR43:
        case NR44:
        case NR50:
        case NR51:
        case NR52:
            #ifdef IO_DEBUG
            std::cerr << "NR5* not implemented" << std::endl;
            #endif

            break;
        case LCDC:
            #ifdef IO_DEBUG
            std::cout << "IO write: LCDC" << std::endl;
            #endif

            m_LCDC = data;
            break;
        case STAT:
            #ifdef IO_DEBUG
            std::cout << "IO write: STAT" << std::endl;
            #endif

            m_STAT = data;
            break;
        case SCY:
            #ifdef IO_DEBUG
            std::cout << "IO write: SCY" << std::endl;
            #endif

            m_SCY = data;
            break;
        case SCX:
            #ifdef IO_DEBUG
            std::cout << "IO write: SCX" << std::endl;
            #endif

            m_SCX = data;
            break;
        case LY:
            #ifdef IO_DEBUG
            std::cout << "IO write: LY" << std::endl;
            #endif

            m_LY = data;
            break;
        case LYC:
            #ifdef IO_DEBUG
            std::cout << "IO write: LYC" << std::endl;
            #endif

            m_LYC = data;
            break;
        case DMA:
            #ifdef IO_DEBUG
            std::cout << "IO write: DMA" << std::endl;
            #endif

            m_DMA = data;
            break;
        case BGP:
            #ifdef IO_DEBUG
            std::cout << "IO write: BGP" << std::endl;
            #endif

            m_BGP = data;
            break;
        case OBP0:
            #ifdef IO_DEBUG
            std::cout << "IO write: OBP0" << std::endl;
            #endif

            m_OBP0 = data;
            break;
        case OBP1:
            #ifdef IO_DEBUG
            std::cout << "IO write: OBP1" << std::endl;
            #endif

            m_OBP1 = data;
            break;
        case WY:
            #ifdef IO_DEBUG
            std::cout << "IO write: WY" << std::endl;
            #endif

            m_WY = data;
            break;
        case WX:
            #ifdef IO_DEBUG
            std::cout << "IO write: WX" << std::endl;
            #endif

            m_WX = data;
            break;
        case IE:
            #ifdef IO_DEBUG
            std::cout << "IO write: IE" << std::endl;
            #endif

            m_IE = data;
            break;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            throw new std::exception;
    }

    return address;
}

void IO::increment_counter(IORegisters_t reg) {
    switch (reg) {
        case LY:
            #ifdef IO_DEBUG
            std::cout << "IO: Incremented LY" << std::endl;
            #endif
            m_LY++;
            break;
        case DIV:
            #ifdef IO_DEBUG
            std::cout << "IO: Incremented DIV" << std::endl;
            #endif
            m_DIV++;
            break;
        default:
            std::cerr << "IO register is not a counter. Cannot be incremented." << std::endl;
            throw new std::exception;
    }
}