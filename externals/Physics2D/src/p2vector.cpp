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

#include <p2vector.h>
#include <cmath>
#include <vector>
#include <corecrt_math_defines.h>

p2Vec2::p2Vec2() {}

p2Vec2::p2Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

p2Vec2 p2Vec2::operator+(const p2Vec2& v) const
{
	return p2Vec2(x + v.x, y + v.y);
}

p2Vec2& p2Vec2::operator+=(const p2Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

p2Vec2 p2Vec2::operator-(const p2Vec2& v) const
{
	return p2Vec2(x-v.x, y-v.y);
}

p2Vec2& p2Vec2::operator-=(const p2Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

p2Vec2& p2Vec2::operator*=(float f)
{
	x *= f;
	y *= f;
	return (*this);
}

p2Vec2 p2Vec2::operator/(float f) const
{
	return p2Vec2(x/f, y/f);
}

p2Vec2 p2Vec2::operator*(float f) const
{
	return p2Vec2(x*f, y*f);
}

float p2Vec2::Dot(p2Vec2 v1, p2Vec2 v2) {
	//DONE
	float result = (v1.x * v2.x) + (v1.y * v2.y);
	return result;
}

p2Vec3 p2Vec2::Cross(p2Vec2 v1, p2Vec2 v2) {
	//DONE
	float x = (v1.y * 0) - (0 * v1.y);
	float y = (0 * v2.x) - (v1.x * 0);
	float z = (v1.x*v2.y) - (v1.y *v2.x);

	p2Vec3 result = p2Vec3(x, y, z);
	return result;
}

float p2Vec2::GetMagnitude() {
	//DONE 
	return sqrt(pow(x,2) + pow(y,2));
}

p2Vec2 p2Vec2::Normalized() {
	//DONE 

	p2Vec2 vector = p2Vec2(x, y);

	const float magnitude = vector.GetMagnitude();

	if (magnitude == 0) {
		return p2Vec2(0, 0);
	}

	const p2Vec2 result = vector / magnitude;
	return result;
}

void p2Vec2::NormalizeSelf() {
	//DONE
	p2Vec2 vector = p2Vec2(x, y);
	vector = vector.Normalized();
	*this = vector;
}

p2Vec2 p2Vec2::Rotate(float angle) const {
	//TODO
	return p2Vec2();
}

p2Vec2 p2Vec2::Lerp(const p2Vec2& v1, const p2Vec2& v2, float t) {
	//done
	float x = (1 - t) * v1.x + t * v2.x;
	float y = (1 - t) * v1.y + t * v2.y;

	return p2Vec2(x,y);
}

float p2Vec2::AngleBetween(const p2Vec2& v1, const p2Vec2& v2, int to_Deg=0) {
	//DONE

	//if to_Deg == 0 -> angle in Rad | if to_Deg == 1 -> angle in Deg
	p2Vec2 vector1 = p2Vec2(v1.x, v1.y);
	p2Vec2 vector2 = p2Vec2(v2.x, v2.y);

	float dotProduct = p2Vec2().Dot(v1, v2);
	float magMulti = vector1.GetMagnitude() * vector2.GetMagnitude();
	float div = dotProduct / magMulti;

	
	float angleBetween = acos(div);
	if(to_Deg == 1) {
		angleBetween *= 180 / M_PI;
	}
	
	return angleBetween;
}

p2Vec2 p2Vec3::to2() {
	return p2Vec2(x, y);
}

p2Vec3 p2Vec2::to3() {
	return p2Vec3(x, y, 0.0f);
}

p2Vec3::p2Vec3() {}

p2Vec3::p2Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

p2Vec3 p2Vec3::operator+(const p2Vec3& v)const
{
	return p2Vec3(x + v.x, y + v.y, z + v.z);
}

p2Vec3& p2Vec3::operator+=(const p2Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

p2Vec3 p2Vec3::operator-(const p2Vec3& v) const
{
	return p2Vec3(x - v.x, y - v.y, z- v.z);
}

p2Vec3& p2Vec3::operator-=(const p2Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

p2Vec3& p2Vec3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= z;
	return (*this);
}

p2Vec3 p2Vec3::operator/(float f) const
{
	return p2Vec3(x / f, y / f, z/f);
}

p2Vec3 p2Vec3::operator*(float f) const
{
	return p2Vec3(x*f, y*f, z*f);
}

float p2Vec3::Dot(p2Vec3 v1, p2Vec3 v2) {
	//TODO
	return 0.0f;
}

p2Vec3 p2Vec3::Cross(p2Vec3 v1, p2Vec3 v2) {
	//TODO
	return p2Vec3();
}

p2Vec3 p2Vec3::Rotate(float angle) const {
	return p2Vec3();
}

p2Vec3 p2Vec3::Lerp(const p2Vec3& v1, const p2Vec3& v2, float t) {
	return p2Vec3();
}

float p2Vec3::AngleBetween(const p2Vec3& v1, const p2Vec3& v2) {
	return 0.0f;
}

float p2Vec3::GetMagnitude() {
	return 0.0f;
}

p2Vec3 p2Vec3::Normalized() {
	return p2Vec3();
}

void p2Vec3::NormalizeSelf() {}
