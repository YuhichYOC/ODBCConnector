/*
 *
 * DataEntity.cpp
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

#include "DataEntity.h"

IData::DataType NumberData::GetType() {
    return IData::DataType::NUMBER;
}

void NumberData::SetData(int arg) {
    value = arg;
}

int NumberData::GetData() {
    return value;
}

int * NumberData::GetDataAddress() {
    return &value;
}

NumberData::NumberData() {
    value = 0;
}

NumberData::~NumberData() {
}

IData::DataType StringData::GetType() {
    return IData::DataType::STRING;
}

void StringData::SetData(char * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void StringData::SetData(const char * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void StringData::SetData(wchar_t * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

void StringData::SetData(const wchar_t * arg) {
    wc = wc.Value(arg);
    int valueSize = wc.ToString().length();
    value = new char[valueSize];
    for (int i = 0; i < valueSize; i++) {
        value[i] = wc.ToString().c_str()[i];
    }
}

char * StringData::GetData() {
    return value;
}

StringData::StringData() {
    value = new char();
}

StringData::~StringData() {
}
