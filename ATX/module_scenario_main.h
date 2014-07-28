#pragma once

#include "global.h"
#include "manager.h"

namespace Module
{
namespace Scenario
{
	class Main : public Module::Base
	{
	private:
		Gwen::Controls::Base* gParent;
		Gwen::Controls::Base* gPadding;
		Gwen::Controls::ScrollControl* scrHorizontal;
		void ScrHorizontalMove();

		Gwen::Controls::WindowControl* winScenario;
		void WinScenarioCreate();
		void WinScenarioResize();
		Gwen::Controls::Button* btnScenarioStart;
		void BtnScenarioStartClick();

		Gwen::Controls::Button* btnOne;
		void BtnOneHoverEnter() {};
		void BtnOneHoverLeave() {};
		Gwen::Controls::Button* btnTwo;
		void BtnTwoHoverEnter() {};
		void BtnTwoHoverLeave() {};
		Gwen::Controls::Button* btnThree;
		void BtnThreeHoverEnter() {};
		void BtnThreeHoverLeave() {};
		Gwen::Controls::Button* btnFour;
		void BtnFourHoverEnter() {};
		void BtnFourHoverLeave() {};
		Gwen::Controls::Button* btnFive;
		void BtnFiveHoverEnter() {};
		void BtnFiveHoverLeave() {};

		Gwen::Controls::Button* btnBack;

		ALLEGRO_BITMAP* aBackgroundOne;
		ALLEGRO_BITMAP* aBackgroundTwo;
		ALLEGRO_BITMAP* aBackgroundThree;
		float fWidth;
		float fHeight;
		float fOffset;
		float fPosition;

		bool bOut;

		ALLEGRO_BITMAP* aButtonsOne;
		ALLEGRO_BITMAP* aButtonsTwo;

	public:
		Main() {};

		void Load();
		void Initialize();
		void Resize();
		void HandleEvents(ALLEGRO_EVENT &ev);
		void Update();
		void Render();
		void Cleanup();
	};
};
};