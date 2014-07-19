#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Input/Allegro.h"
#include "Gwen/Renderers/Allegro.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/WindowCanvas.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/NumericUpDown.h"
#include "Gwen/Controls/ComboBox.h"
#include "Gwen/Controls/GroupBox.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/VerticalSlider.h"
#include "Gwen/Controls/ImagePanel.h"
#include "Gwen/Controls/ScrollControl.h"
#include "Gwen/Controls/RichLabel.h"

#include "tinyxml2.h"

#include <iostream>
#include <string>
#include <list>
#include <random>
#include <sys/stat.h>
#include <math.h>

namespace Module
{
namespace Simulator
{
	namespace Structs
	{
		struct Camera
		{
			Camera() {fX = 0.0f; fY = 0.0f; fZ = 0.0f;};
			float fX;
			float fY;
			float fZ;
		};
		struct Waypoint
		{
			Waypoint() {};
			Waypoint(float pX, float pY, float pZ) {fX = pX; fY = pY; fZ = pZ;};
			inline friend bool operator==(const Waypoint& lhs, const Waypoint& rhs) {if (lhs.fX == rhs.fX && lhs.fY == rhs.fY && lhs.fZ == rhs.fZ) {return true;} else {return false;} }
			inline friend bool operator!=(const Waypoint& lhs, const Waypoint& rhs) {return !operator==(lhs,rhs);}
			float fX;
			float fY;
			float fZ;
			std::list<int> nConnected;
		};
	};

	static double ArcTan(float x, float y)
	{
		if (x <= 0 && y >= 0)
			return abs(atan(x/y));
		else if (x <= 0 && y <= 0)
			return ALLEGRO_PI - abs(atan(x/y));
		else if (x >= 0 && y <= 0)
			return ALLEGRO_PI + abs(atan(x/y));
		else if (x >= 0 && y >= 0)
			return ALLEGRO_PI*2 - abs(atan(x/y));
		else
			return 0;
	};

	static double CalculateHeading(Structs::Waypoint alpha, Structs::Waypoint beta)
	{
		return ArcTan(alpha.fX - beta.fX, alpha.fY - beta.fY) * 180.0f / ALLEGRO_PI;
	};
};
};