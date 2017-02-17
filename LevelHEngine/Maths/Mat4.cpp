#include "Mat4.h"

#include "Convert.h"

void Mat4::setPos(Mat4 &matrix, Vec3 pos)
{
	//reset the matrix position to 0,0,0
	matrix.m[3] = 0.0f;
	matrix.m[7] = 0.0f;
	matrix.m[11] = 0.0f;

	//translate to the new position
	translate(matrix, pos);
}

void Mat4::scale(Mat4 &matrix, float sv) //uses row1x, row2y & row3z
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	tm.m[0] = sv;			/*y					  z					  w*/
	/*x*/				tm.m[5] = sv;			/*z					  w*/
	/*x					y*/						tm.m[10] = sv;		/*w*/
	/*x					y						z					  w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::scale(Mat4 &matrix, Vec3 &sv) //uses row1x, row2y & row3z
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	tm.m[0] = sv.x;			/*y					  z					  w*/
	/*x*/				tm.m[5] = sv.y;			/*z					  w*/
	/*x					y*/						tm.m[10] = sv.z;	/*w*/
	/*x					y						z					  w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::translate(Mat4 &matrix, Vec3 tv) //uses row1w, row2w & row3w
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	/*x		y		z*/		tm.m[3] = tv.x;
	/*x		y		z*/		tm.m[7] = tv.y;
	/*x		y		z*/		tm.m[11] = tv.z;
	/*x		y		z		w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::rotate(Mat4 &matrix, Vec3 angle) //rotate around all axis's
{
	rotateAlongX(matrix, angle.x);
	rotateAlongY(matrix, angle.y);
	rotateAlongZ(matrix, angle.z);
}

void Mat4::rotateAlongX(Mat4 &matrix, float angle) //uses row2y, row2z, row3y & row3z
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	/*x		y								z									  w*/
	/*x*/	tm.m[5] = float(cos(angle));	tm.m[6] = float(sin(angle));		/*w*/
	/*x*/	tm.m[9] = float(-sin(angle));	tm.m[10] = float(cos(angle));		/*w*/
	/*x		y								z									  w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::rotateAlongY(Mat4 &matrix, float angle) //uses row1x, row1z, row3x & row3z
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	tm.m[0] = float(cos(angle));	/*y*/		tm.m[2] = float(sin(angle));	/*w*/
	/*x								  y			z								  w*/
	tm.m[8] = float(-sin(angle));	/*y*/		tm.m[10] = float(cos(angle));	/*w*/
	/*x								  y			z								  w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::rotateAlongZ(Mat4 &matrix, float angle) //uses row1x, row1y, row2x & row2y
{
	//make a temporary identity matrix
	Mat4 tm;
	tm.setAsIdentityMatrix();

	tm.m[0] = float(cos(angle));	tm.m[1] = float(sin(angle));	/*z			w*/
	tm.m[4] = float(-sin(angle));	tm.m[5] = float(cos(angle));	/*z			w*/
	/*x								y								  z			w*/
	/*x								y								  z			w*/

	//multiply the current matrix with the temporary matrix
	matrix = matrix * tm;
}

void Mat4::rotatePointAroundXAxis(Mat4 &matrix, Vec3 axisPoint, float angle)
{
	//translate back to the axis
	matrix.translate(matrix, -axisPoint);

	//rotate the matrix along the axis
	matrix.rotateAlongX(matrix, angle);

	//translate to the new point
	matrix.translate(matrix, axisPoint);
}

void Mat4::rotatePointAroundYAxis(Mat4 &matrix, Vec3 axisPoint, float angle)
{
	//translate back to the axis
	matrix.translate(matrix, -axisPoint);

	//rotate the matrix along the axis
	matrix.rotateAlongY(matrix, angle);

	//translate to the new point
	matrix.translate(matrix, axisPoint);
}

void Mat4::rotatePointAroundZAxis(Mat4 &matrix, Vec3 axisPoint, float angle)
{
	//translate back to the axis
	matrix.translate(matrix, -axisPoint);

	//rotate the matrix along the axis
	matrix.rotateAlongZ(matrix, angle);

	//translate to the new point
	matrix.translate(matrix, axisPoint);
}

