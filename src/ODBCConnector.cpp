/*
 *
 * ODBCConnector.cpp
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

#include "ODBCConnector.h"

IBinder::ColumnType RNumberBinder::GetType() {
    return IBinder::ColumnType::NUMBER;
}

void RNumberBinder::SetIndex(int arg) {
    index = arg;
}

int RNumberBinder::GetIndex() {
    return index;
}

void RNumberBinder::SetSize(SQLLEN arg) {
    size = arg;
}

SQLLEN RNumberBinder::GetSize() {
    return size;
}

void RNumberBinder::SetScale(SQLSMALLINT arg) {
    scale = arg;
}

SQLSMALLINT RNumberBinder::GetScale() {
    return scale;
}

int RNumberBinder::GetValue() {
    return value;
}

void RNumberBinder::Bind(SQLHANDLE statement) {
    bindSuccess = false;
    nullIndicator = sizeof(value);
    returnCode = SQLBindCol(
            statement,
            index + 1,
            SQL_C_CHAR,
            (SQLPOINTER) &value,
            size,
            &nullIndicator);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    }
    else {
        bindSuccess = true;
    }
}

SQLRETURN RNumberBinder::GetReturnCode() {
    return returnCode;
}

string RNumberBinder::GetErrorMessage() {
    return errorMessage;
}

bool RNumberBinder::GetBindSuccess() {
    return bindSuccess;
}

RNumberBinder::RNumberBinder() {
    index = 0;
    size = 0;
    scale = 0;
    value = 0;
    nullIndicator = 0;
    returnCode = 0;
    bindSuccess = false;
}

RNumberBinder::~RNumberBinder() {
}

IBinder::ColumnType RStringBinder::GetType() {
    return IBinder::ColumnType::STRING;
}

void RStringBinder::SetIndex(int arg) {
    index = arg;
}

int RStringBinder::GetIndex() {
    return index;
}

void RStringBinder::SetSize(SQLLEN arg) {
    size = arg;
}

SQLLEN RStringBinder::GetSize() {
    return size;
}

void RStringBinder::SetScale(SQLSMALLINT arg) {
    scale = arg;
}

SQLSMALLINT RStringBinder::GetScale() {
    return scale;
}

unique_ptr<char> RStringBinder::GetValue() {
    return move(value);
}

void RStringBinder::Bind(SQLHANDLE statement) {
    bindSuccess = false;
    value = unique_ptr<char>(new char[size]);
    nullIndicator = sizeof(char) * size;
    returnCode = SQLBindCol(
            statement,
            index + 1,
            SQL_C_CHAR,
            (SQLPOINTER) value.get(),
            sizeof(char) * size,
            &nullIndicator);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    }
    else {
        bindSuccess = true;
    }
}

SQLRETURN RStringBinder::GetReturnCode() {
    return returnCode;
}

string RStringBinder::GetErrorMessage() {
    return errorMessage;
}

bool RStringBinder::GetBindSuccess() {
    return bindSuccess;
}

RStringBinder::RStringBinder() {
    index = 0;
    size = 0;
    scale = 0;
    value = nullptr;
    nullIndicator = 0;
    returnCode = 0;
    bindSuccess = false;
}

RStringBinder::~RStringBinder() {
}

void ReadingBinder::AddBinder(IBinder * arg) {
    columns.push_back(arg);
}

bool ReadingBinder::Bind(SQLHANDLE statement) {
    for (size_t i = 0; i < columns.size(); i++) {
        columns.at(i)->Bind(statement);
        if (!columns.at(i)->GetBindSuccess()) {
            returnCode = columns.at(i)->GetReturnCode();
            errorMessage = columns.at(i)->GetErrorMessage();
            return false;
        }
    }
    return true;
}

SQLRETURN ReadingBinder::GetReturnCode() {
    return returnCode;
}

string ReadingBinder::GetErrorMessage() {
    return errorMessage;
}

vector<IBinder *> ReadingBinder::Get() {
    return columns;
}

ReadingBinder::ReadingBinder() {
    returnCode = 0;
}

ReadingBinder::~ReadingBinder() {
    for (size_t i = 0; i < columns.size(); i++) {
        delete columns.at(i);
    }
}

void WNumberBinder::BindParam(SQLHANDLE statement) {
    bindSuccess = false;
    returnCode = SQLBindParameter(
            statement,
            index + 1,
            SQL_PARAM_INPUT,
            SQL_C_SHORT,
            SQL_INTEGER,
            size,
            scale,
            (SQLPOINTER) &value,
            0,
            &size);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    }
    else {
        bindSuccess = true;
    }
}

IBinder::ColumnType WNumberBinder::GetType() {
    return IBinder::ColumnType::NUMBER;
}

void WNumberBinder::SetIndex(int arg) {
    index = arg;
}

int WNumberBinder::GetIndex() {
    return index;
}

void WNumberBinder::SetSize(SQLLEN arg) {
    size = arg;
}

SQLLEN WNumberBinder::GetSize() {
    return size;
}

void WNumberBinder::SetScale(SQLSMALLINT arg) {
    scale = arg;
}

SQLSMALLINT WNumberBinder::GetScale() {
    return scale;
}

void WNumberBinder::SetValue(int arg) {
    value = arg;
}

void WNumberBinder::Bind(SQLHANDLE statement) {
    BindParam(statement);
}

SQLRETURN WNumberBinder::GetReturnCode() {
    return returnCode;
}

string WNumberBinder::GetErrorMessage() {
    return errorMessage;
}

bool WNumberBinder::GetBindSuccess() {
    return bindSuccess;
}

WNumberBinder::WNumberBinder() {
    index = 0;
    size = 0;
    scale = 0;
    value = 0;
    nullIndicator = 0;
    returnCode = 0;
    bindSuccess = false;
}

WNumberBinder::~WNumberBinder() {
}

void WStringBinder::BindParam(SQLHANDLE statement) {
    bindSuccess = false;
    returnCode = SQLBindParameter(
            statement,
            index + 1,
            SQL_PARAM_INPUT,
            SQL_C_CHAR,
            SQL_VARCHAR,
            size,
            0,
            (SQLPOINTER) value.get(),
            size,
            &size);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    }
    else {
        bindSuccess = true;
    }
}

IBinder::ColumnType WStringBinder::GetType() {
    return IBinder::ColumnType::STRING;
}

void WStringBinder::SetIndex(int arg) {
    index = arg;
}

int WStringBinder::GetIndex() {
    return index;
}

void WStringBinder::SetSize(SQLLEN arg) {
    size = arg;
}

SQLLEN WStringBinder::GetSize() {
    return size;
}

void WStringBinder::SetScale(SQLSMALLINT arg) {
    scale = arg;
}

SQLSMALLINT WStringBinder::GetScale() {
    return scale;
}

void WStringBinder::SetValue(char * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(const char * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(wchar_t * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(const wchar_t * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(string arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::Bind(SQLHANDLE statement) {
    BindParam(statement);
}

SQLRETURN WStringBinder::GetReturnCode() {
    return returnCode;
}

string WStringBinder::GetErrorMessage() {
    return errorMessage;
}

bool WStringBinder::GetBindSuccess() {
    return bindSuccess;
}

WStringBinder::WStringBinder() {
    index = 0;
    size = 0;
    scale = 0;
    value = nullptr;
    nullIndicator = 0;
    returnCode = 0;
    bindSuccess = false;
}

WStringBinder::~WStringBinder() {
}

void WritingBinder::AddBinder(IBinder * arg) {
    columns.push_back(arg);
}

bool WritingBinder::Bind(SQLHANDLE statement) {
    for (size_t i = 0; i < columns.size(); i++) {
        columns.at(i)->Bind(statement);
        if (!columns.at(i)->GetBindSuccess()) {
            returnCode = columns.at(i)->GetReturnCode();
            errorMessage = columns.at(i)->GetErrorMessage();
            return false;
        }
    }
    return true;
}

SQLRETURN WritingBinder::GetReturnCode() {
    return returnCode;
}

string WritingBinder::GetErrorMessage() {
    return errorMessage;
}

vector<IBinder *> WritingBinder::Get() {
    return columns;
}

WritingBinder::WritingBinder() {
    returnCode = 0;
}

WritingBinder::~WritingBinder() {
    for (size_t i = 0; i < columns.size(); i++) {
        delete columns.at(i);
    }
}

IData::DataType NumberData::GetType() {
    return IData::DataType::NUMBER;
}

void NumberData::SetData(int arg) {
    value = arg;
}

int NumberData::GetData() {
    return value;
}

NumberData::NumberData() {
    value = 0;
}

NumberData::~NumberData() {
}

IData::DataType StringData::GetType() {
    return IData::DataType::STRING;
}

void StringData::SetData(char * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(const char * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(wchar_t * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(const wchar_t * arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(string arg) {
    WCharString wc;
    wc.Value(arg);
    value = wc.ToChar();
}

unique_ptr<char> StringData::GetData() {
    return move(value);
}

StringData::StringData() {
}

StringData::~StringData() {
}

bool ODBCConnector::DescribeTable() {
    SQLSMALLINT columnsCount;
    SQLNumResultCols(statement, &columnsCount);

    for (SQLSMALLINT i = 0; i < columnsCount; i++) {
        SQLCHAR columnName[128] = { 0 };
        SQLSMALLINT columnNameSize = 0;
        SQLSMALLINT columnType = 0;
        SQLULEN columnSize = 0;
        SQLSMALLINT scale = 0;
        SQLSMALLINT nullable = 0;
        rc = SQLDescribeCol(
                statement,
                (SQLUSMALLINT) (i + 1),
                columnName,
                (SQLSMALLINT) sizeof(columnName),
                &columnNameSize,
                &columnType,
                &columnSize,
                &scale,
                &nullable);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            errorMessage = wc.SysErrMessage();
            return false;
        }
        IBinder * addBinder;
        switch (columnType) {
        case SQL_CHAR:
            case SQL_VARCHAR:
            addBinder = new RStringBinder();
            addBinder->SetIndex(i);
            addBinder->SetSize(columnSize);
            addBinder->SetScale(scale);
            break;
        case SQL_NUMERIC:
            addBinder = new RNumberBinder();
            addBinder->SetIndex(i);
            addBinder->SetSize(columnSize);
            addBinder->SetScale(scale);
            break;
        case SQL_DECIMAL:
            case SQL_INTEGER:
            case SQL_SMALLINT:
            case SQL_FLOAT:
            case SQL_DOUBLE:
            addBinder = new RNumberBinder();
            addBinder->SetIndex(i);
            addBinder->SetSize(columnSize);
            addBinder->SetScale(scale);
            break;
        default:
            break;
        }
        rb.AddBinder(addBinder);
    }

    return rb.Bind(statement);
}

bool ODBCConnector::ExecDML(string arg) {
    unique_ptr<unsigned char> query(wc.Value(arg).ToUChar());
    if (table.size() == 0) {
        rc = SQLExecDirect(statement, query.get(), SQL_NTS);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = wc.SysErrMessage();
            return false;
        }
        return true;
    }
    else {
        rc = SQLPrepare(statement, query.get(), SQL_NTS);
        if (rc != SQL_SUCCESS
                && rc != SQL_NEED_DATA
                && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = wc.SysErrMessage();
            return false;
        }
        for (size_t i = 0; i < table.size(); i++) {
            for (size_t j = 0; j < table.at(i).size(); j++) {
                if (table.at(i).at(j)->GetType() == IData::DataType::NUMBER) {
                    ((WNumberBinder *) wb.Get().at(j))->SetValue(
                            ((NumberData *) (table.at(i).at(j)))->GetData()
                            );
                }
                else {
                    ((WStringBinder *) wb.Get().at(j))->SetValue(
                            wc.Value(
                                    ((StringData *) (table.at(i).at(j)))->GetData()).ToString()
                            );
                }
            }
            if (!wb.Bind(statement)) {
                HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
                errorMessage = wc.SysErrMessage();
                return false;
            }
            rc = SQLExecute(statement);
            if (rc != SQL_SUCCESS
                    && rc != SQL_NEED_DATA
                    && rc != SQL_SUCCESS_WITH_INFO) {
                HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
                errorMessage = wc.SysErrMessage();
                return false;
            }
        }
        return true;
    }
}

void ODBCConnector::Prepare() {
    prepared = false;

    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
        HandleDiagnosticRecord(env, SQL_HANDLE_ENV, rc);
        errorMessage = wc.SysErrMessage();
    }
    else {
        rc = SQLSetEnvAttr(
                env,
                SQL_ATTR_ODBC_VERSION,
                (SQLPOINTER) SQL_OV_ODBC3,
                0);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(env, SQL_HANDLE_ENV, rc);
            errorMessage = wc.SysErrMessage();
        }
        else {
            rc = SQLAllocHandle(SQL_HANDLE_DBC, env, &connection);
            if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
                HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
                errorMessage = wc.SysErrMessage();
            }
        }
    }

    prepared = true;
}

bool ODBCConnector::GetPrepared() {
    return prepared;
}

void ODBCConnector::Connect(string arg) {
    connected = false;

    unique_ptr<unsigned char> cs(wc.Value(arg).ToUChar());
    rc = SQLDriverConnect(
            connection,
            nullptr,
            cs.get(),
            SQL_NTS,
            connectionString,
            1024,
            &bufSize,
            SQL_DRIVER_NOPROMPT);

    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        connected = true;
        transactionBegun = false;
    }
    else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wc.SysErrMessage();
    }
}

bool ODBCConnector::GetConnected() {
    return connected;
}

void ODBCConnector::BeginTransaction() {
    transactionBegun = false;

    rc = SQLSetConnectAttr(
            connection,
            SQL_ATTR_AUTOCOMMIT,
            (SQLPOINTER) SQL_AUTOCOMMIT_OFF,
            SQL_NTS);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = true;
    }
    else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wc.SysErrMessage();
    }
}

bool ODBCConnector::GetTransactionBegun() {
    return transactionBegun;
}

void ODBCConnector::CommitTransaction() {
    rc = SQLEndTran(
    SQL_HANDLE_ENV,
            (SQLPOINTER) env,
            SQL_COMMIT);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = false;
    }
    else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wc.SysErrMessage();
    }
}

void ODBCConnector::RollbackTransaction() {
    rc = SQLEndTran(
    SQL_HANDLE_ENV,
            (SQLPOINTER) env,
            SQL_ROLLBACK);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = false;
    }
    else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wc.SysErrMessage();
    }
}

void ODBCConnector::SQLStatementPrepare() {
    statementPrepared = false;

    // In ODBC 3.x, the ODBC 2.x function SQLAllocStmt has been replaced by SQLAllocHandle.
    // https://msdn.microsoft.com/ja-jp/library/ms709370(v=vs.85).aspx
    // ftp://public.dhe.ibm.com/software/data/db2/everyplace/infocenters/jpn/dbeapr1006.htm
    // https://mariadb.com/kb/en/sql-99/sqlallocstmt/
    // SQLAllocStmt(env, &statement);

    rc = SQLAllocHandle(SQL_HANDLE_STMT, connection, &statement);

    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        statementPrepared = true;
    }
    else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_STMT, rc);
        errorMessage = wc.SysErrMessage();
    }
}

bool ODBCConnector::GetSQLStatementPrepared() {
    return statementPrepared;
}

void ODBCConnector::SQLSelect(string arg) {
    selQuerySuccess = false;

    unique_ptr<unsigned char> query(wc.Value(arg).ToUChar());
    rc = SQLExecDirect(statement, query.get(), SQL_NTS);

    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        if (DescribeTable()) {
            selQuerySuccess = true;
        }
        else {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = rb.GetErrorMessage();
        }
    }
    else {
        HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
        errorMessage = wc.SysErrMessage();
    }
}

bool ODBCConnector::GetSelQuerySuccess() {
    return selQuerySuccess;
}

void ODBCConnector::Fetch() {
    fetchCompleted = false;

    do {
        rc = SQLFetch(statement);

        if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
            vector<IData *> row;
            for (size_t i = 0; i < rb.Get().size(); i++) {
                if (rb.Get().at(i)->GetType()
                        == IBinder::ColumnType::NUMBER) {
                    NumberData * add = new NumberData();
                    add->SetData(
                            ((RNumberBinder *) rb.Get().at(i))->GetValue()
                            );
                    row.push_back(add);
                }
                else {
                    StringData * add = new StringData();
                    add->SetData(
                            wc.Value(
                                    ((RStringBinder *) rb.Get().at(i))->GetValue()
                                    ).ToString()
                            );
                    row.push_back(add);
                }
            }
            rb.Bind(statement);
            table.push_back(row);
        }
        else if (rc == SQL_NO_DATA_FOUND) {
            fetchCompleted = true;
        }
        else {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            return;
        }
        cout << "\n";
    } while (!fetchCompleted);
}

bool ODBCConnector::GetFetchCompleted() {
    return fetchCompleted;
}

void ODBCConnector::AddParamBindPos(
        IBinder::ColumnType type,
        SQLLEN size,
        SQLSMALLINT scale) {
    paramBindPosAdded = false;

    IBinder * addBinder;
    if (type == IBinder::ColumnType::NUMBER) {
        addBinder = new WNumberBinder();
        addBinder->SetIndex(bindPos);
        addBinder->SetSize(size);
        addBinder->SetScale(scale);
    }
    else {
        addBinder = new WStringBinder();
        addBinder->SetIndex(bindPos);
        addBinder->SetSize(size);
        addBinder->SetScale(scale);
    }
    wb.AddBinder(addBinder);
    bindPos++;

    paramBindPosAdded = true;
}

bool ODBCConnector::GetParamBindPosAdded() {
    return paramBindPosAdded;
}

void ODBCConnector::SetInsertData(vector<vector<IData *>> arg) {
    table = arg;
}

void ODBCConnector::SQLInsert(string arg) {
    insQuerySuccess = false;

    if (ExecDML(arg)) {
        insQuerySuccess = true;
    }
}

bool ODBCConnector::GetInsQuerySuccess() {
    return insQuerySuccess;
}

string ODBCConnector::GetErrorMessage() {
    return errorMessage;
}

void ODBCConnector::HandleDiagnosticRecord(
        SQLHANDLE handle,
        SQLSMALLINT handleType,
        SQLRETURN retCode) {
    if (retCode == SQL_INVALID_HANDLE) {
        cout << "Invalid handle" << endl;
        return;
    }
    SQLSMALLINT iRec = 0;
    SQLCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
    SQLINTEGER error;
    SQLCHAR szErrorMessage[1000];
    while (SQLGetDiagRec(handleType,
            handle,
            ++iRec,
            szSQLState,
            &error,
            szErrorMessage,
            (SQLSMALLINT) (sizeof(szErrorMessage) / sizeof(WCHAR)),
            (SQLSMALLINT *) NULL) == SQL_SUCCESS) {
        cout
                << wc.Value("Status    = ").Append(szSQLState).Append("\n").ToString();
        cout
                << wc.Value("Message   = ").Append(szErrorMessage).Append("\n").ToString();
        cout << endl;
    }
}

ODBCConnector::ODBCConnector() {
    env = nullptr;
    connection = nullptr;
    bufSize = 0;
    statement = nullptr;
    rc = 0;
    prepared = false;
    connected = false;
    transactionBegun = false;
    statementPrepared = false;
    selQuerySuccess = false;
    fetchCompleted = false;
    bindPos = 0;
    paramBindPosAdded = false;
    insQuerySuccess = false;
    disposed = false;
}

void ODBCConnector::Dispose() {
    SQLFreeHandle(SQL_HANDLE_STMT, statement);
    SQLFreeHandle(SQL_HANDLE_DBC, connection);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
    disposed = true;
}

ODBCConnector::~ODBCConnector() {
    if (!disposed) {
        Dispose();
    }
}
