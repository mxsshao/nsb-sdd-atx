#include "module_simulator_main.h"

using namespace Module::Simulator;

Main::Main()
{
	mBackground = new Background();
	mInterface = new Interface(Manager::GetInstance()->gBase, this);
}

void Main::Load()
{
	mBackground->Load();
	mInterface->Load();
	Aircraft::Load(this);

	nWaypoints[0] = Structs::Waypoint(100,100,0);
	nWaypoints[1] = Structs::Waypoint(200,200,0);
	nWaypoints[2] = Structs::Waypoint(300,300,0);
	nWaypoints[3] = Structs::Waypoint(1000,600,0);
	nWaypoints[4] = Structs::Waypoint(1000,300,0);

	nWaypoints[0].nConnected.push_back(1);
	//nWaypoints[0].nConnected.push_back(4);
	nWaypoints[1].nConnected.push_back(0);
	//nWaypoints[1].nConnected.push_back(4);
	nWaypoints[1].nConnected.push_back(2);
	nWaypoints[2].nConnected.push_back(1);
	nWaypoints[2].nConnected.push_back(3);
	nWaypoints[2].nConnected.push_back(4);
	nWaypoints[3].nConnected.push_back(2);
	nWaypoints[3].nConnected.push_back(4);
	//nWaypoints[4].nConnected.push_back(0);
	//nWaypoints[4].nConnected.push_back(1);
	nWaypoints[4].nConnected.push_back(2);
	nWaypoints[4].nConnected.push_back(3);
}

void Main::Initialize()
{
	std::cout << "MODULE		-Simulation" << std::endl;

	nAircraft.push_back(new Aircraft(0, 0, 0, 0, 0.4f, 120.0f, 4, "TG3802"));
	bRightClick = false;

	nKeys[UP] = false;
	nKeys[DOWN] = false;
	nKeys[LEFT] = false;
	nKeys[RIGHT] = false;
	nKeys[LSHIFT] = false;

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

	mInterface->Resize();
}
void Main::HandleEvents(ALLEGRO_EVENT &ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		Update();
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

void Main::Update()
{
	//AIRCRAFT
	if (!nAircraft.empty())
	{
		for (iter = nAircraft.begin(); iter != nAircraft.end();)
		{
			(*iter)->Update();

			/*if ((*iter)->done)
			{
				bool shouldSelect = (*iter)->getSelected();
				if (shouldSelect)
					breakaway();
				delete(*iter);
				nAircraft.erase(iter++);
				if (iter != nAircraft.end() && shouldSelect)
				{
					(*iter)->select();
				}
			}
			else
			{*/
				iter++;
			//}
		}
	}

	//CAMERA
	if (nKeys[LSHIFT])
	{
		if ((nKeys[RIGHT] && nKeys[LEFT]) || (!nKeys[RIGHT] && !nKeys[LEFT]))
		{
		}
		else if (nKeys[RIGHT])
		{
			sCamera.fX += 30.0f * (sCamera.fZ + 1);
			//breakaway();
		}
		else if (nKeys[LEFT])
		{
			sCamera.fX -= 30.0f * (sCamera.fZ + 1);
			//breakaway();
		}

		if ((nKeys[UP] && nKeys[DOWN]) || (!nKeys[UP] && !nKeys[DOWN]))
		{
		}
		else if (nKeys[UP])
		{
			sCamera.fY -= 30.0f * (sCamera.fZ + 1);
			//breakaway();
		}
		else if (nKeys[DOWN])
		{
			sCamera.fY += 30.0f * (sCamera.fZ + 1);
			//breakaway();
		}
	}
	else
	{
		if ((nKeys[RIGHT] && nKeys[LEFT]) || (!nKeys[RIGHT] && !nKeys[LEFT]))
		{
		}
		else if (nKeys[RIGHT])
		{
			sCamera.fX += 10.0f * (sCamera.fZ + 1);
			//breakaway();
		}
		else if (nKeys[LEFT])
		{
			sCamera.fX -= 10.0f * (sCamera.fZ + 1);
			//breakaway();
		}

		if ((nKeys[UP] && nKeys[DOWN]) || (!nKeys[UP] && !nKeys[DOWN]))
		{
		}
		else if (nKeys[UP])
		{
			sCamera.fY -= 10.0f * (sCamera.fZ + 1);
			//breakaway();
		}
		else if (nKeys[DOWN])
		{
			sCamera.fY += 10.0f * (sCamera.fZ + 1);
			//breakaway();
		}
	}

	al_identity_transform(&aTransform);
	al_scale_transform(&aTransform, 1.0f / (sCamera.fZ + 1.0f), 1.0f / (sCamera.fZ + 1.0f));
	al_translate_transform(&aTransform, iOffsetW - sCamera.fX / (sCamera.fZ + 1.0f), iOffsetH - sCamera.fY / (sCamera.fZ + 1.0f));
	mBackground->Update(iDisplayW, iDisplayH, iOffsetW, iOffsetH, &sCamera);
}

void Main::Render()
{
	ALLEGRO_BITMAP* aBack = al_get_target_bitmap();
	al_set_target_bitmap(aScreen);
	al_clear_to_color(al_map_rgb(0,0,0));

	al_use_transform(&aTransform);

	mBackground->Render();

	//AIRCRAFT
	if (!nAircraft.empty())
	{
		for (iter = nAircraft.begin(); iter != nAircraft.end(); iter++)
		{
			(*iter)->Render();
		}
	}

	al_set_target_bitmap(aBack);
	al_draw_bitmap(aScreen, 0, 0, 0);

	mInterface->Render();
}
void Main::Cleanup()
{
	mBackground->Cleanup();
	mInterface->Cleanup();
	delete mBackground;
	delete mInterface;
	al_destroy_bitmap(aScreen);
}