#pragma once
#include "ModelCPP.h"
#include "ModelSaveLoader.h"
#include "Layer.h"
#include "FloatArrayPointer.h"
#include "FloatDelegateToFunctionWrapper.h"
#include <functional>
#include <vcclr.h>

namespace MyNetLibraryCppWrapper {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace std;

	public ref class Model
	{
	private:
		ModelCPP* model;

	public:
		Model()
		{
			model = new ModelCPP();
		}

		!Model()
		{
			if (model != nullptr)
			{
				delete model;
				model = nullptr;
			}
		}

		void Train(int maxN, float eta, Func<int, FloatArrayPointer^>^ inpFunc, Func<int, FloatArrayPointer^>^ outFunc)
		{			
			model->Train(maxN,
				eta,
				FloatDelegateToFunctionWrapper::GetFunction(inpFunc),
				FloatDelegateToFunctionWrapper::GetFunction(outFunc));
		}

		void AddLayer(Layer^ layer)
		{
			model->AddLayer(layer->getPtr());
		}

		FloatArrayPointer^ GetRes(FloatArrayPointer^ input)
		{
			float* res = model->GetRes(input->GetPointer());
			FloatArrayPointer^ result = gcnew FloatArrayPointer(res);

			return result;
		}

		void SaveWeights(System::String^ path)
		{
			ModelSaveLoader::SaveWeights(model, path);
		}

		void LoadWeights(System::String^ path)
		{
			ModelSaveLoader::LoadWeights(model, path);
		}
	};
}
