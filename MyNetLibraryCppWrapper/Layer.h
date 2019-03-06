#pragma once
#include "LayerCPP.h"
#include "FunctionTypeWrapper.h"

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
			if (funcWrap != nullptr )
			{
				delete funcWrap;
				funcWrap = nullptr;
			}
			if (layer != nullptr)
			{
				delete layer;
				layer = nullptr;
			}
		}

		~Layer()
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
}
