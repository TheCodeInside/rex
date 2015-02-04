#include "Vector3.hxx"
#include "Color.hxx"
#include <math.h>

REX_NS_BEGIN

// new 3D vector
Vector3::Vector3()
    : Vector3( 0.0, 0.0, 0.0 )
{
}

// new 3D vector
Vector3::Vector3( real64 all )
    : Vector3( all, all, all )
{
}

// new 3D vector
Vector3::Vector3( real64 x, real64 y, real64 z )
    : X( x ),
      Y( y ),
      Z( z )
{
}

// destroy 3D vector
Vector3::~Vector3()
{
    X = Y = Z = 0.0;
}

// get vector length
real64 Vector3::Length() const
{
    return sqrt( LengthSq() );
}

// get vector length squared
real64 Vector3::LengthSq() const
{
    return X * X + Y * Y + Z * Z;
}

// dot product of two vectors
real64 Vector3::Dot( const Vector3& v1, const Vector3& v2 )
{
    return v1.X * v2.X
         + v1.Y * v2.Y
         + v1.Z * v2.Z;
}

// dot product of two vectors
Vector3 Vector3::Cross( const Vector3& v1, const Vector3& v2 )
{
    return Vector3(
        v1.Y * v2.Z - v1.Z * v2.Y,
        v1.Z * v2.X - v1.X * v2.Z,
        v1.X * v2.Y - v1.Y * v2.X
    );
}

// normalize a vector
Vector3 Vector3::Normalize( const Vector3& vec )
{
    real64 invlen = 1.0 / vec.Length();
    return Vector3 (
        vec.X * invlen,
        vec.Y * invlen,
        vec.Z * invlen
    );
}

Vector3::operator Color() const
{
    return Color( real32( X ), real32( Y ), real32( Z ) );
}

bool Vector3::operator==( const Vector3& c ) const
{
    return X == c.X
        && Y == c.Y
        && Z == c.Z;
}

bool Vector3::operator!=( const Vector3& c ) const
{
    return X != c.X
        && Y != c.Y
        && Z != c.Z;
}

Vector3 Vector3::operator+( const Vector3& c ) const
{
    return Vector3(
        X + c.X,
        Y + c.Y,
        Z + c.Z
    );
}

Vector3 Vector3::operator-( const Vector3& c ) const
{
    return Vector3(
        X - c.X,
        Y - c.Y,
        Z - c.Z
    );
}

Vector3 Vector3::operator-() const
{
    return Vector3( -X, -Y, -Z );
}

Vector3& Vector3::operator+=( const Vector3& c )
{
    X += c.X;
    Y += c.Y;
    Z += c.Z;
    return *this;
}

Vector3& Vector3::operator-=( const Vector3& c )
{
    X -= c.X;
    Y -= c.Y;
    Z -= c.Z;
    return *this;
}

Vector3& Vector3::operator*=( real64 s )
{
    X *= s;
    Y *= s;
    Z *= s;
    return *this;
}

Vector3& Vector3::operator/=( real64 s )
{
    X /= s;
    Y /= s;
    Z /= s;
    return *this;
}

Vector3 operator*( const Vector3& v, real64 s )
{
    return Vector3(
        v.X * s,
        v.Y * s,
        v.Z * s
    );
}

Vector3 operator*( real64 s, const Vector3& v )
{
    return Vector3(
        v.X * s,
        v.Y * s,
        v.Z * s
    );
}

Vector3 operator/( const Vector3& v, real64 s )
{
    real64 invs = 1.0 / s;
    return Vector3(
        v.X * invs,
        v.Y * invs,
        v.Z * invs
    );
}

Vector3 operator/( real64 s, const Vector3& v )
{
    real64 invs = 1.0 / s;
    return Vector3(
        v.X * invs,
        v.Y * invs,
        v.Z * invs
    );
}

REX_NS_END