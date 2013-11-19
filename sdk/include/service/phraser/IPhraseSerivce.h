#pragma once
#include<MyTypes.h>
#include<IModel.h>
namespace xc{
	namespace phraser{
		class IPhraserService{
			public:
				//! ��ȡģ��
				virtual shared_ptr<drawBasement::IModel> loadModelFromFile(const wchar_t* filename)=0;
		};
	}
}