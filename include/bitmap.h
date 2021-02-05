// coded by Pouya Mohammadi
// tel: @pouya_moh
// uni_id: 9829039

#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//header structure
#pragma pack(push, 1) // to force compiler to use 1 byte packing
typedef struct
{ // Windows Structure: BITMAPFILEHEADER

   char signature[2];    // type of file 'BM'
   uint32_t file_size;   // file size in bytes
   uint16_t reserved1;   // unused value (must be 0)
   uint16_t reserved2;   // unused value (must be 0)
   uint32_t data_offset; // offset from beginning of file to the beginning of the bitmap data

} bitmap_header;
#pragma(pop)

//info header structure
#pragma pack(push, 1) // to force compiler to use 1 byte packing
typedef struct
{ // Windows Structure: BITMAPINFOHEADER

   uint32_t dib_header_size;    // number of bytes required by the structure
   int32_t width;               // horizontal width of bitmap in pixels
   int32_t height;              /*
 * vertical height of bitmap in pixels
 * if positive, starts from bottom-left (bottom-up DIB)
 * if negative, starts from top-left  (top-down DIB)
 */
   uint16_t planes;             // number of planes (must be = 1)
   uint16_t bit_per_pixel;      /*
 * Bits per Pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
 *1 = monochrome palette. NumColors = 1
 *4 = 4bit palletized. NumColors = 16
 *8 = 8bit palletized. NumColors = 256
 *16 = 16bit RGB. NumColors = 65536
 *24 = 24bit RGB. NumColors = 16M
 */
   uint32_t compression;        /*
 *Type of Compression
 *0 = BI_RGB   no compression
 *1 = BI_RLE8 8bit RLE encoding
 *2 = BI_RLE4 4bit RLE encoding
 */
   uint32_t image_size;         /*
 * 	(compressed) Size of Image
 * It is valid to set this =0 if Compression = 0
 */
   uint32_t x_pixels_per_meter; //horizontal resolution: Pixels/meter
   uint32_t y_pixels_per_meter; //vertical resolution: Pixels/meter
   uint32_t colors_used;        /*
 * Number of actually used colors.
 * For a 8-bit pixel bitmap this will be 100h or 256.
 */
   uint32_t important_colors;   //	Number of important colors (0 = all)

} bitmap_info_header;
#pragma pack(pop)

/*
this is image structure:
which includes 
header ,infoheader and pixels data
in one structure.
*/
typedef struct
{

   bitmap_header *header;          // header file
   bitmap_info_header *infoHeader; // info header file
   uint8_t *pixelData;             //bytes of pixels
} bitmap_image;

bitmap_image *read_bitmap(char *filename);

uint8_t *read_pixel_data(uint32_t size_in_byte, FILE *fp);

/*
this function is for 
saving image.bmp file
and save it in the 
same directory as
program file is.
*/
int save_bitmap_file(bitmap_image *image, char *filename);

/*
this function is for
freeing allocated memory
which was used to 
save image.bmp info
*/
void free_bitmap_file(bitmap_image *image);

/*
this function inver
pixels byte
*/
bitmap_image *invert_pixel(bitmap_image *image);

#endif //BITMAP_H
