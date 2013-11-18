#pragma once
#include<IDrawBuffers.h>
#include<gl/glew.h>
#include <vector>
#include<MyTypes.h>
namespace xc{
	namespace drawBasement{
		class COpenglBuffer:public IDrawBuffer{
		private:
			unsigned int m_Size;
			unsigned int m_ElementSize;
			unsigned char* m_Buff;
			GLuint m_VBO;
		public:
			explicit COpenglBuffer();
			~COpenglBuffer();

			//lock out 内部的缓冲区
			virtual unsigned char* lock();
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize(){
				return m_Size;
			}
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size);
			//! 在指定位置使用此缓冲
			virtual void use(int slot);

			//! 设置内部元素一组有多少个
			virtual void setElemtSize(unsigned int nums){
				m_ElementSize = nums;
			}
			//! 初始化缓冲区
			virtual void initialBuffer();
			//! 释放资源
			virtual void unUse(int slot);
		};

		class COpenglIndexBuffer:virtual public COpenglBuffer,virtual public IDrawIndexBuffer{
		private:
			GLuint m_IBO;
			unsigned int m_IndexNum;
			EnumPrimityType m_EPT;
			EnumIndexType m_EIT;
		public:
			explicit COpenglIndexBuffer();
			~COpenglIndexBuffer();
			//! 在指定位置使用此缓冲
			virtual void use();
			//! 初始化缓冲区
			virtual void initialBuffer();

			//! lock out 内部的缓冲区
			virtual unsigned char* lock(){
				return COpenglBuffer::lock();
			}
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize(){
				return COpenglBuffer::getBufferSize();
			}
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size){
				COpenglBuffer::reSizeBuffer(size);
			}
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums(){
				return m_IndexNum;
			}
			//! 设置绘制的索引个数
			virtual void setIndexNums(unsigned int n){
				m_IndexNum=n;
			}
			//! 获取需要绘制的图元类型
			virtual EnumPrimityType getPrimityType(){
				return m_EPT;
			}
			//! 获取数据类型
			virtual EnumIndexType getIndexType(){
				return m_EIT;
			}
			//! 设置图元类型
			virtual void setPrimityType(EnumPrimityType type){
				m_EPT = type;
			}

			virtual void unUse(){
				
			}
		};
		class COpenglVertexBufferObject:public IDrawVertexBufferOBject{
		private:
			std::vector<shared_ptr<IDrawBuffer>> m_vertexList;
			shared_ptr<IDrawIndexBuffer> m_indexBuffer;
			GLuint m_VBO;
		public:
			COpenglVertexBufferObject();
			~COpenglVertexBufferObject();
			//! 开始初始化
			void initialStart();
			//! 结束初始化
			void initialEnd();
			//! 绑定顶点缓冲
			void addVertexBuf(shared_ptr<IDrawBuffer> vbuf);
			//! 绑定索引缓冲
			void bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf);
			//! 使用此缓冲区
			virtual void use();
			//! 使用完毕
			virtual void unUse();
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums();
			//! 获取需要绘制的图元类型
			virtual EnumPrimityType getPrimityType();
			//! 获取数据类型
			virtual EnumIndexType getIndexType();
		};
	}
}