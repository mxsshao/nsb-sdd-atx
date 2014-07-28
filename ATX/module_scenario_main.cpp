#include "module_scenario_main.h"

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

}