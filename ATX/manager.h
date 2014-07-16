#pragma once

#include "global.h"
#include "module_base.h"

class Manager
{
protected:
	Manager() {};

private:
	static Manager mManager;

public:
	static Manager* getInstance() {return &mManager;};

	bool bDone;
	std::vector<Module::Base*> nModules;
	ALLEGRO_DISPLAY* aDisplay;
	ALLEGRO_EVENT_QUEUE* aEventQueue;

};