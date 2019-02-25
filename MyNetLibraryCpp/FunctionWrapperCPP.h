#pragma once
#include "FunctionTypeCPP.h"

class FunctionWrapperCPP
{
public:
	FunctionWrapperCPP(FunctionTypeCPP type = Liner)
	{
		choseFun(type);
	}
	
	float(*ActivationFunction)(float);
	float(*DerivativeactivationFunction)(float);

private:
	void FunctionWrapperCPP::choseFun(FunctionTypeCPP activationFun)
	{
		switch (activationFun)
		{
		case Liner:
			ActivationFunction = LinerFun;
			DerivativeactivationFunction = DerLinerFun;
			break;
		case BynarySigmoid:
			ActivationFunction = BynarySigmoidFun;
			DerivativeactivationFunction = DerBynarySigmoidFun;
			break;
		case BipolarSigmoid:
			ActivationFunction = BipolarSigmoidFun;
			DerivativeactivationFunction = DerBipolarSigmoidFun;
			break;
		case GyperTan:
			ActivationFunction = GyperTanFun;
			DerivativeactivationFunction = DerGyperTanFun;
			break;
		case ReLu:
			ActivationFunction = ReLuFun;
			DerivativeactivationFunction = DerReLuFun;
			break;
		}
	}
};

