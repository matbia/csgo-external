#pragma once
#define M_RADPI 57.295779513082f

struct Vector {
	float x = 0, y = 0, z = 0;
};

float NormalizeVectorValue(float vectorValue);

Vector ClampVector(Vector &vector);

//https://www.codeproject.com/Articles/69941/Best-Square-Root-Method
double inline __declspec (naked) __fastcall FastSQRT(double n)
{
	_asm fld qword ptr[esp + 4]
	_asm fsqrt
	_asm ret 8
}