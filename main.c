#include "bmp_reader.h"
#include<stdlib.h>

void header_init_4k(HEADER* header_4k, WINBITMAP* winbitmap_4k){
    header_4k->type      =19778     ;       // 0x4D 0x42
    header_4k->size      =33177654  ;       // 3840*2160*4 + 14fileheader + 40winbitmap
    header_4k->reserved  =0         ;
    header_4k->offset    =54        ;       // 14fileheader + 40winbitmap

    winbitmap_4k->size   =40        ;       // fixed
    winbitmap_4k->width  =3840      ;       // 3840 pixels width
    winbitmap_4k->height =2160      ;       // 2160 pixels height
    winbitmap_4k->planes =1         ;
    winbitmap_4k->bits   =32        ;       // 32bpp
    winbitmap_4k->compression=0     ;
    winbitmap_4k->imagesize=33177600;       // 3840*2160*4
    winbitmap_4k->xresolution=3779  ;
    winbitmap_4k->yresolution=3779  ;
    winbitmap_4k->ncolours=0        ;
    winbitmap_4k->importantcolours=0;
}


void main(){
    HEADER header, header_4k;
    WINBITMAP winbitmap, winbitmap_4k;
    RGB pixel;
    RGBa* pixel_new;
    RGBa* pixel_new_backup;
    pixel_new = (RGBa*) malloc(sizeof(RGBa) * 3840 * 2160);
    pixel_new_backup = pixel_new;
    char* bmpfile="lena_32bpp.bmp";
    char* bmpfile_new="new_32bpp.bmp";
    read_header(bmpfile, &header);
    read_winbitmap(bmpfile, &winbitmap);
    read_pixel_win(0,0,bmpfile,header,winbitmap, &pixel);

    printf("pixel.r = %d \n",pixel.r);
    printf("pixel.g = %d \n",pixel.g);
    printf("pixel.b = %d \n",pixel.b);

    header_init_4k(&header_4k,&winbitmap_4k);
    for (int i =0; i<3840;i++){
        for(int j=0; j<2160;j++){
            pixel_new->r = (unsigned char)(i+j);
            pixel_new->g = (unsigned char)(i+j);
            pixel_new->b = (unsigned char)(i+j);
            pixel_new->alpha = (unsigned char)0;
            pixel_new++;
        }
    }

    write_bmp_file(bmpfile_new, &header_4k, &winbitmap_4k, pixel_new_backup);
    free(pixel_new_backup);
}