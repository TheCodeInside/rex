#include "NRooksSampler.hxx"
#include "Random.hxx"

REX_NS_BEGIN

// new n-rooks sampler
NRooksSampler::NRooksSampler()
    : Sampler()
{
}

// new n-rooks sampler w/ samples
NRooksSampler::NRooksSampler( int32 samples )
    : Sampler( samples )
{
}

// new n-rooks sampler w/ samples and sets
NRooksSampler::NRooksSampler( int32 samples, int32 sets )
    : Sampler( samples, sets )
{
}

// destroy n-rooks sampler
NRooksSampler::~NRooksSampler()
{
}

// generate samples
void NRooksSampler::GenerateSamples()
{
    // generate samples along a main diagonal (only N samples are needed for an N*N grid)
    Vector2 vec;
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < _sampleCount; ++i )
        {
            vec.X = ( i + Random::RandReal32() ) / _sampleCount;
            vec.Y = ( i + Random::RandReal32() ) / _sampleCount;

            _unitSquareSamples.push_back( vec );
        }
    }

    // now shuffle the coordinates
    ShuffleXCoordinates();
    ShuffleYCoordinates();
}

// shuffle the X coordinates
void NRooksSampler::ShuffleXCoordinates()
{
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < _sampleCount - 1; ++i )
        {
            // get current and target indices
            const int32 current = i + set * _sampleCount + 1;
            const int32 target  = ( Random::RandInt32() % _sampleCount ) + ( set * _sampleCount );

            // swap X coordinate
            real64 x = _unitSquareSamples[ current ].X;
            _unitSquareSamples[ current ].X = _unitSquareSamples[ target ].X;
            _unitSquareSamples[ target  ].X = x;
        }
    }
}

// shuffle the Y coordinates
void NRooksSampler::ShuffleYCoordinates()
{
    for ( int32 set = 0; set < _setCount; ++set )
    {
        for ( int32 i = 0; i < _sampleCount - 1; ++i )
        {
            // get current and target indices
            const int32 current = i + set * _sampleCount + 1;
            const int32 target = ( Random::RandInt32() % _sampleCount ) + ( set * _sampleCount );

            // swap Y coordinate
            real64 y = _unitSquareSamples[ current ].Y;
            _unitSquareSamples[ current ].Y = _unitSquareSamples[ target ].Y;
            _unitSquareSamples[ target  ].Y = y;
        }
    }
}

REX_NS_END