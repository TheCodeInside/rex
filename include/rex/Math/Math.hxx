#pragma once

#include "../Config.hxx"

#define GLM_FORCE_CUDA
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

REX_NS_BEGIN

/// <summary>
/// Defines static math methods.
/// </summary>
class Math
{
    REX_STATIC_CLASS( Math )

public:
    /// <summary>
    /// Gets the constant Pi.
    /// </summary>
    __both__ static real32 Pi();

    /// <summary>
    /// Gets the constant Pi / 2.
    /// </summary>
    __both__ static real32 HalfPi();

    /// <summary>
    /// Gets the constant 2 * Pi.
    /// </summary>
    __both__ static real32 TwoPi();

    /// <summary>
    /// Gets the constant Pi / 180.
    /// </summary>
    __both__ static real32 PiOver180();

    /// <summary>
    /// Gets the constant 1 / Pi.
    /// </summary>
    __both__ static real32 InvPi();

    /// <summary>
    /// Gets the constant 1 / ( 2 * Pi ).
    /// </summary>
    __both__ static real32 InvTwoPi();

    /// <summary>
    /// Gets a really small value.
    /// </summary>
    __both__ static real32 Epsilon();

    /// <summary>
    /// Gets a really big value.
    /// </summary>
    __both__ static real32 HugeValue();

    /// <summary>
    /// Returns the floor of the given value.
    /// </summary>
    /// <param name="value">The value.</param>
    __both__ static int32 Floor( real32 value );

    /// <summary>
    /// Returns the ceiling of the given value.
    /// </summary>
    /// <param name="value">The value.</param>
    __both__ static int32 Ceiling( real32 value );

    /// <summary>
    /// Returns the floor of the given value.
    /// </summary>
    /// <param name="value">The value.</param>
    __both__ static int64 Floor( real64 value );

    /// <summary>
    /// Returns the ceiling of the given value.
    /// </summary>
    /// <param name="value">The value.</param>
    __both__ static int64 Ceiling( real64 value );

    /// <summary>
    /// Rounds the given value.
    /// </summary>
    /// <param name="value">The value to round.</param>
    __both__ static int32 Round( real32 value );

    /// <summary>
    /// Rounds the given value.
    /// </summary>
    /// <param name="value">The value to round.</param>
    __both__ static int64 Round( real64 value );

    /// <summary>
    /// Transforms the given 3-dimensional vector by the given matrix.
    /// </summary>
    /// <param name="vec">The vector.</param>
    /// <param name="mat">The matrix.</param>
    __both__ static vec3 Transform( const vec3& vec, const mat4& mat );

    /// <summary>
    /// Returns the absolute value of the given value.
    /// </summary>
    /// <param name="value">The value.</param>
    template<class T> __both__ static T Abs( T value );

    /// <summary>
    /// Returns the minimum of the two given values.
    /// </summary>
    /// <param name="a">The first value.</param>
    /// <param name="b">The second value.</param>
    template<class T> __both__ static T Min( T a, T b );

    /// <summary>
    /// Returns the maximum of the two given values.
    /// </summary>
    /// <param name="a">The first value.</param>
    /// <param name="b">The second value.</param>
    template<class T> __both__ static T Max( T a, T b );

    /// <summary>
    /// Clamps the given value to the given min and max.
    /// </summary>
    /// <param name="value">The value to clamp</param>
    /// <param name="min">The minimum.</param>
    /// <param name="max">The maximum.</param>
    template<class T> __both__ static T Clamp( T value, T min, T max );

    /// <summary>
    /// Maps the given value in the first range to a value in the second range.
    /// </summary>
    /// <param name="value">The value to map.</param>
    /// <param name="min1">The minimum for the first range.</param>
    /// <param name="max1">The maximum for the first range.</param>
    /// <param name="min2">The minimum for the second range.</param>
    /// <param name="max2">The maximum for the second range.</param>
    template<class T> __both__ static T Map( T value, T min1, T max1, T min2, T max2 );

    /// <summary>
    /// Linear interpolates between two values.
    /// </summary>
    /// <param name="v0">The first value.</param>
    /// <param name="v1">The second value.</param>
    /// <param name="t">The percentage to interpolate.</param>
    template<class T> __both__ static T Lerp( T v0, T v1, T t );
};

REX_NS_END

#include "Math.inl"