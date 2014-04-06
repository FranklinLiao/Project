// DBConnPool.cpp: implementation of the DBConnPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBConnPool.h"
#include <iostream>
using namespace std;

DBConnect * pDBConn = NULL;
//////////////////////////////////////DBGuard////////////////////////
void DBConnGuard::InitDBIterface(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,int minConn,int maxConn)
{
	DBConnPool::Instanse()->SetDBInfo(strDstAddress,strUsername,strPassword,strDBName,minConn,maxConn);
	int cout = DBConnPool::Instanse()->InitializeAllDBConnections();
}
DBConnect * DBConnGuard::GetAConnect()
{
	DBConnGuard oConnGuard(pDBConn);
	return pDBConn;
}
//////////////////////////////////////DBConnect/////////////////////////
DBConnect::DBConnect(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,BOOL &state)
{
   m_bDBOpen = false;
   if (0 == Open(strDstAddress,strUsername,strPassword,strDBName))
   {
        state =true;
   }
   else
   {
	   state = false;
   }
}
DBConnect::~DBConnect()
{
   Close();
}
int DBConnect::Open(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName)
{
	_strDstAddress = strDstAddress;
	_strDBName       = strDBName;
	_strUsername     = strUsername;
	_strPassword     = strPassword;
	
	HRESULT comhr = ::CoInitialize(NULL);
	if (FAILED(comhr))
		
	{
		return -1;
	}
	HRESULT hr = _connection_ptr.CreateInstance(__uuidof(Connection));
	
	if (FAILED(hr))
	{
		return -1;
	}
	
	char szSQL[SQL_BUFFER_LEN] = {0};
	memset(szSQL, 0, SQL_BUFFER_LEN);
	sprintf(szSQL, "Driver=SQL Server;Server=%s;DATABASE=%s", strDstAddress, strDBName);
	
	try
	{
		// 连接到服务器上数据库
		_connection_ptr->Open(szSQL, strUsername, strPassword,adModeUnknown) ;
		if (FAILED(hr))
			return -1;
	}
	catch (_com_error &err)
	{
		//TRACE(_T("数据库操作失败! 错误信息:%s, 文件:%s, 行:%d.\n"), err.ErrorMessage(), __FILE__, __LINE__);
		cout<<"连接数据库失败"<<endl;
		return -1;
	}
	
	m_bDBOpen = TRUE;
	
	return 0;
}
int DBConnect::Close()
{
	if (m_bDBOpen)
	{
		HRESULT hr =_connection_ptr->Close();
		
		if (FAILED(hr))
		{
			return -1;
		}
		::CoUninitialize();
		m_bDBOpen = FALSE;
	}
	
	return 0;
}
/*
int DBConnect::GetSubmitInfo(vector<SOAP_SUBMIT_SMS> &vecsoapSms)
{
	//*此接口为实际访问数据库的接口，和数据库字段相关，数据库为SQLSERVER
	
	if (!m_bDBOpen)
	{
		return -1;
	}
	// 创建Command对象
	_CommandPtr cmd;
	HRESULT hr = cmd.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		return -1;
	}
    string strSql = "exec SP_SMS_GETSUBMIT";
	cmd->ActiveConnection = _connection_ptr;
	cmd->CommandText = _bstr_t(strSql.c_str());
	cmd->CommandType = adCmdText;
	try 
	{
		_RecordsetPtr rs = cmd->Execute(NULL, NULL, adCmdUnknown);
		
		if (FAILED(hr)) 
		{
			return -1;
		}
		while (!rs->ADOEOF)
		{     
			_variant_t		id;
			_variant_t		recverid;
			_variant_t		recvertel;
			_variant_t		messagecontent;
			_variant_t		recverphonetype;
			_variant_t		inout;
			_variant_t		sendtime;
			_variant_t		cardtime;
			_variant_t		schoolid;
			_variant_t		classid;
		    _variant_t		rfidno;
			
			id = rs->GetCollect("id");
			recverid = rs->GetCollect("recverid");
			recvertel = rs->GetCollect("recvertel");
			messagecontent = rs->GetCollect("messagecontent");
			recverphonetype = rs->GetCollect("recverphonetype");
			inout = rs->GetCollect("inout");
			sendtime = rs->GetCollect("sendtime");
			cardtime = rs->GetCollect("cardtime");
			schoolid = rs->GetCollect("schoolid");
			classid = rs->GetCollect("classid");
			rfidno = rs->GetCollect("rfidno");

			SOAP_SUBMIT_SMS submitsms;
			submitsms.id = (int)(long)id;
			VarientToString(recverid, submitsms.recverid);
        	VarientToString(recvertel, submitsms.recvertel);
			VarientToString(messagecontent, submitsms.messagecontent);
            VarientToString(recverphonetype, submitsms.recverphonetype);
			submitsms.inout = (int)(long)inout;
			VarientToString(sendtime, submitsms.sendtime);
			VarientToString(cardtime, submitsms.cardtime);
			VarientToString(rfidno, submitsms.rfidno);
			submitsms.schoolid = (int)(long)schoolid;
			submitsms.classid = (int)(long)classid;
			vecsoapSms.push_back(submitsms);
			rs->MoveNext() ;
		}
	}
	catch (_com_error &err)
	{
		TRACE(_T("数据库操作失败! 错误信息:%s, 文件:%s, 行:%d.\n"), err.ErrorMessage(), __FILE__, __LINE__);
		
		return -1;
	}
	return 0;
}
int DBConnect::InsertHistory(int id)
{
	if (!m_bDBOpen)
	{
		return -1;
	}
	// 创建Command对象
	_CommandPtr cmd;
	HRESULT hr = cmd.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		return -1;
	}
	char szSQL[SQL_BUFFER_LEN] = {0};
	sprintf(szSQL, "exec SP_SMS_SUBMITRESULT %d", id);

	try
	{
		cmd->ActiveConnection = _connection_ptr;
		cmd->CommandText = _bstr_t(szSQL);
		cmd->CommandType = adCmdText;
		cmd->Execute(NULL, NULL, adCmdUnknown);
	}
	catch (_com_error &err)
	{
		TRACE(_T("数据库操作失败! 错误信息:%s, 文件:%s, 行:%d.\n"), err.ErrorMessage(), __FILE__, __LINE__);
		
		return -1;
	}
	return 0;
}
*/


