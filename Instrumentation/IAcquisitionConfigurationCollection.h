////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IAcquisitionConfigurationCollection.h
///
/// Declares the IAcquisitionConfigurationCollection interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>
#include <instrumentation/IAcquisition.h>

namespace Instrumentation
{
  class IAcquisitionConfiguration;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Gives access to the acquisition configurations in this collection.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IAcquisitionConfigurationCollection
  {
  public:
    virtual ~IAcquisitionConfigurationCollection() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the count for the number of acquisition configurations in this collection.
    ///
    /// @return
    /// The number of acquisition configurations.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::size_t GetCount() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the interface of one acquisition configuration in this set by giving its index in the collection. 
    ///
    /// @param index The index of the requested acquisition configuration in this collection.
    ///
    /// @return
    /// The interface IAcquisitionConfiguration of the requested acquisition configuration.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IAcquisitionConfiguration> GetAcquisitionConfiguration(std::size_t index) const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Add an acquisition configuration to this set and chain it back.
    ///
    /// @param firingTrigger  The way each cycle data are triggered.  .
    ///
    /// @param aquisitionRate  The cycle firing frequency.
    /// @return
    /// The chained IAcquisitionConfiguration.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SWIGCSHARP
    virtual std::shared_ptr<IAcquisitionConfiguration> Add(int firingTrigger, double aquisitionRate) = 0;
#else
    virtual std::shared_ptr<IAcquisitionConfiguration> Add(IAcquisition::FiringTrigger firingTrigger, double aquisitionRate) = 0;
#endif

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Remove an interface IAcquisitionConfiguration in this collection by giving its index.
    ///
    /// @param index The position of the IAcquisitionConfiguration desired to be removed.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Remove(std::size_t index) = 0;

    virtual std::shared_ptr<IAcquisitionConfiguration> Add(std::shared_ptr<IAcquisitionConfiguration> acqConfig) = 0;
  };

  using IAcquisitionConfigurationCollectionPtr =
    std::shared_ptr<IAcquisitionConfigurationCollection>;

  using IAcquisitionConfigurationCollectionConstPtr =
    std::shared_ptr<const IAcquisitionConfigurationCollection>;
}
