///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file View\IColors.h.
///
/// NDE file domain path Not available in NDE
/// 
/// Declares the IColors interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>

namespace Olympus
{
  namespace View
  {
    class IColors
    {
    public:
      virtual ~IColors() = default;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets the number of color in the collection.
      ///
      /// @returns The count.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual std::size_t GetCount() const = 0;

      /////////////////////////////////////////////////////////////////////////////////////////////
      /// Gets a color.
      ///
      /// NDE file domain path Not available in NDE
      /// 
      /// @param index The index of the color.
      ///
      /// @returns A Hexadecimal color specified with #RRGGBB.
      /////////////////////////////////////////////////////////////////////////////////////////////
      virtual std::string GetColor(std::size_t index) const = 0;

      virtual void Add(const std::string& color) = 0;

    };

    using IColorsPtr = std::shared_ptr<IColors>;
    using IColorsConstPtr = std::shared_ptr<const IColors>;
  }
}
