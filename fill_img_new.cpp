
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern "C"{

#define PRIOD 3
#define LS 4*925*480

typedef unsigned char BYTE ;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
#pragma pack(1)
typedef struct BMPFileHead_t {
    WORD bfType;   /* ˵���ļ������� */
    DWORD bfSize;   /* ˵���ļ��Ĵ�С�����ֽ�Ϊ��λ */
    WORD bfReserved1;  /* ����������Ϊ0 */
    WORD bfReserved2;  /* ����������Ϊ0 */
    DWORD bfOffsetBytes;  /* ˵����BITMAPFILEHEADER�ṹ��ʼ��ʵ�ʵ�ͼ������֮����ֽ�ƫ���� */

}BMPFileHead; //14�ֽ�,����sizeof���㳤��ʱΪ16�ֽ�


typedef struct BMPHeaderInfo_t {
    DWORD biSize;   /* ˵���ṹ�������ֽ��� */
    LONG biWidth;   /* ������Ϊ��λ˵��ͼ��Ŀ�� */
    LONG biHeight;   /* ������Ϊ��λ˵��ͼ��ĸ߶� */
    WORD biPlanes;   /* ˵��λ����������Ϊ1 */
    WORD biBitCount;  /* ˵��λ��/���أ�1��2��4��8��24 */
    DWORD biCompression; /* ˵��ͼ���Ƿ�ѹ����ѹ������BI_RGB��BI_RLE8��BI_RLE4��BI_BITFIELDS */
    DWORD biSizeImage;  /* ���ֽ�Ϊ��λ˵��ͼ���С��������4��������*/
    LONG biXPixelsPerMeter; /*Ŀ���豸��ˮƽ�ֱ��ʣ�����/�� */
    LONG biYPixelsPerMeter; /*Ŀ���豸�Ĵ�ֱ�ֱ��ʣ�����/�� */
    DWORD biClrUsed;  /* ˵��ͼ��ʵ���õ�����ɫ�������Ϊ0������ɫ��Ϊ2��biBitCount�η� */
    DWORD biClrImportant; /*˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��*/
}BMPHeaderInfo;  //40�ֽ�
#pragma pack()

typedef struct  RGB_t{
    BYTE rgbBlue;  /*ָ����ɫ����*/
    BYTE rgbGreen;  /*ָ����ɫ����*/
    BYTE rgbRed;  /*ָ����ɫ����*/
    BYTE rgbReserved; /*������ָ��Ϊ0*/
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
    WORD lineSize;    //һ�е��ֽڸ���
    BMPFileHead bfh;   //�����ļ�ͷ��Ϣ
    BMPHeaderInfo bhi;   //����bmpͷ��Ϣ
    RGB  color[256];
    BYTE * databuf;    //���ݻ���
    char *tbuf;
    if((fp = fopen(bmpfilename, "r+b"))== NULL){
        printf("open bmpfile error!\n");
        exit(EXIT_FAILURE);
    }
    //��ȡ�ļ�ͷ��Ϣ
    if ((fread(&bfh,sizeof(WORD), 7, fp)) < 7){
        printf("read file error!\n");
        exit(EXIT_FAILURE);
    }
    printf("BMPFileHead  %x %x %x\n", bfh.bfType, bfh.bfSize,bfh.bfOffsetBytes);
    //��ȡλͼ��Ϣͷ
    if ((fread(&bhi,sizeof(WORD),20 , fp)) < 20){
        printf("read file error!\n");
        exit(EXIT_FAILURE);
    }
//    if (bhi.biHeight%2 == 1 || bhi.biWidth%2 ==1){
//        printf("the size of picture is wrong!\n");
//        exit(EXIT_FAILURE);
//    }
        printf("BMPHeaderInfo  %x %d %d\n", bhi.biSizeImage, bhi.biWidth, bhi.biHeight);
    //�������24λɫ���ȡ��ɫ��
    if (bhi.biBitCount != 0x18){
        for (i=0;i<pow(2,bhi.biBitCount);i++){
           fread(&(color[i]),sizeof(BYTE), 4, fp);
        }
    }
    lineSize = bhi.biSizeImage/bhi.biHeight;
    //�����ڴ��ȡbmp����
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
    //һ���Զ�ȡȫ������
    for (i = bhi.biSizeImage-lineSize;i>=0;i=i-lineSize){
        len = fread(databuf+i, sizeof(BYTE),  lineSize, fp);
        if (len < lineSize){
            printf("get %dth data error! %x %x \n",i, len,  lineSize);
            //exit(EXIT_FAILURE);
        }
    }
    fclose(fp);

    //��ʽת��
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
    if((fp = fopen("/sdcard/ooo.raw", "w+b"))== NULL){
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
    //�ͷ��ڴ�ر��ļ�
    free(databuf);
    free(tbuf);
  //  fclose(fv);
}



int main( void )
{
    char outputFilename[32] = {0};
    char output2Filename[32] = {0};
    char inputFilename[32] = {0};
    char srcFilename[32] = {0};
    FILE *fins = NULL, *fout = NULL;
    char bheader[64] = {0};
    fill_img_t fd;
    char *mbuf = (char*)malloc(LS);
    char *sbuf = (char*)malloc(0x9bd6);
    int len = 0, offset = 0;
    memset(&fd, 0, sizeof(fill_img));
printf("___%p %p %d\n",mbuf,sbuf, len );
    memcpy(outputFilename, "/sdcard/out.bmp", 15);
    memcpy(output2Filename, "/sdcard/o22.bmp", 15);
    memcpy(inputFilename, "/sdcard/1.bmp", 13);
    memcpy(srcFilename, "/sdcard/2.bmp", 13);

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
    fd.dest_w = 720;
    fd.dest_h = 480;
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