// 监听器.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<tools\Clistener.hpp>
#include <iostream>
#include <string>
#include<vector>
#include <agents.h>
using namespace std;
class listener{
public:
	virtual void onEvent()=0;
};
class clis:public listener{
public:
	void onEvent(){
		cout<<"hello";
	}


};
class ABC:public xc::listener::multipulContainer<listener>{
public:
	void doEvent(){
		doFunc([](shared_ptr<listener> l){l->onEvent();});
	}
};

using namespace std::tr1;
using namespace concurrency;
int _tmain(int argc, _TCHAR* argv[])
{
	ABC k;
	xc::listener::IMultipulContainer<listener> *kk=&k;
	shared_ptr<clis> t(new clis);
	shared_ptr<clis> t2(new clis);
	shared_ptr<clis> t3(new clis);
	k.registerListener(t);
	k.registerListener(t);
	k.registerListener(t2);
	k.registerListener(t2);
	k.registerListener(t3);
	k.registerListener(t3);
	k.unregister(t2);
	k.doEvent();
	/*
	call<wchar_t> test([](wchar_t c){wcout<<c;});
	Concurrency::timer<wchar_t> tim(100,_T('.'),&test,true);
	tim.start();
	for(int i=0;i<1000;++i)
	{
		k.doEvent();

	}
	tim.stop();*/
	
	system("pause");
	return 0;
}

