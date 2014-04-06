#include "stdafx.h"
#include "CalculateTool.h"

double CalculateTool::getPower(Point baseStation,Point receiver) {
	double power;
	int count = getCount(baseStation,receiver);
	power = powerStrength - count*descRate;
	return power;
}
int CalculateTool::getCount(Point baseStation,Point receiver){
	string sepOut=";";
	string tableName = "BuildingPoint";
	string sqlInfo = "";
	string sqlString = CreateSqlTool::createQuerySql(tableName,sqlInfo);
	DataBase database;
//	database.getConnection();
	//1.�����ݿ���ȡ�����н������۵�(����˳��Ļ���
	int rowCount = database.getRowCount(tableName);
	vector<BuildingPoint> buildingPointSet = BuildingPoint::getObjectSet(database.getObjectInfo (sqlString,tableName,rowCount),sepOut);
//	database.closeConnection();
	
	if(!buildingPointSet.empty()) {
		//2.
		vector<BuildingPoint>::iterator iter = buildingPointSet.begin();
	
		BuildingPoint  firstPoint = *iter;
		int count = 0;
		BuildingPoint startBuildingPoint;
		BuildingPoint endBuildingPoint;
		SegmentIntersectJudgeTool sijt;
		while(iter != buildingPointSet.end()) {
			//ÿ��ȡ��������м���
			startBuildingPoint = *iter++;
			//������㵽���һ����ʱ��  ��Ҫȡ���һ���͵�һ��
			if(iter != buildingPointSet.end()) {
				 endBuildingPoint = *iter;
			}
			else { 
				break;
			}

			Point startPoint(startBuildingPoint.getLongtitude(),startBuildingPoint.getLatitude());
			Point endPoint(endBuildingPoint.getLongtitude(),endBuildingPoint.getLatitude());
			Lineseg u(baseStation,receiver);
			Lineseg v(startPoint,endPoint);
			bool flag = sijt.intersect(u,v);
			if(flag) 
				count++;
		}
		Point startPoint(firstPoint.getLongtitude(),startBuildingPoint.getLatitude());
		Point endPoint(startBuildingPoint.getLongtitude(),endBuildingPoint.getLatitude());
		Lineseg u(baseStation,receiver);
		Lineseg v(startPoint,endPoint);
		bool flag = sijt.intersect(u,v);
		if(flag) 
			count++;
		return count;
	} else {
		return 0;
	}
}

/*
void main() {
	Point startPoint(116.366616,39.882788);
	Point endPoint(116.366791,39.882698);
	CalculateTool  calc(300,9.5);
	double p = calc.getPower(startPoint,endPoint);
	cout<<"power : "<<p<<endl;
}
*/