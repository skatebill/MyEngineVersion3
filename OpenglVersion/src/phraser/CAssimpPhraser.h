#pragma once
#include <MyTypes.h>
#include <service/phraser/IPhraseSerivce.h>
#include <service/file/IFileService.h>
#include <drawBasement/IDrawFactory.h>
namespace xc{
	namespace phraser{
		shared_ptr<IPhraserService> createAssimpPhraserService(shared_ptr<fileservice::IFileService> f,shared_ptr<drawBasement::IDrawFactory> d);
	}
}