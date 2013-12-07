// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ASSIMPPHRASER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ASSIMPPHRASER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef _WINDOWS 
#ifdef ASSIMPPHRASER_EXPORTS
#define ASSIMPPHRASER_API __declspec(dllexport)
#else
#define ASSIMPPHRASER_API __declspec(dllimport)
#endif
#else
#define ASSIMPPHRASER_API
#endif
#include<service/phraser/IPhraseSerivce.h>
#include<service/file/IFileService.h>
#include<drawBasement/IDrawFactory.h>

ASSIMPPHRASER_API xc::shared_ptr<xc::phraser::IPhraserService> createAssimpPhraserService(xc::shared_ptr<xc::fileservice::IFileService> f,xc::shared_ptr<xc::drawBasement::IDrawFactory> d);