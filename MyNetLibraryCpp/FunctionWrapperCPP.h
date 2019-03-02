#pragma once
#include "FunctionTypeCPP.h"

class FunctionWrapperCPP
{
public:
	FunctionWrapperCPP(FunctionTypeCPP type);
	
	float(*ActivationFunction)(float);
	float(*DerivativeactivationFunction)(float);

private:
	void FunctionWrapperCPP::choseFun(FunctionTypeCPP activationFun);
};

