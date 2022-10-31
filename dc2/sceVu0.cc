#include "sceVu0.h"

inline void sceVu0SubVector(vec4& dest, vec4& v1, vec4& v2)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = v1[i] - v2[i];
	}
}

inline void sceVu0ScaleVector(vec4& dest, vec4& vector, float scale)
{
	for (int i = 0; i < dest.size(); ++i)
	{
		dest[i] = vector[i] * scale;
	}
}

inline void sceVu0ScaleVectorXYZ(vec4& dest, vec4& vector, float scale)
{
	for (int i = 0; i < 3; ++i)
	{
		dest[i] = vector[i] * scale;
	}
}