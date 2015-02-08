#ifndef __REX_DEBUG_HXX
#define __REX_DEBUG_HXX
#pragma once

#pragma warning( push )
#pragma warning( disable : 4789 )

#include "Config.hxx"
#include <iostream>
#include <sstream>

/// <summary>
/// Custom assert macro for Rex.
/// </summary>
/// <param name="cond">The condition to check.</param>
/// <param name="message">The message to log if the condition fails.</param>
#define RexAssert(cond, message) { \
        bool __result = ( cond ); \
        if ( !__result ) { \
            rex::String __fname = __FILE__; \
            __fname = __fname.substr( __fname.find_last_of( '\\' ) + 1 ); \
            rex::WriteLine( "(", __fname, ":", __LINE__, ") Assertion failed: ", message, "\n  ", #cond, "\n" ); \
            __debugbreak(); \
                } \
        }

REX_NS_BEGIN

/// <summary>
/// Logs the given arguments.
/// </summary>
/// <param name="args">The arguments to log.</param>
template<typename ... Args> inline void WriteLine( const Args& ... args )
{
    std::stringstream stream;

    using List = int[];
    (void)List{ 0, ( (void)( stream << args ), 0 ) ... };

    std::cout << stream.str() << std::endl;
}

REX_NS_END

#pragma warning( pop )

#endif