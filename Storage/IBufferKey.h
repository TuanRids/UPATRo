////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IBufferKey.h.
///
/// IBufferKey is used as a unique key to retrieve 
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <storage/IAscanBufferKeyEx.h>
#include <storage/ICscanBufferKeyEx.h>
#include <storage/ITotalFocusingMethodBufferKey.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IBufferKey
      {
      public:
        virtual ~IBufferKey() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets inspection method name of a configuration.
        ///
        /// @returns  The name.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const std::wstring& GetName() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets Ascan keys related to the configuration.
        /// Can be cast to IAscanBufferBeamKey or IAscanMergedBufferKey.
        ///
        /// @returns  The key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IAscanBufferKeyExConstPtr GetAscanBufferKey() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets Cscan keys related to the configuration.
        /// Can be cast to ICscanBufferBeamGateKey or ICscanMergedBufferGateKey.
        ///
        /// @returns  The key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ICscanBufferKeyExConstPtr GetCscanBufferKey() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets Total Focusing Method key related to the configuration.
        ///
        /// @returns  The key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ITotalFocusingMethodBufferKeyConstPtr GetTotalFocusingMethodBufferKey() const = 0;
      };

      using IBufferKeyConstPtr = std::shared_ptr<const IBufferKey>;
    }
  }
}
