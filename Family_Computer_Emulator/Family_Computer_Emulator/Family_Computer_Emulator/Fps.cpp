#include "Fps.h"

Fps::Fps(MyDirectXSystem *myDirectXSystem/*, LPD3DXSPRITE sprite*/)// : sprite(sprite)
{
	fps_number = new FpsFont(myDirectXSystem);
}

Fps::~Fps()
{
	delete fps_number;
}

void Fps::draw_fps()
{
	char fps_str[255];
	sprintf_s(fps_str, _T("%.2lf"), fps);
	fps_number->draw_number_rightup(_T(fps_str), WINDOW_WIDTH, WINDOW_HEIGHT - fps_number->get_number_image_height());
}

void Fps::update()
{
	if (frame == 0) {
		start_time = timeGetTime();
	}
	else if (frame >= FPS)
	{
		DWORD total_time = timeGetTime() - start_time;

		fps = 1000.0 / (total_time / (double) FPS);

		start_time = timeGetTime();

		frame = 0;
	}

	frame++;
}

void Fps::wait()
{
	DWORD total_time = timeGetTime() - start_time;
	DWORD wait_time = (frame * 1000 / FPS) - total_time;

	if ((signed long) wait_time > 0) {
		Sleep(wait_time);
	}
}
