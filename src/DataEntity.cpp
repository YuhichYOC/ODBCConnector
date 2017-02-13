/*
 * DataEntity.cpp
 *
 *  Created on: 2017/02/13
 *      Author: mssqlserver
 */

#include "stdafx.h" // ✝

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
}

NumberData::~NumberData() {
}

IData::DataType StringData::GetType() {
    return IData::DataType::STRING;
}

void StringData::SetData(char * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(const char * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

void StringData::SetData(const wchar_t * arg) {
    wc = wc.Value(arg);
    value = wc.ToChar();
}

char * StringData::GetData() {
    return value;
}

StringData::StringData() {
}

StringData::~StringData() {
}
