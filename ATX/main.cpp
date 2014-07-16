#include "global.h"
#include "manager.h"

int main(int argc, char **argv)
{
	float fGameTime = 0;
	int iFrames = 0;
	int iGameFPS = 0;

	Manager* mManager = Manager::getInstance();
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
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

	//RESOURCES
	aFont = al_load_font("Resources/DolceVita.ttf", 24, 0);

	//LOADING SCREEN
	al_draw_text(aFont, al_map_rgb(255, 0, 255), 5, 5, 0, "LOADING");
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

}