#ifndef SCREENV2_H_
#define SCREENV2_H_

#include "Vector3.h"
#include "Vector2.h"

class Camera {
public:
	Vector3 _observer;
	Vector3 _aimedPoint;
	Vector3 _wayUp;
	double _viewAngle; // TODO: that's in fact the half of the angle
	double _distScreen;
	double _w3D;
	double _h3D;
	double _ratioWH; // for 2D and 3D
	Vector3 _screen3D[4]; // top-left, top-right, bottom-left, bottom-right corners of the screen
	bool _initialized;
	int _w2D;
	int _h2D;

	Camera(const Vector3& observer = 0,
			const Vector3& aimedPoint = 0, double viewAngle = 0,
			int width2D = 0, int height2D = 0);
	virtual ~Camera();

	bool initFromWH3D(double width3D, double height3D);
	/*bool initFromDistScreen ( double _distScreen, double _ratioWH );*/
	bool initFromDistScreen(double distScreen);

	Vector3 getPixel(double x, double y); // returns the 3D point where the pixel is
	Vector3 getPixel(const Vector2& pt);

protected:
	bool initialize();
};

#endif /* SCREENV2_H_ */
