#pragma once

#include "Vec4.h"
#include "Vec3.h"

/**
@brief Contains the Mat4 structure with functions and overloaded operators. This is row major.
*/
struct Mat4
{
	/**
	matrix variables
	[00]x [01]y [02]z [03]w
	[04]x [05]y [06]z [07]w
	[08]x [09]y [10]z [11]w
	[12]x [13]y [14]z [15]w
	*/
	float m[16];

	/**
	@brief Constructs the Mat4 setting the values of the matrix to 0.
	*/
	Mat4() : m{
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f
	} {}

	/**
	@brief Constructs the Mat4 setting the values to the input vectors.
	@param v1 The first inputed vector.
	@param v2 The second inputed vector.
	@param v3 The third inputed vector.
	@param v4 The forth inputed vector.
	*/
	Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4) :
		m{
		v1.x, v1.y, v1.z, v1.w,
		v2.x, v2.y, v2.z, v2.w,
		v3.x, v3.y, v3.z, v3.w,
		v4.x, v4.y, v4.z, v4.w,
	} {}

	/**
	@brief Overloads the += operator.
	@param vecIn The input Mat4.
	@returns The new matrix.
	*/
	Mat4* operator += (Mat4 mIn)
	{
		m[0] += mIn.m[0];	m[1] += mIn.m[1];	m[2] += mIn.m[2];	m[3] += mIn.m[3];
		m[4] += mIn.m[4];	m[5] += mIn.m[5];	m[6] += mIn.m[6];	m[7] += mIn.m[7];
		m[8] += mIn.m[8];	m[9] += mIn.m[9];	m[10] += mIn.m[10];	m[11] += mIn.m[11];
		m[12] += mIn.m[12];	m[13] += mIn.m[13];	m[14] += mIn.m[14];	m[15] += mIn.m[15];
		return this;
	}

	/**
	@brief Overloads the -= operator.
	@param vecIn The input Mat4.
	@returns The new matrix.
	*/
	Mat4* operator -= (Mat4 mIn)
	{
		m[0] -= mIn.m[0];	m[1] -= mIn.m[1];	m[2] -= mIn.m[2];	m[3] -= mIn.m[3];
		m[4] -= mIn.m[4];	m[5] -= mIn.m[5];	m[6] -= mIn.m[6];	m[7] -= mIn.m[7];
		m[8] -= mIn.m[8];	m[9] -= mIn.m[9];	m[10] -= mIn.m[10];	m[11] -= mIn.m[11];
		m[12] -= mIn.m[12];	m[13] -= mIn.m[13];	m[14] -= mIn.m[14];	m[15] -= mIn.m[15];
		return this;
	}

	/**
	@brief Sets the values of the matrix to that of a identity matrix
	*/
	void setAsIdentityMatrix()
	{
		m[0] = 1.0f;	m[1] = 0.0f;	m[2] = 0.0f;	m[3] = 0.0f;
		m[4] = 0.0f;	m[5] = 1.0f;	m[6] = 0.0f;	m[7] = 0.0f;
		m[8] = 0.0f;	m[9] = 0.0f;	m[10] = 1.0f;	m[11] = 0.0f;
		m[12] = 0.0f;	m[13] = 0.0f;	m[14] = 0.0f;	m[15] = 1.0f;
	}

	/**
	@brief Sets the values of the matrix to that of a Perspective matrix
	@param fovy The field of view on the y axis.
	@param a The aspect.
	@param f The z plane which is far from the camera.
	@param n The z plane closer to the camera.
	*/
	void setAsPerspectiveMatrix(float fovy, float aspect, float n, float f)
	{
		float const a = tanf(fovy / 2.0f);

		m[0] = 1.0f / (aspect * a);		m[1] = 0.0f;		m[2] = 0.0f;						m[3] = 0.0f;
		m[4] = 0.0f;					m[5] = 1.0f / a;	m[6] = 0.0f;						m[7] = 0.0f;
		m[8] = 0.0f;					m[9] = 0.0f;		m[10] = -((f + n) / (f - n));		m[11] = -((2.0f * f * n) / (f - n));
		m[12] = 0.0f;					m[13] = 0.0f;		m[14] = -1.0f;						m[15] = 0.0f;
	}

	/**
	@brief Sets the values of the matrix to that of a Orthogonal Projection matrix
	@param w The width of the area to view.
	@param h The height of the area to view.
	@param f The z plane which is the furthest the view can see.
	@param n The z plane which is the closest the view can see.
	*/
	void setAsOrthogonalProjectionMatrix(float w, float h, float n, float f)
	{
		m[0] = w * 0.5f;		m[1] = 0.0f;		m[2] = 0.0f;				m[3] = 0.0f;
		m[4] = 0.0f;			m[5] = h * 0.5f;	m[6] = 0.0f;				m[7] = 0.0f;
		m[8] = 0.0f;			m[9] = 0.0f;		m[10] = 1 / (f - n);		m[11] = -n / (f - n);
		m[12] = 0.0f;			m[13] = 0.0f;		m[14] = 0.0f;				m[15] = 1.0f;
	}

	/**
	@brief Sets the position of the matrix using the input vector
	@param pv The position vector vec3 to set the matrix position.
	*/
	void setPos(Vec3 pv) //uses row1w, row2w & row3w
	{
		/*x		y		z*/		m[3] = pv.x;
		/*x		y		z*/		m[7] = pv.y;
		/*x		y		z*/		m[11] = pv.z;
		/*x		y		z		w*/
	}
	void setPos(Mat4 &matrix, Vec3 pos);

	/**
	@brief Scales the matrix using the input vector
	@param matrix A pointer to the matrix to scale.
	@param sV The scale vector vec3 to scale the matrix by.
	*/
	void scale(Mat4 &matrix, float sv);

	/**
	@brief Scales the matrix using the input vector
	@param matrix A pointer to the matrix to scale.
	@param sV The scale vector vec3 to scale the matrix by.
	*/
	void scale(Mat4 &matrix, Vec3 &sv);

	/**
	@brief Translates the matrix using the input vector
	@param matrix A pointer to the matrix to rotate.
	@param tv The translation vector vec3 to set the matrix position.
	*/
	void translate(Mat4 &matrix, Vec3 tv);

	/**
	@brief Rotate the matrix using the angle of rotation along the axis.
	@param matrix A pointer to the matrix to rotate.
	@param angle The angles to rotate the matrix by, must be a Radian.
	*/
	void Mat4::rotate(Mat4 &matrix, Vec3 angle);

	/**
	@brief Rotate the matrix using the angle of rotation along the x axis.
	@param matrix A pointer to the matrix to rotate.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotateAlongX(Mat4 &matrix, float angle);

	/**
	@brief Rotate the matrix using the angle of rotation along the y axis.
	@param matrix A pointer to the matrix to rotate.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotateAlongY(Mat4 &matrix, float angle);

	/**
	@brief Rotate the matrix using the angle of rotation along the z axis.
	@param matrix A pointer to the matrix to rotate.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotateAlongZ(Mat4 &matrix, float angle);

	/**
	@brief Rotate the matrix around a point using the angle of rotation along the x axis.
	@param matrix A pointer to the matrix to rotate.
	@param axisPoint The point to rtate around.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotatePointAroundXAxis(Mat4 &matrix, Vec3 axisPoint, float angle);

	/**
	@brief Rotate the matrix around a point using the angle of rotation along the y axis.
	@param matrix A pointer to the matrix to rotate.
	@param axisPoint The point to rtate around.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotatePointAroundYAxis(Mat4 &matrix, Vec3 axisPoint, float angle);

	/**
	@brief Rotate the matrix around a point using the angle of rotation along the z axis.
	@param matrix A pointer to the matrix to rotate.
	@param axisPoint The point to rtate around.
	@param angle The angle to rotate the matrix by, must be a Radian.
	*/
	void rotatePointAroundZAxis(Mat4 &matrix, Vec3 axisPoint, float angle);

	/**
	@brief A function to get the inverse of a matrix.
	@param matrix A pointer to the matrix to invert.
	*/
	void getInverse(Mat4 &matrix);

	/**
	@brief Gets the position of the matrix
	@returns pv The position of the matrix as a vec3.
	*/
	Vec3 getPos() { return Vec3(m[3], m[7], m[11]); }

	/**
	@brief A function to get a pointer to the first index of the array
	@returns A pointer to the first index of the array.
	*/
	float* getMatrixArray()
	{
		return &m[0];
	}
};

