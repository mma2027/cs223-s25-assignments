/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 03/07/2025
 * Description: Turns a binary into a 1bpp ascii art
 ---------------------------------------------*/
#include <stdio.h>

int main() {
    //var
    unsigned long img;

    scanf(" %lx", &img);
    printf("Image (unsigned long): %lx\n", img);

    //extracting each bit through masking
    for( int i = 0; i < 8; i++){
        for ( int j = 0; j < 8; j ++){
            if( (img & (0x1ul << (63 - (8 * i+j)))) > 0 ){
                printf("@ ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    return 0;
}
