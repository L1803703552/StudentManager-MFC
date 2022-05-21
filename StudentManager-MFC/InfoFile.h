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
	string id;		// 学号
	string name;	// 姓名
	int sub1;		// 成绩1
	int sub2;		// 成绩2
};

class CInfoFile
{
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

	list<msg> ls;	//存储链表
};

