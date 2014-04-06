#pragma once
#include "stdafx.h"
#include "SegmentIntersectJudgeTool.h"
#include "BuildingPoint.h"
#include "DataBase.h"
#include "CreateSqlTool.h"
#include <vector>
using namespace std;

class CalculateTool {
private:
	 double powerStrength;
	 double descRate;
public:
	
	CalculateTool(double powerStrength,double descRate) {
		this->powerStrength=powerStrength;
		this->descRate=descRate;
	}
	
	
	double getPower(Point baseStation,Point receiver);
	int getCount(Point baseStation,Point receiver);
};
