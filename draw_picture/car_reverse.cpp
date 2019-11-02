#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern "C"{

#define PRIOD 3
#define LS 4*840*720

#define CAR_MODEL_PATH "/home1/caihuanming/workspace/test/draw_picture/carmodel/carmodel.bmp"
#define LINE_PICTURE_PATH "/home1/caihuanming/workspace/test/draw_picture/auxiliary/line_0.bmp"
#define RADAR_R_PATH "/home1/caihuanming/workspace/test/draw_picture/radar/radar_r_1.bmp"
#define RADAR_M_PATH "/home1/caihuanming/workspace/test/draw_picture/radar/radar_m_1.bmp"
#define RADAR_L_PATH "/home1/caihuanming/workspace/test/draw_picture/radar/radar_l_1.bmp"
#define BASE_PICTURE_PATH "/home1/caihuanming/workspace/test/background/background.raw"
#define OUT_PICTURE_PATH "/home1/caihuanming/workspace/test/picture_out/picture_out.bmp"

typedef struct raw_img_s{
	unsigned char *base_dest;
    unsigned char *base_src;
	unsigned char base_path[100];
    int base_h;
    int base_w;
	int rgb_bit;
    int argb_bit;
}raw_img_t;
raw_img_t raw_img;

void select_picture(void *base)
{
    snprintf(bmp_img.carmodel_path, sizeof(bmp_img.carmodel_path), CAR_MODEL_PATH);    
	snprintf(bmp_img.line_path, sizeof(bmp_img.line_path), LINE_PICTURE_PATH);
	snprintf(bmp_img.radar_r_path, sizeof(bmp_img.radar_r_path), RADAR_R_PATH);
	snprintf(bmp_img.radar_m_path, sizeof(bmp_img.radar_m_path), RADAR_M_PATH);
	snprintf(bmp_img.radar_l_path, sizeof(bmp_img.radar_l_path), RADAR_L_PATH);

	printf("path = %s\r\n",bmp_img.line_path);
	printf("path = %s\r\n",bmp_img.radar_r_path);
	printf("path = %s\r\n",bmp_img.radar_m_path);
	printf("path = %s\r\n",bmp_img.radar_l_path);
    memset(raw_img.base_dest, 0 ,1920*720*4);
	
	analysis_carmodel_pictures(bmp_img.carmodel_path, raw_img.base_dest);
	car_model_rgb_to_argb(bmp_img.carmodel_dest, bmp_img.carmodel_src, bmp_img.carmodel_w, bmp_img.carmodel_h);//将图片转码
    copy_to_base(raw_img.base_dest, bmp_img.carmodel_dest, bmp_img.carmodel_w, bmp_img.carmodel_h, 0, 0);//图片数据复制到 base frame 显示

	analysis_auxiliary_line_pictures(bmp_img.line_path, raw_img.base_dest);
	rgb_to_argb(bmp_img.line_dest, bmp_img.line_src, bmp_img.line_w, bmp_img.line_h);//将图片转码
	copy_to_base(raw_img.base_dest, bmp_img.line_dest, bmp_img.line_w, bmp_img.line_h, 840, 240);//图片数据复制到 base frame 显示

	switch (parse_data_idx[R_RADAR_PIC]) {
		case 0:
			break;

	        case 1:
			analysis_radar_r_r_pictures(bmp_img.radar_r_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_r_r_dest, bmp_img.radar_r_r_src, bmp_img.radar_r_r_w, bmp_img.radar_r_r_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_r_r_dest, bmp_img.radar_r_r_w, bmp_img.radar_r_r_h, 640, 529);//图片数据复制到 base frame 显示
			break;

		case 2:
			analysis_radar_r_o_pictures(bmp_img.radar_r_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_r_o_dest, bmp_img.radar_r_o_src, bmp_img.radar_r_o_w, bmp_img.radar_r_o_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_r_o_dest, bmp_img.radar_r_o_w, bmp_img.radar_r_o_h, 651, 548);//图片数据复制到 base frame 显示
			break;
			
	        case 3:
			analysis_radar_r_g_pictures(bmp_img.radar_r_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_r_g_dest, bmp_img.radar_r_g_src, bmp_img.radar_r_g_w, bmp_img.radar_r_g_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_r_g_dest, bmp_img.radar_r_g_w, bmp_img.radar_r_g_h, 661, 566);//图片数据复制到 base frame 显示
			break;

		default:
		    break;
	}


	switch (parse_data_idx[M_RADAR_PIC]) {
		case 0:
			break;

		case 1:
			analysis_radar_m_r_pictures(bmp_img.radar_m_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_m_r_dest, bmp_img.radar_m_r_src, bmp_img.radar_m_r_w, bmp_img.radar_m_r_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_m_r_dest, bmp_img.radar_m_r_w, bmp_img.radar_m_r_h, 540, 529);//图片数据复制到 base frame 显示
			break;

		case 2:
			analysis_radar_m_o_pictures(bmp_img.radar_m_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_m_o_dest, bmp_img.radar_m_o_src, bmp_img.radar_m_o_w, bmp_img.radar_m_o_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_m_o_dest, bmp_img.radar_m_o_w, bmp_img.radar_m_o_h, 532, 548);//图片数据复制到 base frame 显示
			break;
			
		case 3:
			analysis_radar_m_g_pictures(bmp_img.radar_m_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_m_g_dest, bmp_img.radar_m_g_src, bmp_img.radar_m_g_w, bmp_img.radar_m_g_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_m_g_dest, bmp_img.radar_m_g_w, bmp_img.radar_m_g_h, 522, 566);//图片数据复制到 base frame 显示
			break;

		default:
		    break;
	}


	switch (parse_data_idx[L_RADAR_PIC]) {
		case 0:
			break;
			
		case 1:
			analysis_radar_l_r_pictures(bmp_img.radar_l_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_l_r_dest, bmp_img.radar_l_r_src, bmp_img.radar_l_r_w, bmp_img.radar_l_r_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_l_r_dest, bmp_img.radar_l_r_w, bmp_img.radar_l_r_h, 493, 529);//图片数据复制到 base frame 显示
			break;

		case 2:
			analysis_radar_l_o_pictures(bmp_img.radar_l_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_l_o_dest, bmp_img.radar_l_o_src, bmp_img.radar_l_o_w, bmp_img.radar_l_o_h);//将图片转码
            radar_copy_to_base(raw_img.base_dest, bmp_img.radar_l_o_dest, bmp_img.radar_l_o_w, bmp_img.radar_l_o_h, 475, 548);//图片数据复制到 base frame 显示
			break;
			
		case 3:
			analysis_radar_l_g_pictures(bmp_img.radar_l_path, raw_img.base_dest);
			rgb_to_argb(bmp_img.radar_l_g_dest, bmp_img.radar_l_g_src, bmp_img.radar_l_g_w, bmp_img.radar_l_g_h);//将图片转码
			radar_copy_to_base(raw_img.base_dest, bmp_img.radar_l_g_dest, bmp_img.radar_l_g_w, bmp_img.radar_l_g_h, 457, 566);//图片数据复制到 base frame 显示
			break;

		default:
		    break;
	}
}

