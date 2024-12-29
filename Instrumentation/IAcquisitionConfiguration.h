#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>
#include <instrumentation/IAcquisition.h>
#include "IDeviceConfigurationCollection.h"
#include "IEncoderCollection.h"

namespace Instrumentation
{
  class IAcquisitionConfiguration
  {
  public:
    virtual ~IAcquisitionConfiguration() = default;

    virtual double GetAcqRate() const = 0;
    virtual std::shared_ptr<IEncoderCollection> GetEncoders() const = 0;
    virtual std::shared_ptr<IDeviceConfigurationCollection> GetDeviceConfigurations() const = 0;

#ifdef SWIG
    virtual int GetFiringTrigger() const = 0;
#else
    virtual IAcquisition::FiringTrigger GetFiringTrigger() const = 0;
#endif

  __declspec(deprecated("Deprecated. Use AreEquals instead."))
  virtual bool Equals(const IAcquisitionConfiguration& other) const = 0;

  virtual bool AreEquals(std::shared_ptr<IAcquisitionConfiguration> other) const = 0;
  };

  using IAcquisitionConfigurationPtr = std::shared_ptr<IAcquisitionConfiguration>;
  using IAcquisitionConfigurationConstPtr = std::shared_ptr<const IAcquisitionConfiguration>;
}

