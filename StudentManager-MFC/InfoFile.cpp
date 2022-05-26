#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	ifs.getline(buf, sizeof(buf)); // 再读取一行，跳过本地用户名密码
	ifs.getline(buf, sizeof(buf));
	Sql_Host = buf;// 主机地址
	ifs.getline(buf, sizeof(buf));
	Sql_User = buf;// 用户名
	ifs.getline(buf, sizeof(buf));
	Sql_Pwd = buf;// 密码
	ifs.getline(buf, sizeof(buf));
	Sql_DB = buf;// 数据库名
	ifs.getline(buf, sizeof(buf));
	Sql_Port = atoi(buf);// 端口号
	ifs.close(); //关闭文件
}


CInfoFile::~CInfoFile()
{
}

//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);
	ifs.close(); //关闭文件
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl;
	ofs << pwd << endl;

	ofs.close();	//关闭文件
}

//读取学生信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		// AfxMessageBox(CString(buf));
		char *sst = strtok(buf, ","); //以“,”切割
		if (sst != NULL)
		{
			tmp.id = sst; //学号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, ",");
		tmp.name = sst;	//姓名

		sst = strtok(NULL, ",");
		tmp.sub1 = atoi(sst);	//学科1

		sst = strtok(NULL, ",");
		tmp.sub2 = atoi(sst);	//学科2

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//学生链表有内容才执行
	{
		ofs << "学号,姓名,学科1,学科2" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“,”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << ",";		
			ofs << it->name << ",";
			ofs << it->sub1 << ",";
			ofs << it->sub2 << endl;
		}
	}

	ofs.close();//关闭文件
}

// 添加学生
// id:学号，name:姓名，sub1:成绩1，sub2:成绩2
void CInfoFile::Addline(CString id, CString name, int sub1, int sub2)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//学号、姓名、数量有效
		if (!name.IsEmpty() && !id.IsEmpty())
		{
			CStringA str;
			str = id;
			tmp.id = str.GetBuffer();
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，姓名
			tmp.sub1 = sub1;	//学科1
			tmp.sub2 = sub2;	//学科2

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}

BOOL CInfoFile::ConnectDB()
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	//设置字符编码
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB18030");
	if (!mysql_real_connect(&m_sqlCon, Sql_Host.c_str(), Sql_User.c_str(), Sql_Pwd.c_str(), Sql_DB.c_str(), Sql_Port, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		return FALSE;
	}
	else
	{
		AfxMessageBox(_T("访问数据库成功!"));
		return TRUE;
	}
}

BOOL CInfoFile::DisconnectDB()
{
	mysql_close(&m_sqlCon);//关闭Mysql连接  
	return TRUE;
}

void CInfoFile::GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port)
{
	host = (CString)Sql_Host.c_str();
	user = (CString)Sql_User.c_str();
	pwd = (CString)Sql_Pwd.c_str();
	db = (CString)Sql_DB.c_str();
	port = Sql_Port;
}

void CInfoFile::WriteDBInfo(char* host, char* user, char* pwd, char* db, int port)
{
	ifstream ifs;
	string user_name, user_pwd;
	ifs.open(_F_LOGIN);
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));
	user_name = buf;
	ifs.getline(buf, sizeof(buf));
	user_pwd = buf;
	ifs.close(); //关闭文件

	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << user_name << endl;
	ofs << user_pwd << endl;
	ofs << host << endl;
	ofs << user << endl;
	ofs << pwd << endl;
	ofs << db << endl;
	ofs << port << endl;

	ofs.close();	//关闭文件
}

BOOL CInfoFile::ReadDB()
{
	mysql_query(&m_sqlCon, "select * from stumanager;");
	result = mysql_store_result(&m_sqlCon);
	if (!result)
		return FALSE;
	msg tmp;
	while (row = mysql_fetch_row(result))
	{
		tmp.id = row[0];
		tmp.name = row[1];
		tmp.sub1 = atoi(row[2]);
		tmp.sub2 = atoi(row[3]);
		ls.push_back(tmp);
	}
	return TRUE;
}

BOOL CInfoFile::WriteDB()
{
	return TRUE;
}
