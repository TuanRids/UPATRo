////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file FileManagement.h
///
/// Creates, saves and opens setup or data files.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <string>
#include <storage/StorageExport.h>


namespace Olympus { namespace FileManagement
{
  class ICustomSectionCollection;
  using ICustomSectionCollectionPtr = std::shared_ptr<ICustomSectionCollection>;
  using ICustomSectionCollectionConstPtr = std::shared_ptr<const ICustomSectionCollection>;

  class ISetup;
  using ISetupPtr = std::shared_ptr<ISetup>;
  using ISetupConstPtr = std::shared_ptr<const ISetup>;

  class ISetupFile;
  using ISetupFilePtr = std::shared_ptr<ISetupFile>;
  using ISetupFileConstPtr = std::shared_ptr<const ISetupFile>;

  class IAcquisitionData;
  using IAcquisitionDataPtr = std::shared_ptr<IAcquisitionData>;
  using IAcquisitionConstDataPtr = std::shared_ptr<const IAcquisitionData>;

  class IAcquiredData;
  using IAcquiredDataPtr = std::shared_ptr<IAcquiredData>;
  using IAcquiredDataConstPtr = std::shared_ptr<const IAcquiredData>;

  class IDataFile;
  using IDataFilePtr = std::shared_ptr<IDataFile>;
  using IDataFileConstPtr = std::shared_ptr<const IDataFile>;

  class IApplicationStamp;
  using IApplicationStampPtr = std::shared_ptr<IApplicationStamp>;

  class IOriginalFileSource;
  using IOriginalFileSourcePtr = std::shared_ptr<IOriginalFileSource>;

