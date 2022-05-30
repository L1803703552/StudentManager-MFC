#pragma once
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <mysql.h>
#include <winsock.h>
#include <vector>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./score.txt"
#define _F_INFO "./info.txt"

using namespace std;

struct msg
{
	vector<string> info;// ѧ�š��������ֶ�
	vector<int> sub;// �ɼ��ֶ�
};

class CInfoFile
{
private:
	string Sql_Host;
	string Sql_User;
	string Sql_Pwd;
	string Sql_DB;
	int Sql_Port;
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

	MYSQL_RES* resInfo;
	MYSQL_RES* resSub;
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL_ROW rowInfo;
	MYSQL_ROW rowSub;
	MYSQL m_sqlCon;
	// �������ݿ�
	BOOL ConnectDB();
	// �ر����ݿ�
	BOOL DisconnectDB();
	// ��ȡ���ݿ�������Ϣ
	void GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port);
	// д�����ݿ�������Ϣ
	void WriteDBInfo(char* host, char* user, char* pwd, char* db, int prot);
	// ��ȡ���ݿ�
	BOOL ReadDB();
	// д�����ݿ�
	BOOL WriteDB();
	vector<CString> subName; // ѧ������
	vector<CString> stuInfo; //ѧ����Ϣ
	vector<CString> head; // ��ͷ
	list<msg> ls;	//�洢����
};

