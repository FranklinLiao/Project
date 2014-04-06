#pragma once
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
using namespace std;


class Area {
private:
	int id;
	double longtitude;
	double latitude;
	double height;  
	double frequency;
	double aspectAngle;
	double declineAngle;
	double atannaLength;
	int atannaType;
	double transmitPower;
	int baseStationType;
	vector<int> gridId;
public:
	//构造函数
	Area(){};
	//sep用冒号:
	Area(vector<string> param,string sepOut){
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setLongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setFrequency(ChangeTypeTool::stringToDouble(*iter++));
		this->setAspectAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setDeclineAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setAtannaLength(ChangeTypeTool::stringToDouble(*iter++));
		this->setAtannaType(ChangeTypeTool::stringToInt(*iter++));
		this->setTransmitPower(ChangeTypeTool::stringToDouble(*iter++));
		this->setBaseStationType(ChangeTypeTool::stringToInt(*iter++));
		this->setGridId(ChangeTypeTool::stringToIntVector(*iter,sepOut));
	}

	//得到对象
	static Area getOject(vector<string> param,string sepOut);
	static vector<Area> getObjectSet(vector<vector<string>> param,string sepOut);
	
	//set方法
	void setId(int id) {
		this->id = id;
	}

	void setLongtitude(double longtitude) {
		this->longtitude=longtitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}

	void setHeight(double height) {
		this->height = height;
	}

	void setFrequency(double frequency) {
		this->frequency = frequency;
	}

	void setAspectAngle(double aspectAngle) {
		this->aspectAngle=aspectAngle;
	}

	void setDeclineAngle(double declineAngle) {
		this->declineAngle=declineAngle;
	}

	void setAtannaLength(double atannaLength) {
		this->atannaLength=atannaLength;
	}

	void setAtannaType(int atannaType) {
		this->atannaType=atannaType;
	}

	void setTransmitPower(double transmitPower) {
		this->transmitPower = transmitPower;
	}

	void setBaseStationType(int baseStationType) {
		this->baseStationType=baseStationType;
	}

	void setGridId(vector<int> gridId) {
		this->gridId = gridId;
	}

	//get方法
	int getId() {
		return this->id;
	}

	double getLongtitude() {
		return longtitude;
	}

	double getLatitude() {
		return this->latitude;
	}
	
	double getHeight() {
		return this->height;
	}
	
	double getFrequency() {
		return this->frequency;
	}

	double getAspectAngle() {
		return this->aspectAngle;
	}

	double getDeclineAngle() {
		return this->declineAngle;
	}

	double getAtannaLength() {
		return this->atannaLength;
	}

	int getAtannaType() {
		return this->atannaType;
	}

	double getTransmitPower() {
		return this->transmitPower;
	}

	int getBaseStationType() {
		return this->baseStationType;
	}
	
	vector<int> getGridId() {
		return this->gridId;
	}	
};
