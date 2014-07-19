#pragma once

#include "global.h"
#include "manager.h"
#include "module_simulator_background.h"

namespace Module
{
namespace Simulator
{
	class Main : public Module::Base
	{
	private:
		Background* mBackground;

		ALLEGRO_BITMAP* aScreen;

		bool nKeys [5];
		enum nKeys {UP, DOWN, LEFT, RIGHT, LSHIFT};
		bool bRightClick;

		int iDisplayW;
		int iDisplayH;
		int iOffsetW;
		int iOffsetH;

		Structs::Camera sCamera;
		ALLEGRO_TRANSFORM aTransform;

	public:
		Main();

		void Load();
		void Initialize();
		void Resize();
		void HandleEvents(ALLEGRO_EVENT &ev);
		void Render();
		void Cleanup();
	};
};
};