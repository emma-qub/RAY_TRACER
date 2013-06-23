#include <cmath>
#include <iostream> // debug
#include "Camera.h"

Camera::Camera(const Vector3& observer, const Vector3& aimedPoint,
		double viewAngle, int width2D, int height2D) :
	_observer(observer), _aimedPoint(aimedPoint), _viewAngle(viewAngle), _w2D(width2D), _h2D(height2D) {
	_initialized = false;
}

Camera::~Camera() {
}

bool Camera::initFromWH3D(double width3D, double height3D) {
	double t_va = tan(_viewAngle);
	if (t_va < 0.05 && t_va > -0.05) // TODO: find a proper epsilon
		return false;
	_w3D = width3D;
	_h3D = height3D;
	_ratioWH = _w3D / _h3D;
	_distScreen = _w3D / (2.0 * t_va);
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize();
}

/*
bool Camera::initFromDistScreen ( double distScreen, double ratioWH )
{
	double t_va = tan ( _viewAngle );
	if ( t_va < 0.05 && t_va > - 0.05 ) // TODO: find a proper epsilon
		return false;
	_distScreen = distScreen;
	_ratioWH = ratioWH;
	_w3D = 2*_distScreen*t_va;
	_h3D = _w3D/_ratioWH;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize ();
}
*/

bool Camera::initFromDistScreen(double distScreen) {
	double t_va = tan(_viewAngle);
	if (t_va < 0.05 && t_va > -0.05) // TODO: find a proper epsilon
		return false;
	_distScreen = distScreen;
	_ratioWH = _w2D * 1.0 / _h2D;
	_w3D = 2 * _distScreen * t_va;
	_h3D = _w3D / _ratioWH;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize();
}

bool Camera::initialize() {
	double t_va = tan(_viewAngle);
	if (t_va < 0.05 && t_va > -0.05) // TODO: find a proper epsilon
		return false;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	Vector3 AV = _aimedPoint - _observer; // AV is the vector from the observer to the aimed point

	//We are looking for the plane which equation is y = d and that contains _observer
	double d = AV[0] * _observer[0] + AV[1] * _observer[1] + AV[2] * _observer[2];
	//We are looking for a point at "left of _observer
	//so we fix its x coordinate to _observer[0]+1
	//its y coordinate is the d, and we calculate its z coordinate, last unknown
	double z = (d - AV[0]*(_observer[0]+1) - AV[1] * _observer[1]) / AV[2];

	Vector3 W(_observer[0]+1, _observer[1], z);
	Vector3 VW = (W - _observer).normalize();

	_wayUp = cross_product(VW, AV).normalize();
	if (_wayUp[1] < 0) {
		_wayUp = -_wayUp;
	}

	Vector3 dir = AV.normalize();
	_distScreen = _w3D / (2.0 * t_va);
	Vector3 B = _observer + _distScreen * dir; // B is the center of the screen
	Vector3 cp = cross_product(AV, _wayUp).normalize(); // the third direction: from the center to the right of the screen
	Vector3 temp = (_w3D / 2.0) * cp;
	Vector3 N = B + temp; // N is the point at the center-right of the screen
	Vector3 M = B - temp; // M is the point at the center-left of the screen
	temp = (_h3D / 2.0) * _wayUp;
	_screen3D[0] = M + temp; // top-left, top-right, bottom-left, bottom-right corners of the screen
	_screen3D[1] = N + temp;
	_screen3D[2] = M - temp;
	_screen3D[3] = N - temp;
	_initialized = true;
	return _initialized;
}

Vector3 Camera::getPixel(double x, double y) { // TODO: maybe we should optimize our class data structure to ease this operation
	return _screen3D[0] + (x * 1.0 / _w2D) * (_screen3D[1] - _screen3D[0]) + (y * 1.0 / _h2D) * (_screen3D[2] - _screen3D[0]);
}
Vector3 Camera::getPixel(const Vector2& pt) {
	return _screen3D[0] + (pt[0] * 1.0 / _w2D) * (_screen3D[1] - _screen3D[0]) + (pt[1] * 1.0 / _h2D) * (_screen3D[2] - _screen3D[0]);
}
