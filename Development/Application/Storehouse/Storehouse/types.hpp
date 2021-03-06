#pragma once
#ifndef types_hpp__
#define types_hpp__

#include <string>

// Define tstring
#if UNICODE
    typedef wchar_t tchar_t;
    typedef ::std::wstring tstring;
    typedef ::std::wstringstream tstringstream;
#   ifndef _T
#      define _T(x)      L ## x
#   endif
#else
    typedef char tchar_t;
    typedef ::std::string tstring;
    typedef ::std::stringstream tstringstream;
#   ifndef _T
#      define _T(x)      x
#   endif
#endif

// [ Debugging defines
// helper
#define _TT(x) _T(x)
// File name
#define __TFILE__ _TT(__FILE__)
// Function name
#define __TFUNCTION__ _TT(__FUNCTION__)
// ]

#endif // types_hpp__
