#pragma once
#include "stdafx.h"
#include "DataBase.h"
#include "GetDBConnTool.h"

/*
	//连接数据库
	_ConnectionPtr GetDBConnTool::getMyConnection(_Connection& conn) {
		_ConnectionPtr con = GetDBConnTool::connection;
		return con;
	}
*/	
	//关闭数据库
	void GetDBConnTool::closeConnection(_ConnectionPtr& conn){
		try {
			if(conn->State)
				conn->Close();
		} catch(_com_error e) {
			cout<<"close database  connection failed "<<endl;
		}
	}

	void GetDBConnTool::closeRecordSet(_RecordsetPtr& record) {
		try {
			if(record->State)
				record->Close();
		} catch(_com_error e) {
			cout<<"close database record  failed "<<endl;
		}
	}
	
