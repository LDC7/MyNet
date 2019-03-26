#pragma once
#include "ModelCPP.h"

namespace MyNetLibraryCppWrapper {

	using namespace System;
	using namespace System::IO;
	using namespace System::Text;

	static public ref class ModelSaveLoader
	{
	internal:
		static void SaveWeights(ModelCPP* model, System::String^ path)
		{
			StringBuilder^ sb;
			FileStream^ fs = gcnew FileStream(path, FileMode::OpenOrCreate);
			StreamWriter^ writer;
			try
			{
				writer = gcnew StreamWriter(fs);

				int layersCount = model->GetLayersCount();
				writer->WriteLine(layersCount);

				list<LayerCPP*>* layers = model->GetLayers();
				for (list<LayerCPP*>::iterator it = layers->begin(); it != layers->end(); it++)
				{
					int M = (*it)->GetM();
					int N = (*it)->GetN();

					sb = gcnew StringBuilder();
					sb->Append(N);
					sb->Append(" ");
					sb->Append(M);

					writer->WriteLine(sb->ToString());		
					
					for (int i = 0; i < M; i++)
					{
						sb = gcnew StringBuilder();
						sb->Append((*it)->GetW0()[i]);
						sb->Append(" ");
						for (int j = 0; j < N; j++)
						{
							sb->Append((*it)->GetW()[i][j]);
							sb->Append(" ");
						}
						writer->WriteLine(sb->ToString());
					}

				}
			}
			finally
			{
				delete writer;
				delete fs;
			}
		}

		static void LoadWeights(ModelCPP* model, System::String^ path)
		{
			FileStream^ fs = gcnew FileStream(path, FileMode::Open);
			StreamReader^ reader;
			String^ str;
			try
			{
				str = reader->ReadToEnd();
			}
			finally
			{
				delete reader;
				delete fs;
			}

			wchar_t wchEnter = L'\n';
			auto lines = str->Split(wchEnter);

			int layersN = Int32::Parse(lines[0]);
			if (model->GetLayersCount() != layersN)
			{
				return;
			}

			wchar_t wchSpace = L' ';
			auto layers = model->GetLayers();
			int l = 1;
			for (auto it = layers->begin(); it != layers->end(); it++)
			{
				auto temp = lines[l]->Split(wchSpace);
				if (Int32::Parse(temp[0]) != (*it)->GetN() || Int32::Parse(temp[1]) != (*it)->GetM())
				{
					return;
				}

				l++;
				for (int j = 0; j < (*it)->GetM(); l++, j++)
				{
					temp = lines[l]->Split(wchSpace);
					(*it)->GetW0()[j] = Single::Parse(temp[0]);
					(*it)->GetWn0()[j] = (*it)->GetW0()[j];
					for (int k = 0; k < (*it)->GetN(); k++)
					{
						(*it)->GetW()[j][k] = Single::Parse(temp[k + 1]);
						(*it)->GetWn()[j][k] = (*it)->GetW()[j][k];
					}
				}
			}
		}
	};
}
