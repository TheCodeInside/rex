#include "MultiJitteredSampler.hxx"
#include "Random.hxx"

REX_NS_BEGIN

// new multi-jittered sampler
MultiJitteredSampler::MultiJitteredSampler()
    : Sampler()
{
}

// new multi-jittered sampler w/ samples
MultiJitteredSampler::MultiJitteredSampler( int32 samples )
    : Sampler( samples )
{
}

// new multi-jittered sampler w/ samples and sets
MultiJitteredSampler::MultiJitteredSampler( int32 samples, int32 sets )
    : Sampler( samples, sets )
{
}

// destroy multi-jittered sampler
MultiJitteredSampler::~MultiJitteredSampler()
{
}

// generate samples
void MultiJitteredSampler::GenerateSamples()
{
    // adapted from code provided by Kevin Suffern in bare-bones ray tracer

    const int32 n          = (int32)sqrt( (real32)_sampleCount );
    const real32 cellWidth = 1.0f / _sampleCount;

    _unitSquareSamples.clear();

    // create some dummy points
    const int32 maxPoints = _sampleCount * _setCount;
    for ( int32 i = 0; i < maxPoints; ++i )
    {
        _unitSquareSamples.push_back( Vector2() );
    }

    // now distribute the points in the initial patterns
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < n; ++i )
        {
            for ( int32 j = 0; j < n; ++j )
            {
                const int32 index = i * n + j + set * _sampleCount;
                _unitSquareSamples[ index ].X = ( i * n + j ) * cellWidth + Random::RandReal32( 0.0f, cellWidth );
                _unitSquareSamples[ index ].Y = ( j * n + i ) * cellWidth + Random::RandReal32( 0.0f, cellWidth );
            }
        }
    }

    // shuffle the X coordinates
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < n; ++i )
        {
            for ( int32 j = 0; j < n; ++j )
            {
                const int32 k = Random::RandInt32( j, n - 1 );
                const int32 current = i * n + j + set * _sampleCount;
                const int32 target  = i * n + k + set * _sampleCount;

                real64 x = _unitSquareSamples[ current ].X;
                _unitSquareSamples[ current ].X = _unitSquareSamples[ target ].X;
                _unitSquareSamples[ target ].X = x;
            }
        }
    }

    // shuffle the Y coordinates
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < n; ++i )
        {
            for ( int32 j = 0; j < n; ++j )
            {
                const int32 k = Random::RandInt32( j, n - 1 );
                const int32 current = j * n + i + set * _sampleCount;
                const int32 target  = k * n + i + set * _sampleCount;

                real64 y = _unitSquareSamples[ current ].Y;
                _unitSquareSamples[ current ].Y = _unitSquareSamples[ target ].Y;
                _unitSquareSamples[ target  ].Y = y;
            }
        }
    }
}

REX_NS_END