#pragma once
#include "stdafx.h"
#include <iostream>
#include <iomanip> //for setw()
#include <string>
#include <vector>
#include <cstring>
using namespace std;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")
//�������ݿ⣬ȡ���ݣ��ر����ݿ�������װ��һ��
class GetDBConnTool{
public:
	 _ConnectionPtr connection;
private:
	 _bstr_t databaseInfo;
public:
	GetDBConnTool() {
		::CoInitialize(NULL); //��ʼ��OLE/COM�⻷��,Ϊ����ADO�ӿ���׼��
		databaseInfo="Driver={sql server};Server=192.168.0.26;Database=MapData;uid=sa; pwd=Linux2539311;";
		try {
			connection.CreateInstance(__uuidof(Connection));   //�������ݿ����ӵ�ʵ��
			connection->Open(databaseInfo,"","",adModeUnknown);
			if(connection==NULL) {
				cout<<"connect to database failed"<<endl;
			}
		}catch(_com_error e) {
			cout<<"connect to database failed 2"<<endl;
		}
	};

	//�������
	void  getMyConnection(_ConnectionPtr& conn) {
		conn = connection;
	}
	//�ر�����
	void closeConnection(_ConnectionPtr& conn);
	void closeRecordSet(_RecordsetPtr& record);
};