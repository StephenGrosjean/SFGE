/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2matrix.h>

p2Mat22::p2Mat22()
{
}

p2Mat22::p2Mat22(p2Vec2 r1, p2Vec2 r2)
{
	this->rows[0] = r1;
	this->rows[1] = r2;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	p2Vec2 r0 = p2Vec2(rows[0].x + m1.rows[0].x, rows[0].y + m1.rows[0].y);
	p2Vec2 r1 = p2Vec2(rows[1].x + m1.rows[1].x, rows[1].y + m1.rows[1].y);
	return p2Mat22(r0,r1);
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	p2Vec2 r0 = p2Vec2(rows[0].x - m1.rows[0].x, rows[0].y - m1.rows[0].y);
	p2Vec2 r1 = p2Vec2(rows[1].x - m1.rows[1].x, rows[1].y - m1.rows[1].y);
	return p2Mat22(r0, r1);
	return p2Mat22();
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	p2Vec2 r0 = p2Vec2( (rows[0].x * m1.rows[0].x) + (rows[0].y * m1.rows[1].x),
						(rows[0].x * m1.rows[0].y) + (rows[0].y * m1.rows[1].y));

	p2Vec2 r1 = p2Vec2( (rows[1].x * m1.rows[0].x) + (rows[1].y * m1.rows[1].x),
						(rows[1].x * m1.rows[0].y) + (rows[1].y * m1.rows[1].y));

	return p2Mat22(r0, r1);
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2((rows[0].x * v.x) + (rows[0].y * v.y), (rows[1].x * v.x) + (rows[1].y * v.y));
}

p2Mat22 p2Mat22::operator*(float f)
{
	p2Vec2 r0 = p2Vec2(rows[0].x * f, rows[0].y * f);
	p2Vec2 r1 = p2Vec2(rows[1].x * f, rows[1].y * f);

	return p2Mat22(r0, r1);
}

p2Mat22 p2Mat22::operator/(float f)
{
	p2Vec2 r0 = p2Vec2(rows[0].x / f, rows[0].y / f);
	p2Vec2 r1 = p2Vec2(rows[1].x / f, rows[1].y / f);

	return p2Mat22(r0, r1);
}

p2Mat22 p2Mat22::Invert()
{
	float deter = this->GetDeterminant();
	if (deter == 0) return p2Mat22();

	p2Vec2 r0 = p2Vec2(rows[1].y, -rows[1].x);
	p2Vec2 r1 = p2Vec2(-rows[0].y, rows[0].x);
	p2Mat22 m0 = p2Mat22(r0, r1);
	

	return m0 * 1/deter;
}

float p2Mat22::GetDeterminant()
{
	return (rows[0].x * rows[1].y) - (rows[0].y * rows[1].x);
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3)
{
	this->rows[0] = r1;
	this->rows[1] = r2;
	this->rows[2] = r3;

}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	p2Vec3 r0 = p2Vec3(rows[0].x + m1.rows[0].x, rows[0].y + m1.rows[0].y, rows[0].z + m1.rows[0].z);
	p2Vec3 r1 = p2Vec3(rows[1].x + m1.rows[1].x, rows[1].y + m1.rows[1].y, rows[1].z + m1.rows[1].z);
	p2Vec3 r2 = p2Vec3(rows[2].x + m1.rows[2].x, rows[2].y + m1.rows[2].y, rows[2].z + m1.rows[2].z);

	return p2Mat33(r0, r1, r2);
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	p2Vec3 r0 = p2Vec3(rows[0].x - m1.rows[0].x, rows[0].y - m1.rows[0].y, rows[0].z - m1.rows[0].z);
	p2Vec3 r1 = p2Vec3(rows[1].x - m1.rows[1].x, rows[1].y - m1.rows[1].y, rows[1].z - m1.rows[1].z);
	p2Vec3 r2 = p2Vec3(rows[2].x - m1.rows[2].x, rows[2].y - m1.rows[2].y, rows[2].z - m1.rows[2].z);

	return p2Mat33(r0, r1, r2);
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	p2Vec3 r0 = p2Vec3( (rows[0].x * m1.rows[0].x) + (rows[0].y * m1.rows[1].x) + (rows[0].z * m1.rows[2].x),
						(rows[0].x * m1.rows[0].y) + (rows[0].y * m1.rows[1].y) + (rows[0].z * m1.rows[2].y),
						(rows[0].x * m1.rows[0].z) + (rows[0].y * m1.rows[1].z) + (rows[0].z * m1.rows[2].z));

	p2Vec3 r1 = p2Vec3( (rows[1].x * m1.rows[0].x) + (rows[1].y * m1.rows[1].x) + (rows[1].z * m1.rows[2].x),
						(rows[1].x * m1.rows[0].y) + (rows[1].y * m1.rows[1].y) + (rows[1].z * m1.rows[2].y),
						(rows[1].x * m1.rows[0].z) + (rows[1].y * m1.rows[1].z) + (rows[1].z * m1.rows[2].z));

	p2Vec3 r2 = p2Vec3( (rows[2].x * m1.rows[0].x) + (rows[2].y * m1.rows[1].x) + (rows[2].z * m1.rows[2].x),
						(rows[2].x * m1.rows[0].y) + (rows[2].y * m1.rows[1].y) + (rows[2].z * m1.rows[2].y),
						(rows[2].x * m1.rows[0].z) + (rows[2].y * m1.rows[1].z) + (rows[2].z * m1.rows[2].z));

	return p2Mat33(r0, r1, r2);
}

