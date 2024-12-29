////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IDigitalBandPassFilterCollection.h
///
/// Declares the IDigitalBandPassFilterCollection interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>
#include <ultrasoundConfiguration/IDigitalBandPassFilter.h>

namespace Instrumentation
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// This interface regroups all the different filter interfaces available 
  /// to be apply to the processed signal. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IDigitalBandPassFilterCollection
  {
  public:
    virtual ~IDigitalBandPassFilterCollection() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the number of IDigitalBandPassFilter interfaces in this collection.
    ///
    /// @return
    /// The number of interfaces.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::size_t GetCount() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the specified interface IDigitalBandPassFilter corresonding to the index given. The chosen
    /// filter can be assigned to a beam set by using IFilterSettings::SetDigitalBandPassFilter.
    ///
    /// @param index The index of the desired interface.
    ///
    /// @return
    /// The interface IDigitalBandPassFilter.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IDigitalBandPassFilter> GetDigitalBandPassFilter(std::size_t index) const = 0;
  };

  using IDigitalBandPassFilterCollectionPtr = std::shared_ptr<IDigitalBandPassFilterCollection>;
  using IDigitalBandPassFilterCollectionConstPtr = std::shared_ptr<const IDigitalBandPassFilterCollection>;
}
