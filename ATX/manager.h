#pragma once

#include "global.h"
#include "module_base.h"

class Manager
{
protected:
	Manager() {Module::Base::mManager = this;};

private:
	static Manager mManager;
	Gwen::Renderer::Allegro* gRenderer;
	Gwen::Skin::TexturedBase* gDefaultSkin;
	Gwen::Controls::Canvas* gCanvas;
	Gwen::Input::Allegro* gInput;

public:
	static Manager* GetInstance() {return &mManager;};

	bool bDone;
	std::vector<Module::Base*> nModules;
	ALLEGRO_DISPLAY* aDisplay;
	ALLEGRO_EVENT_QUEUE* aEventQueue;

	Gwen::Controls::Base* gBase;

	void InitializeGwen();
	void ChangeModule(Module::Base* pModule);
	void HandleEvents(ALLEGRO_EVENT &ev);
	void Render();
	void Cleanup();
};