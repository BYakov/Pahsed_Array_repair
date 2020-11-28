#ifndef PROCESS_TYPE_H
#define PROCESS_TYPE_H

enum processing_type {

    processing_channels,    //!< Обработка состояния каналов
    processing_calculators, //!< Обработка кодов вычислителей
    processing_phases,	    //!< Обработка кодов фаз
    processing_grids,	    //!< Обработка антенной решетки
    processing_pulses,      //!< Обработка кодов установки
};

#endif // PROCESS_TYPE_H
