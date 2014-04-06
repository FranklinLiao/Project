// Test4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test4.h"

/*
void main()  {
	DWORD startTime = GetTickCount();
	MainFunction mf;
	mf.mainFunction();
	cout<<"haha"<<endl;
	DWORD endTime = GetTickCount();
	cout<<"time last :"<<endTime-startTime<<endl;
}
*/

void main() {
	DBConnGuard::InitDBIterface("127.0.0.1","sa","Linux2539311","MapData",10,20);
	DWORD startTime = GetTickCount();
	MainFunction mf;
	mf.mainFunction();
	cout<<"haha"<<endl;
	DBConnPool::Instanse()->DestroyAllDBConnections();
	DWORD endTime = GetTickCount();
	cout<<"time last :"<<endTime-startTime<<endl;	
}

void testStrSplit() {
	
	vector<string> haha = ChangeTypeTool::strSplit(";123;12;",";");
	int c= 0;
	
}

void test() {
	DataBase database;
	string tableName = "Building";
	//string tableName = "Grid";
	string sepOut=";";
	string sepIn = ":";
	vector<vector<string>> stringInfo;
	//string stringSql = database.createQuerySql(tableName);

	// tableName    (productNum,productName,productSale,productBank) values(1,'诺基亚N97','4499','12')
	/*
	//插入
	string sqlStringInfo = "(GId,GLongtitude,GLatitude,GFieldStrength,GFieldRealStrength) values(2,110.13232,36.112,'1:13.02;2:13.2','1:13')";
	string sqlString = CreateSqlTool::createInsertSql(tableName,sqlStringInfo);
	*/

	/*
	//更新   //tableName   sendstatus = 1 WHERE teacherid=1001
	string sqlStringInfo = "GLongtitude=123.113 where GId = 1";
	string sqlString = CreateSqlTool::createUpdateSql(tableName,sqlStringInfo);
	*/


	//查询   //table     id = 1
	string sqlStringInfo = "BId = 1";
	string sqlString = CreateSqlTool::createQuerySql(tableName,sqlStringInfo);
	/*
	database.getConnection();
	database.insertInfo(sqlString);
	database.closeConnection();
	*/
	
//	database.getConnection();
	int rowCount = database.getRowCount(tableName);
	stringInfo = database.getObjectInfo(sqlString,tableName,rowCount);
//	database.closeConnection();
	
	//vector<Area> areaSet = Area::getObjectSet(stringInfo);
	//vector<BaseStation> baseStationSet = BaseStation::getObjectSet(stringInfo);
	//vector<Building> buildingSet = Building::getObjectSet(stringInfo);
	//vector<BuildingMaterial> buildingMaterialSet = BuildingMaterial::getObjectSet(stringInfo);
	//vector<BuildingPoint> buildingPointSet = BuildingPoint::getObjectSet(stringInfo);
	//vector<Grid> gridSet = Grid::getObjectSet(stringInfo,sep);
	vector<Building> buildingSet = Building::getObjectSet(stringInfo,sepOut,sepIn);
	int k = 1;
	/*
	//打印出数据
	vector<vector<string>>::iterator iterOut = stringInfo.begin();
	for(;iterOut != stringInfo.end();iterOut++) {
		cout<<"object:"<<"  ";
		//cout<<"iterOut： "<<iterOut.<<endl;
		
		vector<string>::iterator iterIn = iterOut->begin();
		int i = 0;
		
		for(;iterIn != iterOut->end();iterIn++)  {
		//	cout<<"iterIn"<<endl;
			cout<<*iterIn<<" ";
		}
		
	
		cout<<endl;
	}
	*/
	

	//打印出东西
	/*
	cout<<"split data"<<endl;
	vector<vector<string>>::iterator iterOut = stringInfo.begin();
	for(;iterOut != stringInfo.end();iterOut++) {
		cout<<"object:"<<"  ";
		//cout<<"iterOut： "<<iterOut.<<endl;
		
		vector<string>::iterator iterIn = iterOut->begin();
		int i = 0;
		
		int id = ChangeTypeTool::stringToInt(*iterIn++);
		cout<<"id : "<<id<<"  ";
		string info = *iterIn;
		vector<int> gridId=ChangeTypeTool::stringToIntVector(*iterIn);
		vector<int>::iterator iter = gridId.begin();
		while(iter != gridId.end()) {
			cout<<*(iter++)<<" ";
		}
		cout<<endl;
	}
	*/


}


