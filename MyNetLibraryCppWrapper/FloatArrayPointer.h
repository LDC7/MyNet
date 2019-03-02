#pragma once
#include "stdafx.h"

namespace MyNetLibraryCppWrapper {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace std;
	
	public ref class FloatArrayPointer
	{
	private:
		int size;
		float* arr;

	internal:
		float* GetPointer()
		{
			return arr;
		}

		FloatArrayPointer(float* ar)
		{
			arr = ar;
			size = sizeof(arr) / sizeof(float);
		}

	public:
		FloatArrayPointer(int n)
		{
			size = n;
			arr = new float[size];
		}

		!FloatArrayPointer()
		{
			delete[] arr;
		}

		int GetSize()
		{
			return size;
		}

		void SetValue(int i, float val)
		{
			arr[i] = val;
		}
	};
}