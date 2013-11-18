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
			if(m_VBO) glDeleteBuffers(1,&m_VBO);
		}

		//lock out �ڲ��Ļ�����
		unsigned char* COpenglBuffer::lock(){
			if(m_Buff == nullptr) throw std::exception("null ptr");
			return m_Buff;
		}
		//�ض��建������С
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
			if(!m_VBO) glGenBuffers(1,&m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, m_Size, m_Buff, GL_STATIC_DRAW);
		}

		//////////////////////////////////////////////////////////////////////////
		COpenglIndexBuffer::COpenglIndexBuffer():
			m_IBO(0),m_IndexNum(0),m_EPT(EPT_TRIANGLES),m_EIT(EIT_UBYTE)
		{

		}
		COpenglIndexBuffer::~COpenglIndexBuffer(){
			if(m_IBO) glDeleteBuffers(1,&m_IBO);
		}
		//! ��ָ��λ��ʹ�ô˻���
		void COpenglIndexBuffer::use(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		}
		//! ��ʼ��������
		void COpenglIndexBuffer::initialBuffer(){
			if(!m_IBO) glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, COpenglBuffer::getBufferSize(),COpenglBuffer::lock(), GL_STATIC_DRAW);
		}
		//////////////////////////////////////////////////////////////////////////
		COpenglVertexBufferObject::COpenglVertexBufferObject():m_VBO(0){

		}
		COpenglVertexBufferObject::~COpenglVertexBufferObject(){
			if(m_VBO){
				glDeleteVertexArrays(1,&m_VBO);
			}
		}
		//! ��ʼ��ʼ��
		void COpenglVertexBufferObject::initialStart(){
			if(!m_VBO){
				glGenVertexArrays(1,&m_VBO);
			}
			glBindVertexArray(m_VBO);
		}
		//! ������ʼ��
		void COpenglVertexBufferObject::initialEnd(){
			if(m_vertexList.size()==0 || m_indexBuffer == 0){
				throw std::exception("vertexbufferObject initial error");
			}
			glBindVertexArray(0);
		}
		//! �󶨶��㻺��
		void COpenglVertexBufferObject::addVertexBuf(shared_ptr<IDrawBuffer> vbuf){
			unsigned int slot = m_vertexList.size();
			vbuf->use(slot);
			m_vertexList.push_back(vbuf);
		}
		//! ����������
		void COpenglVertexBufferObject::bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf){
			m_indexBuffer=ibuf;
			m_indexBuffer->use();
		}
		//! ʹ�ô˻�����
		void COpenglVertexBufferObject::use(){
			glBindVertexArray(m_VBO);
		}
		//! ʹ�����
		void COpenglVertexBufferObject::unUse(){
			glBindVertexArray(0);
		}
		//! ��ȡ��Ҫ���Ƶ���������
		unsigned int COpenglVertexBufferObject::getIndexNums(){
			return m_indexBuffer->getIndexNums();
		}
		//! ��ȡ��Ҫ���Ƶ�ͼԪ����
		EnumPrimityType COpenglVertexBufferObject::getPrimityType(){
			return m_indexBuffer->getPrimityType();
		}
		//! ��ȡ��������
		EnumIndexType COpenglVertexBufferObject::getIndexType(){
			return m_indexBuffer->getIndexType();
		}
	}
}