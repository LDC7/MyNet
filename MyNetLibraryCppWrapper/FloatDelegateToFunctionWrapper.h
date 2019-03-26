#pragma once
#include "FloatArrayPointer.h"
#include <functional>
#include <vcclr.h>


class FloatDelegateToFunctionWrapper
{
public:
	static std::function<float*(int)> GetFunction(System::Func<int, MyNetLibraryCppWrapper::FloatArrayPointer^>^ del)
	{
		gcroot<System::Func<int, MyNetLibraryCppWrapper::FloatArrayPointer^>^> func(del);

		return [func](int n) -> float* {
			float* res = func->Invoke(n)->GetPointer();
			return res == nullptr ? NULL : res;
		};
	}
};
