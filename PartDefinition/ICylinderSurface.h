///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file PartDefinition\ICylinderSurface.h.
///
/// Declares the ICylinderSurface interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <PartDefinition/IMappingUV.h>

namespace Olympus { namespace PartDefinition {

  class ICylinderSurface : public IMappingUV
  {
  public:
    virtual double GetAngleBegin() const = 0;
    virtual double GetAngleLength() const = 0;
  };

  using ICylinderSurfacePtr = std::shared_ptr<ICylinderSurface>;
  using ICylinderSurfaceConstPtr = std::shared_ptr<const ICylinderSurface>;
  }
}
