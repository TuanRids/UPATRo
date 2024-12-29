#pragma once
#include <cstddef>
#include <PartDefinition/IPatch.h>


///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file PartDefinition\Specimen.h.
///
/// NDE file domain path  dataEncodings / discreteGrid / oneLineScan or rasterScan /
/// 
/// Assembles all the specimen classes
///////////////////////////////////////////////////////////////////////////////////////////////////


namespace Olympus {
  namespace PartDefinition
  {
    class IPatchCollection
    {
    public:
      virtual ~IPatchCollection() = default;

      virtual std::size_t GetCount() const = 0;
      virtual IPatchConstPtr GetPatch(std::size_t) const = 0;
      virtual IPatchPtr GetPatch(std::size_t) = 0;
    };

    using IPatchCollectionPtr = std::shared_ptr<IPatchCollection>;
    using IPatchCollectionConstPtr = std::shared_ptr<const IPatchCollection>;
  }
}
