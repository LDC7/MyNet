#pragma once
#include "ModelCPP.h"
#include "ModelSaveLoader.h"
#include "Layer.h"
#include "FloatArrayPointer.h"

namespace MyNetLibraryCppWrapper {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace std;

	private delegate FloatArrayPointer^ inputDelegate(int n);
	private delegate FloatArrayPointer^ outputDelegate(int n);

	public ref class Model
	{
	private:
		ModelCPP* model;
		inputDelegate^ inputFunction;
		outputDelegate^ outputFunction;

		float* inpDelToPtr(int n)
		{
			float* res = inputFunction->Invoke(n)->GetPointer();			
			return res;
		}

		float* outpDelToPtr(int n)
		{
			float* res = outputFunction->Invoke(n)->GetPointer();
			return res;
		};

	public:
		Model()
		{
			model = new ModelCPP();
		}

		!Model()
		{
			delete model;
		}

		void Train(int maxN, float eta, inputDelegate^ inpFunc, outputDelegate^ outFunc)
		{
			inputFunction = inpFunc;
			outputFunction = outFunc;
			float*(*inp_ptr)(int) = this->inpDelToPtr;
			float*(*outp_ptr)(int) = this->outpDelToPtr;

			model->Train(maxN, eta, inp_ptr, outp_ptr);
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
