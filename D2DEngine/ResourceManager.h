#pragma once

class AnimationAsset;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();



	void CreateD2D1BitmapFromFile(const wchar_t* fileName, ID2D1Bitmap** bitmap);
	void ReleaseD2D1Bitmap(ID2D1Bitmap* bitmap);

	void CreateAnimationAsset(const wchar_t* fileName, AnimationAsset** asset);
	void ReleaseAnimationAsset(AnimationAsset* asset);
};

