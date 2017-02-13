/*
 * DataEntity.h
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#ifndef SRC_DATAENTITY_H_
#define SRC_DATAENTITY_H_

#include "stdafx.h" // ✝

#include "WCharString.h"

class IData {
public:

    enum DataType {
        STRING, NUMBER,
    };

    virtual DataType GetType() = 0;
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