/**
@brief Overloads the + operator allowing a Mat4 to be added to a scalar.
@param mIn The input Mat4.
@param s The scalar to add.
@returns The new Mat4.
*/
inline Mat4 operator + (Mat4 mIn, float s)
{
	Mat4 mOut;
	mOut.m[0] = mIn.m[0] + s;	mOut.m[1] = mIn.m[1] + s;	mOut.m[2] = mIn.m[2] + s;	mOut.m[3] = mIn.m[3] + s;
	mOut.m[4] = mIn.m[4] + s;	mOut.m[5] = mIn.m[5] + s;	mOut.m[6] = mIn.m[6] + s;	mOut.m[7] = mIn.m[7] + s;
	mOut.m[8] = mIn.m[8] + s;	mOut.m[9] = mIn.m[9] + s;	mOut.m[10] = mIn.m[10] + s;	mOut.m[11] = mIn.m[11] + s;
	mOut.m[12] = mIn.m[12] + s;	mOut.m[13] = mIn.m[13] + s;	mOut.m[14] = mIn.m[14] + s;	mOut.m[15] = mIn.m[15] + s;
	return mOut;
}

/**
@brief Overloads the + operator allowing a Mat4 to be added to a scalar.
@param mInA An input Mat4.
@param mInB An input Mat4.
@returns The new Mat4.
*/
inline Mat4 operator + (Mat4 mInA, Mat4 mInB)
{
	Mat4 mOut;
	mOut.m[0] = mInA.m[0] + mInB.m[0];		mOut.m[1] = mInA.m[1] + mInB.m[1];		mOut.m[2] = mInA.m[2] + mInB.m[2];		mOut.m[3] = mInA.m[3] + mInB.m[3];
	mOut.m[4] = mInA.m[4] + mInB.m[4];		mOut.m[5] = mInA.m[5] + mInB.m[5];		mOut.m[6] = mInA.m[6] + mInB.m[6];		mOut.m[7] = mInA.m[7] + mInB.m[7];
	mOut.m[8] = mInA.m[8] + mInB.m[8];		mOut.m[9] = mInA.m[9] + mInB.m[9];		mOut.m[10] = mInA.m[10] + mInB.m[10];	mOut.m[11] = mInA.m[11] + mInB.m[11];
	mOut.m[12] = mInA.m[12] + mInB.m[12];	mOut.m[13] = mInA.m[13] + mInB.m[13];	mOut.m[14] = mInA.m[14] + mInB.m[14];	mOut.m[15] = mInA.m[15] + mInB.m[15];
	return mOut;
}

