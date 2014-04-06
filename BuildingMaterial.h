#pragma once
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
using namespace std;


class BuildingMaterial {
private:
	int id;
	double dielectricConstant;
	double conductivity;

public:
	//���췽��
	BuildingMaterial(){};
	BuildingMaterial(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setDielectricConstant(ChangeTypeTool::stringToDouble(*iter++));
		this->setConductivity(ChangeTypeTool::stringToDouble(*iter));
	}
		
	//��ö���
	static BuildingMaterial getObject(vector<string> param);
	static vector<BuildingMaterial> BuildingMaterial::getObjectSet(vector<vector<string>> param);
	//set����
	void setId(int id) {
		this->id = id;
	}

	void setDielectricConstant(double dielectricConstant) {
		this->dielectricConstant = dielectricConstant;
	}

	void setConductivity(double conductivity) {
		this->conductivity = conductivity;
	}

	//get����
	int getid() {
		return this->id;
	}
	
	double getDielectricConstant() {
		return this->dielectricConstant;
	}

	double getConductivity() {
		return this->conductivity;
	}
};