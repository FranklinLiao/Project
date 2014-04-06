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
	//��������
	 void insertInfo(string insertString);
	//��������
	 void updateInfo(string updateString);
	//��ѯ����  �����vector�ŵĶ���һ��һ���Ķ��������vector�ŵ���ĳ���������������
	/*
	 template <typename  T>
	vector<vector<string>> getObjectInfo(string queryString,T object);
	*/
	 vector<vector<string>> getObjectInfo(string queryString,string tableName,int tableRowCount);
	
	//template <typename K>
	int getRowCount(string tableName);

	//��װ��ѯ���е�sql���
	// string createQuerySql(string tableName);

	/*
	//��ñ������
	template <typename K>
	int getRowCount(K object);

	template <typename T>
		T  getObject(string sqlString,T object);
	template <typename K>
		K combineObject(vector<string>,K object);
	*/
};