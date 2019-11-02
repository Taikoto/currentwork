#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern "C"{

#define PRIOD 3
#define LS 4*840*720

#define OUT_PICTURE_PATH "/home1/caihuanming/workspace/test/draw_picture/out.bmp"
#define O22_PICTURE_PATH "/home1/caihuanming/workspace/test/draw_picture/o22.bmp"
#define INPUT_PICTURE_PATH "/home1/caihuanming/workspace/test/draw_picture/1.bmp"
#define SRC_PICTURE_PATH "/home1/caihuanming/workspace/test/draw_picture/2.bmp"

typedef unsigned char BYTE ;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
#pragma pack(1)
typedef struct BMPFileHead_t {
    WORD bfType;   /* 说明文件的类型 */
    DWORD bfSize;   /* 说明文件的大小，用字节为单位 */
    WORD bfReserved1;  /* 保留，设置为0 */
    WORD bfReserved2;  /* 保留，设置为0 */
    DWORD bfOffsetBytes;  /* 说明从BITMAPFILEHEADER结构开始到实际的图像数据之间的字节偏移量 */

}BMPFileHead; //14字节,但是sizeof计算长度时为16字节


typedef struct BMPHeaderInfo_t {
    DWORD biSize;   /* 说明结构体所需字节数 */
    LONG biWidth;   /* 以像素为单位说明图像的宽度 */
    LONG biHeight;   /* 以像素为单位说明图像的高度 */
    WORD biPlanes;   /* 说明位面数，必须为1 */
    WORD biBitCount;  /* 说明位数/像素，1、2、4、8、24 */
    DWORD biCompression; /* 说明图像是否压缩及压缩类型BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS */
    DWORD biSizeImage;  /* 以字节为单位说明图像大小，必须是4的整数倍*/
    LONG biXPixelsPerMeter; /*目标设备的水平分辨率，像素/米 */
    LONG biYPixelsPerMeter; /*目标设备的垂直分辨率，像素/米 */
    DWORD biClrUsed;  /* 说明图像实际用到的颜色数，如果为0，则颜色数为2的biBitCount次方 */
    DWORD biClrImportant; /*说明对图像显示有重要影响的颜色索引的数目，如果是0，表示都重要。*/
}BMPHeaderInfo;  //40字节
#pragma pack()

typedef struct  RGB_t{
    BYTE rgbBlue;  /*指定蓝色分量*/
    BYTE rgbGreen;  /*指定绿色分量*/
    BYTE rgbRed;  /*指定红色分量*/
    BYTE rgbReserved; /*保留，指定为0*/
}RGB;

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

