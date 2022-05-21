#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	string id;		// ѧ��
	string name;	// ����
	int sub1;		// �ɼ�1
	int sub2;		// �ɼ�2
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��½��Ϣ
	void ReadLogin(CString &name, CString &pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	// ��ȡѧ����Ϣ
	void ReadDocline();

	// д��ѧ����Ϣ
	void WirteDocline();

	// ���ѧ����Ϣ
	void Addline(CString id,CString name, int sub1, int sub2);

	list<msg> ls;	//�洢����
};

