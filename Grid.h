#pragma once
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <map>
using namespace std;
class Grid {
private:
	int id;
	double longtitude;
	double latitude;

	//vector<int> baseStationId;
	//vector<int> buildingPointId; //由于使用vector，所以不需要指定vector的大小
	int areaId;  //最强的那个小区的编号 
	vector<map<string,double>> fieldStrength;  //
	//double fieldRealStength;
	map<int,double> fieldRealStrength;
	//int flag;
public:
	//构造函数
	Grid(){};
	
	Grid(vector<string> param,string sepOut,string sepIn) {
		vector<string>::iterator iter = param.begin();
		//if(*iter!="")  {
			this->setId(ChangeTypeTool::stringToInt(*iter++));
		//} 
		//if(*iter!="") {
			this->setLongtitude(ChangeTypeTool::stringToDouble(*iter++));
		//}
		//if(*iter!="") {
			this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		//}
		//if(*iter!="") {
		//	this->setBuildingPointId(ChangeTypeTool::stringToIntVector(*iter++,sepOut));
		//}
		//if(*iter!="") {
			this->setAreaId(ChangeTypeTool::stringToInt(*iter++));
		//}
		//this->setBaseStationId(ChangeTypeTool::stringToIntVector(*iter++));
		//if(*iter!="") {
			this->setFieldStrength(ChangeTypeTool::stringToStringMapVector(*iter++,sepOut,sepIn));
		//}
		//if(*iter!="") {
			this->setFieldRealStrength(ChangeTypeTool::stringToIntMap(*iter,sepIn));
		//}
		//this->setFlag(ChangeTypeTool::stringToInt(*iter++));
		//this->setFieldStrength(ChangeTypeTool::stringToStringVector(ChangeTypeTool::stringToMap(*iter++,d)));
	}
	
	
	//获得对象
	static Grid getObject(vector<string> param,string sepOut,string sepIn);
	//static Grid getObject(vector<string> param);
	static vector<Grid> getObjectSet(vector<vector<string>> param,string sepOut,string sepIn);
	//set方法
	void setId(int id) {
		this->id = id;
	}

	void setLongtitude(double longtitude) {
		this->longtitude = longtitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}
	/*
	void setBaseStationId(vector<int> baseStation) {
		this->baseStationId = baseStation;
	}
	*/
	/*
	void setBuildingPointId(vector<int> buildingPointId) {
		this->buildingPointId = buildingPointId;
	}
	*/
	void setAreaId(int areaId) {
		this->areaId=areaId;
	}

	void setFieldStrength(vector<map<string,double>> fieldStrength) {
		this->fieldStrength = fieldStrength;
	}

	void setFieldRealStrength(map<int,double>  fieldRealStrength) {
		this->fieldRealStrength = fieldRealStrength;
	}
	/*
	void setFlag(int flag) {
		this->flag = flag;
	}
	*/
	//get方法
	int getId() {
		return this->id;
	}
	double getLongtitude() {
		return this->longtitude;
	}

	double getLatitude() {
		return this->latitude;
	}
	/*
	vector<int> getBaseStationId() {
		return this->baseStationId;
	}
	
	vector<int> getBuildingPointId() {
		return this->buildingPointId;
	}
	*/

	int getAreaId() {
		return this->areaId;
	}

	vector<map<string,double>> getFieldStrength() {
		return this->fieldStrength;
	}

	 map<int,double> getFieldRealStrength() {
		return this->fieldRealStrength;
	}
	/*
	int getFlag() {
		return this->flag;
	}
	*/
};