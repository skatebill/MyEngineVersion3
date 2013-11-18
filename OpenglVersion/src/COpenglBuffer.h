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

			//lock out �ڲ��Ļ�����
			virtual unsigned char* lock();
			//! ��ȡ��������С
			virtual unsigned int getBufferSize(){
				return m_Size;
			}
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size);
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use(int slot);

			//! �����ڲ�Ԫ��һ���ж��ٸ�
			virtual void setElemtSize(unsigned int nums){
				m_ElementSize = nums;
			}
			//! ��ʼ��������
			virtual void initialBuffer();
			//! �ͷ���Դ
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
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use();
			//! ��ʼ��������
			virtual void initialBuffer();

			//! lock out �ڲ��Ļ�����
			virtual unsigned char* lock(){
				return COpenglBuffer::lock();
			}
			//! ��ȡ��������С
			virtual unsigned int getBufferSize(){
				return COpenglBuffer::getBufferSize();
			}
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size){
				COpenglBuffer::reSizeBuffer(size);
			}
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums(){
				return m_IndexNum;
			}
			//! ���û��Ƶ���������
			virtual void setIndexNums(unsigned int n){
				m_IndexNum=n;
			}
			//! ��ȡ��Ҫ���Ƶ�ͼԪ����
			virtual EnumPrimityType getPrimityType(){
				return m_EPT;
			}
			//! ��ȡ��������
			virtual EnumIndexType getIndexType(){
				return m_EIT;
			}
			//! ����ͼԪ����
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
			//! ��ʼ��ʼ��
			void initialStart();
			//! ������ʼ��
			void initialEnd();
			//! �󶨶��㻺��
			void addVertexBuf(shared_ptr<IDrawBuffer> vbuf);
			//! ����������
			void bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf);
			//! ʹ�ô˻�����
			virtual void use();
			//! ʹ�����
			virtual void unUse();
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums();
			//! ��ȡ��Ҫ���Ƶ�ͼԪ����
			virtual EnumPrimityType getPrimityType();
			//! ��ȡ��������
			virtual EnumIndexType getIndexType();
		};
	}
}