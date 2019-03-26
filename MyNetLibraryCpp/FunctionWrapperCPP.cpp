#include "stdafx.h"
#include "FunctionWrapperCPP.h"
#include <cmath>


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

FunctionWrapperCPP::FunctionWrapperCPP(FunctionTypeCPP type)
{
	choseFun(type);
}

void FunctionWrapperCPP::choseFun(FunctionTypeCPP activationFun)
{
	switch (activationFun)
	{
	case Liner:
		actFun = LinerFun;
		deactFun = DerLinerFun;
		break;
	case BynarySigmoid:
		actFun = BynarySigmoidFun;
		deactFun = DerBynarySigmoidFun;
		break;
	case BipolarSigmoid:
		actFun = BipolarSigmoidFun;
		deactFun = DerBipolarSigmoidFun;
		break;
	case GyperTan:
		actFun = GyperTanFun;
		deactFun = DerGyperTanFun;
		break;
	case ReLu:
		actFun = ReLuFun;
		deactFun = DerReLuFun;
		break;
	}
}

float FunctionWrapperCPP::ActivationFunction(float x)
{
	return actFun(x);
}

float FunctionWrapperCPP::DerivativeactivationFunction(float x)
{
	return deactFun(x);
}