/*
 *
 * WCharString.h
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

#ifndef WCHARSTRING_H_
#define WCHARSTRING_H_

#include <codecvt>
#include <iostream>
#include <locale>
#include <memory>
#include <string>

using namespace std;

class WCharString {
private:

    string v;

    string newvfromws(wstring arg);

    wstring wsfromv();

    int maxNullPosition;

    void Assign(char * arg);

    void Assign(unsigned char * arg);

    void Assign(wchar_t * arg);

    void Assign(string arg);

    void Assign(string * arg);

    void Assign(const char * arg);

    void Assign(const unsigned char * arg);

    void Assign(const wchar_t * arg);

    void Assign(const string * arg);

public:

    WCharString Append(char * arg);

    WCharString Append(unsigned char * arg);

    WCharString Append(wchar_t * arg);

    WCharString Append(string arg);

    WCharString Append(string * arg);

    WCharString Append(unique_ptr<char> arg);

    WCharString Append(unique_ptr<wchar_t> arg);

    WCharString Append(const char * arg);

    WCharString Append(const unsigned char * arg);

    WCharString Append(const wchar_t * arg);

    WCharString Append(const string * arg);

    WCharString Value(char * arg);

    WCharString Value(unsigned char * arg);

    WCharString Value(wchar_t * arg);

    WCharString Value(string arg);

    WCharString Value(string * arg);

    WCharString Value(unique_ptr<char> arg);

    WCharString Value(unique_ptr<wchar_t> arg);

    WCharString Value(const char * arg);

    WCharString Value(const unsigned char * arg);

    WCharString Value(const wchar_t * arg);

    WCharString Value(const string * arg);

    unique_ptr<char> ToChar();

    unique_ptr<unsigned char> ToUChar();

    unique_ptr<wchar_t> ToWChar();

    string ToString();

    void SetMaxNullPosition(int arg);

    int NullPosition(char * arg);

    int NullPosition(unsigned char * arg);

    int NullPosition(wchar_t * arg);

    int NullPosition(const char * arg);

    int NullPosition(const unsigned char * arg);

    int NullPosition(const wchar_t * arg);

    bool WChar_tStartsWith(wchar_t * arg1eval, string arg2test);

    string SysErrMessage();

    WCharString();

    ~WCharString();

private:

    const char * ERROR_0 = "Success";
    const char * ERROR_1 = "Operation not permitted";
    const char * ERROR_2 = "No such file or directory";
    const char * ERROR_3 = "No such process";
    const char * ERROR_4 = "Interrupted system call";
    const char * ERROR_5 = "Input/output error";
    const char * ERROR_6 = "No such device or address";
    const char * ERROR_7 = "Argument list too long";
    const char * ERROR_8 = "Exec format error";
    const char * ERROR_9 = "Bad file descriptor";
    const char * ERROR_10 = "No child processes";
    const char * ERROR_11 = "Resource temporarily unavailable";
    const char * ERROR_12 = "Cannot allocate memory";
    const char * ERROR_13 = "Permission denied";
    const char * ERROR_14 = "Bad address";
    const char * ERROR_15 = "Block device required";
    const char * ERROR_16 = "Device or resource busy";
    const char * ERROR_17 = "File exists";
    const char * ERROR_18 = "Invalid cross-device link";
    const char * ERROR_19 = "No such device";
    const char * ERROR_20 = "Not a directory";
    const char * ERROR_21 = "Is a directory";
    const char * ERROR_22 = "Invalid argument";
    const char * ERROR_23 = "Too many open files in system";
    const char * ERROR_24 = "Too many open files";
    const char * ERROR_25 = "Inappropriate ioctl for device";
    const char * ERROR_26 = "Text file busy";
    const char * ERROR_27 = "File too large";
    const char * ERROR_28 = "No space left on device";
    const char * ERROR_29 = "Illegal seek";
    const char * ERROR_30 = "Read-only file system";
    const char * ERROR_31 = "Too many links";
    const char * ERROR_32 = "Broken pipe";
    const char * ERROR_33 = "Numerical argument out of domain";
    const char * ERROR_34 = "Numerical result out of range";
    const char * ERROR_35 = "Resource deadlock avoided";
    const char * ERROR_36 = "File name too long";
    const char * ERROR_37 = "No locks available";
    const char * ERROR_38 = "Function not implemented";
    const char * ERROR_39 = "Directory not empty";
    const char * ERROR_40 = "Too many levels of symbolic links";
    const char * ERROR_41 = "Unknown error 41";
    const char * ERROR_42 = "No message of desired type";
    const char * ERROR_43 = "Identifier removed";
    const char * ERROR_44 = "Channel number out of range";
    const char * ERROR_45 = "Level 2 not synchronized";
    const char * ERROR_46 = "Level 3 halted";
    const char * ERROR_47 = "Level 3 reset";
    const char * ERROR_48 = "Link number out of range";
    const char * ERROR_49 = "Protocol driver not attached";
    const char * ERROR_50 = "No CSI structure available";
    const char * ERROR_51 = "Level 2 halted";
    const char * ERROR_52 = "Invalid exchange";
    const char * ERROR_53 = "Invalid request descriptor";
    const char * ERROR_54 = "Exchange full";
    const char * ERROR_55 = "No anode";
    const char * ERROR_56 = "Invalid request code";
    const char * ERROR_57 = "Invalid slot";
    const char * ERROR_58 = "Unknown error 58";
    const char * ERROR_59 = "Bad font file format";
    const char * ERROR_60 = "Device not a stream";
    const char * ERROR_61 = "No data available";
    const char * ERROR_62 = "Timer expired";
    const char * ERROR_63 = "Out of streams resources";
    const char * ERROR_64 = "Machine is not on the network";
    const char * ERROR_65 = "Package not installed";
    const char * ERROR_66 = "Object is remote";
    const char * ERROR_67 = "Link has been severed";
    const char * ERROR_68 = "Advertise error";
    const char * ERROR_69 = "Srmount error";
    const char * ERROR_70 = "Communication error on send";
    const char * ERROR_71 = "Protocol error";
    const char * ERROR_72 = "Multihop attempted";
    const char * ERROR_73 = "RFS specific error";
    const char * ERROR_74 = "Bad message";
    const char * ERROR_75 = "Value too large for defined data type";
    const char * ERROR_76 = "Name not unique on network";
    const char * ERROR_77 = "File descriptor in bad state";
    const char * ERROR_78 = "Remote address changed";
    const char * ERROR_79 = "Can not access a needed shared library";
    const char * ERROR_80 = "Accessing a corrupted shared library";
    const char * ERROR_81 = ".lib section in a.out corrupted";
    const char * ERROR_82 = "Attempting to link in too many shared libraries";
    const char * ERROR_83 = "Cannot exec a shared library directly";
    const char * ERROR_84 = "Invalid or incomplete multibyte or wide character";
    const char * ERROR_85 = "Interrupted system call should be restarted";
    const char * ERROR_86 = "Streams pipe error";
    const char * ERROR_87 = "Too many users";
    const char * ERROR_88 = "Socket operation on non-socket";
    const char * ERROR_89 = "Destination address required";
    const char * ERROR_90 = "Message too long";
    const char * ERROR_91 = "Protocol wrong type for socket";
    const char * ERROR_92 = "Protocol not available";
    const char * ERROR_93 = "Protocol not supported";
    const char * ERROR_94 = "Socket type not supported";
    const char * ERROR_95 = "Operation not supported";
    const char * ERROR_96 = "Protocol family not supported";
    const char * ERROR_97 = "Address family not supported by protocol";
    const char * ERROR_98 = "Address already in use";
    const char * ERROR_99 = "Cannot assign requested address";
    const char * ERROR_100 = "Network is down";
    const char * ERROR_101 = "Network is unreachable";
    const char * ERROR_102 = "Network dropped connection on reset";
    const char * ERROR_103 = "Software caused connection abort";
    const char * ERROR_104 = "Connection reset by peer";
    const char * ERROR_105 = "No buffer space available";
    const char * ERROR_106 = "Transport endpoint is already connected";
    const char * ERROR_107 = "Transport endpoint is not connected";
    const char * ERROR_108 = "Cannot send after transport endpoint shutdown";
    const char * ERROR_109 = "Too many references: cannot splice";
    const char * ERROR_110 = "Connection timed out";
    const char * ERROR_111 = "Connection refused";
    const char * ERROR_112 = "Host is down";
    const char * ERROR_113 = "No route to host";
    const char * ERROR_114 = "Operation already in progress";
    const char * ERROR_115 = "Operation now in progress";
    const char * ERROR_116 = "Stale file handle";
    const char * ERROR_117 = "Structure needs cleaning";
    const char * ERROR_118 = "Not a XENIX named type file";
    const char * ERROR_119 = "No XENIX semaphores available";
    const char * ERROR_120 = "Is a named type file";
    const char * ERROR_121 = "Remote I/O error";
    const char * ERROR_122 = "Disk quota exceeded";
    const char * ERROR_123 = "No medium found";
    const char * ERROR_124 = "Wrong medium type";
    const char * ERROR_125 = "Operation canceled";
    const char * ERROR_126 = "Required key not available";
    const char * ERROR_127 = "Key has expired";
    const char * ERROR_128 = "Key has been revoked";
    const char * ERROR_129 = "Key was rejected by service";
    const char * ERROR_130 = "Owner died";
    const char * ERROR_131 = "State not recoverable";
    const char * ERROR_132 = "Operation not possible due to RF-kill";
    const char * ERROR_133 = "Memory page has hardware error";
};

#endif /* WCHARSTRING_H_ */