/**
@brief Overloads the - operator allowing a Mat4 to be added to a scalar.
@param mInA The input Mat4.
@param s The scalar to add.
@returns The new Mat4.
*/
inline Mat4 operator - (Mat4 mInA, float s)
{
	Mat4 mOut;
	mOut.m[0] = mInA.m[0] - s;		mOut.m[1] = mInA.m[1] - s;		mOut.m[2] = mInA.m[2] - s;		mOut.m[3] = mInA.m[3] - s;
	mOut.m[4] = mInA.m[4] - s;		mOut.m[5] = mInA.m[5] - s;		mOut.m[6] = mInA.m[6] - s;		mOut.m[7] = mInA.m[7] - s;
	mOut.m[8] = mInA.m[8] - s;		mOut.m[9] = mInA.m[9] - s;		mOut.m[10] = mInA.m[10] - s;	mOut.m[11] = mInA.m[11] - s;
	mOut.m[12] = mInA.m[12] - s;	mOut.m[13] = mInA.m[13] - s;	mOut.m[14] = mInA.m[14] - s;	mOut.m[15] = mInA.m[15] - s;
	return mOut;
}

/**
@brief Overloads the - operator allowing a Mat4 to be subtracted from a scalar.
@param mInA An input Mat4.
@param mInB An input Mat4.
@returns The new Mat4.
*/
inline Mat4 operator - (Mat4 mInA, Mat4 mInB)
{
	Mat4 mOut;
	mOut.m[0] = mInA.m[0] - mInB.m[0];		mOut.m[1] = mInA.m[1] - mInB.m[1];		mOut.m[2] = mInA.m[2] - mInB.m[2];		mOut.m[3] = mInA.m[3] - mInB.m[3];
	mOut.m[4] = mInA.m[4] - mInB.m[4];		mOut.m[5] = mInA.m[5] - mInB.m[5];		mOut.m[6] = mInA.m[6] - mInB.m[6];		mOut.m[7] = mInA.m[7] - mInB.m[7];
	mOut.m[8] = mInA.m[8] - mInB.m[8];		mOut.m[9] = mInA.m[9] - mInB.m[9];		mOut.m[10] = mInA.m[10] - mInB.m[10];	mOut.m[11] = mInA.m[11] - mInB.m[11];
	mOut.m[12] = mInA.m[12] - mInB.m[12];	mOut.m[13] = mInA.m[13] - mInB.m[13];	mOut.m[14] = mInA.m[14] - mInB.m[14];	mOut.m[15] = mInA.m[15] - mInB.m[15];
	return mOut;
}

