#pragma once

#include "global.h"
#include "module_base.h"

class Manager
{
protected:
	Manager() {Module::Base::mManager = this;};

private:
	static Manager mManager;

	Module::Base* mPrevious;

	Gwen::Renderer::Allegro* gRenderer;
	Gwen::Skin::TexturedBase* gDefaultSkin;
	Gwen::Controls::Canvas* gCanvas;
	Gwen::Input::Allegro* gInput;

	ALLEGRO_MUTEX* aMutex;
	ALLEGRO_COND* aCond;
	bool bReady;
	ALLEGRO_THREAD* aThread;
	static void* Thread(ALLEGRO_THREAD* aThread, void* arg);

public:
	static Manager* GetInstance() {return &mManager;};

	bool bDone;
	std::vector<Module::Base*> nModules;
	ALLEGRO_DISPLAY* aDisplay;
	ALLEGRO_EVENT_QUEUE* aEventQueue;

	Gwen::Controls::Base* gBase;

	ALLEGRO_BITMAP* aLoadBackground;
	ALLEGRO_BITMAP* aLoadAnimation;
	ALLEGRO_MUTEX* GetMutex() {return aMutex;};
	ALLEGRO_COND* GetCond() {return aCond;};
	void SetReady(bool pReady) {bReady = pReady;};

	void InitializeGwen();
	void ChangeModule(Module::Base* pModule);
	void HandleEvents(ALLEGRO_EVENT &ev);
	void Render();
	void Cleanup();
};