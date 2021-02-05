// coded by Pouya Mohammadi
// tel: @pouya_moh
// uni_id: 9829039

#include <stdio.h>
#include "../include/bitmap.h"
#include "../include/ui.h"

int main()
{
    int answer;     //handles flow of ui
    int getOut = 0; //check when to exit

    // app flow:
    while (1)
    {
        answer = main_menu(0);

        switch (answer)
        {
        case 1:
            getOut = invert_menu(0, NULL);
            break;
        case 2:
            getOut = show_header_info(0, NULL);
            break;
        case 3:
            help_menu(0);
            break;
        case 4:
            getOut = 1;
            break;
        default:
            break;
        }

        if (getOut == 1) //check to exit flow
            break;
    }

    return 0;
}
