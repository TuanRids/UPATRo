///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\IPalette.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the IPalette interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "IColors.h"


namespace Olympus
{
  namespace View
  {
    class IPalette
    {
    public:
      virtual ~IPalette() = default;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the number of color in the collection.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @returns The count.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual std::wstring GetName() const = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a list of colors.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @returns A hexadecimal color specified with #RRGGBB.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IColorsConstPtr GetColors() const = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a list of special colors.
      ///
      /// Colors are related to data status in this order: has data, is synced on source, is detected
      /// NDE file domain path Not available in NDE
      ///
      /// @returns A hexadecimal color specified with #RRGGBB.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IColorsConstPtr GetSpecialColors() const = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a list of colors.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @returns A hexadecimal color specified with #RRGGBB.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IColorsPtr GetColors() = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a list of special colors.
      ///
      /// Colors are related to data status in this order: has data, is synced on source, is detected
      /// NDE file domain path Not available in NDE
      ///
      /// @returns A hexadecimal color specified with #RRGGBB.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual IColorsPtr GetSpecialColors() = 0;
    };

    using IPalettePtr = std::shared_ptr<IPalette>;
    using IPaletteConstPtr = std::shared_ptr<const IPalette>;
  }
}
