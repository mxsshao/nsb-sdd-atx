#pragma once

#include "global.h"

class Manager;

namespace Module
{
	class Base : public Gwen::Event::Handler
	{
	public:
		Base() {};

		static Manager* mManager;
		virtual void Load() {};
		virtual void Initialize() {};
		virtual void Resize() {};
		virtual void Pause() {};
		virtual void Resume() {};
		virtual void HandleEvents(ALLEGRO_EVENT &ev) {};
		virtual void Render() {};
		virtual void Cleanup() {};
	};
};