#pragma once
namespace Olympus {
  namespace FileManagement
  {
    constexpr const char DATAFILE_VERSION_DEV[] = "0.0.0";   // For development purpose

    constexpr const char DATAFILE_VERSION_100[] = "1.0.0.0"; // Initial version
    constexpr const char DATAFILE_VERSION_101[] = "1.0.1.0"; // Scan & index cell computation
    constexpr const char DATAFILE_VERSION_102[] = "1.0.2.0"; // Cscan crossing & amplitude position
    constexpr const char DATAFILE_VERSION_110[] = "1.1.0";   // File signature with original file source
    constexpr const char DATAFILE_VERSION_120[] = "1.2.0";   // Add attributes for Cscan dataset
    constexpr const char DATAFILE_VERSION_130[] = "1.3.0";   // Add view properties, gate geometry and custom format/usage.

    constexpr const char DATAFILE_VERSION_205[] = "2.0.5-Draft";   // Axes Attributes + JSON setup draft
    constexpr const char DATAFILE_VERSION_206[] = "2.0.6-Draft";   // CscanData3 struture

    constexpr const char DATAFILE_VERSION_210[] = "2.1.0-Draft";   // UnifiedFileAccess component
    constexpr const char DATAFILE_VERSION_220[] = "2.2.0";         // Descriptors

    constexpr const char DATAFILE_VERSION_2210[] = "2.2.10";       // Vestas OVD
    constexpr const char DATAFILE_VERSION_2211[] = "2.2.11";       // nde

    //

    constexpr const char DOMAINSETUP_VERSION_DEV[] = "0.0.0";       // For development purpose
    constexpr const char DOMAINSETUP_VERSION_008[] = "0.0.8";       // Vestas OVD
    constexpr const char DOMAINSETUP_VERSION_100[] = "1.0.0";       // nde
  }
}
