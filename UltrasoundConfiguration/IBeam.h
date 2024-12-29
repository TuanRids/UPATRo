////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IBeam.h
///
/// Declares the individual IBeam interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IBeamFormation;
  class IGateCollection;
  class ITcg;
  class IAdjustedParameterCollection;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Contains all the information concerning an individual beam. 
  /// A beam represents a set of parameters that results in a single AScan.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IBeam
  {
  public:
    enum class SumGainMode { Automatic, Manual };

    virtual ~IBeam() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the gain of the beam, i.e. the number of dB by which the signal is increased.
    ///
    /// @return
    /// The current gain in dB.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Decibel GetGain() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the gain of the beam, i.e. the number of dB by which the signal should be increased.
    ///
    /// @param gain The desired gain in dB.
    ///
    /// @return
    /// The interface IAdjustedParameterCollection containing the parameters that are impacted
    /// by this configuration. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    __declspec(deprecated("Deprecated. Use IBeam::SetGainEx to get more verbosity on which automatic adjustments were applied")) virtual bool SetGain(Decibel gain) = 0;
    virtual std::shared_ptr<IAdjustedParameterCollection> SetGainEx(Decibel gain) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the position at which the AScan should start to display, in nanoseconds.
    ///
    /// @return
    /// The AScan start, in nanoseconds. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual NanoSecond GetAscanStart() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the position at which the AScan should start to display, in nanoseconds. The function 
    /// returns an interface containing all parameters that have been affected by this Set function.
    ///
    /// @param start The desired AScan start in nanoseconds.
    ///
    /// @return
    /// The interface IAdjustedParameterCollection containing the parameters that are impacted
    /// by this configuration. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetAscanStart(NanoSecond start) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the length of the displayed AScan in nanoseconds.
    /// 
    /// @return
    /// The AScan length, in nanoseconds.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual NanoSecond GetAscanLength() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the length of the displayed AScan in nanoseconds. The function returns an interface 
    /// containing all parameters that have been affected by this Set function. 
    /// With respect to the current AScan start, if the desired length exceeds the maximum digitizing
    /// time, then the length value will maxed accordingly.
    ///
    /// @param length The desired AScan length in nanoseconds.
    /// 
    /// @return
    /// The interface IAdjustedParameterCollection containing the parameters that are impacted
    /// by this configuration. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetAscanLength(NanoSecond length) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the applied sum gain of this beam. The sum gain is a gain applied when the FPGA adds all
    /// information from the different elements in a phased array configuration. 
    //TODO: PBLTODO GetSum when in automatic, or conventional config
    ///
    /// @return
    /// The sum gain. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Decibel GetSumGain() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the applied sum gain of this beam. The sum gain is a gain applied when the FPGA sums all
    /// information from the different elements in a phased array configuration. If the sum gain mode is
    /// automatic, it is impossible to change the sum gain, which will be automatically set by the FPGA.
    ///
    /// @param sumGain The desired sum gain. 
    ///
    /// @return
    /// A boolean returning success status:
    /// True if the requested value was applied,
    /// False if the value was adjusted to fit the domain of values, or was not applied.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetSumGain(Decibel sumGain) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the gain mode of this beam : Manual or Automatic. 
    /// The sum gain is a gain applied when the FPGA adds all information from the different elements 
    /// in a phased array configuration. When in Automatic mode, the FPGA calculates itself the gain to
    /// use, but the user can manually change the sum gain with SetSumGain if the gain mode is Manual.
    ///
    /// @return
    /// The gain mode enum. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual SumGainMode GetSumGainMode() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the gain mode of this beam : Manual or Automatic. 
    /// The sum gain is a gain applied when the FPGA adds all information from the different elements 
    /// in a phased array configuration. When in Automatic mode, the FPGA calculates itself the gain to
    /// use, but the user can manually change the sum gain with SetSumGain if the gain mode is Manual.
    ///
    /// @param sumGainMode The desired gain mode enum. 
    ///
    /// @return
    /// A boolean returning success status:
    /// True if the requested value was applied,
    /// False if the value was adjusted to fit the domain of values, or was not applied.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetSumGainMode(SumGainMode sumGainMode) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the Recurrence for this beam. The recurrence represents the time allocated to 
    /// the total digitizing time of this beam in nanoseconds. This time will be allocated
    /// every firing cycle for this particular beam.
    ///
    /// @return
    /// The recurrence as a duration 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual NanoSecond GetRecurrence() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the Recurrence for this beam in nanoseconds. This time will be allocated
    /// every firing cycle for this particular beam. This time includes the firing of 
    /// the pulse and the digitizing of the signal. Increasing the recurrence could 
    /// have an impact on the total acquisition rate. In order to be able to set the 
    /// reccurence, the recurrence mode needs to be manual. This mode can be change
    /// by using IUltrasoundConfiguration::SetRecurrenceMode.
    ///
    /// @param recurrence The duration of the digitizing action for this beam.
    ///
    /// @return
    /// A boolean returning success status:
    /// True if the requested value was applied,
    /// False if the value was adjusted to fit the domain of values, or was not applied.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAdjustedParameterCollection> SetRecurrence(NanoSecond recurrence) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the collection of element delays associated with this beam. These delays determine 
    /// how this beam will be directed in the material.
    /// 
    /// @return
    /// The IBeamFormation containing the list of element delays.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamFormation> GetBeamFormation() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the collection of gates associated with this beam. 
    /// 
    /// @return
    /// The IGateCollection containing the list of gates.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IGateCollection> GetGateCollection() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get access to the ITcg interface which contains all information about Time Corrected Gain (TCG). 
    /// 
    /// @return
    /// The interface ITcg.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<ITcg> GetTcg() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the number of samples in the AScans for this beam. 
    /// 
    /// @return
    /// The number of samples.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::size_t GetAscanSampleQuantity() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compare this Beam to another for equality.
    ///
    /// @return
    /// True if both objects represent the same instance, False otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool Equals(std::shared_ptr<IBeam>) const = 0;
  };

  using IBeamPtr = std::shared_ptr<IBeam>;
  using IBeamConstPtr = std::shared_ptr<const IBeam>;
}
