
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

class coordinate {

private:

        double dv;
        double val;

public:

        coordinate();
        coordinate(double V, double dV);
	virtual ~coordinate();

        double get_step(){return dv;}
        double get_val(){return val;}

        void set_step(double s) {dv = s;}
        void set_val(double v) {val = v;}

	double inc();
	double dec();
};

#endif //_COORDINATE_H_
