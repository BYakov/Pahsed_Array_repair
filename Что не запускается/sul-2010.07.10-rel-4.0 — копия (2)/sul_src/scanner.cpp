#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef _SCANNER_H_
#include "scanner.h"
#endif

using namespace std;

//----------------------------------------------------------------------------

scanner::scanner()
{
}

//----------------------------------------------------------------------------

scanner::scanner(double Rmax, double fi0, double dR)
{
    mode = single;
    type = min_to_max;

    fi = fi0;
    r_max = Rmax;
    dr = dR;

    index = N = x = y = 0;

    calc_direction();
    calc_params();
}

//----------------------------------------------------------------------------

scanner::~scanner()
{
}

//----------------------------------------------------------------------------

void scanner::calc_direction()
{
    if(fi == 90) {
        dir = dir_y;
    }

    if((fi == 0) || (fi == 180)) {
        dir = dir_x;
    }

    if((fi > 0) && (fi < 90)) {
        dir = dir_xy_13;
    }

    if((fi > 90) && (fi < 180)) {
        dir = dir_xy_24;
    }
}

//----------------------------------------------------------------------------

void scanner::calc_params()
{
    switch(dir) {

    case dir_x: {
            y_min = y_max = dy = 0;
            x_min = -r_max;
            x_max = r_max;
            dx = dr;
            dy = 0;
        } break;

    case dir_y: {
            x_min = x_max = dx = 0;
            y_min = -r_max;
            y_max = r_max;
            dy = dr;
        } break;

    case dir_xy_13: {

            dx = dr*cos(to_rad(fi));
            dy = dr*sin(to_rad(fi));

            x_max = r_max*cos(to_rad(fi));
            x_min = -x_max;

            y_max = r_max*sin(to_rad(fi));
            y_min = -y_max;

        } break;

    case dir_xy_24: {

            dx = dr*cos(to_rad(180-fi));
            dy = dr*cos(to_rad(fi-90));

            x_max = r_max*cos(to_rad(180-fi));
            x_min = -x_max;

            y_max = r_max*cos(to_rad(fi-90));
            y_min = -y_max;

        } break;
    }
}

//----------------------------------------------------------------------------

void scanner::calc_step_number()
{
    N = 0;
    index = 0;

    switch(dir) {
    case dir_x: {
            N = 2*x_max/dx;
        } break;

    case dir_y: {
            N = 2*y_max/dy;
        } break;

    case dir_xy_13:
    case dir_xy_24: {

            if(x_max > y_max) {
                N = 2*y_max/dy;
            } else {
                N = 2*x_max/dx;
            }

        } break;
    }
}

//----------------------------------------------------------------------------

void scanner::calc_start_point()
{
    switch(dir) {

    case dir_y:
    case dir_x:
    case dir_xy_13: {
            x = x_min;
            y = y_min;
        } break;
    case dir_xy_24: {
            x = x_max;
            y = y_min;
        } break;
    }
}

//----------------------------------------------------------------------------

bool scanner::start()
{
    calc_direction();
    calc_params();
    calc_step_number();
    calc_start_point();

    is_started = true;
    return is_started;
}

//----------------------------------------------------------------------------

bool scanner::step()
{
    if(!is_started) return false;

    double tmp_x = x;
    double tmp_y = y;

    if(dir == dir_xy_24) {

        tmp_x -= dx;    tmp_y += dy;

        if(tmp_x < x_min || tmp_y > y_max) return false;

    } else {

        tmp_x += dx;    tmp_y += dy;

        if(tmp_x > x_max || tmp_y > y_max) return false;
    }

    x = tmp_x;  y = tmp_y;

    ++index;

    return true;
}

//----------------------------------------------------------------------------

bool scanner::stop()
{
    is_started = false;
    return is_started;
}

//----------------------------------------------------------------------------

void scanner::set_x(double X)
{
    x = X;
}

//----------------------------------------------------------------------------

void scanner::set_y(double Y)
{
    y = Y;
}

//----------------------------------------------------------------------------

void scanner::set_rm(double Rm)
{
    if(is_started)
        return;

    r_max = Rm;
}

//----------------------------------------------------------------------------

void scanner::set_dr(double dR)
{
    if(is_started)
        return;

    dr = dR;
};

//----------------------------------------------------------------------------

void scanner::set_angle(double Fi)
{
    if(is_started)
        return;

    fi = Fi;
}

//----------------------------------------------------------------------------

