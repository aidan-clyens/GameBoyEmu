#include "gtest/gtest.h"
#include "video/video.h"
#include "video/tile.h"
#include "memory/memory_map.h"


TEST(Video, ReadIORegister) {
    MemoryMap mem_map;
    Video video(mem_map);

    EXPECT_EQ(0x91, video.read_io_register(LCDC));
}


TEST(Video, WriteIORegister) {
    uint8_t data = 0xAB;

    MemoryMap mem_map;
    Video video(mem_map);

    EXPECT_NO_THROW(video.write_io_register(LCDC, data));
    EXPECT_EQ(data, video.read_io_register(LCDC));
}


TEST(Video, CheckLCDDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_TRUE(video.lcd_display_enabled());
}


TEST(Video, CheckWindowDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_TRUE(video.window_display_enabled());
}


TEST(Video, CheckSpriteDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_FALSE(video.sprite_display_enabled());
}


TEST(Video, CheckBackgroundDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_FALSE(video.background_display_enabled());
}


TEST(Video, CheckSpriteSize) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(SPRITEx16, video.get_sprite_size());
}


TEST(Video, CheckTileDataTable) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_DATA_SIGNED, video.get_tile_data_selected());
}


TEST(Video, CheckWindowTileMap) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_MAP_2, video.get_window_tile_map_selected());
}


TEST(Video, CheckBackgroundTileMap) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_MAP_2, video.get_background_tile_map_selected());
}


TEST(Video, CheckVideoMode) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());
}


TEST(Video, SetVideoMode) {
    MemoryMap mem_map;
    Video video(mem_map);

    video.set_video_mode(Data_Transfer_Mode);
    EXPECT_EQ(Data_Transfer_Mode, video.get_video_mode());
}


TEST(Video, CheckCoincidenceFlag) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_FALSE(video.get_coincidence_flag());
}


TEST(Video, CheckCoincidenceInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.coincidence_interrupt_enabled());
}


TEST(Video, CheckOAMInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.oam_interrupt_enabled());
}


TEST(Video, CheckVBlankInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_FALSE(video.vblank_interrupt_enabled());
}


TEST(Video, CheckHBlankInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.hblank_interrupt_enabled());
}


TEST(Video, GetScrollY) {
    int scy = 25;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(SCY, scy);
    EXPECT_EQ(scy, video.read_io_register(SCY));

    EXPECT_EQ(scy, video.get_scroll_y());
}


TEST(Video, GetScrollX) {
    int scx = 50;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(SCX, scx);
    EXPECT_EQ(scx, video.read_io_register(SCX));

    EXPECT_EQ(scx, video.get_scroll_x());
}


TEST(Video, GetLY) {
    int ly = 100;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LY, ly);
    EXPECT_EQ(ly, video.read_io_register(LY));

    EXPECT_EQ(ly, video.get_lcd_y_coordinate());
}


TEST(Video, GetLYCompare) {
    int lyc = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LYC, lyc);
    EXPECT_EQ(lyc, video.read_io_register(LYC));

    EXPECT_EQ(lyc, video.get_lcd_y_compare());
}


TEST(Video, GetWindowY) {
    int wy = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(WY, wy);
    EXPECT_EQ(wy, video.read_io_register(WY));

    EXPECT_EQ(wy, video.get_window_y());
}


TEST(Video, GetWindowX) {
    int wx = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(WX, wx);
    EXPECT_EQ(wx, video.read_io_register(WX));

    EXPECT_EQ(wx, video.get_window_x());
}


TEST(Video, TriggerVBlankInterrupt) {
    uint8_t stat = 0x11;    // 0001 0001

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in OAM mode
    video.set_video_mode(OAM_Mode);
    EXPECT_EQ(OAM_Mode, video.get_video_mode());

    // Change to V-Blank mode
    video.write_io_register(STAT, stat);
    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());
    EXPECT_TRUE(video.vblank_interrupt_enabled());
    
    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A V-Blank interrupt should be triggered
    EXPECT_EQ(0x01, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick();

    // Interrupt should only be triggered at the start of the V-Blank period
    EXPECT_EQ(0x0, video.read_io_register(IF));
}


