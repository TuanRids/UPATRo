////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IDigitalBandPassFilter.h
///
/// Declares the IDigitalBandPassFilter interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// The interface for a digital pass filter. This interface contains the type of filter 
  /// the cut off frequencies as well as the characteristic of the filter. This filter can be 
  /// applied to an IBeamSet using SetDigitalBandPassFilter. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IDigitalBandPassFilter
  {
  public:
    enum class Type { None, LowPass, HighPass, BandPass };
    enum class Characteristic { None, TimeOfFlightDiffraction };

    virtual ~IDigitalBandPassFilter() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the type of this filter: None, LowPass, HighPass or BandPass.
    /// Although all filters have a low and high cut off frequency, the low and high pass filters 
    /// have most of their frequencies in the low and high spectrum respectively. 
    /// None filter are analog and depend on the instrument used, whereas Pass filters are digitals. 
    ///
    /// @return
    /// The Type enum.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual IDigitalBandPassFilter::Type GetFilterType() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the low frequency cut off of this filter. Lower frequencies than the cut off are greatly 
    /// attenuated until they are all but innexistants. 
    ///
    /// @return
    /// The low cut off frequency for the filter.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual double GetLowCutOffFrequency() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the high frequency cut off of this filter. Higher frequencies than the cut off are greatly 
    /// attenuated until they are all but innexistants. 
    ///
    /// @return
    /// The high cut off frequency  for the filter.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual double GetHighCutOffFrequency() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the characteristic for this filter: None or TOFD. 
    /// TOFD filters are filters that we believe to be more suitable for TOFD inspections. These  
    /// filters usually have very low cut off frequencies. 
    ///
    /// @return
    /// The Characteristic enum.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual IDigitalBandPassFilter::Characteristic GetCharacteristic() const = 0;

  };

  using IDigitalBandPassFilterPtr = std::shared_ptr<IDigitalBandPassFilter>;
  using IDigitalBandPassFilterConstPtr = std::shared_ptr<const IDigitalBandPassFilter>;
}
