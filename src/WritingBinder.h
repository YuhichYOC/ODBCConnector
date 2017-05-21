/*
 *
 * WritingBinder.h
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

#ifndef SRC_WRITINGBINDER_H_
#define SRC_WRITINGBINDER_H_

#include <string>
#include <vector>

#include <sql.h>
#include <sqlext.h>

#include "IBinder.h"

class WNumberBinder: public IBinder {
private:

    SQLSMALLINT rawColumnType;

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

    void SetType(SQLSMALLINT arg);

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(SQLLEN arg);

    SQLLEN GetSize();

    void SetScale(SQLSMALLINT arg);

    SQLSMALLINT GetScale();

    void SetValue(int arg);

    int GetValue();

    int * GetValueAddress();

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    WNumberBinder();

    ~WNumberBinder();
};

class WStringBinder: public IBinder {
private:

    SQLSMALLINT rawColumnType;

    int index;

    SQLLEN size;

    SQLSMALLINT scale;

    char * value;

    WCharString wc;

    SQLLEN nullIndicator;

    SQLRETURN returnCode;

    string errorMessage;

    bool bindSuccess;

    void BindParam(SQLHANDLE statement);

public:

    void SetType(SQLSMALLINT arg);

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

    char * GetValue();

    void Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    WStringBinder();

    ~WStringBinder();
};

class WritingBinder {
private:

    vector<IBinder *> * columns;

    SQLRETURN returnCode;

    string errorMessage;

public:

    void AddBinder(IBinder * arg);

    bool Bind(SQLHANDLE statement);

    SQLRETURN GetReturnCode();

    string GetErrorMessage();

    vector<IBinder *> * Get();

    WritingBinder();

    ~WritingBinder();
};
#endif /* SRC_WRITINGBINDER_H_ */
