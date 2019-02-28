#pragma once
#include <cmath>
using namespace std;

enum FunctionTypeCPP
{
	Liner,
	BynarySigmoid,
	BipolarSigmoid,
	GyperTan,
	ReLu
};

float LinerFun(float x) { return x; }
float DerLinerFun(float x) { return 1; }

float BynarySigmoidFun(float x) { return (1.0f / (1.0f + std::expf(-x))); }
float DerBynarySigmoidFun(float x) { return ((1.0f - BynarySigmoidFun(x)) * BynarySigmoidFun(x)); }

float BipolarSigmoidFun(float x) { return ((2.0f / (1.0f + std::expf(-x))) - 1.0f); }
float DerBipolarSigmoidFun(float x) { return ((1.0f + BipolarSigmoidFun(x)) * (1.0f - BipolarSigmoidFun(x)) / 2.0f); }

float GyperTanFun(float x) { return (((std::expf(2.0f * x) - 1.0f) / (std::expf(2.0f * x))) + 1.0f); }
float DerGyperTanFun(float x) { return (1.0f - powf(GyperTanFun(x), 2.0f)); }

float ReLuFun(float x) { return x > 0.0f ? x : 0.0f; }
float DerReLuFun(float x) { return logf(1.0f + std::expf(x)); } // приближение
