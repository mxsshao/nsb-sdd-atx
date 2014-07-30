#include "manager.h"

Manager Manager::mManager;

void Manager::InitializeGwen()
{
	gRenderer = new Gwen::Renderer::Allegro();
	gDefaultSkin = new Gwen::Skin::TexturedBase(gRenderer);
	gDefaultSkin->SetRender(gRenderer);
	gDefaultSkin->Init("Resources/defaultskin.png");
	gDefaultSkin->SetDefaultFont(L"Resources/OpenSans.ttf", 14);
	gCanvas = new Gwen::Controls::Canvas(gDefaultSkin);
	gCanvas->SetSize(al_get_display_width(aDisplay), al_get_display_height(aDisplay));
	gCanvas->SetDrawBackground(false);

	gBase = new Gwen::Controls::Base(gCanvas);
	gBase->SetPos(0,0);
	gBase->SetSize(al_get_display_width(aDisplay), al_get_display_height(aDisplay));
	gBase->SetCursor(Gwen::CursorType::Normal);
	gBase->SetKeyboardInputEnabled(false);

	gInput = new Gwen::Input::Allegro();
	gInput->Initialize(gCanvas);

	aLoadBackground = al_load_bitmap("Resources/loading.png");
	aLoadAnimation = al_load_bitmap("Resources/loading2.png");
	bReady = false;
	aMutex = al_create_mutex();
	aCond = al_create_cond();
}

void Manager::ChangeModule(Module::Base* pModule)
{
	al_stop_samples();
	al_set_target_bitmap(NULL);

	aThread = al_create_thread(Thread, this);
	al_start_thread(aThread);

	al_lock_mutex(aMutex);
	while (!bReady)
	{
		al_wait_cond(aCond, aMutex);
	}
	al_unlock_mutex(aMutex);
	bReady = false;

	if (!nModules.empty())
	{
		nModules.back()->Cleanup();
		mPrevious = nModules.back();
		nModules.pop_back();
	}

	nModules.push_back(pModule);
	nModules.back()->Load();

	al_destroy_thread(aThread);
	
	al_set_target_bitmap(al_get_backbuffer(aDisplay));

	nModules.back()->Initialize();

	al_convert_bitmaps();

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
		if(mPrevious)
		{
			delete mPrevious;
			mPrevious = NULL;
		}
	}
}

void* Manager::Thread(ALLEGRO_THREAD* aThread, void* arg)
{
	Manager* mManager = (Manager*) arg;
	int iCount = 0;

	al_lock_mutex(mManager->GetMutex());

	al_set_target_bitmap(al_get_backbuffer(mManager->aDisplay));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP | ALLEGRO_CONVERT_BITMAP);

	ALLEGRO_BITMAP* aLoadBackground = al_clone_bitmap(mManager->aLoadBackground);
	ALLEGRO_BITMAP* aLoadAnimation = al_clone_bitmap(mManager->aLoadAnimation);

	float fSize = al_get_display_height(mManager->aDisplay) / 1080.0f;
	float fX = al_get_display_width(mManager->aDisplay) - (fSize * 150.0f) - 60.0f;
	float fY = al_get_display_height(mManager->aDisplay) - (fSize * 150.0f) - 60.0f;

	float fWidth;
	float fHeight;
	float fBackgroundX;
	float fBackgroundY;

	if (al_get_display_width(mManager->aDisplay) / float(al_get_display_height(mManager->aDisplay)) > 16.0f / 9.0f) //Height Limit
	{
		fWidth = al_get_display_width(mManager->aDisplay);
		fHeight = al_get_display_width(mManager->aDisplay) / 16.0f * 9.0f;
		fBackgroundX = 0;
		fBackgroundY = al_get_display_height(mManager->aDisplay) / 2.0f - fHeight / 2.0f;
	}
	else
	{
		fWidth = al_get_display_height(mManager->aDisplay) / 9.0f * 16.0f;
		fHeight = al_get_display_height(mManager->aDisplay);
		fBackgroundX = al_get_display_width(mManager->aDisplay) / 2.0f - fWidth / 2.0f;
		fBackgroundY = 0;
	}
	
	mManager->SetReady(true);
	al_broadcast_cond(mManager->GetCond());
	al_unlock_mutex(mManager->GetMutex());

	while(!al_get_thread_should_stop(aThread))
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(mManager->aEventQueue, &ev);

		al_lock_mutex(mManager->GetMutex());

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			iCount -= 5;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
		{
			if (!al_resize_display(ev.display.source, ev.display.width, ev.display.height))
			{
				al_show_native_message_box(NULL, "ERROR", "A03:", "Error resizing window.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
				mManager->bDone = true;
				return NULL;
			}
			mManager->gBase->SetSize(ev.display.width, ev.display.height);

			float fSize = al_get_display_height(mManager->aDisplay) / 1080.0f;
			float fX = al_get_display_width(mManager->aDisplay) - (fSize * 150.0f) - 60.0f;
			float fY = al_get_display_height(mManager->aDisplay) - (fSize * 150.0f) - 60.0f;

			if (al_get_display_width(mManager->aDisplay) / float(al_get_display_height(mManager->aDisplay)) > 16.0f / 9.0f) //Height Limit
			{
				fWidth = al_get_display_width(mManager->aDisplay);
				fHeight = al_get_display_width(mManager->aDisplay) / 16.0f * 9.0f;
				fBackgroundX = 0;
				fBackgroundY = al_get_display_height(mManager->aDisplay) / 2.0f - fHeight / 2.0f;
			}
			else
			{
				fWidth = al_get_display_height(mManager->aDisplay) / 9.0f * 16.0f;
				fHeight = al_get_display_height(mManager->aDisplay);
				fBackgroundX = al_get_display_width(mManager->aDisplay) / 2.0f - fWidth / 2.0f;
				fBackgroundY = 0;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			mManager->bDone = true;
			return NULL;
		}

		if (al_is_event_queue_empty(mManager->aEventQueue))
		{
			al_draw_scaled_bitmap(aLoadBackground, 0, 0, 1920, 1080, fBackgroundX, fBackgroundY, fWidth, fHeight, 0);
			al_draw_tinted_scaled_rotated_bitmap_region(aLoadAnimation, 0, 0, 282, 282, al_map_rgb(255,255,255), 141, 141, fX, fY, fSize, fSize, 0, 0);
			al_draw_tinted_scaled_rotated_bitmap_region(aLoadAnimation, 385, 280, 127, 232, al_map_rgb(255,255,255), 11, 116, fX, fY, fSize, fSize, iCount * ALLEGRO_PI / 180.0f, 0);
			//al_draw_tinted_scaled_rotated_bitmap_region(aLoadAnimation, 395, 280, 117, 232, al_map_rgb(255,255,255), 2, 116, fX, fY, fSize, fSize, (iCount + 180.0f) * ALLEGRO_PI / 180.0f, 0);
			//al_draw_scaled_rotated_bitmap(circleLarge, 50, 50, x, y, size, size, countA*ALLEGRO_PI/180, 0);
			//al_draw_scaled_rotated_bitmap(circleSmall, 50, 50, x, y, size, size, countB*ALLEGRO_PI/180, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		al_unlock_mutex(mManager->GetMutex());
	}

	al_destroy_bitmap(aLoadBackground);
	al_destroy_bitmap(aLoadAnimation);
	return NULL;
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