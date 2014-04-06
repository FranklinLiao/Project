#pragma once
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <iterator>
#include <string>
using namespace std;
class Source{
private :
	double longtitude;
	double latitude;
public:
	//构造方法
	Source(double lontitude,double latitude) {
		this->setLongtitude(lontitude);
		this->setLatitude(latitude);
	}

	Source(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setLongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		/*
		//this->setHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setGridId(ChangeTypeTool::stringToInt(*iter++));
		this->setAreaId(ChangeTypeTool::stringToInt(*iter++));
		this->setAtennaId(ChangeTypeTool::stringToIntVector(*iter++));
		this->setTransmitPower(ChangeTypeTool::stringToDouble(*iter++));
		*/
	}

	//set方法
	void setLongtitude(double longtitude) {
		this->longtitude=longtitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}

	//get方法
	double getLongtitude() {
		return longtitude;
	}

	double getLatitude() {
		return latitude;
	}
};