#pragma once
#include"appTypes.h"
#include <MyTypes.h>
#include<site/site.h>
#include<functional>
namespace xc{
	namespace app{
		class IApplication{
		private:
			shared_ptr<ISite> mSite;
		public:
			//! 安装站点
			void installSite(shared_ptr<ISite> site){
				mSite=site;
			}
			inline shared_ptr<ISite> getSite(){
				return mSite;
			}

			//////////////////////////////////////////////////////////////////////////
			//	接口
			//  UI 事件
			//! 初始化窗口信息
			virtual void onInitialWindow(std::function<void(const char*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun)=0;
			//! 鼠标事件
			virtual void onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos)=0;
			//! 键盘事件
			virtual void onKeyEvent(KeyEvent key,int keyCode)=0;
			//! 初始化
			virtual void onInitialData()=0;
			//! 销毁
			virtual void onCleanup()=0;
		};
	}
}