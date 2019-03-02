// Layer.h

#pragma once
#include "LayerCPP.h"
#include "FunctionWrapperCPP.h"

namespace MyNetLibraryCppWrapper {

	using namespace System;

	public ref class Layer
	{
	private:
		LayerCPP* layer;
		FunctionWrapperCPP* funcWrap;
		
	public:
		Layer(int enters, int exits, FunctionType function)
		{
			funcWrap = new FunctionWrapperCPP((FunctionTypeCPP)((int)function));
			layer = new LayerCPP(enters, exits, funcWrap);
		}

		!Layer()
		{
			delete funcWrap;
			delete layer;
		}

	internal:
		LayerCPP* getPtr()
		{
			return layer;
		}
	};

	public enum FunctionType
	{
		Liner,
		BynarySigmoid,
		BipolarSigmoid,
		GyperTan,
		ReLu
	};
}
