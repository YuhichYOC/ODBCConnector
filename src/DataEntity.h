/*
 *
 * DataEntity.h
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

#ifndef SRC_DATAENTITY_H_
#define SRC_DATAENTITY_H_

#include "WCharString.h"

class IData {
public:

    enum DataType {
        STRING, NUMBER,
    };

    virtual DataType GetType() = 0;

    virtual ~IData() {
    }
    ;
};

class NumberData: public IData {
private:

    int value;

public:

    IData::DataType GetType();

    void SetData(int value);

    int GetData();

    int * GetDataAddress();

    NumberData();

    ~NumberData();
};

class StringData: public IData {
private:

    char * value;

    WCharString wc;

public:

    IData::DataType GetType();

    void SetData(char * arg);

    void SetData(const char * arg);

    void SetData(wchar_t * arg);

    void SetData(const wchar_t * arg);

    char * GetData();

    StringData();

    ~StringData();
};

#endif /* SRC_DATAENTITY_H_ */
