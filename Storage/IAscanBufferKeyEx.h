////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferKeyEx.h.
///
/// IAscanBufferKeyEx is used as a unique key to retrieve a buffer and his descriptor.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <memory>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferKeyEx
      {
      public:
        virtual ~IAscanBufferKeyEx() = default;

        virtual const std::wstring& GetName() const = 0;
      };

      using IAscanBufferKeyExConstPtr = std::shared_ptr<const IAscanBufferKeyEx>;
    }
  }
}
