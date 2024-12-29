#pragma once
#include <utility>
#include <vector>
#include <instrumentation/IDeviceInfo.h>

namespace Instrumentation
{
  class IDigitizerCapabilities;

  class IDeviceCapabilities
  {
  public:

    virtual ~IDeviceCapabilities() = default;

    virtual std::shared_ptr<IDigitizerCapabilities> GetDigitizerCapabilities(UltrasoundTechnology technology) const = 0;

    virtual IDeviceInfo::Platform GetPlatform() const = 0;
    virtual IDeviceInfo::Model GetDeviceModel() const = 0;

    virtual std::size_t GetMaxGatesQty() const = 0;

    //TODO currently not swigable, they must be at the end of the vtable because the following methods will be shifted
#ifndef SWIGCSHARP //TODO
    virtual std::vector<UltrasoundTechnology> GetDigitizerCapabilitiesSupported() const = 0;
    virtual std::pair<double, double> GetAcquisitionRateLimits() const = 0;
#endif
  };
}
