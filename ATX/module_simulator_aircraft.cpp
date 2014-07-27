#include "module_simulator_aircraft.h"
#include "module_simulator_main.h"

using namespace Module::Simulator;

Main* Aircraft::mMain;

Aircraft::Aircraft(float pX, float pY, float pZ, int pStart, double pSpeed, double pHeading, int pDestination, std::string pType)
{
	//std::cout << "NEW AIRCRAFT	-x" << ex << " -y" << ey << " -z" << ez << " -s" << start << " -v" << eSpeed << " -h" << eHeading << " -d" << eDestination <<std::endl;

	aImage = al_load_bitmap(std::string("Resources/").append(pType).append(".png").c_str());
	iState = 15.0f;

	fSpeed = pSpeed;
	fCurrentHeading = pHeading;
	fFinalHeading = pHeading;
	iDirection = NONE;

	bIsSelected = false;
	fFlipCount = 1.0f;

	iPrevious = pStart;
	//nPoints.push_back(nWaypoints[start]);
	fX = pX;
	fY = pY;
	fZ = pZ;

	std::list<int> nDestination;
	nDestination.push_front(pDestination);
	Navigate(&nDestination);
}

Aircraft::~Aircraft()
{
	al_destroy_bitmap(aImage);
}

void Aircraft::Load(Main* pMain)
{
	mMain = pMain;
}

void Aircraft::Navigate(std::list<int>* nDestination)
{
	nPoints.push_back(iPrevious);
	std::list<int>::iterator iter;
	std::list<int>::iterator duplicate;

	int value = 0;
	double min = 0.0f;
	double heading = 0;
	double theta = 0;

	while (!nDestination->empty())
	{
		value = 0;
		min = 360.0f;
		heading = CalculateHeading(mMain->nWaypoints[nPoints.back()], mMain->nWaypoints[nDestination->back()]);
		theta = 0;
		
		for (iter = mMain->nWaypoints[nPoints.back()].nConnected.begin(); iter != mMain->nWaypoints[nPoints.back()].nConnected.end(); iter++)
		{
			theta = abs(heading - CalculateHeading(mMain->nWaypoints[nPoints.back()], mMain->nWaypoints[(*iter)]));
			if (theta >= 180) {theta = 360 - theta;};
			if (theta <= min)
			{
				min = theta;
				value = (*iter);
			}
		}

		duplicate = std::find(nPoints.begin(), nPoints.end(), value);
		if (duplicate != nPoints.end())
		{
			nPoints.erase(duplicate, nPoints.end());
		}
		else
		{
			nPoints.push_back(value);
		}

		if (nPoints.back() == nDestination->back())
		{
			nDestination->pop_back();
		}
		
	}
}

void Aircraft::Update()
{
	//CHECK POINTS
	if (!nPoints.empty())
	{
		fFinalHeading = CalculateHeading(Structs::Waypoint(fX,fY,fZ), mMain->nWaypoints[nPoints.front()]);

		if (abs(fX - mMain->nWaypoints[nPoints.front()].fX) <= fSpeed)
		{
			if (abs(fY - mMain->nWaypoints[nPoints.front()].fY) <= fSpeed)
			{
				fX = mMain->nWaypoints[nPoints.front()].fX;
				fY = mMain->nWaypoints[nPoints.front()].fY;

				nPoints.pop_front();
			}
		}
	}

	//AIRCRAFT UPDATE
	if (fCurrentHeading != fFinalHeading)
	{
		double dif = fCurrentHeading - fFinalHeading;
		if (dif > 0) {iDirection = (dif < 180) ? LEFT:RIGHT;}
		else {iDirection = (dif < -180) ? LEFT:RIGHT;}
		if (iDirection == LEFT)
		{
			fCurrentHeading = fmod(fCurrentHeading-0.2f, 360);
			if (fCurrentHeading < 0)
			{
				fCurrentHeading += 360;
			}
			if ((abs(fCurrentHeading - fFinalHeading) < 2.6f) && (iState < 14))
			{
				iState ++;
			}
			else if (iState > 0)
			{
				iState --;
			}
		}
		else if (iDirection == RIGHT)
		{
			fCurrentHeading = fmod(fCurrentHeading+0.2f, 360);
			if (fCurrentHeading < 0)
			{
				fCurrentHeading += 360;
			}
			if ((abs(fCurrentHeading - fFinalHeading) < 2.6f) && (iState > 16))
			{
				iState --;
			}
			else if (iState < 30)
			{
				iState ++;
			}
		}
	}

	if (abs(fCurrentHeading - fFinalHeading) < 0.2f)
	{
		iDirection = NONE;
		fCurrentHeading = fFinalHeading;
		iState = 15;
	}

	fX += fSpeed * sin(fCurrentHeading / 180.0f * ALLEGRO_PI);
	fY -= fSpeed * cos(fCurrentHeading / 180.0f * ALLEGRO_PI);
}

void Aircraft::Render()
{
	//AIRCRAFT
	if (bGround)
	{
		al_draw_tinted_scaled_rotated_bitmap_region(aImage, 0, 0, 250, 250, al_map_rgb_f(1,1,1), 125, 125, fX, fY, 1.0f, 1.0f, fCurrentHeading/180.0f*ALLEGRO_PI, 0);
	}
	else
	{
		int iX = 0;
		int iY = 0;
		float fScale = 1.0f;

		if (iState <= 14)
		{
			iY = 500;
			iX = floor((14 - iState) / 2) * 250;
		}
		else if (iState >= 16)
		{
			iY = 250;
			iX = ceil((iState - 16) / 2) * 250;
		}

		al_draw_tinted_scaled_rotated_bitmap_region(aImage, iX, iY, 250, 250, al_map_rgb_f(1,1,1), 125, 125, fX, fY, fScale, fScale, fCurrentHeading/180.0f*ALLEGRO_PI, 0);
	}
}

void Aircraft::Cleanup()
{
}