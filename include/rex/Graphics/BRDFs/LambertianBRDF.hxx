#pragma once

#include "BRDF.hxx"

REX_NS_BEGIN

/// <summary>
/// Defines a Lambertian bidirectional reflectance distribution function.
/// </summary>
class LambertianBRDF : public BRDF
{
    Color  _color;
    real32 _coefficient;

public:
    /// <summary>
    /// Creates a new Lambertian BRDF.
    /// </summary>
    __device__ LambertianBRDF();

    /// <summary>
    /// Creates a new Lambertian BRDF.
    /// </summary>
    /// <param name="kd">The diffuse reflection coefficient.</param>
    /// <param name="dc">The diffuse color.</param>
    __device__ LambertianBRDF( real32 kd, const Color& dc );

    /// <summary>
    /// Destroys this Lambertian BRDF.
    /// </summary>
    __device__ ~LambertianBRDF();

    /// <summary>
    /// Gets the bi-hemispherical reflectance. (rho in Suffern.)
    /// </summary>
    /// <param name="sp">The shade point information.</param>
    /// <param name="wo">The outgoing, reflected light direction.</param>
    __device__ virtual Color GetBHR( const ShadePoint& sp, const vec3& wo ) const;

    /// <summary>
    /// Gets the BRDF itself. (f in Suffern.)
    /// </summary>
    /// <param name="sp">The shade point information.</param>
    /// <param name="wo">The outgoing, reflected light direction.</param>
    /// <param name="wi">The incoming light direction.</param>
    __device__ virtual Color GetBRDF( const ShadePoint& sp, const vec3& wo, const vec3& wi ) const;

    /// <summary>
    /// Gets the color.
    /// </summary>
    __device__ Color GetDiffuseColor() const;

    /// <summary>
    /// Gets the reflection coefficient.
    /// </summary>
    __device__ real32 GetDiffuseCoefficient() const;

    /// <summary>
    /// Sets the color.
    /// </summary>
    /// <param name="color">The new color.</param>
    __device__ void SetDiffuseColor( const Color& color );

    /// <summary>
    /// Sets the reflection coefficient.
    /// </summary>
    /// <param name="coeff">The new reflection coefficient.</param>
    __device__ void SetDiffuseCoefficient( real32 coeff );
};

REX_NS_END