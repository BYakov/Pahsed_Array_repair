
#ifndef _SCANNER_H_
#define _SCANNER_H_

#ifndef _COORDINATE_H_
#include "coordinate.h"
#endif

//-----------------------------------------------------------------------------
// направление сканирования
enum scan_direction {

        dir_x,
        dir_y,
        dir_xy_13,
        dir_xy_24,
};

//-----------------------------------------------------------------------------
// тип сканирования
enum scan_type {

        min_to_max,
        max_to_min,
};

//-----------------------------------------------------------------------------
// режим сканирования
enum scan_mode {

        single,
        continues,
};

//-----------------------------------------------------------------------------

#define		_PI_	3.14159265

//-----------------------------------------------------------------------------

class scanner {

private:

        bool             is_started;

        scan_direction   dir;
        scan_type        type;
        scan_mode        mode;

        //максимальный сектор сканирования (относительно 0,0)
        double           r_max;

        //шаг в плоскости сканирования
        double           dr;

        //шаг сканирования вдоль осей X, Y
        double           dx;
        double           dy;

        //угол плоскости сканирования к оси X ( 0 - 180 )
        double           fi;

        //границы изменения координат
        double           x_min;
        double		 y_min;
        double		 x_max;
        double		 y_max;

        //текущие координаты X, Y
        double           x;
        double           y;

        //текущий номер шага
        int		 index;

        //число шагов
        int		 N;

        //перевод значений угол/градус
        double to_rad(double z) { return (_PI_ * z)/180.0; }
        double to_grd(double z) { return (z * 180.0)/_PI_; }

        void calc_direction();
        void calc_params();
        void calc_step_number();
        void calc_start_point();

public:
        scanner();
        scanner(double Rmax = 90, double Fi0 = 0, double dR = 0.1);
        virtual ~scanner();

        //интерфейсные функции класса
        double get_x() { return x; }
        double get_y() { return y; }
        double get_dx(){ return dx; }
        double get_dy(){ return dy; }
        double get_rm(){ return r_max; }
        double get_angle(){ return fi; }

        double get_n();
        int get_index();

        void set_x(double X);
        void set_y(double Y);
        void set_rm(double Rm);
        void set_dr(double dR);
        void set_angle(double Fi);

        bool start();
        bool step();
        bool stop();
};

//-----------------------------------------------------------------------------

/*
class scanner {

private:

        bool             started;
        bool             started_x;
        bool             started_y;
        bool             disable;

        scan_direction   sdir;
        scan_type        stype;

        //максимальный сектор сканирования (относительно 0,0)
        double           r_max;

        //максимальная зона сканирования (относительно x0,y0)
        double           r0;

        //координаты центра зоны
        double           x0;
        double           y0;

        //шаг сканирования по направлению
        double           dr;

        //шаг сканирования по осям
        double           dx;
        double           dy;

        //угол прохода луча к оси X
        double           fi0;

        //промежуточные переменные (вычисляются при начале сканирования)
        double			 xmin;
        double			 ymin;
        double			 xmax;
        double			 ymax;

        //текущие координаты X, Y
        double			 x;
        double			 y;

        //текущий номер шага
        int				index;
        //число шагов
        int				N;

private:

        double to_rad(double z) { return (_PI_ * z)/180.0; }
        double to_grd(double z) { return (z * 180.0)/_PI_; }

        bool step_xy();
        bool step_x();
        bool step_y();

public:

        scanner();
        //scanner(double Rmax, double R0, double X0, double Y0, double Fi0, double dX, double dY);
        scanner(double Rmax, double R0, double X0, double Y0, double Fi0, double dR);
        virtual ~scanner();

        bool check_params();
        bool correct_params();

        double get_x() { return x; }
        double get_y() { return y; }
        double get_x0() { return x0; }
        double get_y0() { return y0; }
        double get_dx(){ return dx; }
        double get_dy(){ return dy; }
        double get_r0(){ return r0; }
        double get_rm(){ return r_max; }
        double get_angle(){ return fi0; }
        int get_index();
        int get_n();

        void set_x(double X) { x = X; }
        void set_y(double Y) { y = Y; }
        void set_x0(double X0) { x0 = X0; }
        void set_y0(double Y0) { y0 = Y0; }
        void set_r0(double R0) { r0 = R0; }
        void set_rm(double Rm) { r_max = Rm; }
        void set_dr(double dR);
        void set_angle(double Fi) { fi0 = Fi; }

        void set_direction(scan_direction d) { sdir = d; }
        void set_type(scan_type t) { stype = t; }

        bool start();
        bool step();
        void stop();
};
*/
//-----------------------------------------------------------------------------

#endif //_SCANNER_H_
