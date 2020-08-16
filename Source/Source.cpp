/*
=============================================================================
 The solar system simulation using the RK4
 =============================================================================
Updated on Aug 16 2020
@author: Ahmed Alkharusi
I used the olcPixelGameEngine to generate the graphics.
The "olcPixelGameEngine.h" is a single header file that enables us to draw graphics.
This is created by javidx9 (OneLoneCoder).
please download it from his repo
https://github.com/OneLoneCoder/olcPixelGameEngine
*/
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Array.h"
#include "CelestialBody.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

const double pi{ 3.14159265359 };
std::string print_info(double t, double step_size);
void print_about();
std::string print_menu();
CelestialBody deriv(CelestialBody obj_active, CelestialBody obj_passive1);
void rk4(CelestialBody(*deriv)(CelestialBody, CelestialBody), CelestialBody& obj_active, CelestialBody& obj_passive1, double h);
class ThreeBodyProblem : public olc::PixelGameEngine
{
public:
	ThreeBodyProblem()
	{
		sAppName = "The solar system (Simulation)";
	}

private:
	double step_size{ 1.0 / 1000.0 };//step size for the RK4 method

	//initial conditions (play around with these)
	double t{ 0 };
	//see the 
	CelestialBody sun{ Array{ 0,0},			Array{0,0}, 4.0*pi*pi,30 };
	//CelestialBody moon{ Array{ 0.996+ 0.00256955529,0},		Array{0,-0.00021544285},1 ,10 };

	CelestialBody mercury{ Array{ 0.384,0},	Array{0,10.090399}, 1,3.83 };
	CelestialBody venus{ Array{0.72,0},		Array{0,7.4203409}, 1,9.49 };

	CelestialBody earth{ Array{ 0.996,0},		Array{0,2 * 3.14},1 ,10};
	CelestialBody mars{ Array{ 1.57,0},		Array{0,4.9117598},1 ,5.32 };

	CelestialBody jupiter{ Array{ 5.13,0},		Array{0,2.80370840}, 1, 112.1 *0.2};
	CelestialBody saturn{ Array{  8.99,0},		Array{0,2.1502124}, 1,94.5 * 0.2 };

	CelestialBody uranus{ Array{19.1,0},		Array{0,1.441907},1,40.1 *0.5};
	CelestialBody neptune{ Array{30,0},		Array{0,1.150996}, 1,38.8 *0.5};
	int zoom = 245;


public:

