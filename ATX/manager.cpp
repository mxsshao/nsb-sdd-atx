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

void Manager::HandleEvents(ALLEGRO_EVENT &ev)
{
	gCanvas->ProcessDelayedDeletes();
	gInput->ProcessMessage(ev);
}

void Manager::Cleanup()
{
	al_destroy_event_queue(aEventQueue);
	al_destroy_display(aDisplay);
}