#pragma once
#include <vector>
#include <ultrasoundConfiguration/IDigitalBandPassFilter.h>

namespace Instrumentation
{
  class IConnectorCollection;
  class IDigitalBandPassFilterCollection;
  class IPulserVoltageCollection;
  class ISmoothingFilterCollection;

  class IDigitizerCapabilities
  {
  public:
    virtual ~IDigitizerCapabilities() = default;

    virtual UltrasoundTechnology GetUltrasoundTechnology() const = 0;
    virtual unsigned short GetMaxAperture() const = 0;
    virtual unsigned short GetMaxPulserReceiver() const = 0;
    virtual double GetMaxGain() const = 0;
    virtual double GetResolutionGain() const = 0;
    virtual std::size_t GetMaxSamples() const = 0;
    virtual double GetMaxAscanRange() const = 0;
    virtual double GetMinAscanRange() const = 0;
    virtual double GetMinAscanStart() const = 0;
    virtual std::size_t GetMaxCompression() const = 0;
    virtual std::size_t GetMaxCompressionRF() const = 0;
    virtual double GetMinPulseWidth() const = 0;
    virtual double GetMaxPulseWidth() const = 0;
    virtual double GetResolutionPulseWidth() const = 0;
    virtual std::size_t GetMaxGatesQty() const = 0;
    virtual double GetMaxCscanRange() const = 0;
    virtual double GetMinCscanRange() const = 0;
    virtual double GetMinCscanStart() const = 0;
    virtual double GetAscanResolution() const = 0;
    virtual double GetCscanResolution() const = 0;
    virtual double GetRecurrenceMinimum() const = 0;
    virtual double GetRecurrenceMaximum() const = 0;
    virtual double GetAcquisitionRateMinimum() const = 0;
    virtual double GetAcquisitionRateMaximum() const = 0;
    virtual double GetPulserDelayMaximum() const = 0;
    virtual double GetReceiverDelayMaximum() const = 0;
    virtual double GetPulserDelayResolution() const = 0;
    virtual double GetReceiverDelayResolution() const = 0;
    virtual bool IsLogarithmicAmplitudeScalingSupported() const = 0;
    virtual unsigned long GetAscanAveragingFactorMaximum() const = 0;
    virtual unsigned long GetSamplingDecimationFactorMaximum() const = 0;
    virtual bool AreDigitalBandBassFiltersSupported() const = 0;
    virtual bool AreSmoothingFiltersSupported() const = 0;

    virtual std::shared_ptr<IConnectorCollection> GetConnectors() const = 0;
    virtual std::shared_ptr<IDigitalBandPassFilterCollection> GetDigitalBandPassFilters() const = 0;
    virtual std::shared_ptr<ISmoothingFilterCollection> GetSmoothingFilters() const = 0;
    virtual std::shared_ptr<IPulserVoltageCollection> GetPulserVoltages() const = 0;

    virtual void AddDigitalBandPassFilter(IDigitalBandPassFilter::Type type, double lowFrequency, double highFrequency, IDigitalBandPassFilter::Characteristic characteristic) = 0;

    //TODO currently not swigable, they must be at the end of the vtable because the following methods will be shifted
#ifndef SWIG //TODO
    virtual std::vector<unsigned long> GetSamplingDecimationFactors() const = 0;
    virtual std::vector<double> const& GetVoltageCodes() const = 0;
#endif

  };
}