/*
Linmath aligned to my floats
m[0][0];0	m[1][0];1	m[2][0];2	m[3][0];3
m[0][1];4	m[1][1];5	m[2][1];6	m[3][1];7
m[0][2];8	m[1][2];9	m[2][2];10	m[3][2];11
m[0][3];12	m[1][3];13	m[2][3];14	m[3][3];15
*/
void Mat4::getInverse(Mat4 &matrix)
{
	//make a temporary matrix
	Mat4 tm = matrix;

	float s[6];
	float c[6];
	s[0] = tm.m[0] * tm.m[5] - tm.m[1] * tm.m[4];
	s[1] = tm.m[0] * tm.m[9] - tm.m[1] * tm.m[8];
	s[2] = tm.m[0] * tm.m[13] - tm.m[1] * tm.m[12];
	s[3] = tm.m[4] * tm.m[9] - tm.m[5] * tm.m[8];
	s[4] = tm.m[4] * tm.m[13] - tm.m[5] * tm.m[12];
	s[5] = tm.m[8] * tm.m[13] - tm.m[9] * tm.m[12];

	c[0] = tm.m[2] * tm.m[7] - tm.m[3] * tm.m[6];
	c[1] = tm.m[2] * tm.m[11] - tm.m[3] * tm.m[10];
	c[2] = tm.m[2] * tm.m[15] - tm.m[3] * tm.m[14];
	c[3] = tm.m[6] * tm.m[11] - tm.m[7] * tm.m[10];
	c[4] = tm.m[6] * tm.m[15] - tm.m[7] * tm.m[14];
	c[5] = tm.m[10] * tm.m[15] - tm.m[11] * tm.m[14];

	/* Assumes it is invertible */
	float idet = 1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

	matrix.m[0] = (tm.m[5] * c[5] - tm.m[9] * c[4] + tm.m[13] * c[3]) * idet;
	matrix.m[4] = (-tm.m[4] * c[5] + tm.m[8] * c[4] - tm.m[12] * c[3]) * idet;
	matrix.m[8] = (tm.m[7] * s[5] - tm.m[11] * s[4] + tm.m[15] * s[3]) * idet;
	matrix.m[12] = (-tm.m[6] * s[5] + tm.m[10] * s[4] - tm.m[14] * s[3]) * idet;

	matrix.m[1] = (-tm.m[1] * c[5] + tm.m[9] * c[2] - tm.m[13] * c[1]) * idet;
	matrix.m[5] = (tm.m[0] * c[5] - tm.m[8] * c[2] + tm.m[12] * c[1]) * idet;
	matrix.m[9] = (-tm.m[3] * s[5] + tm.m[11] * s[2] - tm.m[15] * s[1]) * idet;
	matrix.m[13] = (tm.m[2] * s[5] - tm.m[10] * s[2] + tm.m[14] * s[1]) * idet;

	matrix.m[2] = (tm.m[1] * c[4] - tm.m[5] * c[2] + tm.m[13] * c[0]) * idet;
	matrix.m[6] = (-tm.m[0] * c[4] + tm.m[4] * c[2] - tm.m[12] * c[0]) * idet;
	matrix.m[10] = (tm.m[3] * s[4] - tm.m[7] * s[2] + tm.m[15] * s[0]) * idet;
	matrix.m[14] = (-tm.m[2] * s[4] + tm.m[6] * s[2] - tm.m[14] * s[0]) * idet;

	matrix.m[3] = (-tm.m[1] * c[3] + tm.m[5] * c[1] - tm.m[9] * c[0]) * idet;
	matrix.m[7] = (tm.m[0] * c[3] - tm.m[4] * c[1] + tm.m[8] * c[0]) * idet;
	matrix.m[11] = (-tm.m[3] * s[3] + tm.m[7] * s[1] - tm.m[11] * s[0]) * idet;
	matrix.m[15] = (tm.m[2] * s[3] - tm.m[6] * s[1] + tm.m[10] * s[0]) * idet;
}