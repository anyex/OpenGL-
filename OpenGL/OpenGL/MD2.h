#pragma once
#ifndef _MD2_H
#define _MD2_H
#include "stdio.h"
#define  BITMAP_ID 0x4D42//bmpID号
//支持的纹理类型
enum texTypes_t {
	PCX,BMP,TGA,JPG
};
//md2文件头
typedef struct 
{
	int ident;//MD2文件的标示
	int version;//应该等于8
	int skinwidth;//纹理的宽度
	int skinheight;//纹理的高度
	int framesize;//每一帧的字节数
	int numSkins;//纹理的数量
	int numXYZ;//顶点的数量
	int numST;//纹理坐标的数量
	int numTris;//三角形的数量
	int numGLcmds;//OpenGL命令类型的数量
	int numFrames;//总的帧数
	int offsetSkins;//纹理(皮肤)名字的偏移量(64字节)
	int offsetST;//纹理s-t的偏移量
	int offsetTris;//三角形网格的偏移量
	int offsetFrames;//帧数据(点)的偏移量
	int offsetGLcmds;//OpenGL命令的偏移量
	int offsetEnd;//文件结尾


}modelMD2Header_t;
/************************************************************************/
/* ident：用于将所载入的模型标示为一个MD2文件，在载入模型时，可以通过检查ident是否等于“IDP2”
   skinwidth,skinheight:指定了用于对此模型进行蒙皮的纹理的宽度和高度
   framesize:用于设置每一帧的字节数
   numSkins:设置了模型可用的皮肤的数量
   其中的offset参数指定了对应内容的存放位置
*/
/************************************************************************/




/************************************************************************/
/* 向量的相关处理方法                                                                     */
/************************************************************************/
typedef struct {
	float point[3];
}vector_t;

vector_t vecSub(vector_t a, vector_t b);//减法
vector_t vecAdd(vector_t a, vector_t b);//加法
vector_t vecMul(vector_t a, vector_t b);//乘法
vector_t vecDiv(vector_t a, vector_t b);//除法

/************************************************************************/
/* 纹理            */
/************************************************************************/
//纹理坐标
typedef struct
{
	float s;
	float t;
}texCoord_t;
//纹理坐标索引
typedef struct 
{
	short s;
	short t;
}stIndex_t;
typedef struct 
{
	texTypes_t textureType;//此纹理的图像文件类型

	int width;//纹理的宽度
	int height;//纹理高度
	long int scaledWidth;
	long int scaleHeight;//PCX图像的缩放宽度和高度
	unsigned int texID;//此纹理的纹理对象标示ID
	unsigned char *data;//纹理数据
	unsigned char *palett;//纹理的调色板


}texture_t;

void SetupMD2Texture(texture_t* thisTexture);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
texture_t *LoadTexture(char *textureName);//加载纹理
texture_t *LoadBMPTexture(char *textureName);//加载BMP纹理
texture_t *LoadJPGTexture(char *textureName);//加载JPG纹理
/************************************************************************/
/* 模型帧信息                                                                 */
/************************************************************************/
//一帧中每个点的信息
typedef struct 
{
	unsigned char v[3];//点信息
	unsigned char normalIndex;//
}framePoint_t;

//单一帧的信息
typedef struct 
{
	float scale[3];//帧中顶点的缩放比例
	float translate[3];//帧中顶点的平移
	char name[16];//模型的名字
	framePoint_t fp[1];//帧中顶点列表的开始
}frame_t;

typedef struct 
{
	unsigned short meshIndex[3];//顶点索引
	unsigned short stIndex[3];//纹理坐标索引


}mesh_t;


//模型的数据结构
typedef struct 
{
	int numFrames;//帧的数量
	int numPoints;//顶点的数量
	int numTriangles;//三角形的数量
	int numST;//纹理坐标的数量
	int frameSize;//每一帧数据的字节数
	int texWidth;
	int texHeight;//纹理的宽度和高度
	int currentFrame;//动画中的当前帧的号
	int nextFrame;//动画中的下一帧的号
	float interpol;//通过当前帧的百分比(插值方式)
	mesh_t *triIndex;//三角形列表
	texCoord_t *st;//纹理坐标列表
	vector_t *pointList;//顶点列表
	texture_t *modelTex;//纹理数据

}modelData_t;


modelData_t *LoadMD2Model(char* filename, char* textureName);//加载MD2模型
void DisplayMD2(modelData_t* model, int frameNum);//显示MD2模型



#endif