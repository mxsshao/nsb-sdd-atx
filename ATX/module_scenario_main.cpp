#include "module_scenario_main.h"
#include "module_simulator_main.h"

using namespace Module::Scenario;

void Main::Load()
{
	gParent = mManager->gBase;

	scrHorizontal = new Gwen::Controls::ScrollControl(gParent);
	scrHorizontal->SetAutoHideBars(false);
	scrHorizontal->SetScroll(true, false);
	scrHorizontal->GetHScroll()->onBarMoved.Add(this, &Module::Scenario::Main::ScrHorizontalMove);

	fPosition = 0;

	gPadding = new Gwen::Controls::Base(scrHorizontal);
	gPadding->SetSize(0, 0);
	gPadding->SetDisabled(true);

	aBackgroundOne = al_load_bitmap("Resources/scenario1.png");
	aBackgroundTwo = al_load_bitmap("Resources/scenario2.png");
	aBackgroundThree = al_load_bitmap("Resources/scenario3.png");
	aButtonsOne = al_load_bitmap("Resources/scenariobuttons.png");
	aButtonsTwo = al_load_bitmap("Resources/scenariobuttons2.png");

	btnOne = new Gwen::Controls::Button(scrHorizontal);
	btnOne->SetShouldDrawBackground(false);
	btnOne->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 0, 340, 206));
	btnOne->SetCursor(Gwen::CursorType::Finger);
	btnOne->onPress.Add(this, &Module::Scenario::Main::WinScenarioCreate);
	btnOne->onHoverEnter.Add(this, &Module::Scenario::Main::BtnOneHoverEnter);
	btnOne->onHoverLeave.Add(this, &Module::Scenario::Main::BtnOneHoverLeave);

	btnTwo = new Gwen::Controls::Button(scrHorizontal);
	btnTwo->SetShouldDrawBackground(false);
	btnTwo->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 256, 446, 206));
	btnTwo->SetCursor(Gwen::CursorType::Finger);
	btnTwo->onPress.Add(this, &Module::Scenario::Main::WinScenarioCreate);
	btnTwo->onHoverEnter.Add(this, &Module::Scenario::Main::BtnTwoHoverEnter);
	btnTwo->onHoverLeave.Add(this, &Module::Scenario::Main::BtnTwoHoverLeave);

	btnThree = new Gwen::Controls::Button(scrHorizontal);
	btnThree->SetShouldDrawBackground(false);
	btnThree->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 512, 438, 206));
	btnThree->SetCursor(Gwen::CursorType::Finger);
	btnThree->onPress.Add(this, &Module::Scenario::Main::WinScenarioCreate);
	btnThree->onHoverEnter.Add(this, &Module::Scenario::Main::BtnThreeHoverEnter);
	btnThree->onHoverLeave.Add(this, &Module::Scenario::Main::BtnThreeHoverLeave);

	btnFour = new Gwen::Controls::Button(scrHorizontal);
	btnFour->SetShouldDrawBackground(false);
	btnFour->SetImage(al_create_sub_bitmap(aButtonsOne, 0, 768, 390, 206));
	btnFour->SetCursor(Gwen::CursorType::Finger);
	btnFour->onPress.Add(this, &Module::Scenario::Main::WinScenarioCreate);
	btnFour->onHoverEnter.Add(this, &Module::Scenario::Main::BtnFourHoverEnter);
	btnFour->onHoverLeave.Add(this, &Module::Scenario::Main::BtnFourHoverLeave);

	btnFive = new Gwen::Controls::Button(scrHorizontal);
	btnFive->SetShouldDrawBackground(false);
	btnFive->SetImage(al_create_sub_bitmap(aButtonsOne, 512, 0, 504, 206));
	btnFive->SetCursor(Gwen::CursorType::Finger);
	btnFive->onPress.Add(this, &Module::Scenario::Main::WinScenarioCreate);
	btnFive->onHoverEnter.Add(this, &Module::Scenario::Main::BtnFiveHoverEnter);
	btnFive->onHoverLeave.Add(this, &Module::Scenario::Main::BtnFiveHoverLeave);

	btnBack = new Gwen::Controls::Button(gParent);
	btnBack->SetText(L"Back");
	btnBack->SetCursor(Gwen::CursorType::Finger);

	Resize();
}