/**
@brief Overloads the * operator allowing a Mat4 to be multiplied to a scalar.
@param mInA The input Mat4.
@param s The scalar to add.
@returns The new Mat4.
*/
inline Mat4 operator * (Mat4 mInA, float s)
{
	Mat4 mOut;
	mOut.m[0] = mInA.m[0] * s;		mOut.m[1] = mInA.m[1] * s;		mOut.m[2] = mInA.m[2] * s;		mOut.m[3] = mInA.m[3] * s;
	mOut.m[4] = mInA.m[4] * s;		mOut.m[5] = mInA.m[5] * s;		mOut.m[6] = mInA.m[6] * s;		mOut.m[7] = mInA.m[7] * s;
	mOut.m[8] = mInA.m[8] * s;		mOut.m[9] = mInA.m[9] * s;		mOut.m[10] = mInA.m[10] * s;	mOut.m[11] = mInA.m[11] * s;
	mOut.m[12] = mInA.m[12] * s;	mOut.m[13] = mInA.m[13] * s;	mOut.m[14] = mInA.m[14] * s;	mOut.m[15] = mInA.m[15] * s;
	return mOut;
}

/**
@brief Overloads the * operator allowing a Mat4 to be multiplied with another Mat4.
REMEMBER: Mat1 * Mat2 != Mat2 * Mat1
@param matInA An input Mat4.
@param matInB An input Mat4.
@returns The new Mat4.
*/
inline Mat4 operator * (Mat4 mInA, Mat4 mInB)
{
	Mat4 mOut;

	//row 1
	//(row1x * row1x) + (row1y * row2x) + (row1z * row3x) + (row1w * row4x)
	mOut.m[0] = (mInA.m[0] * mInB.m[0]) + (mInA.m[1] * mInB.m[4]) + (mInA.m[2] * mInB.m[8]) + (mInA.m[3] * mInB.m[12]);
	//(row1x * row1y) + (row1y * row2y) + (row1z * row3y) + (row1w * row4y)
	mOut.m[1] = (mInA.m[0] * mInB.m[1]) + (mInA.m[1] * mInB.m[5]) + (mInA.m[2] * mInB.m[9]) + (mInA.m[3] * mInB.m[13]);
	//(row1x * row1z) + (row1y * row2z) + (row1z * row3z) + (row1w * row4z)
	mOut.m[2] = (mInA.m[0] * mInB.m[2]) + (mInA.m[1] * mInB.m[6]) + (mInA.m[2] * mInB.m[10]) + (mInA.m[3] * mInB.m[14]);
	//(row1x * row1w) + (row1y * row2w) + (row1z * row3w) + (row1w * row4w)
	mOut.m[3] = (mInA.m[0] * mInB.m[3]) + (mInA.m[1] * mInB.m[7]) + (mInA.m[2] * mInB.m[11]) + (mInA.m[3] * mInB.m[15]);

	//row 2
	//(row2x * row1x) + (row2y * row2x) + (row2z * row3x) + (row2w * row4x)
	mOut.m[4] = (mInA.m[4] * mInB.m[0]) + (mInA.m[5] * mInB.m[4]) + (mInA.m[6] * mInB.m[8]) + (mInA.m[7] * mInB.m[12]);
	//(row2x * row1y) + (row2y * row2y) + (row2z * row3y) + (row2w * row4y)
	mOut.m[5] = (mInA.m[4] * mInB.m[1]) + (mInA.m[5] * mInB.m[5]) + (mInA.m[6] * mInB.m[9]) + (mInA.m[7] * mInB.m[13]);
	//(row2x * row1z) + (row2y * row2z) + (row2z * row3z) +(row2w * row4z)
	mOut.m[6] = (mInA.m[4] * mInB.m[2]) + (mInA.m[5] * mInB.m[6]) + (mInA.m[6] * mInB.m[10]) + (mInA.m[7] * mInB.m[14]);
	//(row2x * row1w) + (row2y * row2w) + (row2z * row3w) + (row2w * row4w)
	mOut.m[7] = (mInA.m[4] * mInB.m[3]) + (mInA.m[5] * mInB.m[7]) + (mInA.m[6] * mInB.m[11]) + (mInA.m[7] * mInB.m[15]);

	//row 3
	//(row3x * row1x) + (row3y * row2x) + (row3z * row3x) + (row3w * row4x)
	mOut.m[8] = (mInA.m[8] * mInB.m[0]) + (mInA.m[9] * mInB.m[4]) + (mInA.m[10] * mInB.m[8]) + (mInA.m[11] * mInB.m[12]);
	//(row3x * row1y) + (row3y * row2y) + (row3z * row3y) + (row3w * row4y)
	mOut.m[9] = (mInA.m[8] * mInB.m[1]) + (mInA.m[9] * mInB.m[5]) + (mInA.m[10] * mInB.m[9]) + (mInA.m[11] * mInB.m[13]);
	//(row3x * row1z) + (row3y * row2z) + (row3z * row3z) + (row3w * row4z)
	mOut.m[10] = (mInA.m[8] * mInB.m[2]) + (mInA.m[9] * mInB.m[6]) + (mInA.m[10] * mInB.m[10]) + (mInA.m[11] * mInB.m[14]);
	//(row3x * row1w) + (row3y * row2w) + (row3z * row3w) + (row3w * row4w)
	mOut.m[11] = (mInA.m[8] * mInB.m[3]) + (mInA.m[9] * mInB.m[7]) + (mInA.m[10] * mInB.m[11]) + (mInA.m[11] * mInB.m[15]);

	//row 4
	//(row4x * row1x) + (row4y * row2x) + (row4z * row3x) + (row4w * row4x)
	mOut.m[12] = (mInA.m[12] * mInB.m[0]) + (mInA.m[13] * mInB.m[4]) + (mInA.m[14] * mInB.m[8]) + (mInA.m[15] * mInB.m[12]);
	//(row4x * row1y) + (row4y * row2y) + (row4z * row3y) + (row4w * row4y)
	mOut.m[13] = (mInA.m[12] * mInB.m[1]) + (mInA.m[13] * mInB.m[5]) + (mInA.m[14] * mInB.m[9]) + (mInA.m[15] * mInB.m[13]);
	//(row4x * row1z) + (row4y * row2z) + (row4z * row3z) + (row4w * row4z)
	mOut.m[14] = (mInA.m[12] * mInB.m[2]) + (mInA.m[13] * mInB.m[6]) + (mInA.m[14] * mInB.m[10]) + (mInA.m[15] * mInB.m[14]);
	//(row4x * row1w) + (row4y * row2w) + (row4z * row3w) + (row4w * row4w)
	mOut.m[15] = (mInA.m[12] * mInB.m[3]) + (mInA.m[13] * mInB.m[7]) + (mInA.m[14] * mInB.m[11]) + (mInA.m[15] * mInB.m[15]);

	return mOut;
}