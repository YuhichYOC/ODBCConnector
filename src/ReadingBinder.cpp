/*
 * ReadingBinder.cpp
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#include "stdafx.h" // ✝

#include "ReadingBinder.h"

void RNumberBinder::SetType(SQLSMALLINT arg) {
    rawColumnType = arg;
}

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

void RNumberBinder::SetValue(int arg) {
    value = arg;
}

int RNumberBinder::GetValue() {
    return value;
}

int * RNumberBinder::GetValueAddress() {
    return &value;
}

void RNumberBinder::Bind(SQLHANDLE statement) {
    bindSuccess = false;
    returnCode = SQLBindCol(statement, index + 1,
    SQL_C_CHAR, (SQLPOINTER) &value, size, &nullIndicator);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
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
}

RNumberBinder::~RNumberBinder() {
}

void RStringBinder::SetType(SQLSMALLINT arg) {
    rawColumnType = arg;
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

void RStringBinder::SetValue(char * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar();
}

void RStringBinder::SetValue(const char * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar();
}

void RStringBinder::SetValue(wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar();
}

void RStringBinder::SetValue(const wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar();
}

wchar_t * RStringBinder::GetValue() {
    return value;
}

void RStringBinder::Bind(SQLHANDLE statement) {
    bindSuccess = false;

    if (rawColumnType == 12) {
        rawColumnType = 1;
    }

    value = new wchar_t[size];
    returnCode = SQLBindCol(
            statement,
            index + 1,
            SQL_C_TCHAR,
            (SQLPOINTER) value,
            (size + 1) * sizeof(wchar_t),
            &nullIndicator);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
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
}

RStringBinder::~RStringBinder() {
}

void ReadingBinder::AddBinder(IBinder * arg) {
    columns->push_back(arg);
}

bool ReadingBinder::Bind(SQLHANDLE statement) {
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

SQLRETURN ReadingBinder::GetReturnCode() {
    return returnCode;
}

string ReadingBinder::GetErrorMessage() {
    return errorMessage;
}

vector<IBinder*>* ReadingBinder::Get() {
    return columns;
}

ReadingBinder::ReadingBinder() {
    columns = new vector<IBinder *>();
}

ReadingBinder::~ReadingBinder() {
    for (size_t i = 0; i < columns->size(); i++) {
        delete columns->at(i);
    }
    delete columns;
}