int scanner::get_index()
{
    if(!is_started)
        return 0;

    return index;
}

//----------------------------------------------------------------------------

double scanner::get_n()
{
    if(!is_started)
        return 0;

    return N;
}

//----------------------------------------------------------------------------


/*
scanner::scanner()
{
        stype = SCAN_SINGLE;
        sdir = SCAN_XY;

        started_x = false;
        started_y = false;
        started = false;
        disable = false;

        //максимальный сектор сканирования (относительно 0,0)
        r_max = 0;

        //максимальная зона сканирования (относительно x0,y0)
        r0 = 0;

        //координаты центра зоны
        x0 = 0;
        y0 = 0;

        //шаг сканирования по осям
        dx = 0;
        dy = 0;

        //угол прохода луча к оси X
        fi0 = 0;

        index = 0;
        N = 0;
}

//scanner::scanner(double rMax, double R0, double X0, double Y0, double fi, double dX, double dY)
scanner::scanner(double rMax, double R0, double X0, double Y0, double fi, double dR)
{
        stype = SCAN_SINGLE;
        sdir = SCAN_XY;

        started_x = false;
        started_y = false;
        started = false;
        disable = false;

        //максимальный сектор сканирования (относительно 0,0)
        r_max = rMax;

        //максимальная зона сканирования (относительно x0,y0)
        r0 = R0;

        //координаты центра зоны
        x0 = X0;
        y0 = Y0;

        //угол прохода луча к оси X
        fi0 = fi;

        //шаг сканирования по осям
        set_dr(dR);

        index = 0;
        N = 0;
}

scanner::~scanner()
{
}

void scanner::set_dr(double dR)
{
        dr = dR;
        dx = dr*cos(to_rad(fi0));
        dy = dr*sin(to_rad(fi0));

        if(dx < 0.001) dx = 0;
        if(dy < 0.001) dy = 0;

        double Ny = 0;
        double Nx = 0;

        if(dy != 0)
                Ny = r0*sin(to_rad(fi0))/dy;

        if(dx != 0)
                Nx = r0*cos(to_rad(fi0))/dx;

        int NY = Ny;
        int NX = Nx;

        NY > NX ? N = NY : N = NX;
}

bool scanner::step()
{
        if(disable)
                return false;

        if(!step_x()) {
                stop();
                return false;
        }

        if(!step_y()) {
                stop();
                return false;
        }

        index++;

        return true;
}

bool scanner::step_x()
{
        if(dx == 0)
                return true;

        if(!started_x) {

                double Nx = r0*cos(to_rad(fi0))/dx;
                xmin = x0 - Nx*dx;
                xmax = x0 + Nx*dx;
                x = xmin;
                started_x = true;

                //N = Nx;
        }

        x = xmin + index*dx;

        if(x > xmax) {
                return false;
        }

        return true;
}

bool scanner::step_y()
{
        if(dy == 0)
                return true;

        if(!started_y) {

                double Ny = r0*sin(to_rad(fi0))/dy;

                ymin = y0 - Ny*dy;
                ymax = y0 + Ny*dy;
                y = ymin;
                started_y = true;

                //N = Ny;
        }

        y = ymin + index*dy;

        if(y > ymax) {
                return false;
        }

        return true;
}

bool scanner::step_xy()
{
        return false;
}

bool scanner::check_params()
{
        // проверка правильности угла
        if(fi0 > 180.0)
                return false;

        // проекции радиуса сканирования на оси Х и Y
        double rx = r0*cos(to_rad(fi0)) + x0;
        double ry = r0*sin(to_rad(fi0)) + y0;

        // проекции максимального радиуса сканирования на оси Х и Y (смещенные)
        double Rx = r_max*cos(to_rad(fi0)) - x0;
        double Ry = r_max*sin(to_rad(fi0)) - y0;

        if( rx > Rx || ry > Ry )
                return false;

        return true;
}

bool scanner::correct_params()
{
        return false;
}

bool scanner::start()
{
        if(started)
                return true;

        started = true;
        disable = false;
        started_x = false;
        started_y = false;

        index = 0;

        x = x0;
        y = y0;

        return true;
}

void scanner::stop()
{
        disable = true;
        started_x = false;
        started_y = false;
        started = false;

        index = 0;
}

int scanner::get_index()
{
        int tmp = index;
        return tmp;
}

int scanner::get_n()
{
        int tmp = 2*N;
        return tmp;
}
*/
