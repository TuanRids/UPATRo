////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IAcquisition.h
///
/// Declares the IAcquisition interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <instrumentation/InstrumentationTypes.h>
#include <ultrasoundConfiguration/UltrasoundTypes.h>

#if defined(INSTRUMENTATION_EXPORTS)
#define INSTRUMENTATION_API __declspec(dllexport)
#else
#define INSTRUMENTATION_API __declspec(dllimport)
#endif

namespace Instrumentation
{
  class ICycleData;
  class IDevice;
  class ISyncedDeviceCollection;
  class IEncoderCollection;
  class IAcquisitionConfiguration;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Controls the acquisition of data and regroups all parameters associated with it.
  ///
  /// The proposed application comprises
  ///
  ///   - a main configuration thread, which configure the devices (See AcquisitionProcess Snippet, main.cpp)
  ///   - a data consumer thread which get the data from the buffer. (See AcquisitionProcess Snippet, DataProcess.h)
  ///
  ///     (the buffer has a 5 seconds duration and must be read to avoid overflow)
  ///
  ///
  ///
  /// @image html IAcquisitionDataFlow.png "Data Flow" width=50%
  ///
  /// @image html IAcquisitionDataFlowTable.png "Acquisition Scenarios" width=50%
  ///
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IAcquisition
  {
  public:

    __declspec(deprecated("Deprecated. Use StateEx.")) enum class State { Started, Stopped , WaitingForData};
    enum class FiringTrigger { Internal, External, Encoder };

    struct __declspec(deprecated("Deprecated. Use WaitForDataResultEx.")) WaitForDataResult
    {
      enum Status
      {
        CycleAcquired,
        NewConfigurationApplied,
        Stopped
      };

      Status status;
      std::shared_ptr<ICycleData> cycleData;
    };
    virtual ~IAcquisition() = default;

    //////////////////////////////////////////////////////////////////////////
    /// Start the data acquisition process.
    ///
    //////////////////////////////////////////////////////////////////////////
    virtual void Start() = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Stop the data acquisition process.
    ///
    /// - Does nothing if called when the acquisition is already stopped.
    ///
    //////////////////////////////////////////////////////////////////////////
    virtual void Stop() = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Return the state of the acquisition process, either Started or Stopped.
    ///
    //////////////////////////////////////////////////////////////////////////
#pragma warning(suppress : 4996)
    __declspec(deprecated("Deprecated. Use GetStateEx.")) virtual State GetState() const = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Wait until new data is available and return a pointer to it.
    ///
    /// - Throw if called when the acquisition is stopped.
    /// - Throw if called when the acquisition buffer is overflown.
    /// - When an exception is thrown, the acquisition automatically stop.
    //
    /// \return Pointer pointing to the newly read data.
    //////////////////////////////////////////////////////////////////////////
#pragma warning(suppress : 4996)
    __declspec(deprecated("Deprecated. Use WaitForDataEx.")) virtual WaitForDataResult WaitForData() = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Get the acquisition rate, which represents the number of cycle that are
    /// acquired each seconds.
    ///
    //TODO: Default acquisition rate is "Insert default acquisition rate here"
    ///
    /// \return The current acquisition rate in hertz
    //////////////////////////////////////////////////////////////////////////
    virtual double GetRate() const = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Change the acquisition rate, which represents the number of cycle that are
    /// acquired each seconds.
    ///
    /// The requested rate will be effectively applied on the next call of
    /// IAcquisition::ApplyConfiguration
    ///
    /// The acquisition rate can be auto-adjusted based on device limitation.
    /// This means that the requested rate may not be applied as requested, in
    /// which case it will be lowered to the maximum possible value.
    /// If the applied acquisition rate is not as requested, function will
    /// return false and IAcquisition::GetRate can be called to retreive the current rate.
    ///
    /// @param requestedRate Requested acquisition rate in hertz
    ///
    /// \return True if the rate fall into known allowed range. False otherwise
    ///         True does not necessarily mean that the requested value will be appllied
    ///         on next apply, it only means that it falls between absolute capabilities
    ///         of the device given perfect circumstances.
    //////////////////////////////////////////////////////////////////////////
    virtual bool SetRate(double requestedRate) = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Get the the amount of data passing through the acquisition process.
    ///
    /// \return The current throughput in megabytes per second
    ///
    //////////////////////////////////////////////////////////////////////////
    virtual double GetThroughput() const = 0;

    virtual FiringTrigger GetFiringTrigger() const = 0;
    virtual void SetFiringTrigger(FiringTrigger firingTrigger) = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Program the configuration changes of all the devices owned by the acquisition
    ///
    /// Can be called in any state of the acquisition
    ///
    /// If the acquisition is running and the configuration changes need it
    /// to be stopped in order to be programmed, the acquisition will temporarily be stopped
    /// during the programmation and restarted when it finishes.
    ///
    /// It will not be restarted if the configuration changes involved deleting all the beams
    /// of a device owned by the acquisition
    //////////////////////////////////////////////////////////////////////////
    virtual void ApplyConfiguration() = 0;
    virtual std::shared_ptr<IEncoderCollection> GetEncoders() const = 0;

    virtual bool IsDigitalInputDataEnabled() const = 0;
    virtual void EnableDigitalInputData(bool doEnable) = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Creates an acquisition using the specified device(s).
    ///
    /// - A device cannot be used in multiple acquisitions at the same time.
    ///
    /// \return The acquisition object.
    ///
    //////////////////////////////////////////////////////////////////////////
    __declspec(deprecated("Deprecated. Use CreateEx.")) static std::shared_ptr<IAcquisition> INSTRUMENTATION_API Create(std::shared_ptr<IDevice> const& device);
    __declspec(deprecated("Deprecated. Use CreateEx.")) static std::shared_ptr<IAcquisition> INSTRUMENTATION_API Create(std::shared_ptr<ISyncedDeviceCollection> const& syncedDevices);

    virtual std::shared_ptr<IAcquisitionConfiguration> GetConfiguration() const = 0;


    // IAcquisition Extension ////////////////////////////////////////////////
    enum class StateEx { Started, Stopped };

    struct WaitForDataResultEx
    {
      enum Status
      {
        DataAvailable,
        NoMoreData
      };

      Status status;
      std::shared_ptr<ICycleData> cycleData;
    };

    //////////////////////////////////////////////////////////////////////////
    /// Wait until new data is available and return a pointer to it and a status.
    ///
    /// The status can be
    /// - DataAvailable if there is still data in the buffer
    /// - NoMoreData if there is no more data in the buffer (The pointer will be null)
    ///
    /// There can be no more data in the buffer if the acquisition was stopped
    /// or if there was an error
    ///
    /// - Throw if called when the acquisition buffer is overflown.
    /// - Throw if called when there is a Data integrity error.
    /// - When an exception is thrown, the acquisition automatically stop.
    //
    /// \return Pointer pointing to the newly read data.
    //////////////////////////////////////////////////////////////////////////
    virtual WaitForDataResultEx WaitForDataEx() = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Return the state of the data producer, either Started or Stopped.
    ///
    //////////////////////////////////////////////////////////////////////////
    virtual StateEx GetStateEx() const = 0;

    //////////////////////////////////////////////////////////////////////////
    /// Creates an acquisition using the specified device(s).
    /// This EX version uses the Ex functions instead of their non ex counterparts
    /// Calling the non Ex version of the functions will throw a runtime_error exception.
    ///
    /// - A device cannot be used in multiple acquisitions at the same time.
    ///
    /// \return The acquisition object.
    ///
    //////////////////////////////////////////////////////////////////////////
    static std::shared_ptr<IAcquisition> INSTRUMENTATION_API CreateEx(std::shared_ptr<IDevice> const& device);
    static std::shared_ptr<IAcquisition> INSTRUMENTATION_API CreateEx(std::shared_ptr<ISyncedDeviceCollection> const& syncedDevices);
  };

  using IAcquisitionPtr = std::shared_ptr<IAcquisition>;
  using IAcquisitionConstPtr = std::shared_ptr<const IAcquisition>;
}
