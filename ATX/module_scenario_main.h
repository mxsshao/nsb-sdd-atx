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
		void WinScenarioClose();
		Gwen::Controls::Button* btnScenarioStart;
		void BtnScenarioStartClick();

		Gwen::Controls::Button* btnOne;
		void BtnOneHoverEnter() {btnOne->SetImage(al_create_sub_bitmap(aButtonsTwo, 0, 0, 340, 206));};
		void BtnOneHoverLeave() {btnOne->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 0, 340, 206));};
		Gwen::Controls::Button* btnTwo;
		void BtnTwoHoverEnter() {btnTwo->SetImage(al_create_sub_bitmap(aButtonsTwo, 0, 256, 446, 206));};
		void BtnTwoHoverLeave() {btnTwo->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 256, 446, 206));};
		Gwen::Controls::Button* btnThree;
		void BtnThreeHoverEnter() {btnThree->SetImage(al_create_sub_bitmap(aButtonsTwo, 0, 512, 438, 206));};
		void BtnThreeHoverLeave() {btnThree->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 512, 438, 206));};
		Gwen::Controls::Button* btnFour;
		void BtnFourHoverEnter() {btnFour->SetImage(al_create_sub_bitmap(aButtonsTwo, 0, 768, 390, 206));};
		void BtnFourHoverLeave() {btnFour->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 768, 390, 206));};
		Gwen::Controls::Button* btnFive;
		void BtnFiveHoverEnter() {btnFive->SetImage(al_create_sub_bitmap(aButtonsTwo, 512, 0, 504, 206));};
		void BtnFiveHoverLeave() {btnFive->SetImage(al_create_sub_bitmap(aButtonsOne, 512, 0, 504, 206));};

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
		~Main() {};

		void Load();
		void Initialize() {};
		void Resize();
		void HandleEvents(ALLEGRO_EVENT &ev);
		void Update();
		void Render();
		void Cleanup();
	};
};
};