int init_raw(void)
{
	raw_img.argb_bit = 4;
	raw_img.rgb_bit = 3;
	
	raw_img.base_w = 1920;
	raw_img.base_h = 720;
	
	return 0;
}

int create_base_frame(void)
{
	printf("%s Enter\r\n",__FUNCTION__);
	raw_img.base_src = (char *)malloc(raw_img.rgb_bit*raw_img.base_w*raw_img.base_h);
	if (raw_img.base_src == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",raw_img.rgb_bit,raw_img.base_w,raw_img.base_h);
		return -1;
	}
	
	raw_img.base_dest = (char *)malloc(raw_img.argb_bit*raw_img.base_w*raw_img.base_h);
	if (raw_img.base_dest == NULL) {
		printf("ubmp malloc %d*%d*%d Bytes memory failed!\n",raw_img.argb_bit,raw_img.base_w,raw_img.base_h);
		return -1;
	}
}

int free_base_frame(void)
{
	free(raw_img.base_src);
	free(raw_img.base_dest);
	raw_img.base_src = NULL;
	raw_img.base_dest = NULL;
	
	return 0;
}

int main(void)
{
	init_raw();
	init_picture();
	create_base_frame();
	alloc_memery();
	select_picture(raw_img.base_dest);
	free_memery();
	free_base_frame();
	
	return 0;
}
