#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ubmp.h"


bmp_img_t bmp_img;


int init_picture(void)
{
	bmp_img.argb_bit = 4;
	bmp_img.rgb_bit = 3;
	
	bmp_img.line_w = 1080;
	bmp_img.line_h = 480;
	
	bmp_img.carmodel_w = 840;
	bmp_img.carmodel_h = 720;

	bmp_img.radar_r_g_w = 92;
	bmp_img.radar_r_g_h = 112;
	bmp_img.radar_r_o_w = 84;
	bmp_img.radar_r_o_h = 104;
	bmp_img.radar_r_r_w = 76;
	bmp_img.radar_r_r_h = 92;

	bmp_img.radar_m_g_w = 160;
	bmp_img.radar_m_g_h = 112;
	bmp_img.radar_m_o_w = 140;
	bmp_img.radar_m_o_h = 104;
	bmp_img.radar_m_r_w = 124;
	bmp_img.radar_m_r_h = 92;

	bmp_img.radar_l_g_w = 88;
	bmp_img.radar_l_g_h = 112;
	bmp_img.radar_l_o_w = 80;
	bmp_img.radar_l_o_h = 104;
	bmp_img.radar_l_r_w = 72;
	bmp_img.radar_l_r_h = 92;

	return 0;
}


int alloc_memery(void)
{
	/*
	alloc rgb analysis_pictures memery
	alloc argb analysis_pictures memery
	alloc rgb radar_pictures memery
	alloc argb radar_pictures memery
	*/
		
	bmp_img.line_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.line_w*bmp_img.line_h);
	if (bmp_img.line_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.line_w,bmp_img.line_h);
		return -1;
	}
	
	bmp_img.line_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.line_w*bmp_img.line_h);
	if (bmp_img.line_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.line_w,bmp_img.line_h);
		return -1;
	}

	bmp_img.carmodel_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.carmodel_w*bmp_img.carmodel_h);
	if (bmp_img.carmodel_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.carmodel_w,bmp_img.carmodel_h);
		return -1;
	}
	
	bmp_img.carmodel_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.carmodel_w*bmp_img.carmodel_h);
	if (bmp_img.carmodel_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.carmodel_w,bmp_img.carmodel_h);
		return -1;
	}

	bmp_img.radar_r_g_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_r_g_w*bmp_img.radar_r_g_h);
	if (bmp_img.radar_r_g_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_r_g_w,bmp_img.radar_r_g_h);
		return -1;
	}
	bmp_img.radar_r_o_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_r_o_w*bmp_img.radar_r_o_h);
	if (bmp_img.radar_r_o_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_r_o_w,bmp_img.radar_r_o_h);
		return -1;
	}
	bmp_img.radar_r_r_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_r_r_w*bmp_img.radar_r_r_h);
	if (bmp_img.radar_r_r_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_r_r_w,bmp_img.radar_r_r_h);
		return -1;
	}

	bmp_img.radar_m_g_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_m_g_w*bmp_img.radar_m_g_h);
	if (bmp_img.radar_m_g_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_m_g_w,bmp_img.radar_m_g_h);
		return -1;
	}
	bmp_img.radar_m_o_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_m_o_w*bmp_img.radar_m_o_h);
	if (bmp_img.radar_m_o_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_m_o_w,bmp_img.radar_m_o_h);
		return -1;
	}
	bmp_img.radar_m_r_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_m_r_w*bmp_img.radar_m_r_h);
	if (bmp_img.radar_m_r_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_m_r_w,bmp_img.radar_m_r_h);
		return -1;
	}

	bmp_img.radar_l_g_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_l_g_w*bmp_img.radar_l_g_h);
	if (bmp_img.radar_l_g_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_l_g_w,bmp_img.radar_l_g_h);
		return -1;
	}
	bmp_img.radar_l_o_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_l_o_w*bmp_img.radar_l_o_h);
	if (bmp_img.radar_l_o_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_l_o_w,bmp_img.radar_l_o_h);
		return -1;
	}
	bmp_img.radar_l_r_src = (char *)malloc(bmp_img.rgb_bit*bmp_img.radar_l_r_w*bmp_img.radar_l_r_h);
	if (bmp_img.radar_l_r_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.rgb_bit,bmp_img.radar_l_r_w,bmp_img.radar_l_r_h);
		return -1;
	}

	bmp_img.radar_r_g_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_r_g_w*bmp_img.radar_r_g_h);
	if (bmp_img.radar_r_g_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_r_g_w,bmp_img.radar_r_g_h);
		return -1;
	}
	bmp_img.radar_r_o_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_r_o_w*bmp_img.radar_r_o_h);
	if (bmp_img.radar_r_o_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_r_o_w,bmp_img.radar_r_o_h);
		return -1;
	}
	bmp_img.radar_r_r_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_r_r_w*bmp_img.radar_r_r_h);
	if (bmp_img.radar_r_r_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_r_r_w,bmp_img.radar_r_r_h);
		return -1;
	}
	
	bmp_img.radar_m_g_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_m_g_w*bmp_img.radar_m_g_h);
	if (bmp_img.radar_m_g_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_m_g_w,bmp_img.radar_m_g_h);
		return -1;
	}
	bmp_img.radar_m_o_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_m_o_w*bmp_img.radar_m_o_h);
	if (bmp_img.radar_m_o_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_m_o_w,bmp_img.radar_m_o_h);
		return -1;
	}
	bmp_img.radar_m_r_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_m_r_w*bmp_img.radar_m_r_h);
	if (bmp_img.radar_m_r_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_m_r_w,bmp_img.radar_m_r_h);
		return -1;
	}

	bmp_img.radar_l_g_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_l_g_w*bmp_img.radar_l_g_h);
	if (bmp_img.radar_l_g_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_l_g_w,bmp_img.radar_l_g_h);
		return -1;
	}
	bmp_img.radar_l_o_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_l_o_w*bmp_img.radar_l_o_h);
	if (bmp_img.radar_l_o_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_l_o_w,bmp_img.radar_l_o_h);
		return -1;
	}
	bmp_img.radar_l_r_dest = (char *)malloc(bmp_img.argb_bit*bmp_img.radar_l_r_w*bmp_img.radar_l_r_h);
	if (bmp_img.radar_l_r_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",bmp_img.argb_bit,bmp_img.radar_l_r_w,bmp_img.radar_l_r_h);
		return -1;
	}

	printf("%s Exit\r\n",__FUNCTION__);
	return 0;
} 



