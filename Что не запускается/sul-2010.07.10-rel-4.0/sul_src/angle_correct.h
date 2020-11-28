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
	CORRECTION_TYPE_1,  //!< Коррекция 1 (синусно-косинусная)
	CORRECTION_TYPE_2,  //!< Коррекция 2 (арктангенсная)
};

//---------------------------------------------------------------------------
//!  Класс осуществляет преобразование угла в код и его коррекцию.
/*!
Отвечает за взаимодействие с СУЛ АВР. Реализует все интерфейсные функции,
определенные в классе sul_base.
*/
class angle
{
private:
	angle();

protected:
	//! Шаг решетки вдоль оси X
	double   dx;
	//! Шаг решетки вдоль оси Y
	double   dy;
	double   k1;
	double   k2;
	//! Длина волны
	double   l;
	double   a1;
	double   ox;
	double   oy;

	//! Тип коррекции
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

	//! Преобразует угол в код для координаты X (горизонтальная)
	/*!
	\param anglex - угол отклонения вдоль оси X.
	\param angley - угол отклонения вдоль оси Y.
	*/
	virtual u16 to_hcode(double anglex, double angley) = 0;

	//! Преобразует угол в код для координаты Y (горизонтальная)
	/*!
	\param anglex - угол отклонения вдоль оси X.
	\param angley - угол отклонения вдоль оси Y.
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
