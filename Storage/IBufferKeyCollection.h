////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IBufferKeyCollection.h.
///
/// Declares the IBufferKeyCollection interface, collecting 
/// all the key to access buffers and descriptors
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IBufferKey.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IBufferKeyCollection
      {
      public:
        virtual ~IBufferKeyCollection() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the key count for the collection
        ///
        /// @returns  The count.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual size_t GetCount() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets configuration buffer key for a specific index
        ///
        /// @param  index Zero-based index of the key.
        ///
        /// @returns  The buffer key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IBufferKeyConstPtr GetKey(size_t index) const = 0;
      };

      using IBufferKeyCollectionConstPtr = std::shared_ptr<const IBufferKeyCollection>;
    }
  }
}
