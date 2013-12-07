#pragma once
#include<tools/MyTypes.h>
#include<drawBasement/IDrawBuffers.h>
#include<GLES2/gl2.h>
#include <vector>
namespace xc{
	namespace drawBasement{
		class COGLESBuffer:public IDrawBuffer{
		private:
			unsigned int m_Size;
			unsigned int m_ElementSize;
			unsigned char* m_Buff;
			GLuint m_VBO;
			GLuint mDataType;
		public:
			explicit COGLESBuffer();
			~COGLESBuffer();

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

			//! 设置数据类型
			virtual void setDataType(EnumDataType t){
				switch (t)
				{
				case xc::drawBasement::EDT_FLOAT:
					mDataType = GL_FLOAT;
					break;
				case xc::drawBasement::EDT_UINT:
					mDataType = GL_UNSIGNED_INT;
					break;
				case xc::drawBasement::EDT_INT:
					mDataType = GL_INT;
					break;
				case xc::drawBasement::EDT_USHORT:
					mDataType = GL_UNSIGNED_SHORT;
					break;
				case xc::drawBasement::EDT_SHORT:
					mDataType = GL_SHORT;
					break;
				case xc::drawBasement::EDT_UBYTE:
					mDataType = GL_UNSIGNED_BYTE;
					break;
				case xc::drawBasement::EDT_BYTE:
					mDataType = GL_BYTE;
					break;
				default:
					break;
				}
			}
		};

		class COGLESIndexBuffer:virtual public COGLESBuffer,virtual public IDrawIndexBuffer{
		private:
			GLuint m_IBO;
			unsigned int m_IndexNum;
			EnumPrimityType m_EPT;
			EnumIndexType m_EIT;
		public:
			explicit COGLESIndexBuffer();
			~COGLESIndexBuffer();
			//! 在指定位置使用此缓冲
			virtual void use();
			//! 初始化缓冲区
			virtual void initialBuffer();

			//! lock out 内部的缓冲区
			virtual unsigned char* lock(){
				return COGLESBuffer::lock();
			}
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize(){
				return COGLESBuffer::getBufferSize();
			}
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size){
				COGLESBuffer::reSizeBuffer(size);
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
		class COGLESVertexBufferObject:public IDrawVertexBufferOBject{
		private:
		public:
			std::vector<shared_ptr<IDrawBuffer>> m_vertexList;
			shared_ptr<IDrawIndexBuffer> m_indexBuffer;
			COGLESVertexBufferObject();
			~COGLESVertexBufferObject();
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