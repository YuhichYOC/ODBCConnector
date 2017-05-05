/*
 *
 * WCharString.cpp
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

#include "WCharString.h"

string WCharString::newvfromws(wstring arg) {
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cu8;
    return cu8.to_bytes(arg);
}

wstring WCharString::wsfromv() {
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cu8;
    return cu8.from_bytes(v);
}

void WCharString::Assign(char * arg) {
    v.assign(arg);
}

void WCharString::Assign(unsigned char * arg) {
    int nullPosition = NullPosition(arg);
    unique_ptr<char> carg(new char[nullPosition]);
    for (int i = 0; i < nullPosition; i++) {
        carg.get()[i] = arg[i];
    }
    v.assign(carg.get());
}

void WCharString::Assign(wchar_t * arg) {
    wstring warg(arg);
    v.assign(newvfromws(warg));
}

void WCharString::Assign(string arg) {
    v.assign(arg);
}

void WCharString::Assign(string * arg) {
    v.assign(*arg);
}

void WCharString::Assign(const char * arg) {
    v.assign(arg);
}

void WCharString::Assign(const unsigned char * arg) {
    int nullPosition = NullPosition(arg);
    unique_ptr<char> carg(new char[nullPosition]);
    for (int i = 0; i < nullPosition; i++) {
        carg.get()[i] = arg[i];
    }
    v.assign(carg.get());
}

void WCharString::Assign(const wchar_t * arg) {
    wstring warg(arg);
    v.assign(newvfromws(warg));
}

void WCharString::Assign(const string * arg) {
    v.assign(*arg);
}

WCharString WCharString::Append(char * arg) {
    v.append(arg);
    return *this;
}

WCharString WCharString::Append(unsigned char * arg) {
    int nullPosition = NullPosition(arg);
    unique_ptr<char> carg(new char[nullPosition]);
    for (int i = 0; i < nullPosition; i++) {
        carg.get()[i] = arg[i];
    }
    v.append(carg.get());
    return *this;
}

WCharString WCharString::Append(wchar_t * arg) {
    wstring warg(arg);
    v.append(newvfromws(warg));
    return *this;
}

WCharString WCharString::Append(string arg) {
    v.append(arg);
    return *this;
}

WCharString WCharString::Append(string * arg) {
    v.append(*arg);
    return *this;
}

WCharString WCharString::Append(const char * arg) {
    v.append(arg);
    return *this;
}

WCharString WCharString::Append(const unsigned char * arg) {
    int nullPosition = NullPosition(arg);
    unique_ptr<char> carg(new char[nullPosition]);
    for (int i = 0; i < nullPosition; i++) {
        carg.get()[i] = arg[i];
    }
    v.append(carg.get());
    return *this;
}

WCharString WCharString::Append(const wchar_t * arg) {
    wstring warg(arg);
    v.append(newvfromws(warg));
    return *this;
}

WCharString WCharString::Append(const string * arg) {
    v.append(*arg);
    return *this;
}

WCharString WCharString::Value(char * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(unsigned char * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(wchar_t * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(string arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(string * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const char * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const unsigned char * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const wchar_t * arg) {
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const string * arg) {
    Assign(arg);
    return *this;
}

unique_ptr<unsigned char> WCharString::ToUChar() {
    unique_ptr<unsigned char> ret(new unsigned char[v.length()]);
    for (size_t i = 0; i < v.length(); i++) {
        ret.get()[i] = v.c_str()[i];
    }
    return ret;
}

unique_ptr<wchar_t> WCharString::ToWChar() {
    unique_ptr<wchar_t> ret(new wchar_t[v.size()]);
    wstring wv = wsfromv();
    for (size_t i = 0; i < v.size(); i++) {
        ret.get()[i] = wv.c_str()[i];
    }
    return ret;
}

string WCharString::ToString() {
    return v;
}

void WCharString::SetMaxNullPosition(int arg) {
    maxNullPosition = arg;
}

int WCharString::NullPosition(char * arg) {
    int ret = 0;
    while (arg[ret] != '\0') {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

int WCharString::NullPosition(unsigned char * arg) {
    int ret = 0;
    while (arg[ret] != '\0') {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

int WCharString::NullPosition(wchar_t * arg) {
    int ret = 0;
    while (arg[ret] != (wchar_t) ('\0')) {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

int WCharString::NullPosition(const char * arg) {
    int ret = 0;
    while (arg[ret] != '\0') {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

int WCharString::NullPosition(const unsigned char * arg) {
    int ret = 0;
    while (arg[ret] != '\0') {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

int WCharString::NullPosition(const wchar_t * arg) {
    int ret = 0;
    while (arg[ret] != (wchar_t) ('\0')) {
        ret++;
        if (ret > maxNullPosition) {
            return maxNullPosition;
        }
    }
    return ret;
}

bool WCharString::WChar_tStartsWith(wchar_t * arg1eval, string arg2test) {
    wstring warg = arg1eval;
    if (warg.length() < arg2test.length()) {
        return false;
    }
    string sarg = newvfromws(warg);
    for (size_t i = 0; i < arg2test.length(); i++) {
        if (sarg.at(i) != arg2test.at(i)) {
            return false;
        }
    }
    return true;
}

string WCharString::SysErrMessage() {
    int index = errno;
    const char * ret = ERROR_0;
    for (int i = 0; i < index; i++) {
        while (ret[0] != '\0') {
            ret++;
        }
        ret++;
    }
    return string(ret);
}

WCharString::WCharString() {
    maxNullPosition = 1024;
}

WCharString::~WCharString() {
}
