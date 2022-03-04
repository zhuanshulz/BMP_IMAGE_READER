#include<stdio.h>
#include<string.h>
#pragma pack(push, 1)

typedef struct {
    unsigned short  type;                 
    unsigned int    size;                       /* File size in bytes          */
    unsigned int    reserved;
    unsigned int    offset;                     /* Offset to image data, bytes */
} HEADER;

typedef struct {
    unsigned int size;                          /* Header size in bytes      */
    int width,height;                           /* Width and height of image */
    unsigned short planes;                      /* Number of colour planes   */
    unsigned short bits;                        /* Bits per pixel            */
    unsigned int compression;                   /* Compression type          */
    unsigned int imagesize;                     /* Image size in bytes       */
    unsigned int xresolution,yresolution;       /* Pixels per meter          */
    unsigned int ncolours;                      /* Number of colours         */
    unsigned int importantcolours;              /* Important colours         */
} WINBITMAP;

typedef struct {
    unsigned int size;                          /* Header size in bytes      */
    unsigned int width,height;                  /* Width and height of image */
    unsigned short planes;                      /* Number of colour planes   */
    unsigned short bits;                        /* Bits per pixel            */
} OS21XBITMAP;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    RGB rgb;
    unsigned char alpha;
} RGBa;
#pragma pack(pop)

void read_pixel_win(int x, int y, char * filename, HEADER fileheader, WINBITMAP winbitpmap, RGB * rgb){
    FILE *filePtr;  //our file pointer
    //open file in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL){
        printf("Error0! File not found!\n");
    }
    //move file pointer to the beginning of bitmap data
    fseek(filePtr, fileheader.offset + (x + y * winbitpmap.width)*4, SEEK_SET);
    //read the bitmap file header
    fread(rgb, 3,1,filePtr);
    fclose(filePtr);
}

void read_pixela_win(int x, int y, char * filename, HEADER fileheader, WINBITMAP winbitpmap, RGBa * rgba){
    FILE *filePtr;  //our file pointer
    //open file in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL){
        printf("Error0! File not found!\n");
    }
    //move file pointer to the beginning of bitmap data
    fseek(filePtr, fileheader.offset + (x + y * winbitpmap.width)*4, SEEK_SET);
    //read the bitmap file header
    fread(rgba, 4,1,filePtr);
    fclose(filePtr);
}

unsigned short  endian_change_short(unsigned short temp){
    temp = temp >> 8 | temp <<8;
    return temp;
}

unsigned int  endian_change_int(unsigned int temp){
    temp = (temp >> 24) 
            | ((temp >> 8) & 0x0000ff00)
            | ((temp << 8) & 0x00ff0000)
            | ((temp << 24) );
    return temp;
}


void read_header(char * filename, HEADER * headerptr){
    FILE *filePtr;  //our file pointer
    //open file in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL){
        printf("Error1! File not found!\n");
    }
    //read the bitmap file header
    fread(headerptr, 14,1,filePtr);

    headerptr->type = endian_change_short(headerptr->type);
    // headerptr->size = endian_change_int(headerptr->size);
    // headerptr->offset = endian_change_int(headerptr->offset);
    fclose(filePtr);
}
void read_winbitmap(char * filename, WINBITMAP* winbitmap){
    FILE *filePtr;  //our file pointer
    //open file in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL){
        printf("Error2! File not found!\n");
    }
    //read the bitmap file header
    fseek(filePtr, 14, SEEK_SET);
    fread(winbitmap, 40,1,filePtr);
    fclose(filePtr);
}
void write_bmp_file(char * filename, HEADER * headerptr, WINBITMAP* winbitmap, RGBa* pixel_ptr){
    FILE *filePtr;  //our file pointer
    //open file in read binary mode
    filePtr = fopen(filename,"w+");
    fwrite(headerptr, sizeof(HEADER), 1, filePtr);
    fwrite(winbitmap, sizeof(WINBITMAP), 1, filePtr);
    fwrite(pixel_ptr, winbitmap->imagesize, 1, filePtr);
    fclose(filePtr);
}