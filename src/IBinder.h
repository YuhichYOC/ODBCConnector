/*
 *
 * IBinder.h
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

#ifndef SRC_IBINDER_H_
#define SRC_IBINDER_H_

#include "WCharString.h"

class IBinder {
public:

    enum ColumnType {
        STRING, NUMBER,
    };

    virtual ColumnType GetType() = 0;

    virtual void SetIndex(int arg) = 0;

    virtual void SetType(signed short arg) = 0;

    virtual void SetSize(long arg) = 0;

    virtual void SetScale(signed short arg) = 0;

    virtual void Bind(void * statement) = 0;

    virtual signed short GetReturnCode() = 0;

    virtual string GetErrorMessage() = 0;

    virtual bool GetBindSuccess() = 0;

    virtual ~IBinder() {
    }
    ;
};

#endif /* SRC_IBINDER_H_ */
