// coded by Pouya Mohammadi
// tel: @pouya_moh
// uni_id: 9829039

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/bitmap.h"
#include "../include/ui.h"

//this function clears terminal
void clear(void)
{

#ifdef _WIN32 //checks if it is windows
    system("cls");
#endif
#ifdef __unix //checks if it is linux
    system("clear");
#endif
#ifdef __MACH__ // checks if it is mac os
    system("clear");
#endif
}

//checks file format if it is not ".bmp" return 0
int checkFormat(char *filename, int size)
{
    char format[5];
    format[0] = filename[size - 4];
    format[1] = filename[size - 3];
    format[2] = filename[size - 2];
    format[3] = filename[size - 1];
    format[5] = '\0';

    if (strcmp(format, ".bmp") == 0)
        return 1;

    return 0;
}

//shows main menu information
//and handles its input!
int main_menu(int error)
{
    clear();

    if (error == 1)
        printf("Wrong Input.\n");

    //shown information on the main menu
    printf("Main Menu:\n");
    printf("1- Invert image Color\n");
    printf("2- Show bitmap file info\n");
    printf("3- Help (Read me to know)\n");
    printf("4- Exit\n");
    printf("Input:\n");

    int input = 0;
    char inputC = 0;
    scanf("%d", &input);

    if (input > 4 || input < 1)
        return main_menu(1);

    return input;
}

//this function handles help messages
void help_menu(int error)
{

    clear();
    if (error == 1)
        printf("Wrong Input.\n");

    //shown information in this menu
    printf("1- How to input file location or name (reading file)\n");
    printf("2- How to save output file (over write or copy)\n");
    printf("3- What information of file.bmp can be shown\n");
    printf("4- How this app works\n");
    printf("5- Back to Main Menu\n");
    printf("Input:\n");

    int input = 0;
    scanf("%d", &input);
    if (input > 5 || input < 1)
        main_menu(1);

    if (input != 5)
        help_message(input);

    return;
}

/*
this function handles 
saving file process
*/
int save_bitmap_menu(int error, bitmap_image *image, char *filename)
{

    if (error == 1)
    {
        printf("Wrong Input\n");
        printf("Format must be '.bmp'\n");
    }

    char new_filename[1024];
    int output;

    printf("Input 1 to overwrite on the read file\n");
    printf("or input file name (like: image.bmp):\n");

    scanf("%s", new_filename);

    if (strlen(new_filename) < 5)
    {

        if (strlen(new_filename) == 1)
        {

            //checks if the user wants to overwrite the file
            if (new_filename[0] == '1')
            {
                clear();
                return save_bitmap_file(image, filename);
            }
            else
            {
                return save_bitmap_menu(1, image, filename);
            }
        }
        else
        {
            return save_bitmap_menu(1, image, filename);
        }
    }

    if (checkFormat(new_filename, strlen(new_filename)) == 0)
    {
        return save_bitmap_menu(1, image, filename);
    }

    clear();
    return save_bitmap_file(image, new_filename);
}

/*
this function reads image.bmp
and inverts the pixels data
and checks if sth wrong happened!
*/
bitmap_image *invert_bitmap_file(char *filename, int size)
{

    static bitmap_image *image = NULL;
    image = read_bitmap(filename); // to read the file

    if (image == NULL)
    {
        printf("\n\nSomethig went wrong during reading input file\n");
        printf("or \"%s\" does not exist!\n\n", filename);
        free_bitmap_file(image); // if sth  bad happened :)
        exit(0);
        return NULL;
    }

    image = invert_pixel(image); // to invert pixels data

    if (image == NULL)
    {
        printf("\n\nsomething went wrong during inverting pixels\n\n");
        free_bitmap_file(image); // if sth  bad happened :)
        exit(0);
        return NULL;
    }

    return image;
}