p2Vec3 p2Mat33::operator*(p2Vec3 v)
{
	return p2Vec3(  (rows[0].x * v.x) + (rows[0].y * v.y) + (rows[0].z * v.z), 
					(rows[1].x * v.x) + (rows[1].y * v.y) + (rows[1].z * v.z),
					(rows[2].x * v.x) + (rows[2].y * v.y) + (rows[2].z * v.z));

}

p2Mat33 p2Mat33::operator*(float f)
{
	p2Vec3 r0 = p2Vec3(rows[0].x * f, rows[0].y * f, rows[0].z * f);
	p2Vec3 r1 = p2Vec3(rows[1].x * f, rows[1].y * f, rows[1].z * f);
	p2Vec3 r2 = p2Vec3(rows[2].x * f, rows[2].y * f, rows[2].z * f);


	return p2Mat33(r0, r1, r2);
}

p2Mat33 p2Mat33::operator/(float f)
{
	p2Vec3 r0 = p2Vec3(rows[0].x / f, rows[0].y / f, rows[0].z / f);
	p2Vec3 r1 = p2Vec3(rows[1].x / f, rows[1].y / f, rows[1].z / f);
	p2Vec3 r2 = p2Vec3(rows[2].x / f, rows[2].y / f, rows[2].z / f);


	return p2Mat33(r0, r1, r2);
}

p2Mat33 p2Mat33::Invert()
{
	float deter = this->GetDeterminant();
	if (deter == 0) return p2Mat33();

	//FIRST STEP : CALCULATE MATRIX OF DETERMINANT

	//First row
	p2Mat22 x0 = p2Mat22(p2Vec2(rows[1].y, rows[1].z), 
						 p2Vec2(rows[2].y, rows[2].z));

	p2Mat22 y0 = p2Mat22(p2Vec2(rows[1].x, rows[1].z), 
						 p2Vec2(rows[2].x, rows[2].z));

	p2Mat22 z0 = p2Mat22(p2Vec2(rows[1].x, rows[1].y),
						 p2Vec2(rows[2].x, rows[2].y));

	//Second row
	p2Mat22 x1 = p2Mat22(p2Vec2(rows[0].y, rows[0].z),
						 p2Vec2(rows[2].y, rows[2].z));

	p2Mat22 y1 = p2Mat22(p2Vec2(rows[0].x, rows[0].z),
						 p2Vec2(rows[2].x, rows[2].z));

	p2Mat22 z1 = p2Mat22(p2Vec2(rows[0].x, rows[0].y),
						 p2Vec2(rows[2].x, rows[2].y));

	//Third row
	p2Mat22 x2 = p2Mat22(p2Vec2(rows[0].y, rows[0].z),
						 p2Vec2(rows[1].y, rows[1].z));

	p2Mat22 y2 = p2Mat22(p2Vec2(rows[0].x, rows[0].z),
						 p2Vec2(rows[1].x, rows[1].z));

	p2Mat22 z2 = p2Mat22(p2Vec2(rows[0].x, rows[0].y),
						 p2Vec2(rows[1].x, rows[1].y));
	//Calculating determinants
	float dx0 = x0.GetDeterminant();
	float dx1 = x1.GetDeterminant();
	float dx2 = x2.GetDeterminant();

	float dy0 = y0.GetDeterminant();
	float dy1 = y1.GetDeterminant();
	float dy2 = y2.GetDeterminant();

	float dz0 = z0.GetDeterminant();
	float dz1 = z1.GetDeterminant();
	float dz2 = z2.GetDeterminant();

	//SECOND STEP: MIRROR ALONG DIAGONAL (from dx0 to dz2 by dy1) AND REVERT SIGNS

	//Creating new matrix of determinant with reverted signs
	p2Vec3 r0 = p2Vec3(dx0, dx1, dx2) * -1;
	p2Vec3 r1 = p2Vec3(dy0, dy1, dy2) * -1;
	p2Vec3 r2 = p2Vec3(dz0, dz1, dz2) * -1;
	
	p2Mat33 matrix = p2Mat33(r0, r1, r2);

	matrix = matrix * deter;

	return matrix;
}

float p2Mat33::GetDeterminant()
{
	//Using rule of Sarrus
	float m1 = rows[0].x * rows[1].y * rows[2].z;
	float m2 = rows[0].y * rows[1].z * rows[2].x;
	float m3 = rows[0].z * rows[1].x * rows[2].y;

	float n1 = rows[2].x * rows[1].y * rows[0].z;
	float n2 = rows[2].y * rows[1].z * rows[0].x;
	float n3 = rows[2].z * rows[1].x * rows[0].y;

	float deter = (m1 + m2 + m3) - (n1 + n2 + n3);
	return deter;
}
