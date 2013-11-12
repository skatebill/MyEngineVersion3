#include"COpenglBuffer.h"
#include <stdlib.h>
#include <exception>

namespace xc{
	namespace drawBasement{

		COpenglBuffer::COpenglBuffer():m_Buff(nullptr),m_Size(0),m_VBO(0),m_ElementSize(0){

		}
		COpenglBuffer::~COpenglBuffer(){
			if(m_Buff) free(m_Buff);
			m_Buff = nullptr;
		}

		//lock out 内部的缓冲区
		unsigned char* COpenglBuffer::lock(){
			if(m_Buff == nullptr) throw std::exception("null ptr");
			return m_Buff;
		}
		//重定义缓冲区大小
		void COpenglBuffer::reSizeBuffer(unsigned int size){
			if(m_Buff) free(m_Buff);
			m_Buff = (unsigned char*)malloc(size);
			m_Size = size;
		}
		void COpenglBuffer::use(int slot){
			glEnableVertexAttribArray(slot);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glVertexAttribPointer(slot, m_ElementSize, GL_FLOAT, GL_FALSE, 0, 0);
		}
		void COpenglBuffer::unUse(int slot){
			glDisableVertexAttribArray(slot);
		}
		void COpenglBuffer::initialBuffer(){
			if(m_Buff == nullptr) throw std::exception("null ptr");
			glGenBuffers(1,&m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, m_Size, m_Buff, GL_STATIC_DRAW);
		}

		//////////////////////////////////////////////////////////////////////////
		COpenglIndexBuffer::COpenglIndexBuffer():
			m_IBO(0),m_IndexNum(0),m_EPT(EPT_TRIANGLES),m_EIT(EIT_UBYTE)
		{

		}
		//! 在指定位置使用此缓冲
		void COpenglIndexBuffer::use(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		}
		//! 初始化缓冲区
		void COpenglIndexBuffer::initialBuffer(){
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, COpenglBuffer::getBufferSize(),COpenglBuffer::lock(), GL_STATIC_DRAW);
		}
	}
}