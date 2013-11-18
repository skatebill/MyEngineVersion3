//////////////////////////////////////////////////////////////////////////
//		�������Ľӿ�
//		
//		author by Ф�� @ 2013��11��3��2:44:18
//
//////////////////////////////////////////////////////////////////////////
#pragma once
namespace xc{
	namespace drawBasement{
		class IDrawBuffer{
		public:
			//! lock out �ڲ��Ļ��������ٸ�������֮��
			virtual unsigned char* lock()=0;
			//! ��ȡ��������С
			virtual unsigned int getBufferSize()=0;
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size)=0;
			//! �����ڲ�Ԫ��һ���ж��ٸ�
			virtual void setElemtSize(unsigned int nums)=0;
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use(int slot)=0;
			//! ʹ�����
			virtual void unUse(int slot)=0;
			//! ��ʼ��������(�����ݸ��ĺ����һ�¿����ϴ������ݵ��Դ���)
			virtual void initialBuffer()=0;
		};
		//! ͼԪ����ö��
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
			//! lock out �ڲ��Ļ��������ٸ�������֮��
			virtual unsigned char* lock()=0;
			//! ��ȡ��������С
			virtual unsigned int getBufferSize()=0;
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size)=0;
			//! ʹ�ô˻���
			virtual void use()=0;
			//! ʹ�����
			virtual void unUse()=0;
			//! ��ʼ��������(�����ݸ��ĺ����һ�¿����ϴ������ݵ��Դ���)
			virtual void initialBuffer()=0;

			//! ���û��Ƶ���������
			virtual void setIndexNums(unsigned int n)=0;

			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums()=0;
			//! ��ȡ��Ҫ���Ƶ�ͼԪ����
			virtual EnumPrimityType getPrimityType()=0;
			//! ����ͼԪ����
			virtual void setPrimityType(EnumPrimityType type)=0;
			//! ��ȡ��������
			virtual EnumIndexType getIndexType()=0;
		};

		class IDrawVertexBufferOBject{
		public:
			//! ʹ�ô˻�����
			virtual void use()=0;
			//! ʹ�����
			virtual void unUse()=0;
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums()=0;
			//! ��ȡ��Ҫ���Ƶ�ͼԪ����
			virtual EnumPrimityType getPrimityType()=0;
			//! ��ȡ��������
			virtual EnumIndexType getIndexType()=0;
		};
	}
}