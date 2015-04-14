#pragma once

#include "Geometry.hxx"
#include "../../Math/Vector3.hxx"

// TODO : Make get and set methods for the radius and center ?

REX_NS_BEGIN

/// <summary>
/// Defines a sphere.
/// </summary>
class Sphere : public Geometry
{
    REX_IMPLEMENT_DEVICE_MEM_OPS()

    Vector3 _center;
    real_t  _radius;

public:
    /// <summary>
    /// Creates a new sphere.
    /// </summary>
    /// <param name="material">The material to use with this sphere.</param>
    template<typename T> __device__ Sphere( const T& material );

    /// <summary>
    /// Creates a new sphere.
    /// </summary>
    /// <param name="material">The material to use with this sphere.</param>
    /// <param name="center">The initial center of the sphere.</param>
    /// <param name="radius">The initial radius of the sphere.</param>
    template<typename T> __device__ Sphere( const T& material, const Vector3& center, real_t radius );

    /// <summary>
    /// Destroys this sphere.
    /// </summary>
    __device__ virtual ~Sphere();

    /// <summary>
    /// Gets this sphere's bounds.
    /// </summary>
    __device__ virtual BoundingBox GetBounds() const;

    /// <summary>
    /// Checks to see if the given ray hits this sphere. If it does, the shading
    /// point information is populated and the collision distance is recorded.
    /// </summary>
    /// <param name="ray">The ray to check.</param>
    /// <param name="tmin">The distance to intersection.</param>
    /// <param name="sp">The shading point information.</param>
    __device__ virtual bool Hit( const Ray& ray, real_t& tmin, ShadePoint& sp ) const;

    /// <summary>
    /// Performs the same thing as a normal ray hit, but for shadow rays.
    /// </summary>
    /// <param name="ray">The ray to check.</param>
    /// <param name="tmin">The distance to intersection.</param>
    __device__ virtual bool ShadowHit( const Ray& ray, real_t& tmin ) const;
};

REX_NS_END

#include "Sphere.inl"