#pragma once

class AnimationAsset;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();


	


	bool CreateD2D1BitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	void ReleaseD2D1Bitmap(ID2D1Bitmap* bitmap);

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimationAsset(AnimationAsset* asset);
};

