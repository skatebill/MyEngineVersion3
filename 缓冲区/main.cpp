// ������.cpp : �������̨Ӧ�ó������ڵ㡣
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