void Main::Resize()
{
	scrHorizontal->Dock(Gwen::Pos::Fill);

	float fRatio = al_get_display_height(mManager->aDisplay)/1080.0f;
	
	fWidth = fRatio * 5760.0f;
	fHeight = al_get_display_height(mManager->aDisplay);
	fOffset = al_get_display_width(mManager->aDisplay);

	fPosition = (fWidth-fOffset) * scrHorizontal->GetHScroll()->GetScrolledAmount();

	gPadding->SetPos(fWidth, 0);

	btnOne->SetSize(340 * fRatio, 206 * fRatio);
	btnOne->SetPos(554 * fRatio, 542 * fRatio);
	btnTwo->SetSize(446 * fRatio, 206 * fRatio);
	btnTwo->SetPos(1172 * fRatio, 340 * fRatio);
	btnThree->SetSize(438 * fRatio, 206 * fRatio);
	btnThree->SetPos(1730 * fRatio, 678 * fRatio);
	btnFour->SetSize(390 * fRatio, 206 * fRatio);
	btnFour->SetPos(2462 * fRatio, 517 * fRatio);
	btnFive->SetSize(504 * fRatio, 206 * fRatio);
	btnFive->SetPos(3174 * fRatio, 456 * fRatio);

	btnBack->SetSize(300 * fRatio, 80 * fRatio);
	btnBack->SetPos(20 * fRatio, 960 * fRatio);

	bOut = fOffset / fHeight > 5760.0f / 1080.0f;
}

void Main::WinScenarioCreate()
{
	if (!winScenario)
	{
		winScenario = new Gwen::Controls::WindowControl(gParent);
		winScenario->MakeModal();
		winScenario->SetClosable(true);
		winScenario->DisableResizing();
		winScenario->SetTitle(L"Scenario");
		winScenario->SetDeleteOnClose(true);
		winScenario->onWindowClosed.Add(this, &Module::Scenario::Main::WinScenarioClose);

		btnScenarioStart = new Gwen::Controls::Button(winScenario);
		btnScenarioStart->SetText(L"Start");
		btnScenarioStart->onPress.Add(this, &Module::Scenario::Main::BtnScenarioStartClick);

		WinScenarioResize();
	}
}

void Main::WinScenarioResize()
{
	if (winScenario)
	{
		winScenario->SetSize(400, 300);
		winScenario->SetPos((fOffset - 400)/2, (fHeight-300)/2);
		btnScenarioStart->SetSize(400,100);
		btnScenarioStart->Dock(Gwen::Pos::Top);
	}
}

void Main::WinScenarioClose()
{
	winScenario = NULL;
}

void Main::BtnScenarioStartClick()
{
	mManager->ChangeModule(new Module::Simulator::Main());
}

void Main::ScrHorizontalMove()
{
	fPosition = (fWidth - fOffset) * scrHorizontal->GetHScroll()->GetScrolledAmount();
}

void Main::HandleEvents(ALLEGRO_EVENT &ev)
{
}

void Main::Render()
{
	al_draw_scaled_bitmap(aBackgroundOne, 0, 0, 1920, 1080, 0 - fPosition, 0, fWidth/3.0f, fHeight, 0);
	al_draw_scaled_bitmap(aBackgroundTwo, 0, 0, 1920, 1080, fWidth/3.0f - fPosition, 0, fWidth/3.0f, fHeight, 0);
	al_draw_scaled_bitmap(aBackgroundThree, 0, 0, 1920, 1080, fWidth/3.0f*2.0f - fPosition, 0, fWidth/3.0f, fHeight, 0);

	if (bOut)
	{
		al_draw_scaled_bitmap(aBackgroundThree, 0, 0, 1920, 1080, fWidth/3.0f*4.0f - fPosition, 0, -fWidth/3.0f, fHeight, 0);
	}

	gParent->GetCanvas()->RenderCanvas();
}

void Main::Cleanup()
{
	scrHorizontal->DelayedDelete();
	btnBack->DelayedDelete();
	if (winScenario)
		winScenario->CloseButtonPressed();
	al_destroy_bitmap(aBackgroundOne);
	al_destroy_bitmap(aBackgroundTwo);
	al_destroy_bitmap(aBackgroundThree);
	al_destroy_bitmap(aButtonsOne);
	al_destroy_bitmap(aButtonsTwo);
}