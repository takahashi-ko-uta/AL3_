#include "Vector3Math.h"
#include "MathUtility.h"
#include <math.h>

namespace Vector3Math 
{
Vector3 diff(Vector3& vecA, Vector3& vecB) 
{
	Vector3 vecC;
	vecC.x = vecA.x - vecB.x;
	vecC.y = vecA.y - vecB.y;
	vecC.z = vecA.z - vecB.z;

	return vecC;
}
bool norm(Vector3& vec3) { 
	float norm = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z); 
	return norm;
}
Vector3 Normalize(Vector3& vec3) 
{ 
	float norm = Vector3Math::norm(vec3);
	float mag = 1 / norm;
	vec3.x *= mag;
	vec3.y *= mag;
	vec3.y *= mag;

	return vec3;
}
}





