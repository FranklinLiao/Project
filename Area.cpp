#include "stdafx.h"
#include "Area.h"

Area Area::getOject(vector<string> param,string sepOut) {
	Area area = Area(param,sepOut);
	return area;
}

vector<Area> Area::getObjectSet(vector<vector<string>> param,string sepOut) {
	vector<Area> AreaSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Area area = Area::getOject(*iter++,sepOut);
		AreaSet.push_back(area);
	}
	return AreaSet;
}