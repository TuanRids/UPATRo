///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\IPoint.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the IPoint interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
//#include <View/IOverlay.h>

namespace Olympus
{
  namespace View
  {
    class IPoint
    {
    public:
      virtual ~IPoint() = default;
    
      virtual double X() = 0;
      virtual double Y() = 0;
      virtual double Z() = 0;

      virtual void X(double) = 0;
      virtual void Y(double) = 0;
      virtual void Z(double) = 0;
    };

    using IPointPtr = std::shared_ptr<IPoint>;
    using IPointConstPtr = std::shared_ptr<const IPoint>;
  }
}

