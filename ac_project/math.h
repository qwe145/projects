#pragma once 

#include "Classes.h"

float distance2d(vector3 source, vector3 distance)
{
	float dx = distance.x - source.x;
	float dy = distance.y - source.y;

	return sqrtf(dx*dx + dy * dy);
}

vector3 vectorToAngle(vector3 start, vector3 end)
{
	vector3 angles;

	angles.x = (-(float)atan2(end.x - start.x, end.y - start.y)) / 3.1415927f * 180.0f + 180.0f;
	angles.y = (atan2(end.z - start.z, distance2d(start, end))) * 180.0f / 3.1415927f;
	angles.z = 0.0f;
	return angles;
}