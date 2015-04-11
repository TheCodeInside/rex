#include <rex/Graphics/Lights/Light.hxx>

REX_NS_BEGIN

// create light
Light::Light()
    : _castShadows( false ),
      _dThis( nullptr )
{
}

// destroy light
Light::~Light()
{
    _castShadows = 0;
}

// check if casts shadows
bool Light::CastsShadows() const
{
    return _castShadows;
}

// set whether to cast shadows
void Light::SetCastShadows( bool value )
{
    _castShadows = value;
}

REX_NS_END