void calculate() {
	

	/*
	string tableName = "BaseStation";
	string sqlInfo = " where BId = 1 ";
	string sqlString = CreateSqlTool::createQuerySql(tableName,sqlInfo);
	DataBase db;
	db.getConnection();
	int rowCount = db.getRowCount(tableName);
	vector<BaseStation> bsSet = BaseStation::getObjectSet(db.getObjectInfo(sqlString,tableName,rowCount));
	
	vector<BaseStation>::iterator iter = bsSet.begin();
	while(iter!=bsSet.end()) {
		BaseStation bs = *iter++;
		Point baseStationPoint(bs.getLongtitude(),bs.getLatitude());

		tableName =  "Grid";
		sqlInfo = " ";
		sqlString = CreateSqlTool::createQuerySql(tableName,sqlInfo);
		rowCount = db.getRowCount(tableName);
		vector<Grid> gridSet = Grid::getObjectSet(db.getObjectInfo(
	sqlString,tableName,rowCount));
		vector<Grid>::iterator iterGrid = gridSet.begin();
		while(iterGrid != gridSet.end()) {
			Grid grid = *iterGrid++;
			Point recevier(grid.getLongtitude(),grid.getLatitude());
			double power = CalculateTool::getPower(baseStationPoint,recevier);

		}

	}


	db.closeConnection();
	*/

	//先把一个网格的所有基站跑完，再遍历网格
	double powerStrength=300;
	double descRate=9.5;
	string tableName =  "Grid";
	string sepOut=";";
	string sepIn = ":";
	string sqlInfo = " ";
	string sqlString = CreateSqlTool::createQuerySql(tableName,sqlInfo);
	DataBase db;
//	db.getConnection();
	int rowCount = db.getRowCount(tableName);
	vector<Grid> gridSet = Grid::getObjectSet(db.getObjectInfo(
		sqlString,tableName,rowCount),sepOut,sepIn);
	vector<Grid>::iterator iterGrid = gridSet.begin();
	while(iterGrid != gridSet.end()) {
		Grid grid = *iterGrid++;
		Point recevier(grid.getLongtitude(),grid.getLatitude());

		tableName =  "BaseStation";
		sqlInfo = " where BId = 1 ";
		sqlString = CreateSqlTool::createQuerySql(tableName,sqlInfo);
		rowCount = db.getRowCount(tableName);
		vector<BaseStation> bsSet = BaseStation::getObjectSet(db.getObjectInfo(sqlString,tableName,rowCount),sepOut);
		vector<BaseStation>::iterator iter = bsSet.begin();
		string powerString = "";
		while(iter!=bsSet.end()) {
			BaseStation bs = *iter++;
			Point baseStationPoint(bs.getLongtitude(),bs.getLatitude());
			//构造计算对象
			CalculateTool calculate(powerStrength,descRate);
			double power = calculate.getPower(baseStationPoint,recevier);
			//string tmp = bs.getId()+":"＋power;
			powerString.append(ChangeTypeTool::intToString(bs.getId()));
			powerString.append(":");
			powerString.append(ChangeTypeTool::doubleToString(power));
			powerString.append(";");
		}
		//把对应的数据插入到数据库中
		//tableName   sendstatus = 1 WHERE teacherid=1001
		tableName = "Grid";
		sqlInfo = "GFieldStrength = ";
		sqlInfo.append(powerString);
		sqlInfo.append(" where GId = ");
		sqlInfo.append(ChangeTypeTool::intToString(grid.getId()));
		sqlInfo.append(";");
		sqlString = CreateSqlTool::createUpdateSql(tableName,sqlInfo);
		db.updateInfo(sqlString);
	}

	//db.closeConnection();
	
}