int free_memery(void)
{
	printf("%s Enter\r\n",__FUNCTION__);
	free(bmp_img.line_src);
	free(bmp_img.carmodel_src);
	free(bmp_img.radar_r_g_src);
	free(bmp_img.radar_m_g_src);
	free(bmp_img.radar_l_g_src);

	free(bmp_img.radar_r_o_src);
	free(bmp_img.radar_m_o_src);
	free(bmp_img.radar_l_o_src);

	free(bmp_img.radar_r_r_src);
	free(bmp_img.radar_m_r_src);
	free(bmp_img.radar_l_r_src);

	free(bmp_img.line_dest);
	free(bmp_img.carmodel_dest);
	free(bmp_img.radar_r_g_dest);
	free(bmp_img.radar_m_g_dest);
	free(bmp_img.radar_l_g_dest);

	free(bmp_img.radar_r_o_dest);
	free(bmp_img.radar_m_o_dest);
	free(bmp_img.radar_l_o_dest);

	free(bmp_img.radar_r_r_dest);
	free(bmp_img.radar_m_r_dest);
	free(bmp_img.radar_l_r_dest);

	//free(base);

	bmp_img.line_src = NULL;
	bmp_img.carmodel_src = NULL;

	bmp_img.line_dest = NULL;
	bmp_img.carmodel_dest = NULL;
	
	bmp_img.radar_r_g_src = NULL;
	bmp_img.radar_m_g_src = NULL;
	bmp_img.radar_l_g_src = NULL;
	bmp_img.radar_r_o_src = NULL;
	bmp_img.radar_m_o_src = NULL;
	bmp_img.radar_l_o_src = NULL;
	bmp_img.radar_r_r_src = NULL;
	bmp_img.radar_m_r_src = NULL;
	bmp_img.radar_l_r_src = NULL;

	bmp_img.radar_r_g_dest = NULL;
	bmp_img.radar_m_g_dest = NULL;
	bmp_img.radar_l_g_dest = NULL;
	bmp_img.radar_r_o_dest = NULL;
	bmp_img.radar_m_o_dest = NULL;
	bmp_img.radar_l_o_dest = NULL;
	bmp_img.radar_r_r_dest = NULL;
	bmp_img.radar_m_r_dest = NULL;
	bmp_img.radar_l_r_dest = NULL;

	//base = NULL;
	
	printf("%s Exit\r\n",__FUNCTION__);
	return 0;
}


int analysis_auxiliary_line_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.line_src, 1, bmp_img.rgb_bit*bmp_img.line_w*bmp_img.line_h, filp);
	fclose(filp);
 
	return 0;   
}

int analysis_radar_r_g_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_r_g_src, 1, bmp_img.rgb_bit*bmp_img.radar_r_g_w*bmp_img.radar_r_g_h, filp);
	fclose(filp);

	return 0;   
}

