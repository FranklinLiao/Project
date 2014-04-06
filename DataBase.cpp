#include "stdafx.h"
#include "DataBase.h"


	//��������
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

	//��������
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

	//��ѯ����   ���ض���    ������Ƕ���  ������Ƕ��������
	
	vector<vector<string>> DataBase::getObjectInfo(string queryString,string tableName,int tableRowCount){
		GetDBConnTool dbCon;
		DBConnect* dbconnection;
		_ConnectionPtr connection;
		_RecordsetPtr recordSet;
		try {
			//��������
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnGuard::GetAConnect();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));;
			vector<vector<string>> stringObjectSet;
			sqlString = queryString.c_str();
			int rowCount = tableRowCount;
				//��ñ������
				//int rowCount = getRowCount(T object);
				// ȡ�ñ��еļ�¼
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
	
				//string stringObject[rowCount];
				//int counter= 0;
				while(!recordSet->EndOfFile)
				{
					int i =0;
					//�ǵø���  �˴�֪��Ϊ4
					//int rowCount = 4;
					
					vector<string> stringObject;
					//�ж��Ƿ�ǿգ��ǿ�������
					if(!stringObject.empty())
						stringObject.clear();
					/*
					//ȡ�����еĸ����У�׼����װ����
					for(;i++;i<rowCount) {
						vTmp = myRecordset->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
						var.ChangeType(VT_BSTR, NULL); 
						stringObject[i] = var; 
					}
					//��װ�ɶ���
					*/
					for(;i<rowCount;i++) {
						vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
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
					recordSet->MoveNext(); ///�Ƶ���һ����¼
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

	//��ñ������
	
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
	//�����ݽ�����װ�ɶ�Ӧ�Ķ���
	template <typename K>
	K combineObject(vector<string> info,K object) {
		//����object�����ͣ���vector���������������Ҫ���ǵ����ݱ������Ե�˳�򣩣�������װ
		 K realObject;
		 //�ж�object����   switch case���
		 //�������
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


