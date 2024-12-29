///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\ISegment.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the ISegment interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include <View/IPoint.h>

namespace Olympus
{
  namespace View
  {
    class ISegment
    {
    public:
      virtual ~ISegment() = default;
               
      virtual IPointPtr GetFirstPoint() = 0;
      virtual IPointPtr GetSecondPoint() = 0;
    };

    using ISegmentPtr = std::shared_ptr<ISegment>;
    using ISegmentConstPtr = std::shared_ptr<const ISegment>;
  }
}