int analysis_radar_r_o_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_r_o_src, 1, bmp_img.rgb_bit*bmp_img.radar_r_o_w*bmp_img.radar_r_o_h, filp);
	fclose(filp);
 
	return 0;   
}

int analysis_radar_r_r_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_r_r_src, 1, bmp_img.rgb_bit*bmp_img.radar_r_r_w*bmp_img.radar_r_r_h, filp);
	fclose(filp);

	return 0;   
}


int analysis_radar_m_g_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_m_g_src, 1, bmp_img.rgb_bit*bmp_img.radar_m_g_w*bmp_img.radar_m_g_h, filp);
	fclose(filp);

	return 0;   
}

int analysis_radar_m_o_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_m_o_src, 1, bmp_img.rgb_bit*bmp_img.radar_m_o_w*bmp_img.radar_m_o_h, filp);
	fclose(filp);

	return 0;   
}

int analysis_radar_m_r_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_m_r_src, 1, bmp_img.rgb_bit*bmp_img.radar_m_r_w*bmp_img.radar_m_r_h, filp);
	fclose(filp);

	return 0;   
}


int analysis_radar_l_g_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_l_g_src, 1, bmp_img.rgb_bit*bmp_img.radar_l_g_w*bmp_img.radar_l_g_h, filp);
	fclose(filp);
 
	return 0;   
}

int analysis_radar_l_o_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_l_o_src, 1, bmp_img.rgb_bit*bmp_img.radar_l_o_w*bmp_img.radar_l_o_h, filp);
	fclose(filp);

	return 0;   
}

int analysis_radar_l_r_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.radar_l_r_src, 1, bmp_img.rgb_bit*bmp_img.radar_l_r_w*bmp_img.radar_l_r_h, filp);
	fclose(filp);
 
	return 0;   
}


int analysis_carmodel_pictures(const char *path, void *base)
{
	int cnt = 0;
	FILE *filp;

	filp = fopen(path, "r+b");	
	if (filp == NULL){
		printf("Open file failed, error code = %d\n", (int)filp);
		return -1;
	}
			
	fseek(filp,54,SEEK_SET);
	cnt = fread(bmp_img.carmodel_src, 1, bmp_img.rgb_bit*bmp_img.carmodel_w*bmp_img.carmodel_h, filp);
	fclose(filp);
 
	return 0;   
}


int rgb_to_argb(unsigned char *dest, unsigned char *src, int dest_w, int dest_h)
{
	int w = 0,h = 0;
	int k = 0;
    int tmp = 0;
    int count = 0;
    int c_h = 0, c_w = 0;
	int r_val = 0,g_val = 0,b_val = 0;

#if 0
	printf("dest_w = %d, dest_h = %d\r\n",dest_w, dest_h);
	
	for(h = 0; h < dest_h; h++) {
		for(w = 0; w < dest_w; w++) {
			*(c_h*dest_w*4+4*c_w+dest) = *(h*dest_w*3+3*w+src);
		    *(c_h*dest_w*4+4*c_w+dest+1) = *(h*dest_w*3+3*w+src+1);
			*(c_h*dest_w*4+4*c_w+dest+2) = *(h*dest_w*3+3*w+src+2);
			*(c_h*dest_w*4+4*c_w+dest+3) = 0;
			
			count++;
			c_w++;
			if((count+1) % (dest_w) == 1 && (count!=1)) {
				c_h++;
				c_w = 0;
			}
		}
	}
#endif

#if 1
	//printf("dest_w = %d, dest_h = %d\r\n",dest_w, dest_h);
	for(h = 0; h < dest_h; h++) {
		for(w = 0; w < dest_w; w++) {
			*(c_h*dest_w*4+4*c_w+dest)   = *(h*dest_w*3+3*w+src);    //r
			*(c_h*dest_w*4+4*c_w+dest+1) = *(h*dest_w*3+3*w+src+1);  //g
			*(c_h*dest_w*4+4*c_w+dest+2) = *(h*dest_w*3+3*w+src+2);  //b
			//tmp = *(c_h*dest_w*4+4*c_w+dest) | *(c_h*dest_w*4+4*c_w+dest+1) | *(c_h*dest_w*4+4*c_w+dest+2);
			r_val = *(c_h*dest_w*4+4*c_w+dest);
			g_val = *(c_h*dest_w*4+4*c_w+dest+1);
			b_val = *(c_h*dest_w*4+4*c_w+dest+2);
			if(r_val < 10 && g_val < 10 && b_val < 10) {
				*(c_h*dest_w*4+4*c_w+dest+3) = 0;
			} else {
				*(c_h*dest_w*4+4*c_w+dest+3) = 255;
			}
				
			count++;
			c_w++;
			if((count+1) % (dest_w) == 1 && (count!=1)) {
				c_h++;
				c_w = 0;
			}
		}
	}
#endif

    return 0;	
}


