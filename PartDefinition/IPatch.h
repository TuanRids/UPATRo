#pragma once
#include <memory>
#include <PartDefinition/IAxis.h>
#include <PartDefinition/IMappingUV.h>
#include <Equipment/IEncoderSensor.h>

namespace Olympus { namespace PartDefinition
{
  enum class ScanType { OneLineScan, RasterScan, Helicoidal };

class IPatch
{
public:
  virtual ~IPatch() = default;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the scan axis of the patch
  ///
  /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / uCoordinateAxis
  /// 
  /// @return
  /// The scan axis, following the same direction as the scan encoder.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual IAxisPtr GetScanAxis() = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the scan axis of the patch
  ///
  /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / uCoordinateAxis
  /// 
  /// @return
  /// The const scan axis, following the same direction as the scan encoder.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual IAxisConstPtr GetScanAxis() const = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the index axis of the patch
  ///
  /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / vCoordinateAxis
  /// 
  /// @return
  /// The index axis, following the same direction as the index encoder.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual IAxisPtr GetIndexAxis() = 0;


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the index axis of the patch
  ///
  /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / vCoordinateAxis
  /// 
  /// @return
  /// The const index axis, following the same direction as the index encoder.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual IAxisConstPtr GetIndexAxis() const = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the inspected Surface linked to the patch
  ///
  /// NDE file domain path specimens[index] / pipeGeometry or plateGeometry or barGeometry / surfaces 
  /// 
  /// @return
  /// The inspected Surface linked to the patch. In basic setups, this refers to the Top() of the
  /// plate specimen or the Inside or Outside of the Pipe specimen.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual IMappingUVConstPtr GetSurface() const = 0;

  /////////////////////////////////////////////////////////////////////////////////////////////
  /// Gets scan type inspection
  ///
  /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan
  /// 
  /// @returns The scanType type.
  /////////////////////////////////////////////////////////////////////////////////////////////
  virtual ScanType GetScanType() const = 0;

  /////////////////////////////////////////////////////////////////////////////////////////////
  /// Sets scan type inspection
  ///
  /// @param scanType The scanType.
  /////////////////////////////////////////////////////////////////////////////////////////////
  virtual void SetScanType(ScanType scanType) = 0;
};

using IPatchPtr = std::shared_ptr<IPatch>;
using IPatchConstPtr = std::shared_ptr<const IPatch>;
}}
