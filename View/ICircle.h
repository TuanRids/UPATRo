///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\ICircle.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the ICircle interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include <View/IPoint.h>

namespace Olympus
{
  namespace View
  {
    class ICircle
    {
    public:
      virtual ~ICircle() = default;
               
      virtual IPointPtr GetCenterPoint() = 0;
      virtual double GetRadius() = 0;
      virtual void SetRadius(double radius) = 0;
    };

    using ICirclePtr = std::shared_ptr<ICircle>;
    using ICircleConstPtr = std::shared_ptr<const ICircle>;
  }
}

