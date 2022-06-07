#pragma once

class Main
{
private:
	Main() {}
	~Main() {}
public:
	static bool draw_screen_up_down_flag;

	static bool ready_read_ROM_flag;
	static TCHAR ROMFilePath[MAX_PATH];

	static bool ROM_loaded_flag;
	static uint32_t PGM_size;
	static uint32_t CHR_size;
	static uint8_t Mapper;
	static uint8_t Mirror;

	static bool Show_FPS_Flag;
};
