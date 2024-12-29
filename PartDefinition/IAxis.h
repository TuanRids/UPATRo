#pragma once
#include <memory>
#include <string>
#include <Equipment/IEncoderSensor.h>

namespace Olympus {
  namespace PartDefinition
  {
    class IAxis
    {
    public:
      virtual ~IAxis() = default;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Get the origin of the inspected area
      ///
      /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / 
      /// uCoordinateAxis or vCoordinateAxis / origin
      /// 
      /// @return
      /// Get the origin of the inspected area. The default value is zero, refering to the origin of the surface.
      /// The unit is defined by the Unit() function
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual double GetOrigin() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Set the origin of the inspected area
      ///
      /// @param origin
      /// Set the origin of the inspected area. The default value is zero, refering to the origin of the surface.
      /// The unit is defined by the Unit() function
      /// @return
      ///
      /// void
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void SetOrigin(double origin) = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Get the length of the inspected area
      ///
      /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / 
      /// uCoordinateAxis or vCoordinateAxis / length
      /// 
      /// @return
      /// Get the length of the inspected area from the origin. The default value is equal to the underlying
      /// surface length.
      /// The unit is defined by the Unit() function
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual double GetLength() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Set the length of the inspected area
      ///
      /// @param length
      /// Get the length of the inspected area from the origin. The default value is equal to the underlying
      /// surface length.
      /// Set the length of the inspected area from the origin. 
      /// The default value is equal to the underlying surface length.
      /// Axis length must be a mutiple of his resolution.
      /// The equation CellQuantity = (Length / Resolution) + 1 gives the size of the buffers.
      /// The unit is defined by the Unit() function
      /// @return
      ///
      /// void
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void SetLength(double length) = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Get the resolution of the inspected area
      ///
      /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / 
      /// uCoordinateAxis or vCoordinateAxis / resolution
      /// 
      /// @return
      /// The inspection resolution. The equation SampleQuantity = Ceiling(Length / Resolution) gives the
      /// size of the patch. The resolution is in Unit/sample.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual double GetResolution() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Set the resolution of the inspected area
      ///
      /// @param resolution
      /// The inspection resolution. The equation CellQuantity = (Length / Resolution) + 1 gives the
      /// size of the buffers. The resolution is in sample/Unit.
      /// @return
      ///
      /// void
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void SetResolution(double resolution) = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Get the unit of the axis
      ///
      /// NDE file domain path -- Always Meters
      /// 
      /// @return
      /// The unit of the axis. Default values are millimeters or degrees.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual const std::wstring& GetUnit() const = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Set the unit of the axis
      ///
      /// @param unit
      /// The unit of the axis. Default values are millimeters or degrees.
      /// @return
      ///
      /// void
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void SetUnit(const std::wstring& unit) = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Sets the encoder associated to this axis
      ///
      /// @param  encoder The encoder.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual void SetEncoder(Equipment::IEncoderSensorPtr encoder) = 0;

      ////////////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the encoder associated to this axis
      ///
      /// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan / 
      /// uCoordinateAxis or vCoordinateAxis / motionDeviceId
      /// 
      /// @returns  The encoder.
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual Equipment::IEncoderSensorPtr GetEncoder() const = 0;
    };

    using IAxisPtr = std::shared_ptr<IAxis>;
    using IAxisConstPtr = std::shared_ptr<const IAxis>;
  }
}
