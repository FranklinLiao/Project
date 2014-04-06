#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;
/*
class Atenna {
private :
	int id;
	double frequency;
	double frontToBackRatio;
	double beamWidth;
	bool polarization; //0:水平极化    1：垂直极化
	double areaRadius;
	double machineAngle;
	double electricAngle;
	double horizonAngle;
	int baseStationId;
	double vswr;//驻波比
	double feedImpedence;//输入阻抗
public:
	//构造函数，实现返回一个对象   传入各个参数
	Atenna() {};
	Atenna(vector<string> param) {
		vector<string>::iterator iter =  param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		
	}

	

	Atenna getObject(vector<string> param);
	//set方法
	void setId(int id) {
		this->id = id;
	}

	void setFrequency(double frequency) {
		this->frequency = frequency;
	}

	void setFrontToBackRatio() {

	}
	/* 剩余的set方法
	*************
	*/

	/*
	//get方法
	int getId() {
		return id;
	}
	/* 剩余的get方法
	**************
	*/

	//其他方法
//};
