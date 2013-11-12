// 容器.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"tools\CobjContainer.hpp"
#include<iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	xc::CobjContainer<int> a;
	xc::IobjContainer<int> *k=&a;
	k->addObj(1);
	k->addObj(2);
	k->addObj(3);
	k->removeObj(2);
	//auto i = a.begin();
	/*while(i!= a.end()){
		cout<<*i++<<endl;
	}
	try
	{
		cout<<a.getObjAt(3)<<endl;
	}
	catch (xc::outOfRangeException& e)
	{
		
	}*/
	k->doFunc([](int& i){cout<<i<<endl;});
	system("pause");
	return 0;
}

