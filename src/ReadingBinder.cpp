/*
 *
 * ReadingBinder.cpp
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
    rawColumnType = 0;
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
    value = wc.ToWChar().get();
}

void RStringBinder::SetValue(const char * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar().get();
}

void RStringBinder::SetValue(wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar().get();
}

void RStringBinder::SetValue(const wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToWChar().get();
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
    rawColumnType = 0;
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

vector<IBinder *> * ReadingBinder::Get() {
    return columns;
}

ReadingBinder::ReadingBinder() {
    columns = new vector<IBinder *>();
    returnCode = 0;
}

ReadingBinder::~ReadingBinder() {
    for (size_t i = 0; i < columns->size(); i++) {
        delete columns->at(i);
    }
    delete columns;
}
