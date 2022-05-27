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
	string id;		// 学号
	string name;	// 姓名
	int sub1;		// 成绩1
	int sub2;		// 成绩2
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

	//读取登陆信息
	void ReadLogin(CString &name, CString &pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取学生信息
	void ReadDocline();

	// 写入学生信息
	void WirteDocline();

	// 添加学生信息
	void Addline(CString id,CString name, int sub1, int sub2);
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL m_sqlCon;
	// 连接数据库
	BOOL ConnectDB();
	// 关闭数据库
	BOOL DisconnectDB();
	// 获取数据库连接信息
	void GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port);
	// 写入数据库连接信息
	void WriteDBInfo(char* host, char* user, char* pwd, char* db, int prot);
	// 读取数据库
	BOOL ReadDB();
	// 写入数据库
	BOOL WriteDB();
	list<msg> ls;	//存储链表
};

