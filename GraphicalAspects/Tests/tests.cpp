#include "tests.h"
#include <iostream>
#include "../Data/math_structs.h"
#include "../utils.h"

void beginTest(const std::string& title)
{
	std::cout << title << ": " << std::endl;
}

void assert(const std::string & title, bool condition)
{
	std::cout << "    - " << title << ": ";
	std::cout << (condition ? "passed" : "failed");
	std::cout << std::endl;
}

void finishTest()
{
	std::cout << std::endl;
}

void createVector3Test()
{
	float3 v = { 1.f, 2.f, 3.f };

	beginTest("float3 creation");
	assert("X, Y, Z", v.x == 1.f && v.y == 2.f && v.z == 3.f);
	assert("R, G, B", v.r == 1.f && v.g == 2.f && v.b == 3.f);
	assert("Indicies", v[0] == 1.f && v[1] == 2.f && v[2] == 3.f);
	finishTest();
}

void createVector4Test()
{
	float4 v = { 1.f, 2.f, 3.f, 4.f };

	beginTest("float4 creation");
	assert("X, Y, Z, W", v.x == 1.f && v.y == 2.f && v.z == 3.f && v.w == 4.f);
	assert("Indicies", v[0] == 1.f && v[1] == 2.f && v[2] == 3.f && v[3] == 4.f);
	finishTest();
}

void arythmeticsVector3Test()
{
	float3 a = { 1.f, 2.f, 3.f };
	float3 b = { 4.f, 5.f, 6.f };

	auto sum = a + b;
	auto mult = a * 5.f;

	beginTest("float3 arythmetics");
	assert("Adding", sum.x == 5.f && sum.y == 7.f && sum.z == 9.f);
	assert("Multiplying", mult.x == 5.f && mult.y == 10.f && mult.z == 15.f);
	finishTest();
}

void arythmeticsVector4Test()
{
	float4 a = { 1.f, 2.f, 3.f, 8.f };
	float4 b = { 4.f, 5.f, 6.f, 9.f };

	auto sum = a + b;
	auto mult = a * 5.f;

	beginTest("float4 arythmetics");
	assert("Adding", sum.x == 5.f && sum.y == 7.f && sum.z == 9.f && sum.w == 17.f);
	assert("Multiplying", mult.x == 5.f && mult.y == 10.f && mult.z == 15.f && mult.w == 40.f);
	finishTest();
}

void dotVector3Test()
{
	float3 a = { 3.f, 10.f, 5.f };
	float3 b = { 4.f, 12.f, 8.f };

	beginTest("float3 dot product");
	assert("Dot", dot(a, b) == 172);
	finishTest();
}

void dotVector4Test()
{
	float4 a = { 3.f, 10.f, 5.f, 2.f };
	float4 b = { 4.f, 12.f, 8.f, 2.f };

	beginTest("float4 dot product");
	assert("Dot", dot(a, b) == 176);
	finishTest();
}

void crossVector3Test()
{
	float3 a = { 1, 2, 3 };
	float3 b = { 4, 5, 6 };

	auto res = cross(a, b);

	beginTest("Cross product");
	assert("Cross", res.x == -3 && res.y == 6 && res.z == -3);
	finishTest();
}

void lenVector3Test()
{
	auto l = len({ 3, 4, 6 });

	beginTest("Vector3 length");
	assert("len", l - 7.810249 < 0.0001);
	finishTest();
}

void lenVector4Test()
{
	auto l = len({ 3, 4, 6, 10});

	beginTest("Vector4 length");
	assert("len", l - 12.68857 < 0.0001);
	finishTest();
}

void normalizeVector3Test()
{
	float3 v = { 1.f, 8.4f, 3.f };
	v = normalize(v);

	beginTest("Vector3 normalization");
	assert("Normalize", len(v) - 1 < 0.0001f);
	finishTest();
}

void normalizeVector4Test()
{
	float4 v = { 1.f, 8.4f, 3.f, 9.4f };
	v = normalize(v);

	beginTest("Vector4 normalization");
	assert("Normalize", len(v) - 1 < 0.0001f);
	finishTest();
}