void DBConnect::VarientToString(_variant_t var, string& str)
{
	if (VT_NULL == var.vt)
	{
		str = "";
	}
	else
	{
		str = (char*)_bstr_t(var);
	}
}
//////////////////////////////////////End//////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DBConnPool* DBConnPool::m_pInstanse = NULL;


DBConnPool::DBConnPool()
{
	m_bNeedStop = FALSE;
	m_bNeedConnection = FALSE;
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	
	// 线程控制
	m_hHaveData = CreateEvent (NULL, TRUE, FALSE, _T("DataConnPool"));
	
	
	InitializeCriticalSection(&m_csIdleConnList);
	InitializeCriticalSection(&m_csBusyConnList);

}

void DBConnPool::SetDBInfo(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,int minConn,int maxConn)
{
	_strDBName = strDBName;
	_strDstAddress = strDstAddress;
	_strPassword = strPassword;
	_strUsername = strUsername;
	 m_nMaxCount = maxConn;
	 m_nMinCount = minConn;
}

DBConnPool::~DBConnPool()
{
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	m_bNeedStop = TRUE;
	CloseHandle(m_hHaveData);
	CloseHandle(m_hMaintanceThread);
	
    DeleteCriticalSection(&m_csIdleConnList);
	DeleteCriticalSection(&m_csBusyConnList);
}



DBConnPool *DBConnPool::Instanse()
{
	if (NULL == m_pInstanse)
	{
        m_pInstanse = new DBConnPool();
	}

	return m_pInstanse;
}

int DBConnPool::InitializeAllDBConnections()
{
	// 先摧毁现有的连接
	DestroyAllDBConnections();

	// 开始按照最小数量开始创建
	DBConnect * pDBConnect = NULL;
	int nCount = 0;
	for (int i = 0; i < m_nMinCount; i++)
	{
		nCount = InitializeAConnection();
	}

	// 创建一个工作线程，用来进行一些后台维护工作
	if (INVALID_HANDLE_VALUE == m_hMaintanceThread)
	{
		m_hMaintanceThread = CreateThread(NULL, NULL, thread_run, (LPVOID)this, 0, NULL);
	}

	return nCount;
}

void DBConnPool::DestroyAllDBConnections()
{
	// 销毁数据库连接可以使用大锁
	EnterCriticalSection(&m_csIdleConnList);
	DBConnectList::iterator itIdle = m_listIdleConnection.begin();
	DBConnectList::iterator itIdleEnd = m_listIdleConnection.end();

	if(!m_listIdleConnection.empty()) {
		while (itIdle != itIdleEnd)
		{
			if (NULL != (*itIdle))
			{
				(*itIdle)->Close();
				//delete (*itIdle);
			}
			// erase本身就会把跌代器指向下一个
			itIdle++;
			//itIdle = m_listIdleConnection.erase(itIdle);

		}
		m_listIdleConnection.clear();
	}
	LeaveCriticalSection(&m_csIdleConnList);

	// 还有使用中的连接
	EnterCriticalSection(&m_csBusyConnList);
	DBConnectList::iterator itBusy = m_listBusyConnection.begin();
    DBConnectList::iterator itBusyEnd = m_listBusyConnection.end();

	if(!m_listBusyConnection.empty()) {
		while (itBusy != itBusyEnd)
		{
			if (NULL != (*itBusy))
			{
				(*itBusy)->Close();
				//delete (*itBusy);
			}
			itBusy++;
			// erase本身就会把跌代器指向下一个
			//itBusy = m_listBusyConnection.erase(itBusy);
		}
		m_listBusyConnection.clear();
	}
	

	LeaveCriticalSection(&m_csBusyConnList);
}

