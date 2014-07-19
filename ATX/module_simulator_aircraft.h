#pragma once

#include "global.h"

namespace Module
{
namespace Simulator
{
	class Main;
	class Aircraft
	{
	private:
		static Main* mMain;

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

		static void Load(Main* pMain);
		void Navigate(std::list<int>* destination);
		void Update();
		void Render();
		static void Cleanup();
	};
};
};