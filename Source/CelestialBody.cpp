#include "CelestialBody.h"
CelestialBody::CelestialBody(Array arr1, Array arr2, double m) 
	:arr_x{ arr1 }, arr_y{ arr2 }, mass{m} {}

CelestialBody::CelestialBody(Array arr1, Array arr2, double m, float d)
	: arr_x{ arr1 }, arr_y{ arr2 }, mass{ m }, diameter{d} {}

CelestialBody CelestialBody::operator +(double rhs) {
	CelestialBody temp{arr_x+rhs,arr_y+rhs,mass};
	return temp;
}
CelestialBody CelestialBody::operator +(CelestialBody rhs) {
	CelestialBody temp{ arr_x + rhs.arr_x,arr_y + rhs.arr_y, mass };
	return temp;
}

CelestialBody CelestialBody::operator*(double rhs) {
	CelestialBody temp{ arr_x * rhs,arr_y * rhs, mass};
	return temp;
}
CelestialBody& CelestialBody::operator=(CelestialBody rhs) {
	this->arr_x = rhs.arr_x;
	this->arr_y = rhs.arr_y;
	return *this;
}
CelestialBody::CelestialBody(const CelestialBody& rhs)
	:arr_x{ rhs.arr_x }, arr_y{ rhs.arr_y }, mass{rhs.mass}{}