#include "stdafx.h"
#include "Grid.h"

/*
Grid Grid::getObject(vector<string> param,const char *d) {
	Grid grid = Grid(param,d);
	return grid;
}
*/
Grid Grid::getObject(vector<string> param,string sepOut,string sepIn) {
	Grid grid = Grid(param,sepOut,sepIn);
	return grid;
}

vector<Grid> Grid::getObjectSet(vector<vector<string>> param,string sepOut,string sepIn) {
	vector<Grid> gridSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Grid grid = Grid::getObject(*iter++,sepOut,sepIn);
		gridSet.push_back(grid);
	}
	return gridSet;
}
