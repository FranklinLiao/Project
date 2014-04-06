#pragma once
#include "stdafx.h"
//#define  max(a,b){a>b?a;b}
//#define  min(a,b){a>b?b;a}
class Point {
private: 
	double x;
	double y;
public:
	Point(){}

	Point(double x,double y) {
		this->x = x;
		this->y = y;
	}
	double getX() {
		return this->x;
	}
	double getY() {
		return this->y;
	}
};

class Lineseg {
private: 
	Point s;
	Point e;
public:
	Lineseg(Point s,Point e) {
		this->s = s;
		this->e = e;
	}
	Point getStartPoint() {
		return this->s;
	}
	Point getEndPoint() {
		return this->e;
	}
};


class SegmentIntersectJudgeTool {
public:
	double maxer(double d1,double d2);
	double miner(double d1,double d2);
	double multiply(Point sp,Point ep,Point op);
	bool online(Lineseg line,Point p);
    bool intersect(Lineseg u,Lineseg v);
};