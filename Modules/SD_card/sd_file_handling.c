/*
 * File_Handling_RTOS.c
 *
 *  Created on: 14-May-2020
 *      Author: Controllerstech
 */

#include <sd_file_handling.h>

#include "stm32f4xx_hal.h"

/* =============================>>>>>>>> NO CHANGES AFTER THIS LINE =====================================>>>>>>> */

FATFS fs;  // file system
FIL fil;   // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;      // File read/write count

/**** capacity related *****/
FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

void Mount_SD(const TCHAR *path) { fresult = f_mount(&fs, path, 1); }

void Unmount_SD(const TCHAR *path) { fresult = f_mount(NULL, path, 1); }

FRESULT Write_File(char *name, char *data) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        return fresult;
    }

    else {
        /* Create a file with read write access and open it */
        fresult = f_open(&fil, name, FA_OPEN_EXISTING | FA_WRITE);
        if (fresult != FR_OK) {
            return fresult;
        }

        else {
            fresult = f_write(&fil, data, strlen(data), &bw);

            /* Close file */
            fresult = f_close(&fil);
        }
        return fresult;
    }
}

FRESULT Read_File(char *name) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        return fresult;
    }

    else {
        /* Open file to read */
        fresult = f_open(&fil, name, FA_READ);

        if (fresult != FR_OK) {
            return fresult;
        }

        /* Read data from the file
         * see the function details for the arguments */

        char *buffer = malloc(sizeof(f_size(&fil)));
        fresult = f_read(&fil, buffer, f_size(&fil), &br);
        if (fresult != FR_OK) {
        } else {
            /* Close file */
            fresult = f_close(&fil);
        }
        return fresult;
    }
}

FRESULT Create_File(char *name) {
    fresult = f_stat(name, &fno);
    if (fresult == FR_OK) {
        return fresult;
    } else {
        fresult = f_open(&fil, name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
        if (fresult != FR_OK) {
            return fresult;
        } else {
        }

        fresult = f_close(&fil);
    }
    return fresult;
}

FRESULT Update_File(char *name, char *data) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        return fresult;
    }

    else {
        /* Create a file with read write access and open it */
        fresult = f_open(&fil, name, FA_OPEN_APPEND | FA_WRITE);
        if (fresult != FR_OK) {
            return fresult;
        }

        /* Writing text */
        fresult = f_write(&fil, data, strlen(data), &bw);

        /* Close file */
        fresult = f_close(&fil);
    }
    return fresult;
}

FRESULT Remove_File(char *name) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        return fresult;
    }

    else {
        fresult = f_unlink(name);
    }
    return fresult;
}

FRESULT Create_Dir(char *name) {
    fresult = f_mkdir(name);
    return fresult;
}

FRESULT Count_Files(const char *path, uint16_t *file_count) {
    DIR dir;      // Директория
    FILINFO fno;  // Информация о файле
    FRESULT res;  // Результат операции

    *file_count = 0;  // Инициализация счетчика файлов

    // Открываем директорию
    res = f_opendir(&dir, path);
    if (res == FR_OK) {
        while (1) {
            // Читаем содержимое директории
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;  // Ошибка или конец директории

            // Пропускаем каталог "." и ".."
            if (fno.fattrib & AM_DIR) {
                continue;
            } else {
                (*file_count)++;  // Увеличиваем счетчик файлов
            }
        }
        f_closedir(&dir);  // Закрываем директорию
    }
    return res;
}