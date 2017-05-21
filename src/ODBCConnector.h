/*
 *
 * ODBCConnector.h
 *
 * Copyright 2016 Yuichi Yoshii
 *     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef SRC_ODBCCONNECTOR_H_
#define SRC_ODBCCONNECTOR_H_

#include <string>
#include <vector>

#include <sql.h>
#include <sqlext.h>

#include "WCharString.h"

#include "IBinder.h"

#include "ReadingBinder.h"

#include "WritingBinder.h"

#include "DataEntity.h"

class ODBCConnector {
private:

    SQLHANDLE env;

    SQLHANDLE connection;

    SQLCHAR connectionString[1024];

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

    void AddParamBindPos(
            IBinder::ColumnType type,
            SQLLEN size,
            SQLSMALLINT scale);

    bool GetParamBindPosAdded();

    void SetInsertData(vector<vector<IData *>> * arg);

    void SQLInsert(string arg);

    bool GetInsQuerySuccess();

    string GetErrorMessage();

    void HandleDiagnosticRecord(
            SQLHANDLE handle,
            SQLSMALLINT handleType,
            SQLRETURN retCode);

    ODBCConnector();

    void Dispose();

    ~ODBCConnector();
};

#endif /* SRC_ODBCCONNECTOR_H_ */
