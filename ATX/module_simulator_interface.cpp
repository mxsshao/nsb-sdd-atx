#include "module_simulator_interface.h"
#include "module_simulator_main.h"

using namespace Module::Simulator;

void Interface::Load()
{
	winFlights = new Gwen::Controls::WindowControl(gBase);
	winFlights->MakeScroll();
	winFlights->GetScroll()->SetScroll(false, true);
	winFlights->GetScroll()->onResize.Add(this, &Module::Simulator::Interface::WinFlightsResize);
	winFlights->SetTitle(L"Flight Information");
	winFlights->SetMinimumSize(Gwen::Point(200,200));
	winFlights->onResize.Add(this, &Module::Simulator::Interface::WinFlightsResize);

	winTest = new Gwen::Controls::WindowControl(gBase);
	winTest->SetTitle(L"Test Control");
	winTest->SetClosable(false);
	winTest->DisableResizing();

	btnMenu = new Gwen::Controls::Button(winTest);
	btnMenu->SetText(L"MENU");
	btnMenu->SetSize(300, 30);
	btnMenu->Dock(Gwen::Pos::Top);
	btnMenu->onPress.Add(this, &Module::Simulator::Interface::BtnMenuClick);

	btnOne = new Gwen::Controls::Button(winTest);
	btnOne->SetText(L"Add Flight");
	btnOne->SetSize(200, 30);
	btnOne->Dock(Gwen::Pos::Top);
	btnOne->onPress.Add(this, &Module::Simulator::Interface::BtnOneClick);

	btnTwo = new Gwen::Controls::Button(winTest);
	btnTwo->SetText(L"Display Symbols");
	btnTwo->SetIsToggle(true);
	//button2->SetToggleState(true);
	btnTwo->SetSize(200, 30);
	btnTwo->Dock(Gwen::Pos::Top);

	btnThree = new Gwen::Controls::Button(winTest);
	btnThree->SetText(L"Show Flight Window");
	btnThree->SetSize(300, 30);
	btnThree->Dock(Gwen::Pos::Top);
	btnThree->onPress.Add(this, &Module::Simulator::Interface::BtnThreeClick);

	btnFour = new Gwen::Controls::Button(winTest);
	btnFour->SetText(L"Show Radar Window");
	btnFour->SetSize(300, 30);
	btnFour->Dock(Gwen::Pos::Top);
	btnFour->onPress.Add(this, &Module::Simulator::Interface::BtnFourClick);

	winRadar = new Gwen::Controls::WindowControl(gBase);
	winRadar->SetTitle(L"Radar");
	winRadar->DisableResizing();
	
	aRadarImage = al_load_bitmap("Resources/radar.png");
	aRadarRender = al_create_bitmap(256,256);

	imgRadar = new Gwen::Controls::ImagePanel(winRadar);
	imgRadar->SetImage(aRadarRender);
}

void Interface::Resize()
{
	winFlights->SetSize(400, 300);
	winFlights->SetPos(mMain->iDisplayW - 400, mMain->iDisplayH-300);

	winTest->SetSize(200, 300);
	winTest->SetPos(0, mMain->iDisplayH-300);

	winRadar->SetSize(256, 256 + 28);
	winRadar->SetPos(0,0);
	imgRadar->SetSize(winRadar->GetBounds().w - 8, winRadar->GetBounds().w - 8);
	imgRadar->Dock(Gwen::Pos::Top);
}

void Interface::WinFlightsResize()
{
	if (!mMain->nAircraft.empty())
	{
		for (iter = mMain->nAircraft.begin(); iter != mMain->nAircraft.end(); iter++)
		{
			(*iter)->Resize();
		}
	}
}

void Interface::Render()
{
	ALLEGRO_BITMAP* aBack = al_get_target_bitmap();
	al_set_target_bitmap(aRadarRender);
	al_hold_bitmap_drawing(true);
	al_clear_to_color(al_map_rgba(0,0,0,0));
	al_draw_bitmap_region(aRadarImage, 0, 0, 256, 256, 0, 0, 0);

	if (!mMain->nAircraft.empty())
	{
		for (iter = mMain->nAircraft.begin(); iter != mMain->nAircraft.end(); iter++)
		{
			//if ((*iter)->getSelected())
			//{
			//	al_draw_tinted_scaled_rotated_bitmap_region(radarImage, 4, 256, 4, 4, al_map_rgb_f(1,1,1), 2, 2, (*iter)->getX() / 10.0f,  (*iter)->getY() / 10.0f, 1.0f, 1.0f, 0, 0);
			//}
			//else
			//{
				al_draw_tinted_scaled_rotated_bitmap_region(aRadarImage, 0, 256, 4, 4, al_map_rgb_f(1,1,1), 2, 2, (*iter)->GetX() / 10.0f,  (*iter)->GetY() / 10.0f, 1.0f, 1.0f, 0, 0);
			//}
		}
	}

	al_draw_bitmap_region(aRadarImage, 256, 0, 256, 256, 0, 0, 0);
	al_hold_bitmap_drawing(false);

	al_set_target_bitmap(aBack);
	gBase->GetCanvas()->RenderCanvas();
}

void Interface::Cleanup()
{
	winFlights->DelayedDelete();
	winTest->DelayedDelete();
	winRadar->DelayedDelete();
	al_destroy_bitmap(aRadarImage);
}