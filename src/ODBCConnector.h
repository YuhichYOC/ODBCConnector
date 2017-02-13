/*
 * ODBCConnector.h
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#ifndef SRC_ODBCCONNECTOR_H_
#define SRC_ODBCCONNECTOR_H_

#include "stdafx.h" // ✝

#include "WCharString.h"

#include "ReadingBinder.h"

#include "WritingBinder.h"

#include "DataEntity.h"

class ODBCConnector {
private:

    SQLHANDLE env;

    SQLHANDLE connection;

    SQLWCHAR connectionString[1024];

    SQLSMALLINT bufSize;

    SQLHANDLE statement;

    SQLRETURN rc;

    ReadingBinder * rb;

    WritingBinder * wb;

    vector<vector<IData *>> * table;

    WCharString wcharStr;

    string errorMessage;

    bool prepared;

    bool connected;

    bool transactionBegun;

    bool statementPrepared;

    bool selQuerySuccess;

    bool fetchCompleted;

    int bindPos;

    bool paramBindPosAdded;

    bool insQuerySuccess;

    bool disposed;

    bool DescribeTable();

    bool ExecDML(string arg);

public:

    void Prepare();

    bool GetPrepared();

    void Connect(string arg);

    bool GetConnected();

    void BeginTransaction();

    bool GetTransactionBegun();

    void CommitTransaction();

    void RollbackTransaction();

    void SQLStatementPrepare();

    bool GetSQLStatementPrepared();

    void SQLSelect(string arg);

    bool GetSelQuerySuccess();

    void Fetch();

    bool GetFetchCompleted();

    void AddParamBindPos(IBinder::ColumnType type, SQLLEN size,
            SQLSMALLINT scale);

    bool GetParamBindPosAdded();

    void SetInsertData(vector<vector<IData *>> * arg);

    void SQLInsert(string arg);

    bool GetInsQuerySuccess();

    string GetErrorMessage();

    void HandleDiagnosticRecord(SQLHANDLE handle, SQLSMALLINT handleType,
            SQLRETURN retCode);

    ODBCConnector();

    void Dispose();

    ~ODBCConnector();
};

#endif /* SRC_ODBCCONNECTOR_H_ */
