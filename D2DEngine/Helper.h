#pragma once


/*
    Render���� ������ ��ũ�γ� �Լ��� �����Ѵ�.
*/
#define SAFE_RELEASE(p) \
	if(p) \
	{ \
		p->Release(); \
		p = nullptr; \
	} \

#define SAFE_DELETE(p) \
	if(p) \
	{ \
		delete p; \
		p = nullptr; \
	} \

#define LOG_ERROR(...) \
{ \
    wchar_t buffer[256]; \
    swprintf_s(buffer,256, L"[ERROR] %s:%d - ", __FUNCTIONW__, __LINE__); \
    wchar_t message[256]; \
    swprintf_s(message,256, __VA_ARGS__); \
    wcscat_s(buffer, message); \
    wcscat_s(buffer, L"\n"); \
    ::MessageBox(NULL, buffer, L"LOG_ERROR", MB_OK); \
}

#define LOG_WARNING(...) \
{ \
    wchar_t buffer[256]; \
    swprintf_s(buffer,256, L"[WARNING] %s:%d - ", __FUNCTIONW__, __LINE__); \
    wchar_t message[256]; \
    swprintf_s(message,256, __VA_ARGS__); \
    wcscat_s(buffer, message); \
    wcscat_s(buffer, L"\n"); \
    OutputDebugString(buffer); \
}

#define LOG_MESSAGE(...) \
{ \
    wchar_t buffer[256]; \
    swprintf_s(buffer,256, L"[MESSAGE] %s:%d - ", __FUNCTIONW__, __LINE__); \
    wchar_t message[256]; \
    swprintf_s(message,256, __VA_ARGS__); \
    wcscat_s(buffer, message); \
    wcscat_s(buffer, L"\n"); \
    OutputDebugString(buffer); \
}



namespace D2DHelper
{

	D2D1_VECTOR_2F AddVector(const D2D1_VECTOR_2F& a, const D2D1_VECTOR_2F& b);

	D2D1_VECTOR_2F NormalizeVector(const D2D1_VECTOR_2F& vector);

	D2D1_VECTOR_2F MultiplyVector(const D2D1_VECTOR_2F& vector, float scalar);

	bool IsZeroVector(const D2D1_VECTOR_2F& vector);

	float GetVectorLength(const D2D1_VECTOR_2F& vector);

	void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* Rotation);
	void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float* ScaleX, float* ScaleY);
	void GetLocationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* x, float* y);
	void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation);
	void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY);

	// ȭ���ϴ��� 0,0 �� ��ǥ��� ��ȯ�Ѵ�.
	void ModifyMatrixtForBottomUpScreenSpace(ID2D1RenderTarget* pRenderTarget, D2D_MATRIX_3X2_F& in_out);


	bool CheckCollision(const D2D_RECT_F& rc1, const D2D_RECT_F& rc2);

	void Log(const wchar_t* format, ...);

	std::string WStringToString(const std::wstring& wstr);

	std::wstring StringToWString(const std::string& str);

	std::string GetNameFromTypeName(const std::string& typeidName);
} // namespace D2DUtils