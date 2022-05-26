#pragma once
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <mysql.h>
#include <winsock.h>

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
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL m_sqlCon;
	// �������ݿ�
	BOOL ConnectDB(CString strIP, CString strSqlUser, CString strSqlPassworld, CString strDataBase, int sqlPoint);
	// �ر����ݿ�
	BOOL DisconnectDB();

	list<msg> ls;	//�洢����
};

