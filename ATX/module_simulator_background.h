#pragma once

#include "global.h"

namespace Module
{
namespace Simulator
{
	class Background
	{
	private:
		ALLEGRO_BITMAP* nImages[5][5];

		int iStartX;
		int iEndX;
		int iStartY;
		int iEndY;

	public:
		Background() {};

		void Load();
		void Update(int iDisplayW, int iDisplayH, int iOffsetW, int iOffsetH, Structs::Camera* sCamera);
		void Render();
		void Cleanup();
	};
};
};