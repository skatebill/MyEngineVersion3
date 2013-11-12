// 缓冲区.cpp : 定义控制台应用程序的入口点。
//
#include<tools/XCBuffers.hpp>
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	xc::buffer b;
	b.resizeBuffer(100);
	int* buf = (int*)b.get();
	buf[0]=1;
	buf[1]=2;
	return 0;
}

