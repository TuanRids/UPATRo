////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IBeamFormation.h
///
/// Declares the IBeamFormation interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IElementDelayCollection;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Contains information about pulser and receiver delays collections for the creation
  /// of a phased array beam. When using IBeamSetFactory::CreateBeamSetPhasedArray this
  /// beam formation will be used to create a beam.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IBeamFormation
  {
  public:
    virtual ~IBeamFormation() = default;

    virtual std::shared_ptr<IElementDelayCollection> GetPulserDelayCollection() const = 0;
    virtual std::shared_ptr<IElementDelayCollection> GetReceiverDelayCollection() const = 0;
  };

  using IBeamFormationPtr = std::shared_ptr<IBeamFormation>;
  using IBeamConstFormationPtr = std::shared_ptr<const IBeamFormation>;
}
