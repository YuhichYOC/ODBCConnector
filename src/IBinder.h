/*
 * IBinder.h
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#ifndef SRC_IBINDER_H_
#define SRC_IBINDER_H_

#include "stdafx.h" // ✝

#include "WCharString.h"

class IBinder {
public:

    enum ColumnType {
        STRING, NUMBER,
    };

    virtual ColumnType GetType() = 0;

    virtual void SetIndex(int arg) = 0;

    virtual void SetType(SQLSMALLINT arg) = 0;

    virtual void SetSize(SQLLEN arg) = 0;

    virtual void SetScale(SQLSMALLINT arg) = 0;

    virtual void Bind(SQLHANDLE statement) = 0;

    virtual SQLRETURN GetReturnCode() = 0;

    virtual string GetErrorMessage() = 0;

    virtual bool GetBindSuccess() = 0;
};

#endif /* SRC_IBINDER_H_ */
