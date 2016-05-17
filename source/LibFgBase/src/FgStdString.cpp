//
// Copyright (c) 2015 Singular Inversions Inc. (facegen.com)
// Use, modification and distribution is subject to the MIT License,
// see accompanying file LICENSE.txt or facegen.com/base_library_license.txt
//
// Authors:     Andrew Beatty
// Created:     Dec 29, 2004
//

#include "stdafx.h"

#include "FgStdString.hpp"
#include "FgTypes.hpp"

using namespace std;

vector<string>
fgWhiteBreak(const string & str)
{
    vector<string>  retval;
    bool            symbolFlag = false,
                    quoteFlag = false;
    string          currSymbol;
    for (size_t ii=0; ii<str.size(); ++ii)
    {
        if (quoteFlag)
        {
            if (str[ii] == '\"')
            {
                retval.push_back(currSymbol);
                currSymbol.clear();
                quoteFlag = false;
            }
            else
                currSymbol.push_back(str[ii]);
        }
        else if (isspace(str[ii]))
        {
            if (symbolFlag)
            {
                retval.push_back(currSymbol);
                currSymbol.clear();
                symbolFlag = false;
            }
        }
        else if (str[ii] == '\"')
        {
            if (symbolFlag)
            {
                retval.push_back(currSymbol);
                currSymbol.clear();
            }
            quoteFlag = true;
        }
        else
        {
            currSymbol.push_back(str[ii]);
            symbolFlag = true;
        }
    }
    if (symbolFlag)
        retval.push_back(currSymbol);
    return retval;
}

string
fgToFixed(double val,uint fractionalDigits)
{
    ostringstream   os;
    os << std::fixed << std::setprecision(fractionalDigits) << val;
    return os.str();
}

string
fgToPercent(double val,uint fractionalDigits)
{return fgToFixed(val*100.0,fractionalDigits) + "%"; }

std::string
fgToLower(const std::string & s)
{
    string  retval;
    retval.resize(s.length());
    std::transform(s.begin(),s.end(),retval.begin(),::tolower);
    return retval;
}

std::string
fgToUpper(const std::string & s)
{
    string  retval;
    retval.resize(s.length());
    std::transform(s.begin(),s.end(),retval.begin(),::toupper);
    return retval;
}

std::vector<string>
fgSplitAtSeparators(
    const std::string & str,
    char                sep)
{
    vector<string>  ret;
    string          tmp;
    string::const_iterator  it = str.begin();
    while (it != str.end())
    {
        if (*it == sep)
        {
            ret.push_back(tmp);
            tmp.clear();
            it++;
        }
        else
            tmp += *it++;
    }
    if (!tmp.empty())
        ret.push_back(tmp);
    return ret;
}

bool
fgStartsWith(
    const std::string & str,
    const std::string & pattern)
{
    if(pattern.length() > str.length())
        return false;
    string::const_iterator  sit = str.begin(),
                            pit = pattern.begin();
    while (pit != pattern.end())
        if (*sit++ != *pit++)
            return false;
    return true;
}

bool
fgEndsWith(
    const std::string & str,
    const std::string & pattern)
{
    if (pattern.length() > str.length())
        return false;
    string::const_iterator  sit = str.end(),
                            pit = pattern.end();
    // C++ standard allows decrementing end() to give valid element for vector:
    while (pit != pattern.begin())
        if (*(--sit) != *(--pit))
            return false;
    return true;
}

std::string
fgReplace(
    const std::string & str,
    char                orig,
    char                repl)
{
    std::string     ret = str;
    for (size_t ii=0; ii<ret.size(); ++ii)
        if (ret[ii] == orig)
            ret[ii] = repl;
    return ret;
}

string
fgPad(const string & str,size_t len,char ch)
{
    string  ret = str;
    if (len > str.length())
        ret.resize(len,ch);
    return ret;
}

string
fgConcat(const vector<string> & strings,const string & separator)
{
    string      ret;
    for (size_t ii=0; ii<strings.size(); ++ii) {
        ret += strings[ii];
        if (ii < strings.size()-1)
            ret += separator;
    }
    return ret;
}
