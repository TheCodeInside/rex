#include <rex/Graphics/Materials/MatteMaterial.hxx>
#include <rex/Graphics/Scene.hxx>
#include <rex/Utility/GC.hxx>

REX_NS_BEGIN

// create material
__device__ MatteMaterial::MatteMaterial()
    : MatteMaterial( Color::White(), 0.0f, 0.0f, MaterialType::Matte )
{
}

// create material w/ color
__device__ MatteMaterial::MatteMaterial( const Color& color )
    : MatteMaterial( color, 0.0f, 0.0f, MaterialType::Matte )
{
}

// create material w/ color, ambient coefficient, and diffuse coefficient
__device__ MatteMaterial::MatteMaterial( const Color& color, real32 ka, real32 kd )
    : MatteMaterial( color, ka, kd, MaterialType::Matte )
{
}

// create material w/ color, ambient coefficient, diffuse coefficient, and material type
__device__ MatteMaterial::MatteMaterial( const Color& color, real32 ka, real32 kd, MaterialType type )
    : Material( type ),
      _ambient( ka, color ),
      _diffuse( kd, color )
{
}

// destroy material
__device__ MatteMaterial::~MatteMaterial()
{
}

// get area light shaded color
__device__ Color MatteMaterial::AreaLightShade( ShadePoint& sp ) const
{
    // adapted from Suffern, 332
    vec3  wo    = -sp.Ray.Direction;
    Color color = _ambient.GetBHR( sp, wo ) * sp.AmbientLight->GetRadiance( sp );

    for ( uint32 i = 0; i < sp.LightCount; ++i )
    {
        const Light* light  = sp.Lights[ i ];
        vec3         wi     = light->GetLightDirection( sp );
        real32       angle  = glm::dot( sp.Normal, wi );
        
        if ( angle > 0.0f )
        {
            // calculate shadow information
            Ray   shadowRay   = Ray( sp.HitPoint, wi );
            bool  isInShadow  = light->CastsShadows() && light->IsInShadow( shadowRay, sp );
            Color diffuse     = _diffuse.GetBRDF( sp, wo, wi );
            Color shadowColor = diffuse * light->GetRadiance( sp ) * angle
                              * light->GetGeometricFactor( sp ) * light->GetGeometricArea( sp );

            // calculate the color with a branchless conditional
            color += Color::Lerp( shadowColor,
                                  Color::Black(),
                                  static_cast<real32>( isInShadow ) );
        }
    }

    return color;
}

// copy this material
__device__ Material* MatteMaterial::Copy() const
{
    // create the copy of the material
    MatteMaterial* mat = new MatteMaterial( _ambient.GetDiffuseColor(),
                                            _ambient.GetDiffuseCoefficient(),
                                            _diffuse.GetDiffuseCoefficient() );
    return mat;
}

// get ka
__device__ real32 MatteMaterial::GetAmbientCoefficient() const
{
    return _ambient.GetDiffuseCoefficient();
}

// get color
__device__ Color MatteMaterial::GetColor() const
{
    // both ambient and diffuse have the same color
    return _ambient.GetDiffuseColor();
}

// get kd
__device__ real32 MatteMaterial::GetDiffuseCoefficient() const
{
    return _diffuse.GetDiffuseCoefficient();
}

// get shaded color
__device__ Color MatteMaterial::Shade( ShadePoint& sp ) const
{
    // from Suffern, 271
    vec3  wo    = -sp.Ray.Direction;
    Color color = _ambient.GetBHR( sp, wo ) * sp.AmbientLight->GetRadiance( sp );

    // go through all of the lights in the scene
    for ( uint32 i = 0; i < sp.LightCount; ++i )
    {
        const Light*  light = sp.Lights[ i ];
        vec3          wi    = light->GetLightDirection( sp );
        real32        angle = glm::dot( sp.Normal, wi );


        if ( angle > 0.0f )
        {
            // calculate shadow information
            Ray   shadowRay   = Ray( sp.HitPoint, wi );
            bool  isInShadow  = light->CastsShadows() && light->IsInShadow( shadowRay, sp );
            Color diffuse     = _diffuse.GetBRDF( sp, wo, wi );
            Color shadowColor = diffuse * light->GetRadiance( sp ) * angle;

            // calculate the color with a branchless conditional
            color += Color::Lerp( shadowColor,
                                  Color::Black(),
                                  static_cast<real32>( isInShadow ) );
        }
    }

    return color;
}

// set ka
__device__ void MatteMaterial::SetAmbientCoefficient( real32 ka )
{
    _ambient.SetDiffuseCoefficient( ka );
}

// set color
__device__ void MatteMaterial::SetColor( const Color& color )
{
    _ambient.SetDiffuseColor( color );
    _diffuse.SetDiffuseColor( color );
}

// set color w/ components
__device__ void MatteMaterial::SetColor( real32 r, real32 g, real32 b )
{
    Color color = Color( r, g, b );
    SetColor( color );
}

// set kd
__device__ void MatteMaterial::SetDiffuseCoefficient( real32 kd )
{
    _diffuse.SetDiffuseCoefficient( kd );
}

REX_NS_END