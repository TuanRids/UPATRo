////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferBeamKeyCollection.h.
///
/// Declares the IAscanBufferBeamKeyCollection interface, collecting all 
/// the key to access AScan buffers and descriptors
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IBufferKey.h>
#include <Storage/IAscanBufferBeamKey.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferBeamKeyCollection : public IAscanBufferKeyEx
      {
      public:
        virtual ~IAscanBufferBeamKeyCollection() = default;

        virtual size_t GetCount() const = 0;
        virtual IAscanBufferBeamKeyConstPtr GetBeamKey(size_t index) const = 0;
      };

      using IAscanBufferBeamKeyCollectionConstPtr = std::shared_ptr<const IAscanBufferBeamKeyCollection>;
    }
  }
}
