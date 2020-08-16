#pragma once
#include "Array.h"

class CelestialBody
{private:

public:
	Array arr_y{0,0};
	Array arr_x{ 0,0 };
	double mass{1};
	float diameter {1.0f};
	CelestialBody(Array arr1, Array arr2, double m);
	CelestialBody(Array arr1, Array arr2, double m, float d);
	CelestialBody operator +(double rhs);
	CelestialBody operator +(CelestialBody rhs);
	CelestialBody operator*(double rhs);
	CelestialBody& operator=(CelestialBody rhs);
	CelestialBody(const CelestialBody& rhs);
	
};

