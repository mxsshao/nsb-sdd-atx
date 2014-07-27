#pragma once

#include "global.h"
#include "manager.h"
#include "module_simulator_background.h"
#include "module_simulator_aircraft.h"
#include "module_simulator_interface.h"

namespace Module
{
namespace Simulator
{
	class Main : public Module::Base
	{
	private:
		Background* mBackground;
		Interface* mInterface;
		std::list<Aircraft*>::iterator iter;

		ALLEGRO_BITMAP* aScreen;

		bool nKeys [5];
		enum nKeys {UP, DOWN, LEFT, RIGHT, LSHIFT};
		bool bRightClick;

		Structs::Camera sCamera;
		ALLEGRO_TRANSFORM aTransform;

	public:
		Main();

		std::list<Aircraft*> nAircraft;
		Structs::Waypoint nWaypoints[20];

		int iDisplayW;
		int iDisplayH;
		int iOffsetW;
		int iOffsetH;

		void Load();
		void Initialize();
		void Resize();
		void HandleEvents(ALLEGRO_EVENT &ev);
		void Update();
		void Render();
		void Cleanup();
	};
};
};