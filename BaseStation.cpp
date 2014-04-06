#include "stdafx.h"
#include "BaseStation.h"

BaseStation BaseStation::getObject(vector<string> param,string sepOut) {
	BaseStation baseStation = BaseStation(param,sepOut);
	return baseStation;
}


vector<BaseStation> BaseStation::getObjectSet(vector<vector<string>> param,string sepOut) {
	vector<BaseStation> baseStationSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		BaseStation baseStation = BaseStation::getObject(*iter++,sepOut);
		baseStationSet.push_back(baseStation);
	}
	return baseStationSet;
}


