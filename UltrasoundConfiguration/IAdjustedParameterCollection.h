////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IAdjustedParameterCollection.h
///
/// Declares the IAdjustedParameterCollection interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IAdjustedParameter;
  using ObjectKey = std::uint64_t;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// This collection regroups all parameters that have been adjusted after a change to configuration.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IAdjustedParameterCollection
  {
  public:
    virtual ~IAdjustedParameterCollection() = default;
    enum class ObjectType { BeamSet, Beam, Gate, Tcg, TcgPoint };
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the number of parameters that have been adjusted.
    ///
    /// @return
    /// The count of adjusted parameters.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t GetCount() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get one of the adjusted parameter's interface by giving its index. 
    /// 
    /// @param index The position of the desired parameter.
    ///
    /// @return
    /// The interface IAdjustedParameter of the desired parameter. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameter> GetAdjustedParameter(std::size_t index) const = 0;
    virtual std::size_t GetAdjustedParameterCollectionCount() const = 0;
    virtual std::shared_ptr<IAdjustedParameterCollection> GetAdjustedParameterCollection(std::size_t index) const = 0;

    virtual ObjectType GetObjectType() const = 0;
    virtual ObjectKey GetObjectKey() const = 0;
  };

  using IAdjustedParameterCollectionPtr = std::shared_ptr<IAdjustedParameterCollection>;
  using IAdjustedParameterCollectionConstPtr = std::shared_ptr<const IAdjustedParameterCollection>;
}

