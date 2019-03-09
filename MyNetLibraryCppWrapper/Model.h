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

		// ÑÂÎÉÑÒÂÀ

		void SetTargetError(float targetError)
		{
			model->SetTargetError(targetError);
		}

		float GetTargetError()
		{
			return model->GetTargetError();
		}

		void SetMinDW(float minDW)
		{
			model->SetMinDW(minDW);
		}

		float GetMinDW()
		{
			return model->GetMinDW();
		}

		void SetBatchSize(int batchSize)
		{
			model->SetBatchSize(batchSize);
		}

		int GetBatchSize()
		{
			return model->GetBatchSize();
		}

		void SetRandom(bool random)
		{
			model->SetRandom(random);
		}

		bool GetRandom()
		{
			return model->GetRandom();
		}

		void SetMomentumCoefficient(float momentumCoefficient)
		{
			model->SetMomentumCoefficient(momentumCoefficient);
		}

		float GetMomentumCoefficient()
		{
			return model->GetMomentumCoefficient();
		}

		void SetErrorListLength(int errorListLength)
		{
			model->SetErrorListLength(errorListLength);
		}

		int GetErrorListLength()
		{
			return model->GetErrorListLength();
		}

		void SetLambdaReg(float lambdaReg)
		{
			model->SetLambdaReg(lambdaReg);
		}

		float GetLambdaReg()
		{
			return model->GetLambdaReg();
		}

		List<float>^ GetErrorList()
		{
			List<float>^ res = gcnew List<float>();
			list<float>* l = &model->GetErrorList();

			for (list<float>::iterator it = l->begin(); it != l->end(); it++)
			{
				res->Add(*it);
			}

			return res;
		}

		int GetLayersCount()
		{
			return model->GetLayersCount();
		}
	};
}
