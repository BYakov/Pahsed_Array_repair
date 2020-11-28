
#ifndef _RAM_CONFIG_H_
#define _RAM_CONFIG_H_

//------------------------------------------------------------------------------

class ram : public space {

private:
        ram();

        unsigned char  	        *tuned_data;  //!< Конфигурационное пространство для динамической настройки СУЛ

protected:

        const struct space_info& ram_file_info();
        int ram_reconfig(const char *config);
        int ram_reconfig(const char *config, int block_count = 0);
        const unsigned char *ram_data_block(int zone,int block);

public:
        ram(const char *ram);
        virtual ~ram();

        const char *ram_config_file();

        int ram_block_size() { return info.block_size; }
        int ram_block_count() { return info.blocks_in_zone; }
        int ram_zone_count() { return info.zones ; }

        //! Устанавливает значение элемента RAM.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param offset - смещение в блоке (номер элемента)
        \param data - элемент данных
        */
        int sul_ram_set_element(int zone, int block, int offset, u8& data);

        //! Возвращает значение элемента RAM.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param offset - смещение в блоке (номер элемента)
        \param *data - элемент данных
        */
        int sul_ram_get_element(int zone, int block, int offset, u8& data);

        //! Заполняет тестовыми данными RAM.
        /*!
        \param zone - номер сегмента (начиная с нуля)
        \param block - номер блока, относительно начала сегмента
        \param type - тип заполнения
        \param pattern - шаблон для заполнения
        */
        int sul_ram_fill(int zone, int block, space_fill_type type = FILL_RANDOM, u8 pattern = 0);

        //! Получить контрольную сумму из пространства конфигурации
        /*!
        \param devn - номер абонента для выполнения команды. 0 - сумма по всем абонентам
        */
        virtual  u16 sul_ram_space_crc(int devn = 0);

        //! Записать конфигурационную информацию во FLASH для всех абонентов
        /*!
        Записать информацию из файла конфигурации во FLASH устройства
        \param file - имя файла конфигурации
        \param devn - номер абонента. 0 - для всех абонентов.
        */
        virtual int sul_ram_load(const char *file = NULL, int devn = 0) = 0;

        //! Провести реконфигурацию пространства данными из файла.
        /*!
        Функция удаляет старое пространство, создает
        и заполняет новое конфигурационное пространство
        на основе файла config.
        \param config - имя нового файла конфигурации
        */
        virtual int sul_ram_reconfig(const char *config);

        //! Сохранить конфигурационную информацию из RAM в файл
        /*!
        Записать информацию из файла конфигурации во FLASH устройства
        \param file - имя файла конфигурации
        */
        virtual  int sul_ram_save(const char *file = NULL) = 0;

        //! Стереть конфигурационную информацию RAM
        /*!
        \param devn - номер абонента для выполнения команды. 0 - для всех абонентов
        */
        virtual  int sul_ram_erase(int devn = 0) = 0;

        //! Получить контрольную сумму информации из RAM
        /*!
        \param devn - номер абонента для выполнения команды. 0 - сумма по всем абонентам
        */
        virtual  u16 sul_ram_crc(int devn = 0) = 0;
};

//------------------------------------------------------------------------------

#endif //_RAM_CONFIG_H_
