#include "sceVu0.h"

inline void sceVu0AddVector(vec4& dest, vec4& lhs, vec4& rhs)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = lhs[i] + rhs[i];
	}
}

inline void sceVu0SubVector(vec4& dest, vec4& lhs, vec4& rhs)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = lhs[i] - rhs[i];
	}
}

inline void sceVu0MulVector(vec4& dest, vec4& lhs, vec4& rhs)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = lhs[i] * rhs[i];
	}
}

inline void sceVu0ScaleVector(vec4& dest, vec4& vector, float scale)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = vector[i] * scale;
	}
}

inline void sceVu0CopyVector(vec4& dest, vec4& source)
{
	memcpy(&dest, &source, sizeof(vec4));
}

inline void sceVu0CopyMatrix(matrix4& dest, matrix4& source)
{
	memcpy(&dest, &source, sizeof(matrix4));
}

inline void sceVu0FTOI4Vector(vec4& dest, vec4& source)
{
	s32 d;
	for (int i = 0; i < dest.size(); ++i)
	{
		d = static_cast<int>(dest[i]);
		memcpy(&dest[i], &d, sizeof(float));
	}
}

inline void sceVu0ITOF4Vector(vec4& dest, vec4& source)
{
	s32 d;
	for (int i = 0; i < dest.size(); ++i)
	{
		memcpy(&d, &dest[i], sizeof(float));
		dest[i] = static_cast<float>(d);
	}
}

inline void sceVu0ScaleVectorXYZ(vec4& dest, vec4& vector, float scale)
{
	for (int i = 0; i < 3; ++i)
	{
		dest[i] = vector[i] * scale;
	}
}