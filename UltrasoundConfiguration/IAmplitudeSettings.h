////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IAmplitudeSettings.h
///
/// NDE file domain path:  dataGroups[index] / ultrasound / sectorialPulseEcho or linearPulseEcho
/// or compoundPulseEcho
/// 
/// Declares the IAmplitudeSettings interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IAdjustedParameterCollection;

  class IAmplitudeSettings
  {
  public:
    enum class AscanDataSize { EightBits = 8, TwelveBits = 12, SixteenBits = 16 };
    enum class ScalingType { Linear, Logarithmic };
    enum class RectificationType { None, Positive, Negative, Full };

    virtual ~IAmplitudeSettings() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the data size of the AScan points : EightBits, TwelveBits or SixteenBits.
    ///
    /// @return
    /// The data size.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual AscanDataSize GetAscanDataSize() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the data size of the AScan points : EightBits, TwelveBits or SixteenBits.
    ///
    /// @param ascanDataSize The desired data size.
    ///
    /// @return
    /// The interface IAdjustedParameterCollection containing the parameters that are impacted
    /// by this configuration. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetAscanDataSize(AscanDataSize ascanDataSize) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the rectification of the AScan : None, Positive, Negative or Full.
    /// Unipolars show only the positive or negative side of the AScan while Full shows both sides,
    /// but with the negative side in the positive, this is also called a rectified AScan. 
    ///
    /// NDE file domain path:  dataGroups[index] / ultrasound / sectorialPulseEcho or linearPulseEcho
    /// or compoundPulseEcho / rectification
    /// 
    /// @return
    /// The rectification type enum.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual RectificationType GetAscanRectification() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the rectification of the AScan : None, Positive, Negative or Full.
    /// Unipolars show only the positive or negative side of the AScan while Full shows both sides,
    /// but with the negative side in the positive, this is also called a rectified AScan. 
    ///
    /// @param rectification The desired rectification type enum.
    ///
    /// @return
    /// The interface IAdjustedParameterCollection containing the parameters that are impacted
    /// by this configuration. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetAscanRectification(RectificationType rectification) = 0;

    virtual ScalingType GetScalingType() const = 0;

    virtual void SetScalingType(ScalingType scalingType) = 0;
  };

  using IAmplitudeSettingsPtr = std::shared_ptr<IAmplitudeSettings>;
  using IAmplitudeSettingsConstPtr = std::shared_ptr<const IAmplitudeSettings>;
}
