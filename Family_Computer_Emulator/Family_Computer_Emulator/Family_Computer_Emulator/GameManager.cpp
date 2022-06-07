#include "GameManager.h"

GameManager::GameManager(MyDirectXSystem *myDirectXSystem, Key *key/*, LPD3DXSPRITE sprite*/) :
	myDirectXSystem(myDirectXSystem), key(key)//, sprite(sprite)
{
}

GameManager::~GameManager()
{
	delete fc;
}

/*
ƒQ[ƒ€‚Ìˆ—‚ð‚·‚é
*/
void GameManager::execute_game_process()
{
	if (Main::ready_read_ROM_flag == true) {
		delete fc;

		//M_debug_printf("Main::ROMFilePath = %s\n", Main::ROMFilePath);
		fc = new FC(Main::ROMFilePath, key);

		Main::ready_read_ROM_flag = false;
	}

	if (fc != nullptr) {
		if (fc->get_FATAL_ERROR_FLAG() == true) {
			delete fc;
			fc = nullptr;

			Main::ROM_loaded_flag = false;
		}
	}

	if (fc != nullptr) {
		fc->execute_all(myDirectXSystem);
	}
	else {
		MyDirectXDraw::draw_box_leftup(myDirectXSystem, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);
	}
}
