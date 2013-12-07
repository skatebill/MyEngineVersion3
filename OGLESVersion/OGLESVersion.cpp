// OGLESVersion.cpp : 定义 DLL 应用程序的导出函数。
//

#include "OGLESVersion.h"

xc::drawBasement::COGLESFactory* createOGLESFactory(){
	return new xc::drawBasement::COGLESFactory;
}