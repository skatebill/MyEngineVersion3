// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� OGLESVERSION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// OGLESVERSION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef _WINDOWS
#ifdef OGLESVERSION_EXPORTS
#define OGLESVERSION_API __declspec(dllexport)
#else
#define OGLESVERSION_API __declspec(dllimport)
#endif
#else
#define  OGLESVERSION_API
#endif
#include"src/COGLESFactory.h"

OGLESVERSION_API xc::drawBasement::COGLESFactory* createOGLESFactory();