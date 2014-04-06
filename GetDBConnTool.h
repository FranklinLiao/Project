#pragma once
#include "stdafx.h"
#include <iostream>
#include <iomanip> //for setw()
#include <string>
#include <vector>
#include <cstring>
using namespace std;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")
//连接数据库，取数据，关闭数据库整个封装在一起
class GetDBConnTool{
public:
	 _ConnectionPtr connection;
private:
	 _bstr_t databaseInfo;
public:
	GetDBConnTool() {
		::CoInitialize(NULL); //初始化OLE/COM库环境,为访问ADO接口做准备
		databaseInfo="Driver={sql server};Server=192.168.0.26;Database=MapData;uid=sa; pwd=Linux2539311;";
		try {
			connection.CreateInstance(__uuidof(Connection));   //建立数据库连接的实例
			connection->Open(databaseInfo,"","",adModeUnknown);
			if(connection==NULL) {
				cout<<"connect to database failed"<<endl;
			}
		}catch(_com_error e) {
			cout<<"connect to database failed 2"<<endl;
		}
	};

	//获得连接
	void  getMyConnection(_ConnectionPtr& conn) {
		conn = connection;
	}
	//关闭连接
	void closeConnection(_ConnectionPtr& conn);
	void closeRecordSet(_RecordsetPtr& record);
};