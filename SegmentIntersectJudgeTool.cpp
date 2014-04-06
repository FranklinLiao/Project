#include "stdafx.h"
#include "SegmentIntersectJudgeTool.h"



double SegmentIntersectJudgeTool::maxer(double a,double b) {
	return a>b?a:b;
}

double SegmentIntersectJudgeTool::miner(double a,double b) {
	return a>b?b:a;
}


double SegmentIntersectJudgeTool::multiply(Point sp,Point ep,Point op) {
	return (op.getX()-sp.getX())*(ep.getY()-sp.getY())-(ep.getX()-sp.getX())*(op.getY()-sp.getY());
}


 //1.保证共线  2.保证在线段中间，不会在延长线上
bool SegmentIntersectJudgeTool::online(Lineseg line,Point p) {
	return (multiply(line.getEndPoint(),p,line.getStartPoint())==0) &&   
		(((p.getX()-line.getStartPoint().getX())*(p.getX()-line.getEndPoint().getX())<=0) &&
		((p.getY()-line.getStartPoint().getY())*(p.getY()-line.getEndPoint().getY())<=0));   
}



bool SegmentIntersectJudgeTool::intersect(Lineseg u,Lineseg v) {
	return ((maxer(u.getStartPoint().getX(),u.getEndPoint().getX())>=miner(v.getStartPoint().getX(),v.getEndPoint().getX())) && (maxer(v.getStartPoint().getX(),v.getEndPoint().getX())>=miner(u.getStartPoint().getX(),u.getEndPoint().getX())) &&
		   (maxer(u.getStartPoint().getY(),u.getEndPoint().getY())>=miner(v.getStartPoint().getY(),v.getEndPoint().getY())) && (maxer(v.getStartPoint().getY(),v.getEndPoint().getY())>=miner(u.getStartPoint().getY(),u.getEndPoint().getY())) &&
		   (multiply(u.getStartPoint(),u.getEndPoint(),v.getStartPoint())*multiply(u.getStartPoint(),u.getEndPoint(),v.getEndPoint())<=0) && 
		   (multiply(v.getStartPoint(),v.getEndPoint(),u.getStartPoint())*multiply(v.getStartPoint(),v.getEndPoint(),u.getEndPoint())<=0));
}


