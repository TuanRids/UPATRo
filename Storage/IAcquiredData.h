////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAcquiredData.h
///
/// The acquired data is the data stored in the file. It can also be seen as previously recorded
/// acquisition data, that is now saved in a file. It includes the setup as well as the data
/// received from the FocusPX.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <memory>
#include <Storage/ISetup.h>
#include <storage/IReadOnlyAscanBufferCollection.h>
#include <storage/IReadOnlyCscanBufferCollection.h>
#include <storage/IReadOnlyTotalFocusingMethodBuffer.h>
#include <storage/IAscanBufferKeyCollection.h>
#include <storage/ICscanBufferKeyCollection.h>
#include <storage/IBufferKeyCollection.h>
#include <storage/IAscanBufferBeamKeyCollection.h>
#include <storage/IAscanMergedBufferKey.h>
#include <storage/ICscanBufferBeamKeyCollection.h>
#include <storage/ICscanMergedBufferKey.h>

namespace Olympus
{
  namespace FileManagement
  {
    class IAcquiredData
    {
    public:
      virtual ~IAcquiredData() = default;

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
      virtual Ultrasound::Data::IReadOnlyAscanBufferConstPtr GetAscanBuffer(Ultrasound::Data::IAscanBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Ascan buffers in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      ///
      /// @returns The found Ascan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyAscanBufferCollectionConstPtr FindAscanBuffers(const std::wstring& beamSetName) const = 0;

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
      virtual Ultrasound::Data::IReadOnlyCscanBufferConstPtr GetCscanBuffer(Ultrasound::Data::ICscanBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Cscan buffers for a particular gate in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      /// @param gateName    Name of the gate.
      ///
      /// @returns The found Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferCollectionConstPtr FindCscanBuffers(const std::wstring& beamSetName, const std::wstring& gateName) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for all Cscan buffers in a beamset.
      ///
      /// @param beamSetName Name of the beamset.
      ///
      /// @returns The found Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferCollectionConstPtr FindCscanBuffers(const std::wstring& beamSetName) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Search for a specific Total Focusing Method (FMC) buffer.
      ///
      /// @param name The name of the Inspection Method which is part of a configuration.
      ///
      /// @returns The found TFM buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyTotalFocusingMethodBufferConstPtr FindTotalFocusingMethodBuffer(const std::wstring& name) const = 0;

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
      virtual Ultrasound::Data::IReadOnlyAscanBufferCollectionConstPtr GetAscanBeamBuffers(Ultrasound::Data::IAscanBufferBeamKeyCollectionConstPtr keys) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a beam of a configuration.
      ///
      /// @returns The Ascan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyAscanBufferConstPtr GetAscanBeamBuffer(Ultrasound::Data::IAscanBufferBeamKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Ascan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a multibeam configuration.
      ///
      /// @returns The Ascan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyAscanBufferConstPtr GetAscanMergedBuffer(Ultrasound::Data::IAscanMergedBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key The key used to retrieve buffers for every beams of a configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferCollectionConstPtr GetCscanBeamBuffers(Ultrasound::Data::ICscanBufferBeamKeyCollectionConstPtr keys) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key  The key used to retrieve buffers by beam for every gates of a configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferCollectionConstPtr GetCscanGateBuffers(Ultrasound::Data::ICscanBufferBeamKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a beam and gate of a configuration.
      ///
      /// @returns The Cscan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferConstPtr GetCscanGateBuffer(Ultrasound::Data::ICscanBufferBeamGateKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffers.
      ///
      /// @param key The key used to retrieve a buffer for every gates of a multibeam configuration.
      ///
      /// @returns The Cscan buffers.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferCollectionConstPtr GetCscanMergedBuffers(Ultrasound::Data::ICscanMergedBufferKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Cscan buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a gate of a multibeam configuration.
      ///
      /// @returns The Cscan buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyCscanBufferConstPtr GetCscanMergedBuffer(Ultrasound::Data::ICscanMergedBufferGateKeyConstPtr key) const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the Total Focusing Method buffer.
      ///
      /// @param key  The key used to retrieve a buffer for a configuration.
      ///
      /// @returns The Total Focusing Method buffer.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Ultrasound::Data::IReadOnlyTotalFocusingMethodBufferConstPtr GetTotalFocusingMethodBuffer(Ultrasound::Data::ITotalFocusingMethodBufferKeyConstPtr key) const = 0;
    };

    using IAcquiredDataPtr = std::shared_ptr<IAcquiredData>;
    using IAcquiredDataConstPtr = std::shared_ptr<const IAcquiredData>;
  }
}
