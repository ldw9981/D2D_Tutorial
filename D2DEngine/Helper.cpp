#include "pch.h"
#include "Helper.h"
#include <string>
#include <locale>
#include <codecvt>

namespace Helper
{

	D2D1_VECTOR_2F AddVector(const D2D1_VECTOR_2F& a, const D2D1_VECTOR_2F& b)
	{
		D2D1_VECTOR_2F result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		return result;
	}

	D2D1_VECTOR_2F NormalizeVector(const D2D1_VECTOR_2F& vector)
	{
		D2D1_VECTOR_2F result{ 0 };
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		if ((vector.x == 0.0f) && (vector.y == 0.0f))
		{
			return result;
		}

		result.x = vector.x / length;
		result.y = vector.y / length;
		return result;
	}

	D2D1_VECTOR_2F MultiplyVector(const D2D1_VECTOR_2F& vector, float scalar)
	{
		D2D1_VECTOR_2F result;
		result.x = vector.x * scalar;
		result.y = vector.y * scalar;
		return result;
	}

	bool IsZeroVector(const D2D1_VECTOR_2F& vector)
	{
		return (vector.x == 0.0f) && (vector.y == 0.0f);
	}

	float GetVectorLength(const D2D1_VECTOR_2F& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* Rotation)
	{
		*Rotation = atan2f(mat._21, mat._11);
	}

	void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float* ScaleX, float* ScaleY)
	{
		*ScaleX = sqrtf(mat._11 * mat._11 + mat._12 * mat._12);
		*ScaleY = sqrtf(mat._21 * mat._21 + mat._22 * mat._22);
	}

	void GetLocationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* x, float* y)
	{
		*x = mat._31;
		*y = mat._32;
	}

	void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation)
	{
		mat._11 = cosf(Rotation);
		mat._12 = sinf(Rotation);
		mat._21 = -sinf(Rotation);
		mat._22 = cosf(Rotation);
	}

	void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY)
	{
		mat._11 = ScaleX;
		mat._22 = ScaleY;
	}

	/*
		ȸ���� ������ ���� ������
	*/
	void ModifyMatrixtForBottomUpScreenSpace(ID2D1RenderTarget* pRenderTarget, D2D_MATRIX_3X2_F& in_out)
	{
		//in_out._32 = pRenderTarget->GetSize().height - in_out._32;
	}

	bool CheckCollision(const D2D_RECT_F& rc1, const D2D_RECT_F& rc2)
	{
		if (rc1.left < rc2.right && rc1.right > rc2.left &&
			rc1.top < rc2.bottom && rc1.bottom > rc2.top)
		{
			return true;
		}
		return false;
	}



	bool CheckPointCollision(const D2D_RECT_F& rc, const D2D_POINT_2F& pt)
	{
		if (rc.left < pt.x && rc.right > pt.x &&
			rc.top < pt.y && rc.bottom > pt.y)
		{
			return true;
		}
		return false;
	}


	void SetPositionToMatrix(D2D_MATRIX_3X2_F& mat, float x, float y)
	{
		mat._31 = x;
		mat._32 = y;
	}

	// minX : rc.left
	// maxX : rc.right

	// maxY : rc.top
	// minY : rc.bottom
	bool IntersectSphereAndRect(const D2D_RECT_F& rc, const D2D_POINT_2F& center, float radius)
	{
		// get the closest point to the circle within the rectangle

		float x = fmaxf(rc.left, fminf(center.x, rc.right));
		float y = fmaxf(rc.bottom, fminf(center.y, rc.top));

		float dx = x - center.x;
		float dy = y - center.y;

		float dist = sqrtf(dx * dx + dy * dy);

		if (dist <= radius)
			return true;

		return false;
	}

	void Log(const wchar_t* format, ...)
	{
		va_list args;
		va_start(args, format);

		wchar_t buffer[1024];
		vswprintf_s(buffer, format, args);

		va_end(args);

		OutputDebugStringW(buffer);
	}

	std::string WStringToString(const std::wstring& wstr)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(wstr);
	}

	std::wstring StringToWString(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(str);
	}


	std::string GetNameFromTypeName(const std::string& typeidName)
	{
		std::string className = typeidName;

		// The typeid name may contain other information, like namespaces and other decorations.
		// We'll attempt to find the class name by removing any leading unwanted characters.

		// Remove leading "class " if present
		size_t classPos = className.find("class ");
		if (classPos != std::string::npos) {
			className.erase(classPos, 6); // 6 is the length of "class "
		}

		// Remove leading "struct " if present
		size_t structPos = className.find("struct ");
		if (structPos != std::string::npos) {
			className.erase(structPos, 7); // 7 is the length of "struct "
		}

		// If the name starts with 'const' or 'volatile', remove them too
		if (className.substr(0, 6) == "const ") {
			className.erase(0, 6);
		}
		else if (className.substr(0, 9) == "volatile ") {
			className.erase(0, 9);
		}

		return className;



	}

}

