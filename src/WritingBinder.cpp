/*
 *
 * WritingBinder.cpp
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

#include "WritingBinder.h"

void WNumberBinder::BindParam(void * statement) {
    bindSuccess = false;
    long cbTextSize = SQL_LEN_DATA_AT_EXEC(size);
    returnCode = SQLBindParameter(
            statement,
            index + 1,
            SQL_PARAM_INPUT,
            SQL_C_SHORT,
            SQL_INTEGER,
            size,
            scale,
            (void *) &value,
            0,
            &cbTextSize);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
        bindSuccess = true;
    }
}

void WNumberBinder::SetType(signed short arg) {
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

void WNumberBinder::SetSize(long arg) {
    size = arg;
}

long WNumberBinder::GetSize() {
    return size;
}

void WNumberBinder::SetScale(signed short arg) {
    scale = arg;
}

signed short WNumberBinder::GetScale() {
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

void WNumberBinder::Bind(void * statement) {
    BindParam(statement);
}

signed short WNumberBinder::GetReturnCode() {
    return returnCode;
}

string WNumberBinder::GetErrorMessage() {
    return errorMessage;
}

bool WNumberBinder::GetBindSuccess() {
    return bindSuccess;
}

WNumberBinder::WNumberBinder() {
    rawColumnType = 0;
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

void WStringBinder::BindParam(void * statement) {
    bindSuccess = false;

    long cbTextSize = SQL_LEN_DATA_AT_EXEC(size);
    returnCode = SQLBindParameter(
            statement,
            index + 1,
            SQL_PARAM_INPUT,
            SQL_C_TCHAR,
            SQL_VARCHAR,
            size,
            0,
            (void *) value,
            0,
            &cbTextSize);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        WCharString wcs;
        errorMessage = wcs.SysErrMessage();
    } else {
        bindSuccess = true;
    }
}

void WStringBinder::SetType(signed short arg) {
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

void WStringBinder::SetSize(long arg) {
    size = arg;
}

long WStringBinder::GetSize() {
    return size;
}

void WStringBinder::SetScale(signed short arg) {
    scale = arg;
}

signed short WStringBinder::GetScale() {
    return scale;
}

void WStringBinder::SetValue(char * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void WStringBinder::SetValue(const char * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void WStringBinder::SetValue(wchar_t * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void WStringBinder::SetValue(const wchar_t * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

char * WStringBinder::GetValue() {
    return value;
}

void WStringBinder::Bind(void * statement) {
    BindParam(statement);
}

signed short WStringBinder::GetReturnCode() {
    return returnCode;
}

string WStringBinder::GetErrorMessage() {
    return errorMessage;
}

bool WStringBinder::GetBindSuccess() {
    return bindSuccess;
}

WStringBinder::WStringBinder() {
    rawColumnType = 0;
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
    columns->push_back(arg);
}

bool WritingBinder::Bind(void * statement) {
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

signed short WritingBinder::GetReturnCode() {
    return returnCode;
}

string WritingBinder::GetErrorMessage() {
    return errorMessage;
}

vector<IBinder *> * WritingBinder::Get() {
    return columns;
}

WritingBinder::WritingBinder() {
    columns = new vector<IBinder *>();
    returnCode = 0;
}

WritingBinder::~WritingBinder() {
    for (size_t i = 0; i < columns->size(); i++) {
        delete columns->at(i);
    }
    delete columns;
}
