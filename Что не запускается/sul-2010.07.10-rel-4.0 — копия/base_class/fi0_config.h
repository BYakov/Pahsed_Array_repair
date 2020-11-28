
#ifndef _FI0_CONFIG_H_
#define _FI0_CONFIG_H_

//-------------------------------------------------------------------------

#include <vector>

//-------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------

class fi0 {

private:
        fi0();

	bool		configured;
	vector<int>	phases;

protected:
        int read_data_file(const char *file);

public:

        fi0(const char *file);
        virtual ~fi0();

        //! Возвращает значение элемента PHASE0.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param offset - смещение в блоке (номер элемента)
        \param *data - элемент данных
        */
	int sul_fi0_get_element(unsigned channel, int& data);

        bool fi0_configured() { return configured; };
};

//-------------------------------------------------------------------------

#endif //_FI0_CONFIG_H_
