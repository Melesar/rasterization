#include "tests.h"
#include <iostream>


inline void runMathTests()
{
	createVector3Test();
	createVector4Test();

	arythmeticsVector3Test();
	arythmeticsVector4Test();

	dotVector3Test();
	dotVector4Test();

	crossVector3Test();

	lenVector3Test();
	lenVector4Test();

	normalizeVector3Test();
	normalizeVector4Test();

	createMatrixTest();
	transposeTest();
	matrixMultiplicationTest();
	matrixVector4MultiplicationTest();
	matrixVector3MultiplicationTest();

	std::cin.get();
}