	bool OnUserCreate() override
	{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		
		int x_shift = ScreenWidth() / 2 - 200;
		int y_shift = ScreenHeight() / 2;
		
		Clear(olc::BLACK);

		//rk4(deriv, moon, earth, step_size);

		rk4(deriv, mercury,	sun, step_size);
		rk4(deriv, venus,	sun, step_size);
		rk4(deriv, earth,	sun, step_size);
		rk4(deriv, mars,	sun, step_size);
		rk4(deriv, jupiter, sun, step_size);
		rk4(deriv, saturn,	sun, step_size);
		rk4(deriv, uranus,	sun, step_size);
		rk4(deriv, neptune,	sun, step_size);

		//FillCircle((moon.arr_x).position * zoom + x_shift, (moon.arr_y).position * zoom + y_shift, earth.diameter/2, olc::Pixel(255,255,255));


		FillCircle((sun.arr_x).position * zoom + x_shift,    (sun.arr_y).position * zoom + y_shift, sun.diameter, olc::Pixel(252, 150, 1));

		FillCircle((mercury.arr_x).position * zoom + x_shift, (mercury.arr_y).position * zoom + y_shift, mercury.diameter , olc::Pixel(181, 167, 167));
		FillCircle((venus.arr_x).position * zoom + x_shift,   (venus.arr_y).position * zoom + y_shift,   venus.diameter , olc::Pixel(221, 216, 212));
		FillCircle((earth.arr_x).position * zoom + x_shift,   (earth.arr_y).position * zoom + y_shift,   earth.diameter , olc::Pixel(140, 177, 222));
		FillCircle((mars.arr_x).position * zoom + x_shift,    (mars.arr_y).position * zoom + y_shift,    mars.diameter , olc::Pixel(255, 157, 111));
		FillCircle((jupiter.arr_x).position * zoom + x_shift, (jupiter.arr_y).position * zoom + y_shift, jupiter.diameter  , olc::Pixel(167, 156, 134));
		FillCircle((saturn.arr_x).position * zoom + x_shift,  (saturn.arr_y).position * zoom + y_shift,  saturn.diameter , olc::Pixel(197, 171, 110));
		FillCircle((uranus.arr_x).position * zoom + x_shift,  (uranus.arr_y).position * zoom + y_shift,  uranus.diameter , olc::Pixel(187, 225, 228));
		FillCircle((neptune.arr_x).position * zoom + x_shift, (neptune.arr_y).position * zoom + y_shift, neptune.diameter , olc::Pixel(62, 102, 249));

		DrawString((mercury.arr_x).position * zoom + x_shift,	-20 +(mercury.arr_y).position * zoom + y_shift, "Mercury"   , olc::Pixel(181, 167, 167));
		DrawString((venus.arr_x).position * zoom + x_shift,		-20 + (venus.arr_y).position * zoom + y_shift, "Venus",			olc::Pixel(221, 216, 212));
		DrawString((earth.arr_x).position * zoom + x_shift,		-20 + (earth.arr_y).position * zoom + y_shift,	    "Earth", olc::Pixel(140, 177, 222));
		DrawString((mars.arr_x).position * zoom + x_shift,		-20 + (mars.arr_y).position * zoom + y_shift,		  "Mars"  , olc::Pixel(255, 157, 111));
		DrawString((jupiter.arr_x).position * zoom + x_shift,   -50 + (jupiter.arr_y).position * zoom + y_shift,  "Jupiter" , olc::Pixel(167, 156, 134));
		DrawString((saturn.arr_x).position * zoom + x_shift,	 -50 + (saturn.arr_y).position * zoom + y_shift,	"Saturn"	, olc::Pixel(197, 171, 110));
		DrawString((uranus.arr_x).position * zoom + x_shift,	 -30 + (uranus.arr_y).position * zoom + y_shift,	"Uranus"	, olc::Pixel(187, 225, 228));
		DrawString((neptune.arr_x).position * zoom + x_shift,	 -30 + (neptune.arr_y).position * zoom + y_shift,"Neptune"	, olc::Pixel(62, 102, 249));

		if (GetKey(olc::ESCAPE).bHeld) {
			return false;
		}

		if (GetKey(olc::R).bPressed) {
			sun={ Array{ 0,0},			Array{0,0}, 4.0 * pi * pi,30 };
			//moon={ Array{ 0.996 + 0.00256955529,0},		Array{0,0.00021544285},1 ,10 };

			 mercury={ Array{ 0.384,0},	Array{0,10.090399}, 1,3.83 };
			 venus={ Array{0.72,0},		Array{0,7.4203409}, 1,9.49 };

			 earth={ Array{ 0.996,0},		Array{0,2 * 3.14},1 ,10 };
			 mars={ Array{ 1.57,0},		Array{0,4.9117598},1 ,5.32 };

			 jupiter={ Array{ 5.13,0},		Array{0,2.80370840}, 1, 112.1 * 0.2 };
			 saturn={ Array{  8.99,0},		Array{0,2.1502124}, 1,94.5 * 0.2 };

			 uranus={ Array{19.1,0},		Array{0,1.441907},1,40.1 * 0.5 };
			 neptune={ Array{30,0},		Array{0,1.150996}, 1,38.8 * 0.5 };
		}

		if (GetKey(olc::Z).bHeld)
			zoom += 1;
		if (GetKey(olc::X).bHeld) {
			if(zoom>5)
				zoom -= 1;
		}
		if (GetMouse(1).bHeld) {
			(sun.arr_x).position = (static_cast<int>(GetMouseX()) - x_shift)/(zoom*1.0);
			(sun.arr_y).position = (static_cast<int>(GetMouseY()) - y_shift) /(zoom * 1.0);
		}
			
		if (!GetKey(olc::Key::H).bHeld) {
			DrawString(ScreenWidth() - 500, 50, print_menu(), olc::WHITE, 2);
			DrawString(ScreenWidth() - 500, ScreenHeight() - 500, print_info(t, step_size), olc::WHITE, 2);
		}
		if (GetKey(olc::Key::A).bHeld) print_about();
		t += step_size;
		if (GetKey(olc::Key::Q).bPressed) 
			step_size +=0.0001;
		if (GetKey(olc::Key::W).bPressed) {
			if (step_size > 0.0002)
				step_size -= 0.0001;
		}

		t += step_size;
		return true;
	}
};



