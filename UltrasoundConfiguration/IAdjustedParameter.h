#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IAdjustedParameter
  {
  public:
    virtual ~IAdjustedParameter() = default;

    virtual std::string GetParameterName() const = 0;
    virtual double GetPreviousValue() const = 0;
    virtual double GetRequestedValue() const = 0;
    virtual double GetAdjustedValue() const = 0;
  };
}

