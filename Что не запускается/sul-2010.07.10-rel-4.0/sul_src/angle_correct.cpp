#include <math.h>

#ifndef _ANGLE_CORRECT_H_
#include "angle_correct.h"
#endif

//---------------------------------------------------------------------------
angle::angle(double dX, double dY, double K1, double K2)
{
	dx = dX;
	dy = dY;
	k1 = K1;
	k2 = K2;
	l = 8.82;
}
//---------------------------------------------------------------------------
angle::~angle()
{
}
//---------------------------------------------------------------------------
void angle::set_type(correction_type t)
{
	type = t;
}
//---------------------------------------------------------------------------
double angle::calc_phi(double theta_x, double theta_y)
{
	double phi = 0;

	phi = atan(tan(theta_y)/tan(theta_x));

	return phi;
}
//---------------------------------------------------------------------------
double angle::calc_theta(double theta_x, double theta_y)
{
	double theta = 0;
	double phi = calc_phi(theta_x, theta_y);

	theta = atan(tan(theta_x)/cos(phi));

	return theta;
}
//---------------------------------------------------------------------------
angle_correct::angle_correct(double dX, double dY, double K1, double K2 ) :
angle(dX, dY, K1, K2)
{
	ox=0.0;
	oy=0.0;
	a1=0.0;
	l=8.82;

	set_type(CORRECTION_TYPE_1);
}
//---------------------------------------------------------------------------
angle_correct::~angle_correct()
{
}
//---------------------------------------------------------------------------
u16     angle_correct::to_hcode(double anglex, double angley)
{
	const double pi = 3.1415926535;
	u16 X = 0;

	if(type == CORRECTION_TYPE_1) {
		X = (u16)(65535.0 * (k1*(sin( anglex * pi / 180.0  ) * dx + ox)/l ));
	} else {
		X = angle_to_hcode(anglex, angley);
	}

	return X;
}
//---------------------------------------------------------------------------
u16     angle_correct::to_vcode(double anglex, double angley)
{
	const double pi = 3.1415926535;
	u16 Y = 0;

	if(type == CORRECTION_TYPE_1) {
		Y = (u16)(65535.0 * (k2*(sin( angley * pi / 180.0  ) * dy * cos(a1 * pi / 180.0) + oy)/l ));
	} else {
		Y = angle_to_vcode(anglex, angley);
	}

	return Y;
}
//---------------------------------------------------------------------------
u16 angle_correct::angle_to_hcode(double anglex, double angley)
{
	const double pi = 3.1415926535;
	double phi = calc_phi(anglex, angley);
	double theta = calc_theta(anglex, angley);
	double k = -2*pi/l;

	u16 X = (u16)(65535.0*(k*dx*sin(theta)*cos(phi)));

	return X;
}
//---------------------------------------------------------------------------
u16 angle_correct::angle_to_vcode(double anglex, double angley)
{
	const double pi = 3.1415926535;
	double phi = calc_phi(anglex, angley);
	double theta = calc_theta(anglex, angley);
	double k = -2*pi/l;

	u16 Y = (u16)(65535.0*(k*dy*sin(theta)*sin(phi)));

	return Y;
}
//---------------------------------------------------------------------------
