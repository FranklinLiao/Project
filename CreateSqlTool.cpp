#include  "stdafx.h"
#include "CreateSqlTool.h"

string CreateSqlTool::createInsertSql(string tableName,string sqlInfo) {
	string sqlString = "insert into ";
	sqlString.append(tableName);
	sqlString.append(" ");
	sqlString.append(sqlInfo);
	sqlString.append(";");
	return sqlString;
}

string  CreateSqlTool::createUpdateSql(string tableName,string sqlInfo) {
	string sqlString = "update ";
	sqlString.append(tableName);
	sqlString.append(" set ");
	sqlString.append(sqlInfo);
	sqlString.append(";");
	return sqlString;
}


string  CreateSqlTool::createQuerySql(string tableName,string sqlInfo) {
	string sqlString = "select * from ";
	sqlString.append(tableName);
	sqlString.append(" ");
	sqlString.append(sqlInfo);
	sqlString.append(";");
	return sqlString;
}


string CreateSqlTool::getString(int count,...) {
	string info;
	va_list pArg;
	va_start(pArg,count);
	while(count--) {
		char* tmp = va_arg(pArg,char *);
		info.append(tmp);
	}
	va_end(pArg);
	return info;
}