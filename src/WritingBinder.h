/*
 * WritingBinder.h
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#ifndef SRC_WRITINGBINDER_H_
#define SRC_WRITINGBINDER_H_

#include "stdafx.h" // ✝

#include "WCharString.h"

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
