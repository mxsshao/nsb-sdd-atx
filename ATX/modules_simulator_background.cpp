#include "module_simulator_background.h"

using namespace Module::Simulator;

void Background::Load()
{
	nImages[0][0] = al_load_bitmap("Resources/bg.png");
	nImages[0][1] = al_load_bitmap("Resources/bg.png");
	nImages[0][2] = al_load_bitmap("Resources/bg.png");
	nImages[0][3] = al_load_bitmap("Resources/bg.png");
	nImages[0][4] = al_load_bitmap("Resources/bg.png");
	nImages[1][0] = al_load_bitmap("Resources/bg.png");
	nImages[1][1] = al_load_bitmap("Resources/bg.png");
	nImages[1][2] = al_load_bitmap("Resources/bg.png");
	nImages[1][3] = al_load_bitmap("Resources/bg.png");
	nImages[1][4] = al_load_bitmap("Resources/bg.png");
	nImages[2][0] = al_load_bitmap("Resources/bg.png");
	nImages[2][1] = al_load_bitmap("Resources/bg.png");
	nImages[2][2] = al_load_bitmap("Resources/bg.png");
	nImages[2][3] = al_load_bitmap("Resources/bg.png");
	nImages[2][4] = al_load_bitmap("Resources/bg.png");
	nImages[3][0] = al_load_bitmap("Resources/bg.png");
	nImages[3][1] = al_load_bitmap("Resources/bg.png");
	nImages[3][2] = al_load_bitmap("Resources/bg.png");
	nImages[3][3] = al_load_bitmap("Resources/bg.png");
	nImages[3][4] = al_load_bitmap("Resources/bg.png");
	nImages[4][0] = al_load_bitmap("Resources/bg.png");
	nImages[4][1] = al_load_bitmap("Resources/bg.png");
	nImages[4][2] = al_load_bitmap("Resources/bg.png");
	nImages[4][3] = al_load_bitmap("Resources/bg.png");
	nImages[4][4] = al_load_bitmap("Resources/bg.png");

}

void Background::Update(int iDisplayW, int iDisplayH, int iOffsetW, int iOffsetH, Structs::Camera* sCamera)
{
	iStartX = floor((sCamera->fX - (iOffsetW * (sCamera->fZ + 1.0f))) / 512.0f);
	iStartY = floor((sCamera->fY - (iOffsetH * (sCamera->fZ + 1.0f))) / 512.0f);

	if (iStartX < 0)
		iStartX = 0;
	if (iStartY < 0)
		iStartY = 0;

	int iWidth = ceil(iDisplayW * (sCamera->fZ + 1.0f) / 512.0f);
	int iHeight = ceil(iDisplayW * (sCamera->fZ + 1.0f) / 512.0f);

	iEndX = iStartX + iWidth;
	iEndY = iStartY + iHeight;

	if (iEndX > 4)
		iEndX = 4;
	if (iEndY > 2)
		iEndY = 4;
}

void Background::Render()
{
	int iterX;
	int iterY;
	for (iterX = iStartX; iterX <= iEndX; iterX++)
	{
		for (iterY = iStartY; iterY <= iEndY; iterY++)
		{
			al_draw_bitmap(nImages[iterX][iterY], iterX * 512.0f, iterY * 512.0f, 0);
		}
	}
}

void Background::Cleanup()
{
	int i;
	int j;
	for (i = 0; i <= 4; i++)
	{
		for (j = 0; j <= 4; j++)
		{
			al_destroy_bitmap(nImages[i][j]);
		}
	}
}