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
	vector<string> info;// 学号、姓名等字段
	vector<int> sub;// 成绩字段
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

	MYSQL_RES* resInfo;
	MYSQL_RES* resSub;
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL_ROW rowInfo;
	MYSQL_ROW rowSub;
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
	vector<CString> subName; // 学科名称
	vector<CString> stuInfo; //学生信息
	vector<CString> head; // 表头
	list<msg> ls;	//存储链表
};