  class IGeoCoordinate;
  using IGeoCoordinatePtr = std::shared_ptr<IGeoCoordinate>;

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a setup file
  ///
  /// @param destinationFile Destination file.
  /// @param setup           The setup.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveSetupFile( const std::wstring& destinationFile, ISetupPtr setup);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a setup file
  ///
  /// @param destinationFile Destination file.
  /// @param setup           The setup.
  /// @param customSections  The custom sections.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveSetupFile(const std::wstring& destinationFile, ISetupPtr setup,
    ICustomSectionCollectionPtr customSections);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param acquisitionData Information describing the acquisition.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile,
    IAcquisitionDataPtr acquisitionData);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param acquisitionData Information describing the acquisition.
  /// @param customSections  The custom sections.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile, 
    IAcquisitionDataPtr acquisitionData,
    ICustomSectionCollectionPtr customSections);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param dataFile Previously saved dataFile.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile, IDataFilePtr dataFile);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Opens a setup file
  ///
  /// @param sourceFile Source file.
  ///
  /// @returns An ISetupFilePtr.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API ISetupFilePtr OpenSetupFile(const std::wstring& sourceFile);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Opens a data file
  ///
  /// @param sourceFile Source file.
  ///
  /// @returns An IDataFilePtr.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API IDataFilePtr OpenDataFile(const std::wstring& sourceFile);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param acquisitionData Information describing the acquisition.
  /// @param appStamp Application stamp to create the file signature.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile,
    IAcquisitionDataPtr acquisitionData, IApplicationStampPtr appStamp);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param acquisitionData Information describing the acquisition.
  /// @param customSections  The custom sections.
  /// @param appStamp Application stamp to create the file signature.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile,
    IAcquisitionDataPtr acquisitionData,
    ICustomSectionCollectionPtr customSections,
    IApplicationStampPtr appStamp);

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// Saves a data file
  ///
  /// @param destinationFile Destination file.
  /// @param dataFile Previously saved dataFile.
  /// @param appStamp Application stamp to create the file signature.
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  STORAGE_API void SaveDataFile(const std::wstring& destinationFile, IDataFilePtr dataFile,
    IApplicationStampPtr appStamp);


  namespace Storage
  {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new setup
    ///
    /// @returns The new setup.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API ISetupPtr CreateSetup();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new instance of ICustomSectionCollection.
    ///
    /// @returns Pointer to the newly created object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API ICustomSectionCollectionPtr CreateCustomSectionCollection();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new acquisition data to create buffers based on the setup.
    ///
    /// @param setup an existing setup.
    ///
    /// @returns A pointer to the new acquisition data object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API IAcquisitionDataPtr CreateAcquisitionData(ISetupPtr setup);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Version of the library.
    ///
    /// @returns The loaded OlympusNDT.Storage library version.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    __declspec(deprecated("Deprecated. Use GetLibraryVersion"))
    STORAGE_API std::string GetVersion();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Enable to log library operations.
    ///
    /// @returns bool True if the the configuration file "Log.properties" was found.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    __declspec(deprecated("Deprecated. Log is always enabled")) STORAGE_API bool EnableLogger();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new acquisition data to create buffers based on the setup.
    ///
    /// @param setup an existing setup.
    ///
    /// @returns IAcquisitionDataPtr A pointer to the new acquisition data object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
  #ifndef SWIG
    __declspec(deprecated("Deprecated. Use CreateAcquisitionData")) 
      STORAGE_API IAcquisitionDataPtr CreateDataStorage(ISetupPtr setup);
  #endif

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new original file source.
    ///
    /// @param fileName a file were data was originally collected.
    ///
    /// @returns IOriginalFileSourcePtr A pointer to the new origianl file source object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API IOriginalFileSourcePtr CreateOriginalFileSource(const std::wstring& fileName,
      const std::string& dateTime);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new application stamp.
    ///
    /// @param companyName a name.
    /// @param appName an application name.
    /// @param appVersion an application version.
    ///
    /// @returns IOriginalFileSourcePtr A pointer to the new origianl file source object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API IApplicationStampPtr CreateApplicationStamp(const std::wstring& companyName,
      const std::wstring& appName, const std::wstring& appVersion,
      IOriginalFileSourcePtr originalFileSource = nullptr);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Version of the library.
    ///
    /// @returns The loaded OlympusNDT.Storage library semantic version.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API std::wstring GetLibraryVersion();


    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a GeoCoordinate.
    ///
    /// @param GeoCoordinate where the data file was taken.
    ///
    /// @returns IGeoCoordinatePtr
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API IGeoCoordinatePtr CreateGeoCoordinate(double latitude, double longitude);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new application stamp.
    ///
    /// @param companyName a name.
    /// @param appName an application name.
    /// @param appVersion an application version.
    /// @param originalFileSource an optional original file source.
    /// @param GeoCoordinate: gps coordinate saved in the file.
    ///
    /// @returns IOriginalFileSourcePtr A pointer to the new origianl file source object.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API IApplicationStampPtr CreateApplicationStamp(const std::wstring& companyName,
      const std::wstring& appName, const std::wstring& appVersion,
      IOriginalFileSourcePtr originalFileSource,
      IGeoCoordinatePtr GeoCoordinate);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /// Saves a data file
    ///
    /// @param destinationFile Destination file.
    /// @param dataFile Previously saved dataFile.
    /// @param appStamp Application stamp to create the file signature.
    /// @param fileVersion Version of the format.
    /// @param compressionLevel Level of compression (0-9). OBSELETE
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API void SaveDataFile(const std::wstring& destinationFile, IDataFilePtr dataFile,
      IApplicationStampPtr appStamp, const std::string& fileVersion, uint8_t /*compressionLevel*/);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /// Saves a data file
    ///
    /// @param destinationFile Destination file.
    /// @param dataFile Previously saved dataFile.
    /// @param appStamp Application stamp to create the file signature.
    /// @param fileVersion Version of the format.
    /// @param compressionLevel Level of compression (0-9) OBSELETE.
    /// @param configCount Configuration count saved from file source.
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    STORAGE_API void SaveDataFile(const std::wstring& destinationFile, IDataFilePtr dataFile,
      IApplicationStampPtr appStamp, const std::string& fileVersion, uint8_t /*compressionLevel*/, uint16_t configCount);
  }
}
