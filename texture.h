#ifndef _TEXTURE
#define _TEXTURE

#include <string>
#include <windows.h>   

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

/********************************

Class:	texture

Purpose:	Wraps OpenGL texture
object and performs
their loading.

********************************/

class texture
{
private:
	int id;
	int iWidth, iHeight, iBPP; // Texture width, height, and bytes per pixel
	UINT uiTexture; // Texture name
	UINT uiSampler; // Sampler name
	bool bMipMapsGenerated;

	int tfMinification, tfMagnification;

	//nome file
	std::string sPath;

public:
	//construtor
	texture();

	//ler textura
	bool loadTexture2D(std::string a_sPath, bool bGenerateMipMaps = false);
	
	//fazer bind
	void bindTexture(int iTextureUnit = 0);

	//set filtering
	void setFiltering(int a_tfMagnification, int a_tfMinification);

	//gets
	int getMinificationFilter();
	int getMagnificationFilter();

	//clean
	void releaseTexture();
};

#endif