int DBConnPool::InitializeAConnection()
{
	BOOL bSuccess = FALSE;
	DBConnect * pDBEngine = new DBConnect(_strDstAddress, _strUsername, _strPassword, _strDBName, bSuccess);
	if (bSuccess)
	{
		m_bNeedConnection = FALSE;
		return RestoreAConnection(pDBEngine);
	}
	else
	{
		delete pDBEngine;
		return m_listIdleConnection.size();
	}
}

//这个东西应该没用得上   至少没找到函数显示的调用
void DBConnPool::CloseAConnection(DBConnect* pDBEngine)
{
    pDBEngine->Close();
	// 从空闲队列将其删除
	EnterCriticalSection(&m_csIdleConnList);
	m_listIdleConnection.remove(pDBEngine);
	LeaveCriticalSection(&m_csIdleConnList);
}

void DBConnPool::CloseRecordSet(_RecordsetPtr& record) {
	try {
			if(record->State)
				record->Close();
		} catch(_com_error e) {
			cout<<"close database record  failed "<<endl;
		}
}


DBConnect * DBConnPool::GetAConnection()
{
	DBConnect * pDBEngine = NULL;

	// 做一个循环，反复尝试五次取连接，每次间隔1秒钟
	int nTimes = 0;
	while ((m_listIdleConnection.size() <= 0) && (nTimes < 5))
	{
		Sleep(1000);
		nTimes++;
	}

	if (5 == nTimes)
	{
		// 这样狼狈的进来肯定是没有可用连接了，记录日志退出
		cout<<"Waiting for a connection for a long time, but failed."<<endl;
		return pDBEngine;
	}

	// 从空闲队列中取出，并且加入到使用队列中
	EnterCriticalSection(&m_csIdleConnList);
	if (m_listIdleConnection.size() > 0)
	{
		pDBEngine = m_listIdleConnection.front();
		m_listIdleConnection.pop_front();

		// 加入使用的连接队列
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
	}
	LeaveCriticalSection(&m_csIdleConnList);

	if (m_listIdleConnection.size() <= 1)
	{
		// 剩余空闲连接的数目小于等于1个时候需要检查开始创建
		if ((m_listIdleConnection.size() + m_listBusyConnection.size()) < m_nMaxCount)
		{
			// 还小于最大限制，可以创建
			SetEvent(m_hHaveData);
			m_bNeedConnection = TRUE;
		}
		else
		{
			// 超出限制了，做个记录吧
			cout<<"Database connection reached max count,you have to wait!"<<endl;
		}
	}

	return pDBEngine;
}

//创建一个连接  将它放入到空闲队列中  这样当需要连接的时候就可以从空闲队列中取出来用
int DBConnPool::RestoreAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine)
	{
		// 从使用中的队列取出
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.remove(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);

		// 加入到空闲队列中
		EnterCriticalSection(&m_csIdleConnList);
		m_listIdleConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csIdleConnList);
	}

	EnterCriticalSection(&m_csIdleConnList);
	int nCount = m_listIdleConnection.size();
	LeaveCriticalSection(&m_csIdleConnList);

	return nCount;
}

void DBConnPool::StopThread()
{
	m_bNeedStop = TRUE;
	// 因为线程是无限制等待信号的，所以这里先把标志位置为停止，然后发信号让线程检测
	SetEvent(m_hHaveData);

	// 等待退出
	WaitForSingleObject(m_hMaintanceThread, INFINITE);
	CloseHandle(m_hMaintanceThread);
}

BOOL DBConnPool::IsNeedStop()
{
	return m_bNeedStop;
}

BOOL DBConnPool::IsNeedConnection()
{
	return m_bNeedConnection;
}
/************************************************************************/
/* 维护线程                                                             */
/************************************************************************/
DWORD WINAPI DBConnPool::thread_run( LPVOID pdata)
{
	DBConnPool * pConPool = (DBConnPool *) pdata;

	while (!pConPool->IsNeedStop())
	{
		// 设置事件为无信号, 并且无限制等待
		ResetEvent(pConPool->m_hHaveData);		
		WaitForSingleObject(pConPool->m_hHaveData, INFINITE);

		if (pConPool->IsNeedConnection())
		{
		//	g_pSvrLog->AddRunLog(LL_DEBUG, _T("Create a new DB connection."));
			pConPool->InitializeAConnection();
		}
	}
	return 0;
}
