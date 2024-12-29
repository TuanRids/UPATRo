////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file IGeometry.h
///
/// NDE file domain path specimens[index] / pipeGeometry or plateGeometry or barGeometry
/// 
/// Declares the Geometry structure
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>

namespace Olympus { namespace PartDefinition {

class IGeometry
{
public:
  virtual ~IGeometry() = 0;
};

using IGeometryPtr = std::shared_ptr<IGeometry>;
using IGeometryConstPtr = std::shared_ptr<const IGeometry>;
}}

inline Olympus::PartDefinition::IGeometry::~IGeometry() = default;
