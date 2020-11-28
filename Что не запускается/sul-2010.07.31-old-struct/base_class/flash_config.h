
#ifndef _FLASH_CONFIG_H_
#define _FLASH_CONFIG_H_

#ifndef _SUL_CONFIG_H_
    #include "sul_config.h"
#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

class flash : public space {

private:
        flash();

protected:

        //! Возвращает информацию о структуре конфигурационного пространстве FLASH.
        const struct space_info& flash_file_info();

        //! Получить блок данных из конфигурационного пространства FLASH
        /*!
        \param zone - номер сегмента (начиная с нуля) из которого вывести блок .
        \param block - номер блока относительно номера сегмента.
        */
        const unsigned char *flash_data_block(int zone,int block);

public:

        flash(const char *file, int modules, int channels);
        virtual ~flash();

        //! Возвращает имя конфигурационного файла FLASH.
        const char *flash_config_file();

        //! Возвращает размер блока данных FLASH.
        int flash_block_size() { return info.block_size ; }

        //! Возвращает количество блоков данных FLASH в одном сегменте.
        int flash_block_count() { return info.blocks_in_zone ; }

        //! Возвращает количество сегментов данных FLASH в пространстве.
        int flash_zone_count() { return info.zones ; }

        //! Устанавливает значение элемента FLASH.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param offset - смещение в блоке (номер элемента)
        \param data - элемент данных
        */
        int sul_flash_set_element(int zone, int block, int offset, u8& data);

        //! Возвращает значение элемента FLASH.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param offset - смещение в блоке (номер элемента)
        \param *data - элемент данных
        */
        int sul_flash_get_element(int zone, int block, int offset, u8& data);

        //! Заполняет тестовыми данными FLASH.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param type - тип заполнения
        \param pattern - шаблон для заполнения
        */
        int sul_flash_fill(int zone, int block, space_fill_type type = FILL_RANDOM, u8 pattern = 0);

        //! Получить контрольную сумму из пространства конфигурации
        /*!
        \param devn - номер абонента для выполнения команды. 0 - сумма по всем абонентам
        */
        u16 sul_flash_space_crc(int devn = 0);

        //! Записать конфигурационную информацию во FLASH для всех абонентов
        /*!
        Записать информацию из файла конфигурации во FLASH устройства
        \param file - имя файла конфигурации
        \param devn - номер абонента. 0 - для всех абонентов.
        */
        virtual  int sul_flash_load(const char *file = NULL, int devn = 0) = 0;

        //! Провести реконфигурацию пространства данными из файла.
        /*!
        Функция удаляет старое пространство, создает
        и заполняет новое конфигурационное пространство
        на основе файла config.
        \param config - имя нового файла конфигурации
        */
        virtual int sul_flash_reconfig(const char *config);

        //! Сохранить конфигурационную информацию из FLASH в файл
        /*!
        Записать информацию из файла конфигурации во FLASH устройства
        \param file - имя файла конфигурации
        */
        virtual  int sul_flash_save(const char *file = NULL) = 0;

        //! Стереть конфигурационную информацию FLASH
        /*!
        \param devn - номер абонента для выполнения команды. 0 - для всех абонентов
        */
        virtual  int sul_flash_erase(int devn = 0) = 0;

        //! Получить контрольную сумму информации из FLASH
        /*!
        \param devn - номер абонента для выполнения команды. 0 - сумма по всем абонентам
        */
        virtual  u16 sul_flash_crc(int devn = 0) = 0;
};

//------------------------------------------------------------------------------

#endif //_FLASH_CONFIG_H_
