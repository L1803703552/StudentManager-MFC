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
	subName.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));
	char* head = strtok(buf, ",");//取出学号
	head = strtok(NULL, ",");//姓名
	while (head != NULL)
	{
		head = strtok(NULL, ",");
		if (head == NULL)
			break;
		subName.push_back(CString(head));
	}

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		// AfxMessageBox(CString(buf));
		char *sst = strtok(buf, ","); //以“,”切割
		if (sst != NULL)
			tmp.id = sst; //学号
		else
			break;
		sst = strtok(NULL, ",");
		tmp.name = sst;	//姓名

		for (int i = 0; i < subName.size(); i++)//读取每个学科成绩
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.sub.push_back(0);
			else
				tmp.sub.push_back(atoi(sst));
		}
		
		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	//if (ls.size() > 0)	//学生链表有内容才执行
	//{
		ofs << "学号,姓名"; //写入表头
		for (vector<CString>::iterator it = subName.begin(); it != subName.end(); it++)
		{
			ofs << "," << CStringA(*it);
		}
		ofs << endl;
		//通过迭代器取出链表内容，写入文件，以“,”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << ",";		
			ofs << it->name;
			for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)
			{
				ofs << "," << *its;
			}
			ofs << endl;
		}
	//}

	ofs.close();//关闭文件
}

// 添加学生
// id:学号，name:姓名，sub1:成绩1，sub2:成绩2
void CInfoFile::Addline(char *buf)
{
	msg tmp;

	// AfxMessageBox(CString(buf));
	char* sst = strtok(buf, ",");
	if (sst != NULL)
		tmp.id = sst; //学号
	else
		return;
	sst = strtok(NULL, ",");
	tmp.name = sst;	//姓名

	for (int i = 0; i < subName.size(); i++)//读取每个学科成绩
	{
		sst = strtok(NULL, ",");
		if (sst == NULL)
			tmp.sub.push_back(0);
		else
			tmp.sub.push_back(atoi(sst));
	}

	ls.push_back(tmp); //放在链表的后面
}

BOOL CInfoFile::ConnectDB()
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	//设置字符编码
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB18030");
	if (!mysql_real_connect(&m_sqlCon, Sql_Host.c_str(), Sql_User.c_str(), Sql_Pwd.c_str(), Sql_DB.c_str(), Sql_Port, NULL, 0))
	{
		return FALSE;
	}
	else
	{
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
	ls.clear();
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
	mysql_free_result(result);
	return TRUE;
}

BOOL CInfoFile::WriteDB()
{
	int flag;
	// 删除原记录
	flag = mysql_query(&m_sqlCon, "drop table stumanager;");
	if (flag)
		return FALSE;
	// 创建表头
	flag = mysql_query(&m_sqlCon, "create table if not exists stumanager (\
				`学号` varchar (255) NOT NULL DEFAULT '',\
				`姓名` varchar (255) NULL DEFAULT '',\
				`成绩1` int NULL,\
				`成绩2` int NULL,\
				PRIMARY KEY (`学号`)\
	);");
	if (flag)
		return FALSE;
	// 插入记录
	char sqlhead[1024] = { 0 }, sqlstr[1024] = { 0 };
	snprintf(sqlhead, 1024, "insert into stumanager (学号 ,姓名 ,成绩1 ,成绩2 ) values( ");
	for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		snprintf(sqlstr, 1024, "%s '%s', '%s', %d, %d );", sqlhead, it->id.c_str(), it->name.c_str(), it->sub1, it->sub2);
		flag = mysql_real_query(&m_sqlCon, sqlstr, strlen(sqlstr));
		if (flag)
			return FALSE;
	}
	return TRUE;
}

