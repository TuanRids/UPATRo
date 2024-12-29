////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferBeamKey.h.
///
/// IAscanBufferBeamKey is used as a unique key to retrieve 
/// the IAScanBuffer and IAScanBufferDescriptor of a beam
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IBufferKey.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferBeamKey : public IAscanBufferKeyEx
      {
      public:
        virtual ~IAscanBufferBeamKey() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the beam index  
        ///
        /// @returns  The beam index.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual size_t GetBeamIndex() const = 0;
      };

      using IAscanBufferBeamKeyConstPtr = std::shared_ptr<const IAscanBufferBeamKey>;
    }
  }
}
