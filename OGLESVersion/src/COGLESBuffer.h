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

			//! ������������
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
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use();
			//! ��ʼ��������
			virtual void initialBuffer();

			//! lock out �ڲ��Ļ�����
			virtual unsigned char* lock(){
				return COGLESBuffer::lock();
			}
			//! ��ȡ��������С
			virtual unsigned int getBufferSize(){
				return COGLESBuffer::getBufferSize();
			}
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size){
				COGLESBuffer::reSizeBuffer(size);
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
		class COGLESVertexBufferObject:public IDrawVertexBufferOBject{
		private:
		public:
			std::vector<shared_ptr<IDrawBuffer>> m_vertexList;
			shared_ptr<IDrawIndexBuffer> m_indexBuffer;
			COGLESVertexBufferObject();
			~COGLESVertexBufferObject();
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