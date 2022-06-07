#pragma once

#include "MyDirectXSystem.h"
#include "MyDirectXImage.h"
#include "Key.h"
#include "FC.h"

class GameManager
{
private:
	FC* fc = nullptr;

	MyDirectXSystem *myDirectXSystem;

	//LPD3DXSPRITE sprite;

	Key *key;
public:
	GameManager(MyDirectXSystem *myDirectXSystem, Key *key/*, LPD3DXSPRITE sprite*/);
	~GameManager();

	void execute_game_process();
};
