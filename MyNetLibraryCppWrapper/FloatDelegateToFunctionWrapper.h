#pragma once
#include "FloatArrayPointer.h"
#include <functional>
#include <vcclr.h>


class FloatDelegateToFunctionWrapper
{
public:
	static std::function<float*(int)> GetFunction(System::Func<int, MyNetLibraryCppWrapper::FloatArrayPointer^>^ del)
	{
		gcroot<System::Func<int, MyNetLibraryCppWrapper::FloatArrayPointer^>^> keka(del);

		return [keka](int n) -> float* {
			return keka->Invoke(n)->GetPointer();
		};
	}
};
