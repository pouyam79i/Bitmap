// coded by Pouya Mohammadi
// tel: @pouya_moh
// uni_id: 9829039

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/bitmap.h"

/*
this function reads
pixel data which are in 
image.bmp file
*/
uint8_t *read_pixel_data(uint32_t size_in_byte, FILE *fp)
{

    static uint8_t *data = NULL;

    data = (uint8_t *)malloc((size_in_byte) * sizeof(uint8_t));

    fseek(fp, 0x0036, SEEK_SET);

    for (int i = 0; i < size_in_byte; ++i)
    {
        uint8_t temp;
        fread(&temp, sizeof(uint8_t), 1, fp);
        data[i] = temp;
    }

    return data;
}

/*
this function reads bitmab file
and save its data in the image
structure and return it
*/
bitmap_image *read_bitmap(char *filename)
{

    //opening file part
    FILE *fp;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("cannot read %s\n", filename);
        return NULL;
    }

    rewind(fp);
    //end of opening file

    //getting memory for data of image.bmp
    static bitmap_image *image = NULL;
    image = (bitmap_image *)malloc(sizeof(bitmap_image)); //get a home according to bitmap size

    //handle error if image is NULL
    if (image == NULL)
    {
        printf("not enough memory 1 \n");
        return NULL;
    }

    //puting address of data in struct of image (= null)
    image->infoHeader = NULL;
    image->header = NULL;
    image->pixelData = NULL;

    //getting memory to be able to read image.bmp header file
    bitmap_header *image_header = (bitmap_header *)malloc(sizeof(bitmap_header));

    //handle error if image_header is null
    if (image_header == NULL)
    {
        printf("not enough memory 2 \n");
        return NULL;
    }

    //getting memory to be able to read image.bmp
    bitmap_info_header *image_info_header = (bitmap_info_header *)malloc(sizeof(bitmap_info_header));

    //handle error if image_info_header is null
    if (image_info_header == NULL)
    {
        printf("not enough memory 3 \n");
        return NULL;
    }

    //reading image header file
    fseek(fp, 0x0000, SEEK_SET);
    fread(image_header, sizeof(bitmap_header), 1, fp);

    //reading image info header file
    fseek(fp, 0x00E, SEEK_SET);
    fread(image_info_header, sizeof(bitmap_info_header), 1, fp);

    uint8_t *data = NULL;
    data = read_pixel_data(image_header->file_size, fp);

    //puting data in one srtucture calling it image to be able to reture data
    image->header = image_header;
    image->infoHeader = image_info_header;
    image->pixelData = data;

    fclose(fp);
    printf("DONE Reading file\n");
    return image;
}

//to save bitmap file with an specified name
int save_bitmap_file(bitmap_image *image, char *filename)
{

    if (image == NULL)
    {
        printf("no image.bmp file to save\n");
        return 0;
    }

    FILE *fp;
    fp = fopen(filename, "wb+");

    if (fp == NULL)
    {
        printf("cannot open the file");
        return 0;
    }

    image->header->reserved1 = 0;
    image->header->reserved2 = 0;

    rewind(fp);
    fwrite((image->header), sizeof(bitmap_header), 1, fp);

    fseek(fp, 0x000E, SEEK_SET);
    fwrite((image->infoHeader), sizeof(bitmap_info_header), 1, fp);

    fseek(fp, 0x0036, SEEK_SET);
    for (int i = 0; i < image->header->file_size; i++)
    {
        uint8_t temp;
        temp = (image->pixelData)[i];
        fwrite(&temp, sizeof(uint8_t), 1, fp);
    }

    fclose(fp);
    return 1;
}

/*
This function frees
memory which is allocated
to read image.bmp
*/
void free_bitmap_file(bitmap_image *image)
{
    if (image != NULL)
    {
        if (image->header != NULL)
            free((image->header));
        if (image->infoHeader != NULL)
            free((image->infoHeader));
        if (image->pixelData != NULL)
            free((image->pixelData));
        free(image);
    }
    printf("Memory is free!");
}

/*
this function invert
bytes of pixels 
*/
bitmap_image *invert_pixel(bitmap_image *image)
{
    int i;

    for (i = 0; i < image->header->file_size; i++)
    {
        uint8_t temp = (uint8_t) ~(image->pixelData)[i];
        (image->pixelData)[i] = temp;
    }

    return image;
}
