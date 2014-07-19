#include "manager.h"

Manager Manager::mManager;

void Manager::InitializeGwen()
{
	gRenderer = new Gwen::Renderer::Allegro();
	gDefaultSkin = new Gwen::Skin::TexturedBase(gRenderer);
	gDefaultSkin->SetRender(gRenderer);
	gDefaultSkin->Init("Resources/defaultskin2.png");
	gDefaultSkin->SetDefaultFont(L"Resources/OpenSans.ttf", 14);
	gCanvas = new Gwen::Controls::Canvas(gDefaultSkin);
	gCanvas->SetSize(al_get_display_width(aDisplay), al_get_display_height(aDisplay));
	gCanvas->SetDrawBackground(false);

	gBase = new Gwen::Controls::Base(gCanvas);
	gBase->SetPos(0,0);
	gBase->SetSize(al_get_display_width(aDisplay), al_get_display_height(aDisplay));
	gBase->SetCursor(Gwen::CursorType::Normal);

	gInput = new Gwen::Input::Allegro();
	gInput->Initialize(gCanvas);
}

void Manager::ChangeModule(Module::Base* pModule)
{
	if (!nModules.empty())
	{
		nModules.back()->Cleanup();
		delete nModules.back();
		nModules.pop_back();
	}

	nModules.push_back(pModule);
	nModules.back()->Load();
	nModules.back()->Initialize();

	al_flush_event_queue(aEventQueue);
}

void Manager::HandleEvents(ALLEGRO_EVENT &ev)
{
	gCanvas->ProcessDelayedDeletes();
	gInput->ProcessMessage(ev);

	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		bDone = true;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
	{
		al_resize_display(ev.display.source, ev.display.width, ev.display.height);
		gCanvas->SetSize(ev.display.width, ev.display.height);
		gBase->SetSize(ev.display.width, ev.display.height);
		if(!nModules.empty())
		{
			nModules.back()->Resize();
		}
		std::cout << "DISPLAY RESIZE	-w" << al_get_display_width(aDisplay) << " -h" << al_get_display_height(aDisplay) << std::endl;
	}
	else
	{
		if(!nModules.empty())
		{
			nModules.back()->HandleEvents(ev);
		}
	}
}

void Manager::Render()
{
	nModules.back()->Render();
}

void Manager::Cleanup()
{
	al_destroy_event_queue(aEventQueue);
	al_destroy_display(aDisplay);
}