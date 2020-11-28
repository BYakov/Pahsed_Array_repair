//---------------------------------------------------------------------------

#ifndef _SUL_TUNE_H_
#define _SUL_TUNE_H_

#ifndef _SUL_BASE_H_
#include "..\base_class\sul_base.h"
#endif

//---------------------------------------------------------------------------

class sul_tune
{
private:

    int     total_channels;
    int     connected_channels;

    sul_tune();

    bool    read_slope_file(const char *fname);
    bool    read_f0_file(const char *fname);
    int     calculate_xy();
    void    calculate_sphere(double SX, double SY, double R, double Lambda);
    int     calculate_revises();

public:

    sul_tune(int N);
    virtual ~sul_tune();

    double  *calc_array;
    int     *CoordX;
    int     *CoordY;
    double  *F0;
    double  *Slope;

    void outfile(int [650]);

    double  lambda, SX1, SX2, SX3, SX4, SX5, SX6, SX7, SX8,
        SY1, SY2, SY3, SY4, SY5, SY6, SY7, SY8, R1, R2, R3,
        R4, R5, R6, R7, R8, Kcant, Lambda1, Lambda2,
        Lambda3, Lambda4, Lambda5, Lambda6, Lambda7,
        Lambda8, F0_add;
    int F1[951], CORR1_128[650],
        CORR2_128[650],CORR3_128[650],CORR4_128[650],
        CORR5_128[650],CORR6_128[650],CORR7_128[650],
        CORR8_128[650],CANT_128[650];

    float F_eval[650], CORR1[650], CORR2[650], CORR3[650],
        CORR4[650], CORR5[650], CORR6[650], CORR7[650],
        CORR8[650], CANT[650],
        CORR1_F0[650], CORR2_F0[650], CORR3_F0[650], CORR4_F0[650],
        CORR5_F0[650], CORR6_F0[650], CORR7_F0[650], CORR8_F0[650];

    FILE   *fid_outcorr, *fid_incant, *fid_inf0;


    bool err;
};
#endif //_SUL_TUNE_H_