//this function handles inverting of file process!
int invert_menu(int error, bitmap_image *image)
{
    clear();

    if (error == 1)
        printf("Wrong input\n");
    else if (error == 2)
    {
        printf("wrong input\n");
        printf("it must be '.bmp' \n");
    }

    printf("Import file name to read a '.bmp' file\n");
    printf("or enter 1 to return to main menu\n");
    printf("Input:\n");
    char filename[1024] = {0};
    scanf("%s", filename);
    if (strlen(filename) < 5)
    {
        if (strlen(filename) == 1)
        {
            if (filename[0] == '1')
            {
                return 0;
            }
            return invert_menu(1, image);
        }
        else
        {
            return invert_menu(1, image);
        }
    }

    if (checkFormat(filename, strlen(filename)) == 0)
    { // checks if file format is not correct!
        return invert_menu(2, image);
    }

    image = invert_bitmap_file(filename, strlen(filename)); // read file and inver data the return a bitmap_image structure

    if (save_bitmap_menu(0, image, filename) == 0)
    { //save file and checks if it goes correctly

        printf("\n\nError: Cannot save file!\n\n");
        if (image != NULL)
            free_bitmap_file(image);
        printf("\n Enter to return to main menu\n");
        getchar();
        getchar();
        main_menu(0);
    }

    printf("\n\nDone!\n\n");

    free_bitmap_file(image);

    return 1;
}

//this function display help messages
void help_message(int message)
{
    clear();

    //one of this parts will be shown to the user
    if (message == 1)
    {

        printf("File must be in the same directory as program\n");
        printf("Input file can be like what is shown below:\n");
        printf("    imagename.bmp\n");
        printf("Remember: input all chars of file format '.bmp' as lower case chars\n");
    }
    else if (message == 2)
    {

        printf("To save the output file you have two choice:\n");
        printf("1- Overwrite on the file: \n");
        printf("To do this you just enter 1 as input\n");
        printf("2- Save with a different name: \n");
        printf("To do this you must enter a new name like: imagename.bmp\n");
        printf("Remember: input all chars of file format '.bmp' as lower case chars\n");
    }
    else if (message == 3)
    {

        printf("Shown information by this app is:\n");
        printf("File size, which is shown in byte\n");
        printf("Bit per pixels of image\n");
        printf("Width and height of image\n");
    }
    else if (message == 4)
    {

        printf("This app read the image.bmp file data, then it uses \n");
        printf("the information in the header or header_info file (where ever needed)\n");
        printf("finaly it invert the pixels bytes \n");
        printf("and save the information.\n");
    }

    printf("\n\nEnter to back to main manu\n\n");
    getchar();
    getchar();
    return;
}

/*
this function is used to show some
information of image.bmp :
size of file (in byte)
bit per pixel
width and height
*/
int show_header_info(int error, bitmap_image *image)
{
    clear();

    if (error == 1)
        printf("Wrong input\n");
    else if (error == 2)
    {
        printf("wrong input\n");
        printf("it must be '.bmp' \n");
    }

    printf("Import file name to read a '.bmp' file\n");
    printf("or enter 1 to return to main menu\n");
    printf("Input:\n");

    //check if filename is correct
    char filename[1024] = {0};
    scanf("%s", filename);
    if (strlen(filename) < 5)
    {
        if (strlen(filename) == 1)
        {
            if (filename[0] == '1')
            {
                return 0;
            }
            return show_header_info(1, image);
        }
        else
        {
            return show_header_info(1, image);
        }
    }

    if (checkFormat(filename, strlen(filename)) == 0)
    { // checks if file format is not correct!
        return show_header_info(2, image);
    }

    image = read_bitmap(filename); // read image information

    //handles error of reading image process
    if (image == NULL)
    {
        printf("\n\nSomethig went wrong during reading input file\n");
        printf("or \"%s\" does not exist!\n\n", filename);
        free_bitmap_file(image); // if sth went wrong happened :)
        exit(0);
        return 1;
    }

    clear();

    int32_t height = image->infoHeader->height;
    int32_t width = image->infoHeader->width;

    if (width < 0) // in case of negative width value
        width *= -1;
    if (height < 0) // in case of negative height value
        height *= -1;

    //shown information
    printf("File Size (in byte): %d\n", image->header->file_size);
    printf("Bit Per Pixel: %d\n", image->infoHeader->bit_per_pixel);
    printf("Size of Image(in pixel): W: %d,H: %d\n", width, height);

    printf("\n\nDone\n\n");

    free_bitmap_file(image); // frees memory

    return 1;
}
