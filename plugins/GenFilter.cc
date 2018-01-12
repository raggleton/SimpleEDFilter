// -*- C++ -*-
//
// Package:    GenDump/GenFilter
// Class:      GenFilter
// 
/**\class GenFilter GenFilter.cc GenDump/GenFilter/plugins/GenFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Robin Aggleton
//         Created:  Fri, 12 Jan 2018 14:40:38 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//
// class declaration
//

class GenFilter : public edm::stream::EDFilter<> {
   public:
      explicit GenFilter(const edm::ParameterSet&);
      ~GenFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<reco::GenParticleCollection> gpToken_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenFilter::GenFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
    gpToken_ = consumes<reco::GenParticleCollection>(iConfig.getUntrackedParameter<edm::InputTag>("gp_src", edm::InputTag("genParticles")));

}


GenFilter::~GenFilter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GenFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
  
    edm::Handle<reco::GenParticleCollection> gpColl;
    iEvent.getByToken(gpToken_, gpColl);

    bool interestingEvent = false;
    for (const auto & itr : *gpColl) {
        if (abs(itr.pdgId()) == 24 && itr.pt() > 400 && itr .pt() < 600) {
            interestingEvent = true;
            break;
        }
    }

   return interestingEvent;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
GenFilter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
GenFilter::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
GenFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
GenFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
GenFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
GenFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(GenFilter);
