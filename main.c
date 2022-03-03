#include "bmp_reader.h"

void main(){
    HEADER header;
    WINBITMAP winbitmap;
    RGB pixel;
    char* bmpfile="lena_32bpp.bmp";
    read_header(bmpfile, &header);
    read_winbitmap(bmpfile, &winbitmap);
    read_pixel_win(0,0,bmpfile,header,winbitmap, &pixel);

    printf("pixel.r = %d \n",pixel.r);
    printf("pixel.g = %d \n",pixel.g);
    printf("pixel.b = %d \n",pixel.b);
}