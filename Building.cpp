#include "stdafx.h"
#include "Building.h"

Building Building::getObject(vector<string> param,string sepOut,string sepIn) {
	Building building = Building(param,sepOut,sepIn);
	return building;
}

vector<Building> Building::getObjectSet(vector<vector<string>> param,string sepOut,string sepIn) {
	vector<Building> buildingSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Building building = Building::getObject(*iter++,sepOut,sepIn);
		buildingSet.push_back(building);
	}
	return buildingSet;
}