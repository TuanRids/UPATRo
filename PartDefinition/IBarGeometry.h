///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file PartDefinition\IBarGeometry.h.
///
/// NDE file domain path specimens[index] / barGeometry
/// 
/// Declares the IBarGeometry interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <PartDefinition/ITubularGeometry.h>

namespace Olympus { namespace PartDefinition {

  class IBarGeometry : public ITubularGeometry
  {
  };

    using IBarGeometryPtr = std::shared_ptr<IBarGeometry>;
    using IBarGeometryConstPtr = std::shared_ptr<const IBarGeometry>;
  }
}
