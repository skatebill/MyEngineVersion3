// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ASSIMPPHRASER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ASSIMPPHRASER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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