////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IAscanBufferDescriptor.h.
///
///  Contains all the definitions to interpret the buffer's data 
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <memory>
#include <Storage/IDataAxis.h>
#include <Storage/IAscanBufferKey.h>
#include <Storage/IAscanBufferKeyEx.h>

namespace Olympus {
  namespace Ultrasound {
    namespace Data
    {
      class IAscanBufferDescriptor
      {
      public:
        virtual ~IAscanBufferDescriptor() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the key the get access to the AScanBuffer associated to this descriptor
        ///
        /// @returns  The key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IAscanBufferKeyConstPtr GetKey() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the scan axis description
        /// 
        /// NDE file domain path: "dataEncodings"[index] / "discreteGrid" / oneLineScan or rasterScan / uCoordinateAxis
        /// 
        /// @returns  The scan axis.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IDataAxisConstPtr GetScanAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the index axis description
        /// 
        /// NDE file domain path: "dataEncodings"[index] / "discreteGrid" / oneLineScan or rasterScan / vCoordinateAxis
        /// 
        /// @returns  The index axis.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IDataAxisConstPtr GetIndexAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the Amplitude axis description. Typically the unit of this axis is "Percentage". This axis
        /// may be used in conjunction with the AmplitudeSamplingAxis to calculate a rule of three.
        /// 
        /// NDE file domain path: dataGroups[index] / ultrasound / sectorialPulseEcho or linearPulseEcho
        /// or compoundPulseEcho / amplitudePercentAxis
        /// 
        /// @returns  The amplitude axis.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IDataAxisConstPtr GetAmplitudeAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the Amplitude sampling axis description. Typically the unit of this axis is "Unit". This axis
        /// may be used in conjunction with the AmplitudeAxis to calculate a rule of three.
        /// 
        /// NDE file domain path: dataGroups[index] / ultrasound / datasets[index] / ascan / amplitudeSamplingAxis
        /// 
        /// @returns  The amplitude sampling axis.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IDataAxisConstPtr GetAmplitudeSamplingAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the ultrasound axis description to define the time sampling. The minimum of the axis
        /// corresponds to the digitizing delay and the maximum to (digitizing delay + digitizing length).
        /// The unit for this axis can be retrieved from IDataAxis::GetUnit().
        /// 
        /// NDE file domain path: "dataGroups"[index] / "ultrasound" / "conventionalPulseEcho" or conventionalPitchCatch or tofd / "ultrasoundAxis"
        /// 
        /// NDE file domain path: "dataGroups"[index] / "ultrasound" / sectorialPulseEcho or linearPulseEcho / beams[index] / ultrasoundAxis
        /// 
        /// @returns  The ultrasound axis.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IDataAxisConstPtr GetUltrasoundAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the refracted angle of the beam when it enters in the material. This relates to the primary 
        /// axis of the probe. See IElementOffset::GetPrimary() for the definition of the probe axis.
        /// 
        /// @returns  The refracted angle in degree
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetRefractedAnglePrimaryAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the refracted angle of the beam when it enters in the material. This relates to the secondary 
        /// axis of the probe. See IElementOffset::GetSecondary() for the definition of the probe axis. While
        /// using a single array transducer this value will typically be zero.
        /// 
        /// @returns  The refracted angle in degree
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetRefractedAngleSecondaryAxis() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets ultrasound velocity in the inspected material
        /// 
        /// NDE file domain path  dataGroups[index] / ultrasound / sectorialPulseEcho or linearPulseEcho
        /// or compoundPulseEcho / velocity
        /// 
        /// @returns  The ultrasound velocity in meter per seconds.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetUltrasoundVelocity() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Query if the buffer include every beams or not.
        ///
        /// @returns True if buffer will be merged, false if not.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool IsBufferMerged() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the key the get access to the buffer associated to this descriptor.
        /// Can be cast to IAscanBufferBeamKey or IAscanMergedBufferKey.
        ///
        /// @returns  The key.
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual IAscanBufferKeyExConstPtr GetKeyEx() const = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the data amplitude multiplier factor
        /// If this value is different of 1 data must be adjusted to have the good representation.
        ///
        /// Example of adjustment:
        /// std::vector<short> samples;
        /// const short* dataPtr = reinterpret_cast<const short*>(m_Buffer);
        /// samples.assign(dataPtr, dataPtr + m_SampleQty);
        /// std::for_each(samples.begin(), samples.end(), [&](short &v) { v *= m_Factor; });
        /// 
        /// @returns The Ascan data amplitude multiplier factor.
        /////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetAmplitudeMultiplierFactor() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the refracted angle of the beam when it enters in the material.
        /// 
        /// @returns  The refracted angle in degree
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetRefractedAngle() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the skew angle 
        /// 
        /// @returns  The skew angle in degree
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual double GetSkewAngle() const = 0;

      };

      using IAscanBufferDescriptorConstPtr = std::shared_ptr<const IAscanBufferDescriptor>;
    }
  }
}