int car_model_rgb_to_argb(unsigned char *dest, unsigned char *src, int dest_w, int dest_h)
{
	int w = 0,h = 0;
	int k = 0;
    int tmp = 0;
    int count = 0;
    int c_h = 0, c_w = 0;

	for(h = 0; h < dest_h; h++) {
		for(w = 0; w < dest_w; w++) {
			*(c_h*dest_w*4+4*c_w+dest)   = *(h*dest_w*3+3*w+src);    //r
			*(c_h*dest_w*4+4*c_w+dest+1) = *(h*dest_w*3+3*w+src+1);  //g
			*(c_h*dest_w*4+4*c_w+dest+2) = *(h*dest_w*3+3*w+src+2);  //b
			*(c_h*dest_w*4+4*c_w+dest+3) = 255;
				
			count++;
			c_w++;
			if((count+1) % (dest_w) == 1 && (count!=1)) {
				c_h++;
				c_w = 0;
			}
		}
	}

    return 0;	
}


int copy_to_base(unsigned char *base, unsigned char *src, int src_w, int src_h, int point_w, int point_h)
{
    int w = 0, h = 0;
	int ret = 0;

	int p_byte = (32 / 8) / 4 * 4;
	int base_w = AUXLAYER_WIDTH, base_h = AUXLAYER_HEIGHT;

	//printf("base = 0x%x, src_w = %d, src_h = %d, p_byte = %d\r\n",base,src_w,src_h,p_byte);
	//printf("src = 0x%x, src_w = %d, src_h = %d, p_byte = %d\r\n",src,src_w,src_h,p_byte);
	//printf("point_w = %d, point_h = %d\r\n",point_w,point_h);
	#if 1 //copy to base
	for(h = 0; h < src_h; h++) {
		for(w = 0; w < src_w * p_byte; w++) {
		  *(base + (h+point_h)*base_w*p_byte + (w+point_w*p_byte)) = *(src + h*src_w*p_byte + w);//pix(600,240)
		}
	}
	#endif

	return 0;
}


int radar_copy_to_base(unsigned char *base, unsigned char *src, int src_w, int src_h, int point_w, int point_h)
{
    int w = 0, h = 0;
	int ret = 0;

	int p_byte = (32 / 8) / 4 * 4;
	int base_w = AUXLAYER_WIDTH, base_h = AUXLAYER_HEIGHT;
	int r_val = 0,g_val = 0,b_val = 0;

	for(h = 0; h < src_h; h++) {
		for(w = 0; w < src_w * p_byte; w++) {
			r_val = *(h*src_w*4+w+src);
			g_val = *(h*src_w*4+w+src+1);
			b_val = *(h*src_w*4+w+src+2);
			if(r_val > 5 || g_val > 5 || b_val > 5) {
		    	*(base + (h+point_h)*base_w*p_byte + (w+point_w*p_byte)) = *(src + h*src_w*p_byte + w);//pix(600,240)
			}
		}
	}

	return 0;
}


int print_pic_data(unsigned char *src, int p_byte, int src_w, int src_h)
{
	int w = 0, h = 0;
	
	printf("src = 0x%x,p_byte = %d,src_w = %d,src_h = %d\r\n",src,p_byte,src_w,src_h);
	printf("\n\n");
    for(h = 0; h < src_h; h++) {
        for(w = 0; w < src_w*p_byte; w++) {
			printf("%4x",*((h*src_w*p_byte+w)+src));
        }
        printf("\n");
    }
	
	printf("\n");
	return 0;
}


int copy_to_dest(unsigned char *dest, unsigned char *src, int dest_w, int dest_h, int src_w, int src_h, int point_w, int point_h)
{
	int w = 0, h = 0;
	int p_byte = 3;
	//dest_w = 720, dest_h = 480, src_w = 110, src_h = 120;
	
    #if 1  
	for(h = 0; h < src_h; h++) {
		for(w = 0; w < src_w * p_byte; w++) {
		  *(dest + (h+point_h)*dest_w*p_byte + (w+point_w*p_byte)) = *(src + h*src_w*p_byte + w);//pix(100,100)
		}
	}
	#endif

	//printf("%s\r\n",__FUNCTION__);
	return 0;
}

#if 0
int clear_cache(void *data,int data_w, int data_h, int p_byte)
{
	void *start, *end;
	
	start = data;
	end = (void *)((unsigned long)start + data_w * data_h * p_byte);

	memset(data, 0, data_w * data_h * p_byte);
	dmac_flush_range(start, end);

	return 0;
}
#endif