inline int fill_rgba(fill_img_t *hd) {
    int i = 0, len = (hd->src_w+1)*PRIOD-1;
    char *start = 0;
    char *from;
    from = hd->src;
    printf("\n %p %p %p  \n", from, hd->dest, hd->src);
    for(i = 0; i < hd->src_h; i++) {
        start = hd->dest + ((i + hd->from_w)* hd->dest_w + hd->from_w)*PRIOD;
//        if(i%10 == 0)
//            printf("%p %p %p %d  %d \n",hd->dest, start, from, len, ((i + hd->from_w)* hd->dest_w + hd->from_w)*PRIOD);
        memcpy(start, from, len);
        from += len;
      //  memset(start, 0xff, len);
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

void get_bmpdata(char * bmpfilename,char * buf)
{
    FILE * fp;
    int i = 0, j = 0, len = 0;
    int offset = 0, ct = 0;
    WORD lineSize;    //一行的字节个数
    BMPFileHead bfh;   //定义文件头信息
    BMPHeaderInfo bhi;   //定义bmp头信息
    RGB  color[256];
    BYTE * databuf;    //数据缓存
    char *tbuf;
    if((fp = fopen(bmpfilename, "r+b"))== NULL){
        printf("open bmpfile error!\n");
        exit(EXIT_FAILURE);
    }
    //读取文件头信息
    if ((fread(&bfh,sizeof(WORD), 7, fp)) < 7){
        printf("read file error!\n");
        exit(EXIT_FAILURE);
    }
    printf("BMPFileHead  %x %x %x\n", bfh.bfType, bfh.bfSize,bfh.bfOffsetBytes);
    //读取位图信息头
    if ((fread(&bhi,sizeof(WORD),20 , fp)) < 20){
        printf("read file error!\n");
        exit(EXIT_FAILURE);
    }
//    if (bhi.biHeight%2 == 1 || bhi.biWidth%2 ==1){
//        printf("the size of picture is wrong!\n");
//        exit(EXIT_FAILURE);
//    }
        printf("BMPHeaderInfo  %x %d %d\n", bhi.biSizeImage, bhi.biWidth, bhi.biHeight);
    //如果不是24位色则获取调色板
    if (bhi.biBitCount != 0x18){
        for (i=0;i<pow(2,bhi.biBitCount);i++){
           fread(&(color[i]),sizeof(BYTE), 4, fp);
        }
    }
    lineSize = bhi.biSizeImage/bhi.biHeight;
    //分配内存获取bmp数据
    databuf = (BYTE *)malloc(sizeof(BYTE)*bhi.biSizeImage);
    if (databuf == NULL){
        printf("mallocation error!\n");
        exit(EXIT_FAILURE);
    }
    tbuf = (char *)malloc(3*bhi.biWidth*bhi.biHeight);
    if (tbuf == NULL){
        printf("mallocation error!\n");
        exit(EXIT_FAILURE);
    }
    //一次性读取全部数据
    for (i = bhi.biSizeImage-lineSize;i>=0;i=i-lineSize){
        len = fread(databuf+i, sizeof(BYTE),  lineSize, fp);
        if (len < lineSize){
            printf("get %dth data error! %x %x \n",i, len,  lineSize);
            //exit(EXIT_FAILURE);
        }
    }
    fclose(fp);

    //格式转换
    for(i = 0; i < bhi.biHeight; i++) {
        for(j = 0; j < bhi.biWidth; j++) {
            offset = (i*bhi.biHeight + j);
            ct = (int) databuf[offset] & 0xff;            
            memcpy(&buf[offset*4], &color[ct], 4);
//            buf[offset*PRIOD] = color[ct].rgbBlue;
//            buf[offset*PRIOD+1] = color[ct].rgbGreen;
//            buf[offset*PRIOD+2] = color[ct].rgbRed;
//            buf[offset*PRIOD+3] = color[ct].rgbReserved;
        }
    }
    if((fp = fopen(O22_PICTURE_PATH, "w+b"))== NULL){
        printf("open bmpfile error!\n");
        exit(EXIT_FAILURE);
    }
    bfh.bfSize = 3*bhi.biWidth*bhi.biHeight + 0x36;
    bfh.bfOffsetBytes = 0x36;
    bhi.biBitCount = 24;
    bhi.biCompression = 0; 
    bhi.biSizeImage = 0; 
    bhi.biClrUsed = 0; 
    bhi.biClrImportant = 0; 
 
    fwrite(buf, 4*bhi.biWidth*bhi.biHeight, 1, fp);
    fclose(fp);
    //释放内存关闭文件
    free(databuf);
    free(tbuf);
  //  fclose(fv);
}



int main( void )
{
    char outputFilename[100] = {0};
    char output2Filename[100] = {0};
    char inputFilename[100] = {0};
    char srcFilename[100] = {0};
    FILE *fins = NULL, *fout = NULL;
    char bheader[64] = {0};
    fill_img_t fd;
    char *mbuf = (char*)malloc(LS);
    char *sbuf = (char*)malloc(110*120*3);
    int len = 0, offset = 0;
    memset(&fd, 0, sizeof(fill_img));
printf("___%p %p %d\n",mbuf,sbuf, len );
    memcpy(outputFilename, OUT_PICTURE_PATH, 100);
    memcpy(output2Filename, O22_PICTURE_PATH, 100);
    memcpy(inputFilename, INPUT_PICTURE_PATH, 100);
    memcpy(srcFilename, SRC_PICTURE_PATH, 100);

get_bmpdata(output2Filename, mbuf);

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
    fclose(fins);
dump_data(sbuf, 64);
    fins=fopen(inputFilename,"rb");
    if(fins == NULL) {
        printf("fins open err!! %s \n",inputFilename);
        goto exit_1;
    }
    len = fread(&bheader, 1, 54, fins);
    offset = bheader[11] << 8 | bheader[10];
    offset = fseek(fins, offset, SEEK_SET);
    len = bheader[5] << 24 | bheader[4] << 16 | bheader[3] << 8 | bheader[2];
    len = fread(mbuf, 1, len, fins);
    fclose(fins);

    fd.dest = &mbuf[0];
    fd.dest_w = 840;
    fd.dest_h = 720;
    fd.src = &sbuf[0];
    fd.src_h = 120;
    fd.src_w = 110;
    fd.from_h = 120;
    fd.from_w = 120;
    fill_rgba(&fd);

    fout=fopen(outputFilename,"wb");
    if(fins == NULL) {
        printf("fins open err!!\n");
        goto exit_1;
    }
    fwrite(&bheader, 1, 54, fout);
    len = fwrite(mbuf, 1,   len, fout);
    fclose(fout);

exit_1:
    free(mbuf);
    free(sbuf);
    return 0;
}

}
