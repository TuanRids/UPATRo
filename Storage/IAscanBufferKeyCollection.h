////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferKeyCollection.h.
///
/// Declares the IAscanBufferKeyCollection interface, collecting all the key to access AScan buffers and descriptors
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IAscanBufferKey.h>


namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferKeyCollection
      {
      public:
        virtual ~IAscanBufferKeyCollection() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the key count for the collection
        ///
        /// @returns  The count.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual size_t GetCount() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets buffer key for a specific index
        ///
        /// @param  index Zero-based index of the key.
        ///
        /// @returns  The buffer key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IAscanBufferKeyConstPtr GetBufferKey(size_t index) const = 0;
      };

      using IAscanBufferKeyCollectionConstPtr = std::shared_ptr<const IAscanBufferKeyCollection>;
    }
  }
}
