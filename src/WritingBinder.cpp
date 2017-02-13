/*
 * WritingBinder.cpp
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#include "stdafx.h"

#include "WritingBinder.h"

void WNumberBinder::BindParam(SQLHANDLE statement) {
    bindSuccess = false;
    SQLLEN cbTextSize = SQL_LEN_DATA_AT_EXEC(size);
    returnCode = SQLBindParameter(statement, index + 1,
    SQL_PARAM_INPUT,
    SQL_C_SHORT,
    SQL_INTEGER, size, scale, (SQLPOINTER) &value, 0, &cbTextSize);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
        bindSuccess = true;
    }
}

void WNumberBinder::SetType(SQLSMALLINT arg) {
    rawColumnType = arg;
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

int WNumberBinder::GetValue() {
    return value;
}

int * WNumberBinder::GetValueAddress() {
    return &value;
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
}

WNumberBinder::~WNumberBinder() {
}

void WStringBinder::BindParam(SQLHANDLE statement) {
    bindSuccess = false;

    SQLLEN cbTextSize = SQL_LEN_DATA_AT_EXEC(size);
    returnCode = SQLBindParameter(statement, index + 1,
    SQL_PARAM_INPUT,
    SQL_C_TCHAR,
    SQL_VARCHAR, size, 0, (SQLPOINTER) value, 0, &cbTextSize);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
        bindSuccess = true;
    }
}

void WStringBinder::SetType(SQLSMALLINT arg) {
    rawColumnType = arg;
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
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(const char * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void WStringBinder::SetValue(const wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

char * WStringBinder::GetValue() {
    return value;
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
}

WStringBinder::~WStringBinder() {
}

void WritingBinder::AddBinder(IBinder * arg) {
    columns->push_back(arg);
}

bool WritingBinder::Bind(SQLHANDLE statement) {
    for (size_t i = 0; i < columns->size(); i++) {
        columns->at(i)->Bind(statement);
        if (!columns->at(i)->GetBindSuccess()) {
            returnCode = columns->at(i)->GetReturnCode();
            errorMessage = columns->at(i)->GetErrorMessage();
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

vector<IBinder*>* WritingBinder::Get() {
    return columns;
}

WritingBinder::WritingBinder() {
    columns = new vector<IBinder *>();
}

WritingBinder::~WritingBinder() {
    for (size_t i = 0; i < columns->size(); i++) {
        delete columns->at(i);
    }
    delete columns;
}
