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

#include <memory>
#include <string>
#include <vector>

#include <sql.h>
#include <sqlext.h>

#include "WCharString.h"

using namespace std;

class IBinder
{
public:

    enum ColumnType {
        STRING, NUMBER,
    };

    virtual ColumnType GetType() = 0;

    virtual void SetIndex(int arg) = 0;

    virtual void SetSize(long arg) = 0;

    virtual void SetScale(signed short arg) = 0;

    virtual void Bind(void * statement) = 0;

    virtual signed short GetReturnCode() = 0;

    virtual string GetErrorMessage() = 0;

    virtual bool GetBindSuccess() = 0;

    virtual ~IBinder() {
    }
    ;
};

class RNumberBinder: public IBinder
{
private:

    int index;

    SQLLEN size;

    SQLSMALLINT scale;

    int value;

    SQLLEN nullIndicator;

    SQLRETURN returnCode;

    string errorMessage;

    bool bindSuccess;

public:

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(SQLLEN arg);

    SQLLEN GetSize();

    void SetScale(SQLSMALLINT arg);

    SQLSMALLINT GetScale();

    int GetValue();

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    RNumberBinder();

    ~RNumberBinder();
};

class RStringBinder: public IBinder
{
private:

    int index;

    SQLLEN size;

    SQLSMALLINT scale;

    unique_ptr<char> value;

    SQLLEN nullIndicator;

    SQLRETURN returnCode;

    string errorMessage;

    bool bindSuccess;

public:

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(SQLLEN arg);

    SQLLEN GetSize();

    void SetScale(SQLSMALLINT arg);

    SQLSMALLINT GetScale();

    unique_ptr<char> GetValue();

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    RStringBinder();

    ~RStringBinder();
};

class ReadingBinder
{
private:

    vector<IBinder *> columns;

    SQLRETURN returnCode;

    string errorMessage;

public:

    void AddBinder(IBinder * arg);

    bool Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    vector<IBinder *> Get();

    ReadingBinder();

    ~ReadingBinder();
};

class WNumberBinder: public IBinder
{
private:

    int index;

    SQLLEN size;

    SQLSMALLINT scale;

    int value;

    SQLLEN nullIndicator;

    SQLRETURN returnCode;

    string errorMessage;

    bool bindSuccess;

    void BindParam(SQLHANDLE statement);

public:

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(SQLLEN arg);

    SQLLEN GetSize();

    void SetScale(SQLSMALLINT arg);

    SQLSMALLINT GetScale();

    void SetValue(int arg);

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    WNumberBinder();

    ~WNumberBinder();
};

class WStringBinder: public IBinder
{
private:

    int index;

    SQLLEN size;

    SQLSMALLINT scale;

    unique_ptr<char> value;

    SQLLEN nullIndicator;

    SQLRETURN returnCode;

    string errorMessage;

    bool bindSuccess;

    void BindParam(SQLHANDLE statement);

public:

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(SQLLEN arg);

    SQLLEN GetSize();

    void SetScale(SQLSMALLINT arg);

    SQLSMALLINT GetScale();

    void SetValue(char * arg);

    void SetValue(const char * arg);

    void SetValue(wchar_t * arg);

    void SetValue(const wchar_t * arg);

    void SetValue(string arg);

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    WStringBinder();

    ~WStringBinder();
};

class WritingBinder
{
private:

    vector<IBinder *> columns;

    SQLRETURN returnCode;

    string errorMessage;

public:

    void AddBinder(IBinder * arg);

    bool Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    vector<IBinder *> Get();

    WritingBinder();

    ~WritingBinder();
};

class IData
{
public:

    enum DataType {
        STRING, NUMBER,
    };

    virtual DataType GetType() = 0;

    virtual ~IData() {
    }
    ;
};

class NumberData: public IData
{
private:

    int value;

public:

    IData::DataType GetType();

    void SetData(int value);

    int GetData();

    NumberData();

    ~NumberData();
};

class StringData: public IData
{
private:

    unique_ptr<char> value;

public:

    IData::DataType GetType();

    void SetData(char * arg);

    void SetData(const char * arg);

    void SetData(wchar_t * arg);

    void SetData(const wchar_t * arg);

    void SetData(string arg);

    unique_ptr<char> GetData();

    StringData();

    ~StringData();
};

class ODBCConnector
{
private:

    SQLHANDLE env;

    SQLHANDLE connection;

    SQLCHAR connectionString[1024];

    SQLSMALLINT bufSize;

    SQLHANDLE statement;

    SQLRETURN rc;

    ReadingBinder rb;

    WritingBinder wb;

    vector<vector<IData *>> table;

    WCharString wc;

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

    void SetInsertData(vector<vector<IData *>> arg);

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
