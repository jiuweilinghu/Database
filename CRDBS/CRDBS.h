
// CRDBS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCRDBSApp: 
// �йش����ʵ�֣������ CRDBS.cpp
//

class CCRDBSApp : public CWinApp
{
public:
	CCRDBSApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCRDBSApp theApp;
