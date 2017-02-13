/*
 * ODBCConnector.cpp
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#include "stdafx.h" // ✝

#include "ODBCConnector.h"

bool ODBCConnector::DescribeTable() {
    SQLSMALLINT columnsCount;
    SQLNumResultCols(statement, &columnsCount);

    for (SQLSMALLINT i = 0; i < columnsCount; i++) {
        SQLWCHAR columnName[128];
        SQLSMALLINT columnNameSize;
        SQLSMALLINT columnType;
        SQLULEN columnSize;
        SQLSMALLINT scale;
        SQLSMALLINT nullable;
        rc = SQLDescribeCol(statement, (SQLUSMALLINT) (i + 1), columnName,
                (SQLSMALLINT) sizeof(columnName), &columnNameSize, &columnType,
                &columnSize, &scale, &nullable);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            errorMessage = wcharStr.SysErrMessage();
            return false;
        }
        IBinder * addBinder;
        switch (columnType) {
        case SQL_CHAR:
            case SQL_VARCHAR:
            addBinder = new RStringBinder();
            addBinder->SetType(columnType);
            addBinder->SetIndex(i);
            addBinder->SetSize(columnSize);
            addBinder->SetScale(scale);
            break;
        case SQL_NUMERIC:
            addBinder = new RNumberBinder();
            addBinder->SetType(columnType);
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
            addBinder->SetType(columnType);
            addBinder->SetIndex(i);
            addBinder->SetSize(columnSize);
            addBinder->SetScale(scale);
            break;
        default:
            break;
        }
        rb->AddBinder(addBinder);
    }

    return rb->Bind(statement);
}

bool ODBCConnector::ExecDML(string arg) {
    unique_ptr<wchar_t> query(wcharStr.Value(arg).ToWChar());
    if (table == nullptr || table->size() == 0) {
        rc = SQLExecDirect(statement, query.get(), SQL_NTS);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = wcharStr.SysErrMessage();
            return false;
        }
        return true;
    } else {
        rc = SQLPrepare(statement, query.get(), SQL_NTS);
        if (rc != SQL_SUCCESS && rc != SQL_NEED_DATA
                && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = wcharStr.SysErrMessage();
            return false;
        }
        for (size_t i = 0; i < table->size(); i++) {
            for (size_t j = 0; j < table->at(i).size(); j++) {
                if (table->at(i).at(j)->GetType() == IData::DataType::NUMBER) {
                    int value =
                            ((NumberData *) (table->at(i).at(j)))->GetData();
                    ((WNumberBinder *) wb->Get()->at(j))->SetValue(value);
                } else {
                    char * value =
                            ((StringData *) (table->at(i).at(j)))->GetData();
                    ((WStringBinder *) wb->Get()->at(j))->SetValue(value);
                }
            }
            if (!wb->Bind(statement)) {
                HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
                errorMessage = wcharStr.SysErrMessage();
                return false;
            }
            rc = SQLExecute(statement);
            if (rc != SQL_SUCCESS && rc != SQL_NEED_DATA
                    && rc != SQL_SUCCESS_WITH_INFO) {
                HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
                errorMessage = wcharStr.SysErrMessage();
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
        errorMessage = wcharStr.SysErrMessage();
    } else {
        rc = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION,
                (SQLPOINTER) SQL_OV_ODBC3, 0);
        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
            HandleDiagnosticRecord(env, SQL_HANDLE_ENV, rc);
            errorMessage = wcharStr.SysErrMessage();
        } else {
            rc = SQLAllocHandle(SQL_HANDLE_DBC, env, &connection);
            if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
                HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
                errorMessage = wcharStr.SysErrMessage();
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

    unique_ptr<wchar_t> cs(wcharStr.Value(arg).ToWChar());
    rc = SQLDriverConnect(connection,
    NULL, cs.get(),
    SQL_NTS, connectionString, 1024, &bufSize,
    SQL_DRIVER_NOPROMPT);

    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        connected = true;
        transactionBegun = false;
    } else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wcharStr.SysErrMessage();
    }
}

bool ODBCConnector::GetConnected() {
    return connected;
}

void ODBCConnector::BeginTransaction() {
    transactionBegun = false;

    rc = SQLSetConnectAttr(connection,
    SQL_ATTR_AUTOCOMMIT, (SQLPOINTER) SQL_AUTOCOMMIT_OFF,
    SQL_NTS);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = true;
    } else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wcharStr.SysErrMessage();
    }
}

bool ODBCConnector::GetTransactionBegun() {
    return transactionBegun;
}

void ODBCConnector::CommitTransaction() {
    rc = SQLEndTran(
    SQL_HANDLE_ENV, (SQLHANDLE) env,
    SQL_COMMIT);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = false;
    } else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wcharStr.SysErrMessage();
    }
}

void ODBCConnector::RollbackTransaction() {
    rc = SQLEndTran(
    SQL_HANDLE_ENV, (SQLHANDLE) env,
    SQL_ROLLBACK);
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        transactionBegun = false;
    } else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_DBC, rc);
        errorMessage = wcharStr.SysErrMessage();
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
    } else {
        HandleDiagnosticRecord(connection, SQL_HANDLE_STMT, rc);
        errorMessage = wcharStr.SysErrMessage();
    }
}

bool ODBCConnector::GetSQLStatementPrepared() {
    return statementPrepared;
}

void ODBCConnector::SQLSelect(string arg) {
    selQuerySuccess = false;

    unique_ptr<wchar_t> query(wcharStr.Value(arg).ToWChar());
    rc = SQLExecDirect(statement, query.get(), SQL_NTS);

    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        if (DescribeTable()) {
            selQuerySuccess = true;
        } else {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            errorMessage = rb->GetErrorMessage();
        }
    } else {
        HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
        errorMessage = wcharStr.SysErrMessage();
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
            for (size_t i = 0; i < rb->Get()->size(); i++) {
                locale::global(locale("C"));
                if (rb->Get()->at(i)->GetType()
                        == IBinder::ColumnType::NUMBER) {
                    double outValue =
                            ((RNumberBinder *) rb->Get()->at(i))->GetValue();
                    cout << outValue;
                } else {
                    string outValue =
                            wcharStr.Value(
                                    ((RStringBinder *) rb->Get()->at(i))->GetValue()).ToString();
                    cout << outValue;
                }
                if (i < rb->Get()->size() - 1) {
                    cout << ", ";
                }
                locale::global(locale(""));
            }
        } else if (rc == SQL_NO_DATA_FOUND) {
            fetchCompleted = true;
        } else {
            HandleDiagnosticRecord(statement, SQL_HANDLE_STMT, rc);
            return;
        }
        cout << "\n";
    } while (!fetchCompleted);
}

bool ODBCConnector::GetFetchCompleted() {
    return fetchCompleted;
}

void ODBCConnector::AddParamBindPos(IBinder::ColumnType type, SQLLEN size,
        SQLSMALLINT scale) {
    paramBindPosAdded = false;

    IBinder * addBinder;
    if (type == IBinder::ColumnType::NUMBER) {
        addBinder = new WNumberBinder();
        addBinder->SetIndex(bindPos);
        addBinder->SetSize(size);
        addBinder->SetScale(scale);
    } else {
        addBinder = new WStringBinder();
        addBinder->SetIndex(bindPos);
        addBinder->SetSize(size);
        addBinder->SetScale(scale);
    }
    wb->AddBinder(addBinder);
    bindPos++;

    paramBindPosAdded = true;
}

bool ODBCConnector::GetParamBindPosAdded() {
    return paramBindPosAdded;
}

void ODBCConnector::SetInsertData(vector<vector<IData *>> * arg) {
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

void ODBCConnector::HandleDiagnosticRecord(SQLHANDLE handle,
        SQLSMALLINT handleType, SQLRETURN retCode) {
    if (retCode == SQL_INVALID_HANDLE) {
        locale::global(locale("C"));
        cout << "Invalid handle" << "\n";
        locale::global(locale(""));
        return;
    }
    SQLSMALLINT iRec = 0;
    WCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
    SQLINTEGER error;
    WCHAR szErrorMessage[1000];
    while (SQLGetDiagRec(handleType, handle, ++iRec, szSQLState, &error,
            szErrorMessage,
            (SQLSMALLINT) (sizeof(szErrorMessage) / sizeof(WCHAR)),
            (SQLSMALLINT *) NULL) == SQL_SUCCESS) {
        WCharString msgCnv;
        locale::global(locale("C"));
        cout
                << msgCnv.Value("Status = ").Append(szSQLState).Append(" ").Append(
                        "\n").Append("Message = ").Append(szErrorMessage).ToString()
                << "\n" << "\n";
        locale::global(locale(""));
    }
}

ODBCConnector::ODBCConnector() {
    rb = new ReadingBinder();
    wb = new WritingBinder();
    bindPos = 0;
    disposed = false;
}

void ODBCConnector::Dispose() {
    delete rb;
    delete wb;
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
