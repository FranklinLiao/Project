#pragma once
#include "stdafx.h"
#include "CalculateTool.h"
#include "Area.h"
#include "CalculateTool.h"
#include "Grid.h"
#include "DataBase.h"
#include "DBConnPool.h"
#include <vector>
#include <string>
using namespace std;

class MainFunction{
private:
	vector<Area> areaSet;
	vector<Grid> gridSet;
public:
	MainFunction() {
		
		DataBase database;
		//database.getConnection();

		/*
		DBConnGuard::InitDBIterface("127.0.0.1","sa","Linux2539311","MapData",10,20);
		DBConnect* dbconnection = DBConnGuard::GetAConnect();
		*/

		string sepOut=";";
		string sepIn = ":";
		string sqlStringArea = "select * from area where AId = 1;";
		//string sqlStringGrid = "select * from grid where gid < 3;";
		string sqlStringGrid = "select * from grid where GId < 11;";
		string areaTable = "area";
		string gridTable = "grid";



		/*
		int areaRowCount=database.getRowCount(areaTable);
		int gridRowCount=database.getRowCount(gridTable);
		this->setAreaSet(Area::getObjectSet(database.getObjectInfo(sqlStringArea,areaTable,areaRowCount),sepOut));
		this->setGridSet(Grid::getObjectSet(database.getObjectInfo(sqlStringGrid,gridTable,gridRowCount),sepOut,sepIn));
		*/

		int areaRowCount=database.getRowCount(areaTable);
		int gridRowCount=database.getRowCount(gridTable);
		this->setAreaSet(Area::getObjectSet(database.getObjectInfo(sqlStringArea,areaTable,areaRowCount),sepOut));
		this->setGridSet(Grid::getObjectSet(database.getObjectInfo(sqlStringGrid,gridTable,gridRowCount),sepOut,sepIn));
		//database.closeConnection();
	}
	//get
	vector<Area> getAreaSet() {
		return this->areaSet;
	}

	vector<Grid> getGridSet() {
		return this->gridSet;
	}
	//set
	void setAreaSet(vector<Area> areaSet) {
		this->areaSet=areaSet;
	}

	void setGridSet(vector<Grid> gridSet) {
		this->gridSet=gridSet;
	}
	void mainFunction();
};

