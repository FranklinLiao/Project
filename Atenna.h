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
	bool polarization; //0:ˮƽ����    1����ֱ����
	double areaRadius;
	double machineAngle;
	double electricAngle;
	double horizonAngle;
	int baseStationId;
	double vswr;//פ����
	double feedImpedence;//�����迹
public:
	//���캯����ʵ�ַ���һ������   �����������
	Atenna() {};
	Atenna(vector<string> param) {
		vector<string>::iterator iter =  param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		
	}

	

	Atenna getObject(vector<string> param);
	//set����
	void setId(int id) {
		this->id = id;
	}

	void setFrequency(double frequency) {
		this->frequency = frequency;
	}

	void setFrontToBackRatio() {

	}
	/* ʣ���set����
	*************
	*/

	/*
	//get����
	int getId() {
		return id;
	}
	/* ʣ���get����
	**************
	*/

	//��������
//};
