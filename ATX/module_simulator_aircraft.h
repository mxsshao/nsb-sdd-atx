#pragma once

#include "global.h"

namespace Module
{
namespace Simulator
{
	class Main;
	class Aircraft : public Gwen::Event::Handler
	{
	private:
		static Main* mMain;
		static ALLEGRO_BITMAP* aButtonImage;
		static ALLEGRO_FONT* nFonts[2];
		static Gwen::Controls::Base* gParent;
		ALLEGRO_BITMAP* aButtonRender;
		Gwen::Controls::Button* btnAircraft;

		Gwen::Controls::Button* btnOne;

		ALLEGRO_TRANSFORM aTransform;
		ALLEGRO_BITMAP* aImage;
		
		int iState;
		double fSpeed;
		double fCurrentHeading;
		double fFinalHeading;
		int iDirection;
		enum iDirection {NONE, LEFT, RIGHT};
		float fX;
		float fY;
		float fZ;
		std::list<int> nPoints;
		int iPrevious;

		bool bIsSelected;
		float fFlipCount;
		float fOffset;

		bool bGround;

	public:
		Aircraft(float pX, float pY, float pZ, int pStart, double pSpeed, double pHeading, int pDestination, std::string pType);
		~Aircraft();

		float GetX() {return fX;};
		float GetY() {return fY;};

		void Select();
		void Deselect();
		bool GetSelected() {return bIsSelected;};
		void SetSelected(bool pSelected) {bIsSelected = pSelected;};

		void Resize();

		static void Load(Main* pMain, Gwen::Controls::Base* pParent);
		void Navigate(std::list<int>* destination);
		void Update();
		void Render();
		static void Cleanup();
	};
};
};