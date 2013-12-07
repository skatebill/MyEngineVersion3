// AssimpPhraser.cpp : 定义 DLL 应用程序的导出函数。
//

#include "AssimpPhraser.h"
#include "src/CAssimpPhraser.h"

xc::shared_ptr<xc::phraser::IPhraserService> createAssimpPhraserService(xc::shared_ptr<xc::fileservice::IFileService> f,xc::shared_ptr<xc::drawBasement::IDrawFactory> d)
{
	return xc::phraser::createAssimpPhraserService(f,d);
}