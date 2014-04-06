#include "stdafx.h"
#include "DataBase.h"


	//插入数据
	void DataBase::insertInfo(string insertString) {
		GetDBConnTool dbCon;
		_ConnectionPtr connection;
		DBConnect* dbconnection;
		try {
			//connection=GetDBConnTool::getMyConnection();
			//GetDBConnTool dbCon;
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnGuard::GetAConnect();
			connection = dbconnection->_connection_ptr;
			sqlString = insertString.c_str();
			connection->Execute(sqlString,0,0);
			//dbCon.closeConnection(connection);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		}catch(_com_error e) {
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			cout<<e.Description()<<endl;
			cout<<"insert info failed";
		}
			
	}

	//更新数据
	void DataBase::updateInfo(string updateString) {
		GetDBConnTool dbCon;
		_ConnectionPtr connection;
		DBConnect* dbconnection;
		try {
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnGuard::GetAConnect();
			connection = dbconnection->_connection_ptr;
			sqlString=updateString.c_str();
			connection->Execute(sqlString,0,0);
			//dbCon.closeConnection(connection);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		}catch(_com_error e) {
			//dbCon.closeConnection(connection
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			cout<<"update info failed";
		}
	}

	//查询数据   返回对象    外面的是对象  里面的是对象的属性
	
	vector<vector<string>> DataBase::getObjectInfo(string queryString,string tableName,int tableRowCount){
		GetDBConnTool dbCon;
		DBConnect* dbconnection;
		_ConnectionPtr connection;
		_RecordsetPtr recordSet;
		try {
			//返回数据
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnGuard::GetAConnect();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));;
			vector<vector<string>> stringObjectSet;
			sqlString = queryString.c_str();
			int rowCount = tableRowCount;
				//获得表的列数
				//int rowCount = getRowCount(T object);
				// 取得表中的记录
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
	
				//string stringObject[rowCount];
				//int counter= 0;
				while(!recordSet->EndOfFile)
				{
					int i =0;
					//记得更改  此处知道为4
					//int rowCount = 4;
					
					vector<string> stringObject;
					//判断是否非空，非空则清零
					if(!stringObject.empty())
						stringObject.clear();
					/*
					//取出表中的各个列，准备组装对象
					for(;i++;i<rowCount) {
						vTmp = myRecordset->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
						var.ChangeType(VT_BSTR, NULL); 
						stringObject[i] = var; 
					}
					//封装成对象
					*/
					for(;i<rowCount;i++) {
						vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
						string tmp;
						if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
							tmp = (_bstr_t)"";
						} else {
							tmp = (_bstr_t)vTmp;
						}
						stringObject.push_back(tmp); 
					}
					//
					stringObjectSet.push_back(stringObject);
					recordSet->MoveNext(); ///移到下一条记录
				}
		//	}
			
			//dbCon.closeRecordSet(recordSet);
			//dbCon.closeConnection(connection);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			return stringObjectSet;
		} catch(_com_error e) {
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//dbCon.closeConnection(connection);
			cout<<"get objectinfo   failed "<<endl;
			cout<<e.Description()<<endl;
			//return NULL;
		}
	}	

	//获得表的列数
	
	int DataBase::getRowCount(string tableName) {
		DBConnect* dbconnection;
		GetDBConnTool dbCon;
		_ConnectionPtr connection;
		_RecordsetPtr recordSet;
		try {
			dbconnection = DBConnGuard::GetAConnect();
			connection = dbconnection->_connection_ptr;
			//dbCon.getMyConnection(connection);
			recordSet.CreateInstance(__uuidof(Recordset));
			int rowCount = 0;
			string sqlString="select count(a.name) as counta from syscolumns a where a.id =object_id('";
			sqlString.append(tableName);
			sqlString.append("');");
			//cout<<"sql string is "<<sqlString<<endl;
			
			recordSet->Open(sqlString.c_str(),connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp = recordSet->GetCollect(_variant_t((long)0));
			rowCount=(int)vTmp;
			//cout<<"row count: "<<rowCount<<endl;
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//dbCon.closeConnection(connection);
			return rowCount;
		} catch(_com_error e) {
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//dbCon.closeConnection(connection);
			cout<<"getrowcount  failed "<<endl;
			cout<<e.Description()<<endl;
			return NULL;
		}
	}
	
	/*
	//将数据进行组装成对应的对象
	template <typename K>
	K combineObject(vector<string> info,K object) {
		//根据object的类型，将vector的数据提出来（需要考虑到数据表中属性的顺序），进行组装
		 K realObject;
		 //判断object类型   switch case语句
		 //进行组包
		 return realObject;
	}
	*/

	/*
	string DataBase::createQuerySql(string tableName) {
		string info = "select * from ";
		info.append(tableName);
		info.append(";");
		return info;
	}
	*/
	/*
	void main() {
		DBConnGuard::InitDBIterface("127.0.0.1","sa","Linux2539311","MapData",10,20);
		DataBase database;
		database.insertInfo("insert into basestation (BLongtitude) values(1.00);");
		int max = 1;
		printf("haha");
	}
	*/


