////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBuffer.h.
///
/// Declares the IAscanBuffer interface
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <Storage/IAscanData.h>
#include <Storage/IAscanBufferDescriptor.h>
#include <Storage/IReadOnlyAscanBuffer.h>


namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBuffer : public IReadOnlyAscanBuffer
      {
      public:
        virtual ~IAscanBuffer() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Writes new data into the buffer
        ///
        /// @param          scanCell    The buffer column parallel to the scan axis.
        /// @param          indexCell   The buffer row parallel to the index axis.
        /// @param          data        
        /// Pointer to the data to copy into the buffer. The type of the data pointer is defined by Data::IReadOnlyAscanBuffer::GetDataType
        /// and the size of the date is defined by Instrumentation::IAmplitudeSettings::GetAscanDataSize. The quantity of the array must be 
        /// equal to Data::IReadOnlyAscanBuffer::GetSampleQuantity.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void Write(size_t scanCell, size_t indexCell, const void* data) = 0;

        virtual void Write(size_t scanCell, size_t indexCell, const void* data, bool synced, bool saturated) = 0;
      };

      using IAscanBufferPtr = std::shared_ptr<IAscanBuffer>;
    }
  }
}
