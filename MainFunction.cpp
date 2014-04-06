#include "stdafx.h"
#include "MainFunction.h"

void MainFunction::mainFunction() {
	double powerStrength = 300;
	double descRate = 9.5;
	vector<Area>::iterator iterArea = areaSet.begin();
	while(iterArea != areaSet.end()) {

		Area area = *iterArea++;
		//update Building set BGridId+='3:4' where BId = 1;
		//创建起始点
		Point startPoint(area.getLongtitude(),area.getLatitude());
		vector<Grid>::iterator iterGrid = gridSet.begin();
		while(iterGrid != gridSet.end()) {
			string tableName = "Grid";
			Grid grid = *iterGrid++;
			Point endPoint(grid.getLongtitude(),grid.getLatitude());
			CalculateTool calculate(powerStrength,descRate);
			//CalculateTool calculate;
			double power = calculate.getPower(startPoint,endPoint);
			//将数据放入到数据库中
			string stringInfo = " GFieldStrength+='";
			int areaId=area.getId();
			stringInfo.append(ChangeTypeTool::intToString(area.getId()));
			stringInfo.append(",");
			stringInfo.append(ChangeTypeTool::doubleToString(area.getFrequency()));
			stringInfo.append(":");
			stringInfo.append(ChangeTypeTool::doubleToString(power));
			stringInfo.append(";' ");
			stringInfo.append("where GId = ");
			stringInfo.append(ChangeTypeTool::intToString(grid.getId()));
			string sqlString = CreateSqlTool::createUpdateSql(tableName,stringInfo);
			DataBase database;
		//	database.getConnection();
			database.updateInfo(sqlString);
		//	database.closeConnection();
		}
		int id = 0;
		cout<<id++;
	}
	cout<<"program end!"<<endl;
}
