////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file ultrasoundConfiguration/IBeamSet.h
///
/// Declares the IBeamSet interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <ultrasoundConfiguration/UltrasoundTypes.h>

namespace Instrumentation
{
  class IBeamSet;
  class IBeamFormation;
  class IBeamFormationCollection;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// An interface used to create beam formations and beam sets.   
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class IBeamSetFactory
  {
  public:
    virtual ~IBeamSetFactory() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create a conventional ultrasound beam set's interface, IBeamSet, by giving it a 
    /// name and associating it with an IDigitizerTechnology interface. An IBeamSet interface will be 
    /// created. 
    ///
    /// @param name The desired beam set's name. 
    /// 
    /// @return
    /// The interface IBeamSet created.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamSet> CreateBeamSetConventional(const std::wstring& name) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create a phased array ultrasound beam set's interface, IBeamSet, by giving it a name, by
    /// associating it with the IDigitizerTechnology interface and by assigning it a 
    /// beam formation's interface. Multiples IBeam interfaces will be created with the element delays
    /// from the formation.
    ///
    /// @param name The desired beam set's name. 
    /// @param beamFormations The interface IBeamFormationCollection. 
    /// 
    /// @return
    /// The interface IBeamSet created containing all the IBeams.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamSet> CreateBeamSetPhasedArray(const std::wstring& name, std::shared_ptr<IBeamFormationCollection> beamFormations) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create a beam set formation using a law file as a starting point. The law file will be used to
    /// create the beams of the beam set, which will be given the different element delays of the law file. 
    /// A beam formation collection is required to create a phased array beam set.
    ///
    /// @param lawFilePath The path for the law file.
    /// 
    /// @return
    /// The created IBeamFormationCollection interface.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamFormationCollection> CreateBeamFormationCollectionFromLawFile(const std::wstring& lawFilePath) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create an empty beam set formation that can be filled using the IBeamFormationCollection::Add 
    /// function. A beam formation collection is required to create a phased array beam set.
    /// 
    /// @return
    /// The created IBeamFormationCollection interface.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamFormationCollection> CreateBeamFormationCollection() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create an beam formation using the given quantities of delays for the pulser and receiver.  
    ///
    /// @param pulserQuantity The number of delays that the collection will contain for pulsers.
    /// @param receiverQuantity The number of delays that the collection will contain for receivers.
    ///
    /// @return
    /// The created IBeamFormation interface.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual std::shared_ptr<IBeamFormation> CreateBeamFormation(std::size_t pulserQuantity, std::size_t receiverQuantity, std::size_t firstPulserElementId = 1, std::size_t firstReceiverElementId = 1) = 0;

  };
}
