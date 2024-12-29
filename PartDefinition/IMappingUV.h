#pragma once
#include <memory>

namespace Olympus { namespace PartDefinition
{
class IMappingUV
{
public:
  virtual ~IMappingUV() = 0;
};

using IMappingUVPtr = std::shared_ptr<IMappingUV>;
using IMappingUVConstPtr = std::shared_ptr<const IMappingUV>;
}}

inline Olympus::PartDefinition::IMappingUV::~IMappingUV() {
}

