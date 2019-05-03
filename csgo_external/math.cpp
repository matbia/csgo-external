#include "math.h"
#include <math.h>
#include <windows.h>

float NormalizeVectorValue(float vectorValue)
{
	if (!isfinite(vectorValue)) //NaN check
	{
		vectorValue = 0.0f; //Error handling
	}
	return remainder(vectorValue, 360.0f);
}

Vector ClampVector(Vector &vector)
{
	vector.x = max(-89.0f, min(89.0f, NormalizeVectorValue(vector.x)));
	vector.y = NormalizeVectorValue(vector.y);
	vector.z = 0.f;
	return vector;
}
