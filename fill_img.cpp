#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C"{

#define PRIOD 3
#define LS 4*720*480

typedef struct fill_img_t{
    char *dest;
    int dest_h;
    int dest_w;
    char *src;
    int src_h;
    int src_w;
    int from_h;
    int from_w;
}fill_img;

/* typedef struct tagBITMAPFILEHEADER 
{
    short bfType;    
    int bfSize; 
    short bfReserved1; 
    short bfReserved2; 
    int bfOffBits;
} BITMAPFILEHEADER; */

int fill_rgba(fill_img_t *hd) {
    int i = 0, len = hd->src_h*PRIOD;
    char *start = 0;
    char *from = hd->src;
    for(i = hd->from_w; i < (hd->from_w + hd->src_w); i++) {
        start = hd->dest + ((i+1)* hd->dest_w + hd->from_h)*PRIOD;
        from += len;
        memcpy(start, from, len);
        //memset(start, 0xff, len);        
    }
    return 0;
}

int dump_data(char *buf, int len) {
    int i = 0;
    for(i = 0; i < len; i++) {
        if(i%16 == 0)
            printf("\n");
            
        printf(" %x ", buf[i]);
    }
    return 0;
}

int rgb_to_rgba(char *buf, char *src, int h, int w) {
    int i = 0, j = 0;
    int tmp = 0, offset = 0;
    for(i = 0; i < h; i++) {
        for(j = 0; j < h; j++) {
            offset = i*w +j;
            buf[4*offset] = src[3*offset];            
            buf[4*offset+1] = src[3*offset+1];
            buf[4*offset+2] = src[3*offset+2];
            tmp = buf[4*offset] | buf[4*offset+1] |buf[4*offset+2];
            if (tmp < 100) {
                buf[4*offset+3] = 0;
            } else {
                buf[4*offset+3] = 255;
            }
        }
    }
    return 0;
}


int main( void )
{
    char outputFilename[32] = {0};
    char inputFilename[32] = {0};
    char srcFilename[32] = {0};
    FILE *fins = NULL, *fout = NULL;
    char bheader[64] = {0};
    fill_img_t fd;
    char *mbuf = (char*)malloc(LS);
    char *sbuf = (char*)malloc(0x9bd6);
    int len = 0, offset = 0; 
    memset(&fd, 0, sizeof(fill_img));

    memcpy(outputFilename, "/sdcard/out.bmp", 15);    
    memcpy(inputFilename, "/sdcard/1.bmp", 13);
    memcpy(srcFilename, "/sdcard/2.bmp", 13);
    
    fins=fopen(srcFilename,"rb");
    if(fins == NULL) {
        printf("fins open err!!,%s\n",srcFilename);
        goto exit_1;
    }
    len = fread(&bheader, 1, 54, fins);
    offset = bheader[11] << 8 | bheader[10];
    offset = fseek(fins, offset, SEEK_SET);
    len = bheader[5] << 24 | bheader[4] << 16 | bheader[3] << 8 | bheader[2];
    
    len = fread(sbuf, 1, len, fins);
      dump_data(sbuf, 14);
    fclose(fins);
 
 

    fins=fopen(inputFilename,"rb");
    if(fins == NULL) {
        printf("fins open err!! %s \n",inputFilename);
        goto exit_1;
    }
    len = fread(&bheader, 1, 54, fins);
        dump_data((char*)&bheader, 14);
    offset = bheader[11] << 8 | bheader[10];
    offset = fseek(fins, offset, SEEK_SET);
    len = bheader[5] << 24 | bheader[4] << 16 | bheader[3] << 8 | bheader[2];
    len = fread(mbuf, 1, len, fins);
      dump_data(mbuf, 14);
    fclose(fins);
printf("\nfile %d %d %x\n", len, offset, len);


    fd.dest = mbuf;
    fd.dest_h = 720;
    fd.dest_w = 480;
    fd.src = sbuf;
    fd.src_h = 110;
    fd.src_w = 120;
    fd.from_h = 100;
    fd.from_w = 110; 
printf("file %d l:%d %x\n", len, __LINE__, len);  
    fill_rgba(&fd);
   
printf("file %d l:%d %d\n", len, __LINE__, len);    
    fout=fopen(outputFilename,"wb");
    if(fins == NULL) {
        printf("fins open err!!\n");
        goto exit_1;
    }
    fwrite(&bheader, 1, 54, fout);
    len = fwrite(mbuf, 1,   len, fout);
    fclose(fout);   
  
printf("file %d l:%d %d\n", len, __LINE__, len);   

exit_1:
    free(mbuf);
    free(sbuf);
    return 0;
}

}