/*
 * File_Handling_RTOS.h
 *
 *  Created on: 14-May-2020
 *      Author: Controllerstech
 */

#ifndef FILE_HANDLING_RTOS_H_
#define FILE_HANDLING_RTOS_H_

#include "fatfs.h"
#include "stdio.h"
#include "string.h"
/* mounts the sd card*/
void Mount_SD(const TCHAR *path);

/* unmounts the sd card*/
void Unmount_SD(const TCHAR *path);

/* write the data to the file
 * @ name : is the path to the file*/
FRESULT Write_File(char *name, char *data);

/* read data from the file
 * @ name : is the path to the file*/
FRESULT Read_File(char *name);

/* creates the file, if it does not exists
 * @ name : is the path to the file*/
FRESULT Create_File(char *name);

/* Removes the file from the sd card
 * @ name : is the path to the file*/
FRESULT Remove_File(char *name);

/* creates a directory
 * @ name: is the path to the directory
 */
FRESULT Create_Dir(char *name);

/* updates the file. write pointer is set to the end of the file
 * @ name : is the path to the file
 */
FRESULT Update_File(char *name, char *data);

FRESULT Count_Files(const char *path, uint16_t *file_count);

#endif /* FILE_HANDLING_RTOS_H_ */
