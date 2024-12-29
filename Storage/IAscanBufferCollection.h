////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferCollection.h.
///
/// Declares the IAscanBufferCollection interface used to store one beamset
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IAscanBuffer.h>


namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferCollection
      {
      public:
        virtual ~IAscanBufferCollection() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the IAScan buffer count, equal to the beam quantity of the beamset
        ///
        /// @returns  The IAScan buffer count.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual size_t GetCount() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets a buffer
        ///
        /// @param  index Zero-based index of the IAscanbuffer.
        ///
        /// @returns  The buffer.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IAscanBufferPtr GetBuffer(size_t index) const = 0;

      };

      using IAscanBufferCollectionConstPtr = std::shared_ptr<const IAscanBufferCollection>;
    }
  }
}
