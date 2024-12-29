///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\IViewProperties.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the IViewProperties interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include <View/IPaletteCollection.h>
#include <View/IOverlay.h>

namespace Olympus
{
  namespace View
  {
    class IViewProperties
    {
    public:
      virtual ~IViewProperties() = default;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the palettes collection.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @returns A pointer to the collection of palettes.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IPaletteCollectionConstPtr GetPalettes() const = 0;

      virtual IPaletteCollectionPtr GetPalettes() = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the overlay collection.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @returns A pointer to the collection of overlays.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IOverlayConstPtr GetOverlay() const = 0;

      virtual IOverlayPtr GetOverlay() = 0;
    };

    using IViewPropertiesPtr = std::shared_ptr<IViewProperties>;
    using IViewPropertiesConstPtr = std::shared_ptr<const IViewProperties>;
  }
}
