#pragma once
#include<MyTypes.h>
#include <vector>
#include"ICanvas.h"
#include"IDrawBuffers.h"
#include<tools/CobjContainer.hpp>
namespace xc{
	namespace drawBasement{
		template<typename T>
		class IModel_T:public T{
		public:
			virtual void render(ICanvas* canvas)=0;
		};
		typedef IModel_T<IobjContainer<shared_ptr<IDrawVertexBufferOBject>>> IModel;

		class CModel:public CobjContainer<IModel,shared_ptr<IDrawVertexBufferOBject>>{
		public:
			void render(ICanvas* canvas){
				this->doFunc([&canvas](shared_ptr<IDrawVertexBufferOBject>& vbo){
					canvas->render(vbo);
				});
			}
		};
	}
}