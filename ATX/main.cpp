#include "global.h"
#include "manager.h"
#include "module_simulator_main.h"
#include "module_scenario_main.h"

int main(int argc, char **argv)
{
	float fGameTime = 0;
	int iFrames = 0;
	int iGameFPS = 0;

	Manager* mManager = Manager::GetInstance();
	mManager->bDone = false;

	//ALLEGRO INIT
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "A01:", "Error loading Allegro.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	std::cout << "LIBRARY INIT	-Allegro 5.1.7" << std::endl;

	//ALLEGRO ADDONS
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	ALLEGRO_TIMER* aTimer;
	ALLEGRO_FONT* aFont;

	//Display
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	//al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	mManager->aDisplay = al_create_display(1280, 720);
	if (!mManager->aDisplay)
	{
		al_show_native_message_box(NULL, "ERROR", "A02:", "Error creating display.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_toggle_display_flag(mManager->aDisplay, ALLEGRO_FULLSCREEN_WINDOW, false);

	std::cout << "DISPLAY CREATE	-w" << al_get_display_width(mManager->aDisplay) << " -h" << al_get_display_height(mManager->aDisplay) << std::endl;

	//IMAGE SETTINGS
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP | ALLEGRO_CONVERT_BITMAP);

	//RESOURCES
	aFont = al_load_font("Resources/DolceVita.ttf", 24, 0);

	//LOADING SCREEN
	al_draw_text(aFont, al_map_rgb(255, 0, 255), 5, 5, 0, "LOADING");
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	mManager->InitializeGwen();
	std::cout << "LIBRARY INIT	-Gwen GUI" << std::endl;

	//EVENT INIT
	mManager->aEventQueue = al_create_event_queue();
	aTimer = al_create_timer(1.0 / 60);

	//EVENT SOURCE
	al_register_event_source(mManager->aEventQueue, al_get_timer_event_source(aTimer));
	al_register_event_source(mManager->aEventQueue, al_get_display_event_source(mManager->aDisplay));
	al_register_event_source(mManager->aEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mManager->aEventQueue, al_get_mouse_event_source());

	al_start_timer(aTimer);

	//mManager->ChangeModule(new Module::Simulator::Main());
	mManager->ChangeModule(new Module::Scenario::Main());

	//EVENT LOOP
	while (!mManager->bDone)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(mManager->aEventQueue, &ev);

		mManager->HandleEvents(ev);

		if (al_is_event_queue_empty(mManager->aEventQueue))
		{
			mManager->Render();

			iFrames ++;
			if(al_current_time() - fGameTime >= 1)
			{
				fGameTime = al_current_time();
				iGameFPS = iFrames;
				iFrames = 0;
			}

			al_draw_textf(aFont, al_map_rgb(255, 255, 0), 10, 680, 0, "FPS: %i", iGameFPS);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 124, 150));
		}
	}

	al_stop_timer(aTimer);
	al_destroy_timer(aTimer);
	al_destroy_font(aFont);
	mManager->Cleanup();
	return 0;
}