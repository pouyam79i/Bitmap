// coded by Pouya Mohammadi
// tel: @pouya_moh
// uni_id: 9829039

#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"

void clear(void);                                                     // used to clear terminal
int main_menu(int error);                                             // main menu handler function
int checkFormat(char *filename, int size);                            // it checks file format if it is not '.bmp'
void help_menu(int error);                                            // help menu handler function
void help_message(int message);                                       // contains help messages
int save_bitmap_menu(int error, bitmap_image *image, char *filename); // handles saving process
int invert_menu(int error, bitmap_image *image);                      //handles from reading file to saving it process
bitmap_image *invet_bitmap_file(char *filename, int size);            //handles reading and inverting process
int show_header_info(int error, bitmap_image *image);                 // shows size(in byte),bit per pixel, width x height

#endif
