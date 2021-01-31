#include "pch.h"
#include "ImageManager.h"

#include "Image.h"

ImageManager::~ImageManager()
{
	ImageIter iter = mImageList.begin();

	for (; iter != mImageList.end(); ++iter) {

		SafeDelete(iter->second);
	}

}

void ImageManager::LoadFromFile(wstring key, wstring filePath, int width, int height, bool isTrans, COLORREF transcolor)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end()) {
		return;
	}

	Image* newImage = new Image();
	newImage->LoadFromFile(filePath, width, height, isTrans, transcolor);

	mImageList.insert(make_pair(key, newImage));
}

void ImageManager::LoadFromFile(wstring key, wstring filePath, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transcolor)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end()) {
		return;
	}

	Image* newImage = new Image();
	newImage->LoadFromFile(filePath, width, height, frameX, frameY, isTrans, transcolor);

	mImageList.insert(pair<wstring, Image*>(key, newImage));

}

Image* ImageManager::FindImage(wstring key)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end()) {
		return iter->second;
	}

	return nullptr;
}