TEST(Video, TriggerLCDCStatusOAMInterrupt) {
    uint8_t stat = 0x22; // 0010 0010

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in V-Blank mode
    video.set_video_mode(VBLANK_Mode);
    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());

    // Change to OAM mode
    video.write_io_register(STAT, stat);
    EXPECT_EQ(OAM_Mode, video.get_video_mode());
    EXPECT_TRUE(video.oam_interrupt_enabled());

    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A LCDC status interrupt should be triggered
    EXPECT_EQ(0x02, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick();

    // Interrupt should only be triggered at the start of the OAM period
    EXPECT_EQ(0x0, video.read_io_register(IF));
}


TEST(Video, TriggerLCDCStatusCoincidenceInterrupt) {
    uint8_t stat = 0x46; // 0100 0110

    MemoryMap mem_map;
    Video video(mem_map);

    // Set coincidence flag to true
    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));
    EXPECT_TRUE(video.get_coincidence_flag());
    EXPECT_TRUE(video.coincidence_interrupt_enabled());

    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A LCDC status interrupt should be triggered
    EXPECT_EQ(0x02, video.read_io_register(IF));
}


TEST(Video, GetBackgroundPalette) {
    // LIGHT GRAY, BLACK, WHITE, DARK GRAY
    uint8_t bgp = 0x72; // 0111 0010

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(BGP, bgp);
    EXPECT_EQ(bgp, video.read_io_register(BGP));

    Palette palette = video.get_background_palette();
    EXPECT_EQ(DARK_GRAY, palette.colour0);
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}


TEST(Video, GetSpritePalette0) {
    // LIGHT GRAY, BLACK, WHITE
    uint8_t obp0 = 0x70; // 0111 0000

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(OBP0, obp0);
    EXPECT_EQ(obp0, video.read_io_register(OBP0));

    Palette palette = video.get_sprite_palette_0();
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}


TEST(Video, GetSpritePalette1) {
    // LIGHT GRAY, BLACK, WHITE
    uint8_t obp1 = 0x70; // 0111 0000

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(OBP1, obp1);
    EXPECT_EQ(obp1, video.read_io_register(OBP1));

    Palette palette = video.get_sprite_palette_1();
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}


TEST(Video, LoadTile) {
    // 0, 0, 0, 0, 0, 0, 0, 0
    // 0, 1, 1, 1, 1, 1, 1, 0
    // 0, 1, 2, 2, 2, 2, 1, 0
    // 0, 1, 2, 2, 2, 2, 1, 0
    // 0, 1, 2, 2, 2, 2, 1, 0
    // 0, 1, 2, 2, 2, 2, 1, 0
    // 0, 1, 1, 1, 1, 1, 1, 0
    // 0, 0, 0, 0, 0, 0, 0, 0
    uint16_t starting_address = 0x8000;

    MemoryMap memory_map;

    uint8_t lsb;
    uint8_t msb;
    for (int y = 0; y < TILE_HEIGHT; y++) {
        if (y == 0 || y == 7) {
            lsb = 0x00; // 0000 0000
            msb = 0x00; // 0000 0000
        }
        else if (y == 1 || y == 6) {
            lsb = 0x7E; // 0111 1110
            msb = 0x00; // 0000 0000
        }
        else {
            lsb = 0x42; // 0100 0010
            msb = 0x3C; // 0011 1100
        }

        memory_map.write(starting_address + y, lsb);
        memory_map.write(starting_address + y + 1, msb);
    }

    Tile tile(starting_address, memory_map);

    for (int y = 0; y < TILE_HEIGHT; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            if (y == 0 || y == 7) {
                EXPECT_EQ(Colour0, tile.get_pixel(x, y));
            }
            else if (y == 1 || y == 6) {
                if (x == 0 || x == 7) {
                    EXPECT_EQ(Colour0, tile.get_pixel(x, y));
                }
                else {
                    EXPECT_EQ(Colour1, tile.get_pixel(x, y));
                }
            }
            else {
                if (x == 0 || x == 7) {
                    EXPECT_EQ(Colour0, tile.get_pixel(x, y));
                }
                else if (x == 1 || x == 6) {
                    EXPECT_EQ(Colour1, tile.get_pixel(x, y));
                }
                else {
                    EXPECT_EQ(Colour2, tile.get_pixel(x, y));
                }
            }
        }
    }
}