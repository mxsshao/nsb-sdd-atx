#pragma once

#include "global.h"
#include "module_simulator_aircraft.h"

namespace Module
{
namespace Simulator
{
	class Main;
	class Interface : public Gwen::Event::Handler
	{
	private:
		Main* mMain;
		std::list<Aircraft*>::iterator iter;
		Gwen::Controls::Base* gBase;

		Gwen::Controls::WindowControl* winFlights;
		void WinFlightsResize();
		Gwen::Controls::WindowControl* winTest;
		Gwen::Controls::Button* btnMenu;
		void BtnMenuClick() {};
		Gwen::Controls::Button* btnOne;
		void BtnOneClick() {};
		Gwen::Controls::Button* btnTwo;
		Gwen::Controls::Button* btnThree;
		void BtnThreeClick() {winFlights->Show();};
		Gwen::Controls::Button* btnFour;
		void BtnFourClick() {winRadar->Show();};

		Gwen::Controls::WindowControl* winRadar;
		Gwen::Controls::ImagePanel* imgRadar;
		ALLEGRO_BITMAP* aRadarImage;
		ALLEGRO_BITMAP* aRadarRender;
		void WinRadarResize() {};

		Gwen::Controls::WindowControl* winText;
		void WinTextResize() {};
		std::list<Gwen::Controls::Label*> nLabels;

	public:
		Interface(Gwen::Controls::Base* pBase, Main* pMain) {gBase = pBase; mMain = pMain;};

		void Load();
		void Resize();
		void Render();
		void Cleanup();
	};
};
};