////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAcquisitionData.h
///
/// The acquisition data is the data stored in the memory. It includes the setup as well as the data
/// received from the FocusPX.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <string>
#include <storage/IBufferKeyCollection.h>
#include <storage/IAscanBufferKeyCollection.h>
#include <storage/ICscanBufferKeyCollection.h>
#include <storage/IAscanBufferCollection.h>
#include <storage/IAscanBufferBeamKeyCollection.h>
#include <storage/IAscanMergedBufferKey.h>
#include <storage/ICscanBufferCollection.h>
#include <storage/ICscanBufferBeamKeyCollection.h>
#include <storage/ICscanMergedBufferKey.h>

namespace Olympus
{
  namespace FileManagement
  {
    class IAcquisitionData
    {
    public:
      virtual ~IAcquisitionData() = default;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Creates the Ascan and Cscan buffers for the setup used in CreateAcquisitionData() call.
      ///
      /// Cscan buffers are created only if the call ReserveCscanBuffer(bool) for the corresponding gate
      /// configuration in the setup has been set to true.
      /// 
      /// Patch axes length must be a mutiple of his resolution.
      /// Unsed patch axis dimension ex.:index axis must have all values set to zero.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void CreateBuffers() = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffer keys.
      ///
      /// @returns The Ascan buffer keys.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferKeyCollectionConstPtr GetAscanBufferKeys() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets an Ascan buffer.
      ///
      /// @param key The key used to retrieve the buffer.
      ///
      /// @returns The Ascan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferPtr GetAscanBuffer(Ultrasound::Data::IAscanBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Ascan buffers in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      ///
      /// @returns The found Ascan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferCollectionConstPtr FindAscanBuffers(const std::wstring& beamSetName) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffer keys.
      ///
      /// @returns The Cscan buffer keys.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferKeyCollectionConstPtr GetCscanBufferKeys() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a Cscan buffer.
      ///
      /// @param key The key used to retrieve the buffer.
      ///
      /// @returns The Cscan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferPtr GetCscanBuffer(Ultrasound::Data::ICscanBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Cscan buffers for a particular gate in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      /// @param gateName    Name of the gate.
      ///
      /// @returns The found Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferCollectionConstPtr FindCscanBuffers(const std::wstring& beamSetName, const std::wstring& gateName) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Close the buffers.
      ///
      /// Once the data has been written, the buffers must be closed before saving the file with
      /// the call SaveDataFile() otherwise an exception will be thrown.
      ///
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void CloseBuffers() = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Cscan buffers in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      ///
      /// @returns The found Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferCollectionConstPtr FindCscanBuffersEx(const std::wstring& beamSetName) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the buffer keys.
      /// Each key are unique and correspond to a configuration.
      /// Sub keys determine the data type and buffer format.
      ///
      /// @returns The buffer keys.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IBufferKeyCollectionConstPtr GetBufferKeys() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffers.
      ///
      /// @param key  The key used to retrieve buffers for every beams of a configuration.
      ///
      /// @returns The Ascan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferCollectionConstPtr GetAscanBeamBuffers(Ultrasound::Data::IAscanBufferBeamKeyCollectionConstPtr keys) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a beam of a configuration.
      ///
      /// @returns The Ascan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferPtr GetAscanBeamBuffer(Ultrasound::Data::IAscanBufferBeamKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a multibeam configuration.
      ///
      /// @returns The Ascan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IAscanBufferPtr GetAscanMergedBuffer(Ultrasound::Data::IAscanMergedBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key The key used to retrieve buffers for every beams of a configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferCollectionConstPtr GetCscanBeamBuffers(Ultrasound::Data::ICscanBufferBeamKeyCollectionConstPtr keys) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key  The key used to retrieve buffers by beam for every gates of a configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferCollectionConstPtr GetCscanGateBuffers(Ultrasound::Data::ICscanBufferBeamKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a beam and gate of a configuration.
      ///
      /// @returns The Cscan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferPtr GetCscanGateBuffer(Ultrasound::Data::ICscanBufferBeamGateKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key The key used to retrieve a buffer for every gates of a multibeam configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferCollectionConstPtr GetCscanMergedBuffers(Ultrasound::Data::ICscanMergedBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a gate of a multibeam configuration.
      ///
      /// @returns The Cscan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::ICscanBufferPtr GetCscanMergedBuffer(Ultrasound::Data::ICscanMergedBufferGateKeyConstPtr key) const = 0;

    };

    using IAcquisitionDataPtr = std::shared_ptr<IAcquisitionData>;
    using IAcquisitionDataConstPtr = std::shared_ptr<const IAcquisitionData>;
  }
}
