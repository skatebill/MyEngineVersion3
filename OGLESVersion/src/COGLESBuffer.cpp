#include"COGLESBuffer.h"
#include <stdlib.h>
#include <exception>

namespace xc{
	namespace drawBasement{

		COGLESBuffer::COGLESBuffer():m_Buff(nullptr),m_Size(0),m_VBO(0),m_ElementSize(0),mDataType(GL_FLOAT){

		}
		COGLESBuffer::~COGLESBuffer(){
			if(m_Buff) free(m_Buff);
			m_Buff = nullptr;
			if(m_VBO) glDeleteBuffers(1,&m_VBO);
		}

		//lock out 内部的缓冲区
		unsigned char* COGLESBuffer::lock(){
			if(m_Buff == nullptr) throw std::exception();
			return m_Buff;
		}
		//重定义缓冲区大小
		void COGLESBuffer::reSizeBuffer(unsigned int size){
			if(m_Buff) free(m_Buff);
			m_Buff = (unsigned char*)malloc(size);
			m_Size = size;
		}
		void COGLESBuffer::use(int slot){
			glEnableVertexAttribArray(slot);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			//if(mDataType == GL_UNSIGNED_INT){
				//glVertexAttribPointer(slot, m_ElementSize, mDataType,0, 0);

			//}else{
				glVertexAttribPointer(slot, m_ElementSize, mDataType, GL_FALSE, 0, 0);
			//}
		}
		void COGLESBuffer::unUse(int slot){
			glDisableVertexAttribArray(slot);
		}
		void COGLESBuffer::initialBuffer(){
			if(m_Buff == nullptr) throw std::exception();
			if(!m_VBO) glGenBuffers(1,&m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			if(mDataType == GL_UNSIGNED_INT){
				mDataType = GL_FLOAT;
				u32* ptri = (u32*)this->lock();
				f32* ptrf = (f32*)this->lock();
				int n = m_Size/sizeof(u32);
				while(n){
					n--;
					*ptrf=f32(*ptri);
					ptrf++;
					ptri++;
				}
			}
			glBufferData(GL_ARRAY_BUFFER, m_Size, m_Buff, GL_STATIC_DRAW);
		}

		//////////////////////////////////////////////////////////////////////////
		COGLESIndexBuffer::COGLESIndexBuffer():
			m_IBO(0),m_IndexNum(0),m_EPT(EPT_TRIANGLES),m_EIT(EIT_USHORT)
		{

		}
		COGLESIndexBuffer::~COGLESIndexBuffer(){
			if(m_IBO) glDeleteBuffers(1,&m_IBO);
		}
		//! 在指定位置使用此缓冲
		void COGLESIndexBuffer::use(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		}
		//! 初始化缓冲区
		void COGLESIndexBuffer::initialBuffer(){
			if(!m_IBO) glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, COGLESBuffer::getBufferSize(),COGLESBuffer::lock(), GL_STATIC_DRAW);
		}
		//////////////////////////////////////////////////////////////////////////
		COGLESVertexBufferObject::COGLESVertexBufferObject(){

		}
		COGLESVertexBufferObject::~COGLESVertexBufferObject(){
		}
		//! 开始初始化
		void COGLESVertexBufferObject::initialStart(){
		}
		//! 结束初始化
		void COGLESVertexBufferObject::initialEnd(){
			if(m_vertexList.size()==0 || m_indexBuffer == 0){
				throw std::exception();
			}
		}
		//! 绑定顶点缓冲
		void COGLESVertexBufferObject::addVertexBuf(shared_ptr<IDrawBuffer> vbuf){
			unsigned int slot = m_vertexList.size();
			vbuf->use(slot);
			m_vertexList.push_back(vbuf);
		}
		//! 绑定索引缓冲
		void COGLESVertexBufferObject::bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf){
			m_indexBuffer=ibuf;
			m_indexBuffer->use();
		}
		//! 使用此缓冲区
		void COGLESVertexBufferObject::use(){
			m_indexBuffer->use();
			for(u32 i=0;i<m_vertexList.size();++i){
				m_vertexList[i]->use(i);
			}
		}
		//! 使用完毕
		void COGLESVertexBufferObject::unUse(){
			m_indexBuffer->unUse();
			for(u32 i=0;i<m_vertexList.size();++i){
				m_vertexList[i]->unUse(i);
			}
		}
		//! 获取需要绘制的索引个数
		unsigned int COGLESVertexBufferObject::getIndexNums(){
			return m_indexBuffer->getIndexNums();
		}
		//! 获取需要绘制的图元类型
		EnumPrimityType COGLESVertexBufferObject::getPrimityType(){
			return m_indexBuffer->getPrimityType();
		}
		//! 获取数据类型
		EnumIndexType COGLESVertexBufferObject::getIndexType(){
			return m_indexBuffer->getIndexType();
		}
	}
}