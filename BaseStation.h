// TestClass.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
using namespace std;

class BaseStation {
private :
	int id;
	double longtitude;
	double latitude;
	//double height;     //高度给了天线了
	int gridId;
	int areaId;
	vector<int> atennaId;
	double transmitPower;
public :
	//构造方法
	BaseStation(){};
	BaseStation(vector<string> param,string sepOut) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setLongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		//this->setHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setGridId(ChangeTypeTool::stringToInt(*iter++));
		this->setAreaId(ChangeTypeTool::stringToInt(*iter++));
		this->setAtennaId(ChangeTypeTool::stringToIntVector(*iter++,sepOut));
		this->setTransmitPower(ChangeTypeTool::stringToDouble(*iter++));
	}

	//得到对象
	static BaseStation getObject(vector<string> param,string sepOut);
	static vector<BaseStation> BaseStation::getObjectSet(vector<vector<string>> param,string sepOut);
	//set方法
	void setId(int id) {
		this->id=id;
	}

	void setLongtitude(double longtitude) {
		this->longtitude=longtitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}

	/*
	void setHeight(double height) {
		this->height = height;
	}
	*/
	void setGridId(int gridId) {
		this->gridId = gridId;
	}

	void setAreaId(int areaId) {
		this->areaId = areaId;
	}

	void setAtennaId(vector<int> atennaId) {
		this->atennaId = atennaId;
	}

	void setTransmitPower(double transmitPower) {
		this->transmitPower = transmitPower;
	}

	//get方法
	int getId() {
		return id;
	}
	double getLongtitude() {
		return longtitude;
	}

	double getLatitude() {
		return latitude;
	}
	/*
	double getHeight() {
		return height;
	}
	*/
	int getGridId() {
		return gridId;
	}
	
	int getAreaId() {
		return areaId;
	}

	vector<int> getAtennaId() {
		return atennaId;
	}

	double getTransmitPower() {
		return transmitPower;
	}

};

