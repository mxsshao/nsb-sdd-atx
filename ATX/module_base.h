#pragma once

#include "global.h"

class Manager;

namespace Module
{
	class Base : public Gwen::Event::Handler
	{
	protected:
		Base() {};

	private:
		static Manager* mManager;

	public:
		virtual void load() {};
		virtual void initialize() {};
		virtual void resize() {};
		virtual void pause() {};
		virtual void resume() {};
		virtual void handleEvents(ALLEGRO_EVENT &ev) {};
		virtual void render() {};
		virtual void cleanup() {};
	};
};