int main() {
	
	ThreeBodyProblem object;
	int resolution_height{ 1080 };
	int resolution_width{ 1920 };
	if (object.Construct(resolution_width, resolution_height, 1, 1))
		object.Start();
	


	return 0;
}
CelestialBody deriv(CelestialBody obj_active, CelestialBody obj_passive1) {
	double v_x = (obj_active.arr_x).speed;
	double v_y = (obj_active.arr_y).speed;
	double xo = (obj_active.arr_x).position;
	double yo = (obj_active.arr_y).position;

	double xp1 = (obj_passive1.arr_x).position;
	double yp1 = (obj_passive1.arr_y).position;


	double acc_x = -(obj_passive1.mass * (xo - xp1) / pow(pow(xo - xp1, 2.0) + pow(yo - yp1, 2.0), 3.0 / 2.0));
	double acc_y = -(obj_passive1.mass * (yo - yp1) / pow(pow(xo - xp1, 2.0) + pow(yo - yp1, 2.0), 3.0 / 2.0));

	return CelestialBody{ Array{v_x,acc_x}, Array{v_y,acc_y} ,obj_active.mass};
}
void rk4(CelestialBody(*deriv)(CelestialBody, CelestialBody), CelestialBody& obj_active, CelestialBody& obj_passive1, double h) {
	CelestialBody k1 = deriv(obj_active, obj_passive1);
	CelestialBody k2 = deriv(obj_active + h / 2, obj_passive1);
	CelestialBody k3 = deriv(obj_active + h / 2, obj_passive1);
	CelestialBody k4 = deriv(obj_active + h, obj_passive1);
	obj_active = obj_active + ((k1 + (k2 * 2) + (k3 * 2) + k4)) * (h / 6);
}
std::string print_menu() {
	std::ostringstream oss;
	oss << std::setw(15) << std::left << "MENU" << "| KEY (HOLD) " << "\n\n"
		<< std::setw(15) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(15) << std::left << "HIDE TEXT" << "| H " << "\n\n"
		<< std::setw(15) << std::left << "MOVE THE SUN" << "| MOUSE RIGHT " << "\n\n"
		<< std::setw(15) << std::left << "ZOOM IN" << "| Z " << "\n\n"
		<< std::setw(15) << std::left << "ZOOM OUT" << "| X " << "\n\n"
		<< std::setw(15) << std::left << "INCREASE STEP SIZE" << "| Q " << "\n\n"
		<< std::setw(15) << std::left << "DECREASE STEP SIZE" << "| W " << "\n\n"
		<< std::setw(15) << std::left << "RESET" << "| R " << "\n\n"
		<< std::setw(15) << std::left << "EXIT" << "| ESC " << "\n\n"
		<< std::setw(15) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(15) << std::left << "ABOUT" << "| A " << "\n\n"
		<< std::setw(15) << std::left << "NOTE: THIS WILL APEAR IN" << "\n\n"
		<< std::setw(15) << std::left << "A SEPARATE WINDOW!" << "\n\n"
		<< std::endl;
	std::string str = oss.str();
	return str;
}
std::string print_info(double t, double step_size) {
	std::ostringstream oss;
	oss << std::setw(8) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(8) << std::setprecision(6) << std::left << "STEP SIZE: " << step_size << "\n\n"
		<< std::setw(8) << std::setprecision(2) << std::left << "TIME: " << t << " arb." << "\n\n"
		<< std::endl;
	std::string str = oss.str();
	return str;
}
void print_about() {
	std::cout << "\n\n=============================================================================\nThe solar system simulation using Runge Kutta method(RK4)\n========================================================================================\nUpdated on Aug 16 2020\n@author: Ahmed Alkharusi\nI used the olcPixelGameEngine to generate the graphics.\nThe olcPixelGameEngine.h is a single header file that enables us to draw graphics.\nThis is created by javidx9(OneLoneCoder).\nplease download it from his repo\nhttps ://github.com/OneLoneCoder/olcPixelGameEngine " << std::endl;
}

/*
=============================================================================
 Please check the answers!!!
 =============================================================================
References:
#Implementing the RK4 method in Python
https ://youtu.be/mqoqAovXxWA
by Prof.Niels Walet
# Facts
https://nssdc.gsfc.nasa.gov/planetary/factsheet/planet_table_ratio.html

# For the planets colours
https://www.schemecolor.com/earth-planet-colors.php

#for the initial conditions see
https ://doi.org/10.1093/pasj/psy057

https ://arxiv.org/abs/math/0011268

and 
Universe Sandbox
*/