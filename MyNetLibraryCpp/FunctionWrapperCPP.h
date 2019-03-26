#pragma once
#include "FunctionTypeCPP.h"
#include <functional>

class FunctionWrapperCPP
{
public:
	FunctionWrapperCPP(FunctionTypeCPP type);
	
	float ActivationFunction(float);
	float DerivativeactivationFunction(float);

private:
	void FunctionWrapperCPP::choseFun(FunctionTypeCPP activationFun);

	std::function<float(float)> actFun;
	std::function<float(float)> deactFun;;
};

