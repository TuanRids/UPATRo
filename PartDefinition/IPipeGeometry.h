///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file PartDefinition\IPipeGeometry.h.
///
/// NDE file domain path specimens[index] / pipeGeometry 
/// 
/// Declares the IPipeGeometry interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <PartDefinition/ITubularGeometry.h>

namespace Olympus { namespace PartDefinition {
    /**
    * JSON format location: specimens.pipeGeometry
    */
    class IPipeGeometry : public ITubularGeometry
    {
    public:
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Thickness of the pipe
      ///
      /// NDE file domain path specimens[index] / pipeGeometry / thickness
      /// 
      /// @return
      /// The thickness of the pipe wall measured in millimeters
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual double GetThickness() const = 0;
      virtual ICylinderSurfaceConstPtr GetInsideSurface() const = 0;
    };

    using IPipeGeometryPtr = std::shared_ptr<IPipeGeometry>;
    using IPipeGeometryConstPtr = std::shared_ptr<const IPipeGeometry>;
  }
}
