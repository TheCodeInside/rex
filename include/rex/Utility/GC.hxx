#pragma once

#include "../Config.hxx"
#include <utility>
#include <vector>

REX_NS_BEGIN

/// <summary>
/// Defines a garbage collector.
/// </summary>
class GC
{
    /// <summary>
    /// The cleanup callback type.
    /// </summary>
    /// <param name="data">The data to cleanup.</param>
    typedef void (* CleanupCallback )( void* data );

    /// <summary>
    /// The pair of memory and its associated cleanup callback.
    /// </summary>
    typedef std::pair<void*, CleanupCallback> MemoryPair;

    /// <summary>
    /// The host cleanup callback.
    /// </summary>
    /// <param name="data">The data to cleanup.</param>
    template<typename T> static void HostCleanupCallback( void* data );

    static GC _instance;
    std::vector<void*> _deviceMem;
    std::vector<MemoryPair> _hostMem;

    // ----------------------------------
    GC();
    ~GC();
    GC( const GC& )             = delete;
    GC( GC&& )                  = delete;
    GC& operator=( GC&& )       = delete;
    GC& operator=( const GC& )  = delete;
    // ----------------------------------

public:
    /// <summary>
    /// Allocates memory for the given type on the host.
    /// </summary>
    /// <param name="args">The arguments to pass into the type's constructor.</param>
    template<typename T, typename ... Args> __host__ static T* HostAlloc( const Args& ... args );

    /// <summary>
    /// Allocates memory for the given type on the device.
    /// </summary>
    /// <param name="source">The source object to copy.</param>
    template<typename T> __host__ static T* DeviceAlloc( const T& source );

    /// <summary>
    /// Allocates memory for an array of the given type on the device.
    /// </summary>
    /// <param name="count">The number of items to allocate for.</param>
    template<typename T> __host__ static T* DeviceAllocArray( uint32 count );

    /// <summary>
    /// Allocates memory for an array of the given type on the device and copies data from an initial source.
    /// </summary>
    /// <param name="count">The number of items to allocate for.</param>
    /// <param name="source">The source to copy from.</param>
    template<typename T> __host__ static T* DeviceAllocArray( uint32 count, const T* source );

    /// <summary>
    /// Releases all device memory.
    /// </summary>
    static void ReleaseDeviceMemory();
};

REX_NS_END

#include "GC.inl"