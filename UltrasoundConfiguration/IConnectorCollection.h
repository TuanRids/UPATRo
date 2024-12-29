////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IConnectorCollection.h
///
/// Declares the IConnectorCollection interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IConnector;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Gives access to the connectors in this collection as well as the Voltage of the assigned pulser.
  /// A beam set can be fired on a connector with the IFiringBeamSetCollection interface.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IConnectorCollection
  {
  public:
    virtual ~IConnectorCollection() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the count for the number of connectors in this collection.
    ///
    /// @return
    /// The number of connectors.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::size_t GetCount() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the interface of one connector in this set by giving its index in the collection. 
    ///
    /// @param index The index of the requested connector in this collection.
    ///
    /// @return
    /// The interface IConnector of the requested connector.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IConnector> GetConnector(std::size_t index) const = 0;

    virtual std::shared_ptr<IConnector> GetReceiveConnector(size_t index= 0) const = 0;
    virtual std::shared_ptr<IConnector> GetPulseConnector(size_t index= 0) const = 0;
    virtual std::shared_ptr<IConnector> GetPulseAndReceiveConnector(size_t index= 0) const = 0;
  };

  using IConnectorCollectionPtr = std::shared_ptr<IConnectorCollection>;
  using IConnectorCollectionConstPtr = std::shared_ptr<const IConnectorCollection>;
}
