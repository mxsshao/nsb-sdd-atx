#include "module_simulator_main.h"

using namespace Module::Simulator;

Main::Main()
{
	mBackground = new Background();
}

void Main::Load()
{
	mBackground->Load();
}

void Main::Initialize()
{
	std::cout << "MODULE		-Simulation" << std::endl;

	bRightClick = false;

	Resize();
}
void Main::Resize()
{
	iDisplayW = al_get_display_width(mManager->aDisplay);
	iDisplayH = al_get_display_height(mManager->aDisplay);
	iOffsetW = iDisplayW/2;
	iOffsetH = iDisplayH/2;

	if (aScreen)
	{
		al_destroy_bitmap(aScreen);
	};
	aScreen = al_create_bitmap(iDisplayW, iDisplayH);
}
void Main::HandleEvents(ALLEGRO_EVENT &ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		al_identity_transform(&aTransform);
		al_scale_transform(&aTransform, 1.0f / (sCamera.fZ + 1.0f), 1.0f / (sCamera.fZ + 1.0f));
		al_translate_transform(&aTransform, iOffsetW - sCamera.fX / (sCamera.fZ + 1.0f), iOffsetH - sCamera.fY / (sCamera.fZ + 1.0f));

		mBackground->Update(iDisplayW, iDisplayH, iOffsetW, iOffsetH, &sCamera);
		//update();
		//std::cout << label->Height() << std::endl;
		//std::cout << label->m_Text->Height() << std::endl;
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_RIGHT:
			nKeys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			nKeys[LEFT] = true;
			break;
		case ALLEGRO_KEY_UP:
			nKeys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			nKeys[DOWN] = true;
			break;
		case ALLEGRO_KEY_LSHIFT:
			nKeys[LSHIFT] = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_RIGHT:
			nKeys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			nKeys[LEFT] = false;
			break;
		case ALLEGRO_KEY_UP:
			nKeys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			nKeys[DOWN] = false;
			break;
		case ALLEGRO_KEY_LSHIFT:
			nKeys[LSHIFT] = false;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (ev.mouse.button == 2 && mManager->gBase->IsHovered())
		{
			bRightClick = true;
			//al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE);
			mManager->gBase->SetCursor(Gwen::CursorType::SizeAll);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (ev.mouse.button == 2)
		{
			bRightClick = false;
			//al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			mManager->gBase->SetCursor(Gwen::CursorType::Normal);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		if (ev.mouse.dz != 0 && mManager->gBase->IsHovered())
		{
			sCamera.fZ -= ev.mouse.dz / 3.0f;

			if (sCamera.fZ < 0)
			{
				sCamera.fZ = 0;
			}
		}
		if (bRightClick && mManager->gBase->IsHovered())
		{
			sCamera.fX -= ev.mouse.dx * (sCamera.fZ + 1.0);
			sCamera.fY -= ev.mouse.dy * (sCamera.fZ + 1.0);
			//breakaway();
		}
	}
}
void Main::Render()
{
	ALLEGRO_BITMAP* aBack = al_get_target_bitmap();
	al_set_target_bitmap(aScreen);
	al_clear_to_color(al_map_rgb(0,0,0));

	al_use_transform(&aTransform);

	mBackground->Render();
	//al_draw_circle(sCamera.fX, sCamera.fY, 10, al_map_rgb(255,0,255), 10);

	al_set_target_bitmap(aBack);
	al_draw_bitmap(aScreen, 0, 0, 0);
}
void Main::Cleanup()
{
	mBackground->Cleanup();
	delete mBackground;
	al_destroy_bitmap(aScreen);
}