//////////////////////////////////////////////////////////////////////////
//		缓冲区的接口
//		
//		author by 肖驰 @ 2013年11月3日2:44:18
//
//////////////////////////////////////////////////////////////////////////
#pragma once
namespace xc{
	namespace drawBasement{
		class IDrawBuffer{
		public:
			//! lock out 内部的缓冲区（再更改数据之后）
			virtual unsigned char* lock()=0;
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize()=0;
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size)=0;
			//! 设置内部元素一组有多少个
			virtual void setElemtSize(unsigned int nums)=0;
			//! 在指定位置使用此缓冲
			virtual void use(int slot)=0;
			//! 使用完毕
			virtual void unUse(int slot)=0;
			//! 初始化缓冲区(在数据更改后调用一下可以上传新数据到显存中)
			virtual void initialBuffer()=0;
		};
		//! 图元类型枚举
		enum EnumPrimityType
		{
			EPT_DOTS=0,
			EPT_LINES,
			EPT_LINE_STRIP,
			EPT_TRIANGLES,
			EPT_TRIANGLE_STRIP
		};
		enum EnumIndexType{
			EIT_UINT=0,
			EIT_UBYTE
		};
		static const unsigned short UINT_SIZE = sizeof(unsigned int);
		static const unsigned short UBYTE_SIZE = sizeof(unsigned char);
		class IDrawIndexBuffer{
		public:
			//! lock out 内部的缓冲区（再更改数据之后）
			virtual unsigned char* lock()=0;
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize()=0;
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size)=0;
			//! 使用此缓冲
			virtual void use()=0;
			//! 使用完毕
			virtual void unUse()=0;
			//! 初始化缓冲区(在数据更改后调用一下可以上传新数据到显存中)
			virtual void initialBuffer()=0;

			//! 设置绘制的索引个数
			virtual void setIndexNums(unsigned int n)=0;

			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums()=0;
			//! 获取需要绘制的图元类型
			virtual EnumPrimityType getPrimityType()=0;
			//! 设置图元类型
			virtual void setPrimityType(EnumPrimityType type)=0;
			//! 获取数据类型
			virtual EnumIndexType getIndexType()=0;
		};
	}
}