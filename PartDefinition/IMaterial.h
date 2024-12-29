#pragma once
#include <memory>
#include <string>

namespace Olympus { namespace PartDefinition
{
/**
* JSON format location:
*   specimens.material
*   specimens.*Geometry.material
*   specimens.weldGeometry.material
*/
class IMaterial
{
public:
  virtual ~IMaterial() = default;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the name of the material
  ///
  /// NDE file domain path specimens[index] / pipeGeometry or plateGeometry or barGeometry / material / name
  /// 
  /// @return
  /// The name of the material
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual const std::wstring& GetName() const = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Set the name of the material
  ///
  /// @param name
  /// The name of the material
  /// @return
  ///
  /// void
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual void SetName(const std::wstring& name) = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the longitudinal velocity in the material
  ///
  /// NDE file domain path specimens[index] / pipeGeometry or plateGeometry or barGeometry / material /
  ///  longitudinalWave / nominalVelocity
  /// 
  /// @return
  /// The longitudinal velocity in the material expressed in meter per second
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual double GetLongitudinalVelocity() const = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Set the longitudinal velocity in the material
  ///
  /// @param velocity
  /// The longitudinal velocity in the material expressed in meter per second
  /// @return
  ///
  /// void
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual void SetLongitudinalVelocity(double velocity) = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Get the shear velocity in the material
  ///
  /// NDE file domain path specimens[index] / pipeGeometry or plateGeometry or barGeometry / material /
  ///  transversalVerticalWave / nominalVelocity
  /// 
  /// @return
  /// The shear velocity in the material expressed in meter per second
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual double GetShearVelocity() const = 0;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Set the shear velocity in the material
  ///
  /// @param velocity
  /// The shear velocity in the material expressed in meter per second
  /// @return
  ///
  /// void
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual void SetShearVelocity(double velocity) = 0;
};

using IMaterialPtr = std::shared_ptr<IMaterial>;
using IMaterialConstPtr = std::shared_ptr<const IMaterial>;
}}
