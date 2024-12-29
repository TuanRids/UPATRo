////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanMergedBufferKey.h.
///
/// IAscanMergedBufferKey is used as a unique key to retrieve 
/// the IAscanBuffer and his IAscanBufferDescriptor
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IBufferKey.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanMergedBufferKey : public IAscanBufferKeyEx
      {
      public:
        virtual ~IAscanMergedBufferKey() = default;

        virtual size_t GetBeamCount() const = 0;

      };

      using IAscanMergedBufferKeyConstPtr = std::shared_ptr<const IAscanMergedBufferKey>;
    }
  }
}
