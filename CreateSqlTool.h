#pragma once
#include "stdafx.h"
#include <stdarg.h>
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;


class CreateSqlTool {
public:
	//insert into product1(productNum,productName,productSale,productBank) values(1,'诺基亚N97','4499','12');
	//t
	static string createInsertSql(string tableName,string sqlInfo);

	//UPDATE SendMsg SET sendstatus = 1 WHERE teacherid=1001;
	//tableName   sendstatus = 1 WHERE teacherid=1001
	static string createUpdateSql(string tableName,string sqlInfo);

	//select name from sysobjects where xtype='U';
	//tableName   where xtype='U'
	static string createQuerySql(string tableName,string sqlInfo);
	//拼接字符串   count为参数的个数     输入的参数必须为string,int什么的也要转换成string再传入
	static string getString(int count,...);
};