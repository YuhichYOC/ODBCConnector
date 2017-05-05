/*
 *
 * ReadingBinder.h
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

#ifndef SRC_READINGBINDER_H_
#define SRC_READINGBINDER_H_

#include <string>
#include <vector>

#include <sql.h>
#include <sqlext.h>

#include "IBinder.h"

class RNumberBinder: public IBinder {
private:

    signed short rawColumnType;

    int index;

    long size;

    signed short scale;

    int value;

    long nullIndicator;

    signed short returnCode;

    string errorMessage;

    bool bindSuccess;

public:

    void SetType(signed short arg);

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(long arg);

    long GetSize();

    void SetScale(signed short arg);

    signed short GetScale();

    void SetValue(int arg);

    int GetValue();

    int * GetValueAddress();

    void Bind(void * statement);

    signed short GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    RNumberBinder();

    ~RNumberBinder();
};

class RStringBinder: public IBinder {
private:

    signed short rawColumnType;

    int index;

    long size;

    signed short scale;

    wchar_t * value;

    WCharString wc;

    long nullIndicator;

    signed short returnCode;

    string errorMessage;

    bool bindSuccess;

public:

    void SetType(signed short arg);

    IBinder::ColumnType GetType();

    void SetIndex(int arg);

    int GetIndex();

    void SetSize(long arg);

    long GetSize();

    void SetScale(signed short arg);

    signed short GetScale();

    void SetValue(char * arg);

    void SetValue(const char * arg);

    void SetValue(wchar_t * arg);

    void SetValue(const wchar_t * arg);

    wchar_t * GetValue();

    void Bind(void * statement);

    signed short GetReturnCode();

    string GetErrorMessage();

    bool GetBindSuccess();

    RStringBinder();

    ~RStringBinder();
};

class ReadingBinder {
private:

    vector<IBinder *> * columns;

    signed short returnCode;

    string errorMessage;

public:

    void AddBinder(IBinder * arg);

    bool Bind(void * statement);

    signed short GetReturnCode();

    string GetErrorMessage();

    vector<IBinder *> * Get();

    ReadingBinder();

    ~ReadingBinder();
};

#endif /* SRC_READINGBINDER_H_ */
