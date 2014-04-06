#pragma once
#include "stdafx.h"
#include "GetDBConnTool.h"
#include "DBConnPool.h"
#include <iostream>
#include <iomanip> //for setw()
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class DataBase{
public:
	 _bstr_t sqlString;
public:
	//插入数据
	 void insertInfo(string insertString);
	//更新数据
	 void updateInfo(string updateString);
	//查询数据  外面的vector放的都是一个一个的对象；里面的vector放的是某个对象的所有属性
	/*
	 template <typename  T>
	vector<vector<string>> getObjectInfo(string queryString,T object);
	*/
	 vector<vector<string>> getObjectInfo(string queryString,string tableName,int tableRowCount);
	
	//template <typename K>
	int getRowCount(string tableName);

	//组装查询所有的sql语句
	// string createQuerySql(string tableName);

	/*
	//获得表的列数
	template <typename K>
	int getRowCount(K object);

	template <typename T>
		T  getObject(string sqlString,T object);
	template <typename K>
		K combineObject(vector<string>,K object);
	*/
};