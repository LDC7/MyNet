#pragma once
#include "ModelCPP.h"

namespace MyNetLibraryCppWrapper {

	using namespace System;

	static public ref class ModelSaveLoader
	{
	internal:
		static void SaveWeights(ModelCPP* model, System::String^ path)
		{
			string* stdString;
			MarshalString(path, *stdString);
			model->SaveWeights(*stdString);
			delete stdString;
		}

		static void LoadWeights(ModelCPP* model, System::String^ path)
		{
			string* stdString;
			MarshalString(path, *stdString);
			model->LoadWeights(*stdString);
			delete stdString;
		}

		static void MarshalString(System::String^ s, string& os)
		{
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
	};
}
