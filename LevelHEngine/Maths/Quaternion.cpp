#include "Quaternion.h"

namespace Maths
{

	void Quaternion::rotate(Quaternion &quat, Maths::Vec3 axis, float angle)
	{
		axis = axis * sinf(angle * 0.5f);

		//flip the y to make it rotate the same way as rotating with a matrix
		quat = Quaternion(cosf(angle * 0.5f), axis.x, -axis.y, axis.z);
	}

	Mat4 Quaternion::getMatrix()
	{
		Mat4 matrix;
		matrix.m[0] = (w*w) + (x*x) - (y*y) - (z*z);	matrix.m[1] = 2.0f * (x * y + w * z);			matrix.m[2] = 2.0f * (x * z - w * y);			matrix.m[3] = 0.0f;
		matrix.m[4] = 2.0f * (x * y - w * z);			matrix.m[5] = (w*w) - (x*x) + (y*y) - (z*z);	matrix.m[6] = 2.0f * (y * z + w * x);			matrix.m[7] = 0.0f;
		matrix.m[8] = 2.0f * (x * z + w * y);			matrix.m[9] = 2.0f * (y * z - w * x);			matrix.m[10] = (w*w) - (x*x) - (y*y) + (z*z);	matrix.m[11] = 0.0f;
		matrix.m[12] = 0.0f;							matrix.m[13] = 0.0f;							matrix.m[14] = 0.0f;							matrix.m[15] = 1.0f;
		return matrix;
	}
}