#include "texture.h"

//biblioteca
#include <FreeImage.h>
#include <GL/glew.h>

texture::texture()
{
	bMipMapsGenerated = false;
}

//ler textura
//se queremos mipmaps, false por q quiz
bool texture::loadTexture2D(std::string a_sPath, bool bGenerateMipMaps)
{
	//formato ficheiro
	FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
	FIBITMAP* freeImagedata(0);

	//obter tipo textura
	format = FreeImage_GetFileType(a_sPath.c_str(), 0);

	if (format == FIF_UNKNOWN) {
		//problema
		//se for desconhecido, vamos olhar para nome file 
		format = FreeImage_GetFIFFromFilename(a_sPath.c_str());
	}

	//finger
	if (format == FIF_UNKNOWN)
		return false;

	//se conseguimos ler formato
	if (FreeImage_FIFSupportsReading(format)) {
		//fazemos load textura para formato da biblioteca
		freeImagedata = FreeImage_Load(format, a_sPath.c_str());
	}
	if (!freeImagedata)
		return false;

	//lemos bytes textura
	BYTE* bDataPointer = FreeImage_GetBits(freeImagedata); 

	//obtemos parametros textura
	iWidth = FreeImage_GetWidth(freeImagedata);
	iHeight = FreeImage_GetHeight(freeImagedata);
	iBPP = FreeImage_GetBPP(freeImagedata);

	// If somehow one of these failed (they shouldn't), return failure
	if (bDataPointer == NULL || iWidth == 0 || iHeight == 0)
		return false;

	// gerar id
	glGenTextures(1, &uiTexture);
	
	//fazer bind para trabalharmos com ela
	glBindTexture(GL_TEXTURE_2D, uiTexture);

	//numero componentes por pixel
	int iFormat = iBPP == 24 ? GL_BGR : iBPP == 8 ? GL_LUMINANCE : 0;
	int iInternalFormat = iBPP == 24 ? GL_RGBA : GL_DEPTH_COMPONENT;

	//enviar dados po GPU 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, iFormat, GL_UNSIGNED_BYTE, bDataPointer);

	if (bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);

	FreeImage_Unload(freeImagedata);

	glGenSamplers(1, &uiSampler);

	sPath = a_sPath;
	bMipMapsGenerated = bGenerateMipMaps;

	//estamos bem :)
	return true;
}

//fazer set filtering
void texture::setFiltering(int a_tfMagnification, int a_tfMinification)
{
	//magnificacao
	if (a_tfMagnification == TEXTURE_FILTER_MAG_NEAREST)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else if (a_tfMagnification == TEXTURE_FILTER_MAG_BILINEAR)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//minificacao
	if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	else if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	else if (a_tfMinification == TEXTURE_FILTER_MIN_TRILINEAR)
		glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	tfMinification = a_tfMinification;
	tfMagnification = a_tfMagnification;
}

//bind textura por id
void texture::bindTexture(int iTextureUnit)
{
	this->id = iTextureUnit;

	glActiveTexture(GL_TEXTURE0 + iTextureUnit);
	glBindTexture(GL_TEXTURE_2D, uiTexture);
	glBindSampler(iTextureUnit, uiSampler);
}


//limpar memoria
void texture::releaseTexture()
{
	glDeleteSamplers(1, &uiSampler);
	glDeleteTextures(1, &uiTexture);
}

/*
GETS MIN MAX
*/
int texture::getMinificationFilter()
{
	return tfMinification;
}

int texture::getMagnificationFilter()
{
	return tfMagnification;
}