void createMatrixTest()
{
	float4x4 m = {
		{1, 0, 0, 1},
		{0, 1, 2, 0},
		{0.5, 0, 1, 3.1f},
		{1, 0, 0, 1}
	};

	auto condition = m[0][0] == 1 && m[2][0] == 0.5f && m[1][3] == 0 && m[3][3] == 1;

	beginTest("Matrix creation");
	assert("Access", condition);

	m[0][2] = 5;
	assert("Modification", m[0][2] == 5);
	finishTest();
}

void transposeTest()
{
	float4x4 m = {
		{1, 0, 0, 1},
		{0, 1, 2, 0},
		{0.5, 0, 1, 3.1f},
		{1, 0, 0, 1}
	};

	m = transpose(m);
	auto condition = m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0.5 && m[0][3] == 1 &&
		m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 && m[1][3] == 0 &&
		m[2][0] == 0 && m[2][1] == 2 && m[2][2] == 1 && m[2][3] == 0 &&
		m[3][0] == 1 && m[3][1] == 0 && m[3][2] == 3.1f && m[3][3] == 1;

	beginTest("Transposition");
	assert("Transpose", condition);
	finishTest();
}

void matrixMultiplicationTest()
{
	float4x4 m = {
		{1, 0, 0, 1},
		{0, 1, 2, 0},
		{0.5, 0, 1, 3.1f},
		{1, 0, 0, 1}
	};

	auto res = mul(m, m);

	auto condition = res[0][0] == 2 && res[0][1] == 0 && res[0][2] == 0 && res[0][3] == 2 &&
		res[1][0] == 1 && res[1][1] == 1 && res[1][2] == 4 && isEqual(res[1][3], 6.2f) &&
		isEqual(res[2][0], 4.1f) && res[2][1] == 0 && res[2][2] == 1 && isEqual(res[2][3], 6.7f) &&
		res[3][0] == 2 && res[3][1] == 0 && res[3][2] == 0 && res[3][3] == 2;

	beginTest("Matrix multiplication");
	assert("Mult", condition);
	finishTest();
}

void matrixVector3MultiplicationTest()
{
	float4x4 m = {
		{1, 0, 0, 1},
		{0, 1, 2, 0},
		{0.5, 0, 1, 3.1f},
		{1, 0, 0, 1}
	};

	float3 v = { 1, 2, 3 };

	auto res = mul(v, m);
	auto condition = isEqual(res[0], 1.f) && isEqual(res[1], 4.f) && isEqual(res[2], 3.3f);

	beginTest("Matrix by Vector3");
	assert("Mult", condition);
	finishTest();
}

void matrixVector4MultiplicationTest()
{
	float4x4 m = {
		{1, 0, 0, 1},
		{0, 1, 2, 0},
		{0.5, 0, 1, 3.1f},
		{1, 0, 0, 1}
	};

	float4 v = { 1, 2, 3, 1 };
	auto res = mul(v, m);
	auto condition = isEqual(res[0], 2.f) && isEqual(res[1], 8.f) && isEqual(res[2], 6.6f) && isEqual(res[3], 2.f);

	beginTest("Matrix by Vector4");
	assert("Mult", condition);
	finishTest();
}

void colorTransformationTest()
{
	float3 black = {0, 0, 0};
	float3 white = {1, 1, 1};
	float3 random = {0.5, 0.84, 0.15};

	unsigned iBlack = colorToInt(black);
	unsigned iWhite = colorToInt(white);
	unsigned iRandom = colorToInt(random);

	float3 resBlack = intToColor(iBlack);
	float3 resWhite = intToColor(iWhite);
	float3 resRandom = intToColor(iRandom);

	beginTest("Color transformations");
	assert("Black", isEqual(resBlack, black));
	assert("White", isEqual(resWhite, white));
	assert("Random color", isEqual(resRandom, random, 0.03));
	finishTest();
}
