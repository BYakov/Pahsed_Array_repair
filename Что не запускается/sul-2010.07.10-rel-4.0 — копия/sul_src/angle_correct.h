//---------------------------------------------------------------------------
#ifndef _ANGLE_CORRECT_H_
#define _ANGLE_CORRECT_H_
//---------------------------------------------------------------------------
#ifndef _SUL_DATA_TYPES_H_
#include "sul_data_types.h"
#endif
#ifndef _SUL_ERROR_CODES_H_
#include "sul_error_codes.h"
#endif

//---------------------------------------------------------------------------

enum correction_type {
	CORRECTION_TYPE_1,  //!< ��������� 1 (�������-����������)
	CORRECTION_TYPE_2,  //!< ��������� 2 (�������������)
};

//---------------------------------------------------------------------------
//!  ����� ������������ �������������� ���� � ��� � ��� ���������.
/*!
�������� �� �������������� � ��� ���. ��������� ��� ������������ �������,
������������ � ������ sul_base.
*/
class angle
{
private:
	angle();

protected:
	//! ��� ������� ����� ��� X
	double   dx;
	//! ��� ������� ����� ��� Y
	double   dy;
	double   k1;
	double   k2;
	//! ����� �����
	double   l;
	double   a1;
	double   ox;
	double   oy;

	//! ��� ���������
	correction_type type;

	double calc_phi(double theta_x, double theta_y);
	double calc_theta(double theta_x, double theta_y);

public:
	angle(double dX, double dY, double K1, double K2);
	virtual ~angle();

	void    set_dx(double dX) {dx = dX;};
	void    set_dy(double dY) {dy = dY;};
	void    set_k1(double K1) {k1 = K1;};
	void    set_k2(double K2) {k2 = K2;};
	void    set_L(double L)   {l  = L;};
	void    set_a1(double A1) {a1 = A1;};
	void    set_ox(double oX) {ox = oX;};
	void    set_oy(double oY) {oy = oY;};
	void    set_type(correction_type type);

	//! ����������� ���� � ��� ��� ���������� X (��������������)
	/*!
	\param anglex - ���� ���������� ����� ��� X.
	\param angley - ���� ���������� ����� ��� Y.
	*/
	virtual u16 to_hcode(double anglex, double angley) = 0;

	//! ����������� ���� � ��� ��� ���������� Y (��������������)
	/*!
	\param anglex - ���� ���������� ����� ��� X.
	\param angley - ���� ���������� ����� ��� Y.
	*/
	virtual u16 to_vcode(double anglex, double angley) = 0;
};

//---------------------------------------------------------------------------

class angle_correct : public angle
{
private:
	angle_correct();
	u16     angle_to_hcode(double anglex, double angley);
	u16     angle_to_vcode(double anglex, double angley);

public:
	angle_correct(double dX, double dY, double K1, double K2);
	virtual ~angle_correct();

	u16     to_hcode(double anglex, double angley);
	u16     to_vcode(double anglex, double angley);
};

//-----------------------------------------------------------------------------

#endif //_ANGLE_CORRECT_H_
