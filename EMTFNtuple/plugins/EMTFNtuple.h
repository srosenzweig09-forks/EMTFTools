// -*- C++ -*-
//
// Package:    EMTFTools/EMTFNtuple
// Class:      EMTFNtuple
//
/**\class EMTFNtuple EMTFNtuple.cc EMTFTools/EMTFNtuple/plugins/EMTFNtuple.cc

 Description: Creates flat ntuples to be used for EMTF studies.

*/
//
// Original Author:  Efe Yigitbasi
//         Created:  Tue, 01 Sep 2020 10:52:51 GMT
//
//

// system include files
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdint>

// ROOT includes
#include "TString.h"
#include "TFile.h"
#include "TTree.h"

// CMSSW includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"
#include "L1Trigger/L1TMuonEndCap/interface/Common.h"
#include "L1Trigger/L1TMuonEndCap/interface/EMTFSubsystemCollector.h"
#include "DataFormats/L1Trigger/interface/Muon.h"


//
// ----------------------------------------------------
//

class EMTFNtuple : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit EMTFNtuple(const edm::ParameterSet&);
  ~EMTFNtuple();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // Aux functions
  void getHandles(const edm::Event& iEvent, const edm::EventSetup& iSetup);
  void makeTree();


  template<typename T>
  edm::Handle<T> make_handle(T& t)
  {
    return edm::Handle<T>();
  }

  template<typename T>
  edm::Handle<T> make_handle(T* t)
  {
    return edm::Handle<T>();
  }

  // ----------member data ---------------------------

  // Input parameters
  
  // Run 3 TPs
  const edm::InputTag   CSCInputTag_;
  const edm::InputTag   RPCInputTag_;
  const edm::InputTag   CPPFInputTag_;
  const edm::InputTag   GEMInputTag_;

  // Phase 2 TPs
  const edm::InputTag   IRPCInputTag_;
  const edm::InputTag   ME0InputTag_;
  const edm::InputTag   DTInputTag_;


  // L1T collections
  const edm::InputTag   EMTFHitTag_;
  const edm::InputTag   EMTFTrackTag_;
  const edm::InputTag   GMTMuonTag_;
  const edm::InputTag   GENPartTag_;

  const std::string     outFileName_;
  int verbose_;
  bool enablePhase2_;
  bool enableCPPF_;


  // Run 3 TPs
  edm::EDGetTokenT<emtf::CSCTag::digi_collection>   CSCInputToken_;
  edm::EDGetTokenT<emtf::RPCTag::digi_collection>   RPCInputToken_;
  edm::EDGetTokenT<emtf::CPPFTag::digi_collection>  CPPFInputToken_;
  edm::EDGetTokenT<emtf::GEMTag::digi_collection>   GEMInputToken_;

  // Phase 2 TPs
  edm::EDGetTokenT<emtf::IRPCTag::digi_collection>  IRPCInputToken_;
  edm::EDGetTokenT<emtf::ME0Tag::digi_collection>   ME0InputToken_;
  edm::EDGetTokenT<emtf::DTTag::digi_collection>    DTInputToken_;
  
  // L1T collections
  edm::EDGetTokenT<l1t::EMTFHitCollection>          EMTFHitToken_;
  edm::EDGetTokenT<l1t::EMTFTrackCollection>        EMTFTrackToken_;
  edm::EDGetTokenT<l1t::MuonBxCollection>           GMTMuonToken_;
  edm::EDGetTokenT<reco::GenParticleCollection>     GENPartToken_;

  
  
  TriggerPrimitiveCollection  CSCInputs_;
  TriggerPrimitiveCollection  RPCInputs_;
  TriggerPrimitiveCollection  CPPFInputs_;
  TriggerPrimitiveCollection  GEMInputs_;

  TriggerPrimitiveCollection  IRPCInputs_;
  TriggerPrimitiveCollection  ME0Inputs_;
  TriggerPrimitiveCollection  DTInputs_;

  l1t::EMTFHitCollection      EMTFHits_;
  l1t::EMTFTrackCollection    EMTFTracks_;
  const l1t::MuonBxCollection*       GMTMuons_;
  const reco::GenParticleCollection* GENParts_;

  // TTree
  TTree* tree;

  bool firstEvent_;

  // Output collections

  // CSC Inputs
  std::unique_ptr<std::vector<int16_t> >  cscInput_endcap;
  std::unique_ptr<std::vector<int16_t> >  cscInput_station;
  std::unique_ptr<std::vector<int16_t> >  cscInput_ring;
  std::unique_ptr<std::vector<int16_t> >  cscInput_sector;
  std::unique_ptr<std::vector<int16_t> >  cscInput_subsector;
  std::unique_ptr<std::vector<int16_t> >  cscInput_chamber;
  std::unique_ptr<std::vector<int16_t> >  cscInput_cscid;
  std::unique_ptr<std::vector<int16_t> >  cscInput_bx;
  std::unique_ptr<std::vector<int16_t> >  cscInput_strip;
  std::unique_ptr<std::vector<int16_t> >  cscInput_wire;
  std::unique_ptr<std::vector<int16_t> >  cscInput_quality;
  std::unique_ptr<std::vector<int16_t> >  cscInput_pattern;
  std::unique_ptr<std::vector<int16_t> >  cscInput_bend;

  // RPC Inputs
  std::unique_ptr<std::vector<int16_t> >  rpcInput_region;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_station;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_ring;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_sector;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_subsector;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_roll;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_bx;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_strip;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_strip_high;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_strip_low;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_time;
  std::unique_ptr<std::vector<int16_t> >  rpcInput_valid;

  // GEM Inputs
  std::unique_ptr<std::vector<int16_t> >  gemInput_region;
  std::unique_ptr<std::vector<int16_t> >  gemInput_station;
  std::unique_ptr<std::vector<int16_t> >  gemInput_ring;
  std::unique_ptr<std::vector<int16_t> >  gemInput_sector;
  std::unique_ptr<std::vector<int16_t> >  gemInput_chamber;
  std::unique_ptr<std::vector<int16_t> >  gemInput_roll;
  std::unique_ptr<std::vector<int16_t> >  gemInput_bx;
  std::unique_ptr<std::vector<int16_t> >  gemInput_layer;
  std::unique_ptr<std::vector<int16_t> >  gemInput_pad;
  std::unique_ptr<std::vector<int16_t> >  gemInput_pad_low;
  std::unique_ptr<std::vector<int16_t> >  gemInput_pad_high;

  // ME0 Inputs
  std::unique_ptr<std::vector<int16_t> >  me0Input_region;
  std::unique_ptr<std::vector<int16_t> >  me0Input_station;
  std::unique_ptr<std::vector<int16_t> >  me0Input_ring;
  std::unique_ptr<std::vector<int16_t> >  me0Input_sector;
  std::unique_ptr<std::vector<int16_t> >  me0Input_chamber;
  std::unique_ptr<std::vector<int16_t> >  me0Input_roll;
  std::unique_ptr<std::vector<int16_t> >  me0Input_bx;
  std::unique_ptr<std::vector<int16_t> >  me0Input_layer;
  std::unique_ptr<std::vector<int16_t> >  me0Input_phiposition;
  std::unique_ptr<std::vector<int16_t> >  me0Input_deltaphi;
  std::unique_ptr<std::vector<int16_t> >  me0Input_quality;
  std::unique_ptr<std::vector<int16_t> >  me0Input_bend;
  std::unique_ptr<std::vector<int16_t> >  me0Input_partition;

  // DT Inputs
  std::unique_ptr<std::vector<int16_t> >  dtInput_wheel;
  std::unique_ptr<std::vector<int16_t> >  dtInput_station;
  std::unique_ptr<std::vector<int16_t> >  dtInput_btigroup;
  std::unique_ptr<std::vector<int16_t> >  dtInput_bx;
  std::unique_ptr<std::vector<int16_t> >  dtInput_strip;
  std::unique_ptr<std::vector<int16_t> >  dtInput_wire;
  std::unique_ptr<std::vector<int16_t> >  dtInput_quality;
  std::unique_ptr<std::vector<int16_t> >  dtInput_bend;



  // EMTF Hits
  std::unique_ptr<std::vector<int16_t> >  emtfHit_endcap;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_station;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_ring;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_sector;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_subsector;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_chamber;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_cscid;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_bx;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_type;  // subsystem: DT=0,CSC=1,RPC=2,GEM=3,ME0=4
  std::unique_ptr<std::vector<int16_t> >  emtfHit_neighbor;
  //
  std::unique_ptr<std::vector<int16_t> >  emtfHit_strip;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_wire;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_roll;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_quality;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_pattern;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_bend;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_time;
  std::unique_ptr<std::vector<int16_t> >  emtfHit_fr;
  std::unique_ptr<std::vector<int32_t> >  emtfHit_emtf_phi;   // integer unit
  std::unique_ptr<std::vector<int32_t> >  emtfHit_emtf_theta; // integer unit 
  //
  std::unique_ptr<std::vector<float  > >  emtfHit_sim_phi;    // in degrees
  std::unique_ptr<std::vector<float  > >  emtfHit_sim_theta;  // in degrees
  std::unique_ptr<std::vector<float  > >  emtfHit_sim_r;      // in cm
  std::unique_ptr<std::vector<float  > >  emtfHit_sim_z;      // in cm
  std::unique_ptr<std::vector<int32_t> >  emtfHit_sim_tp1;
  std::unique_ptr<std::vector<int32_t> >  emtfHit_sim_tp2;
  std::unique_ptr<int32_t              >  emtfHit_size;

  // EMTF Tracks
  std::unique_ptr<std::vector<float  > >  emtfTrack_pt;
  std::unique_ptr<std::vector<float  > >  emtfTrack_xml_pt;
  std::unique_ptr<std::vector<float  > >  emtfTrack_pt_dxy;
  std::unique_ptr<std::vector<float  > >  emtfTrack_dxy;
  std::unique_ptr<std::vector<float  > >  emtfTrack_invpt_prompt;
  std::unique_ptr<std::vector<float  > >  emtfTrack_invpt_displ;
  std::unique_ptr<std::vector<float  > >  emtfTrack_phi;        // in degrees
  std::unique_ptr<std::vector<float  > >  emtfTrack_theta;      // in degrees
  std::unique_ptr<std::vector<float  > >  emtfTrack_eta;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_q;          // charge
  //
  std::unique_ptr<std::vector<uint64_t> > emtfTrack_address;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_mode;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_endcap;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_sector;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_bx;
  std::unique_ptr<std::vector<int16_t> >  emtfTrack_nhits;
  std::unique_ptr<std::vector<int32_t> >  emtfTrack_hitref1;
  std::unique_ptr<std::vector<int32_t> >  emtfTrack_hitref2;
  std::unique_ptr<std::vector<int32_t> >  emtfTrack_hitref3;
  std::unique_ptr<std::vector<int32_t> >  emtfTrack_hitref4;
  std::unique_ptr<int32_t              >  emtfTrack_size;

  // GMT Muons
  std::unique_ptr<std::vector<float  > >  gmtMuon_pt;
  std::unique_ptr<std::vector<float  > >  gmtMuon_pt_dxy;
  std::unique_ptr<std::vector<int16_t> >  gmtMuon_dxy;
  std::unique_ptr<std::vector<float  > >  gmtMuon_phi;        // in degrees
  std::unique_ptr<std::vector<float  > >  gmtMuon_eta;
  std::unique_ptr<std::vector<int16_t> >  gmtMuon_q;          // charge
  std::unique_ptr<std::vector<int16_t> >  gmtMuon_qual;      
  std::unique_ptr<int32_t              >  gmtMuon_size;

  // GEN particles
  std::unique_ptr<std::vector<float  > >  genPart_pt;
  std::unique_ptr<std::vector<float  > >  genPart_dxy;
  std::unique_ptr<std::vector<float  > >  genPart_eta;
  std::unique_ptr<std::vector<float  > >  genPart_phi;
  std::unique_ptr<std::vector<int16_t> >  genPart_q;          // charge
  std::unique_ptr<std::vector<int16_t> >  genPart_ID;      
  std::unique_ptr<std::vector<float  > >  genPart_vx;      
  std::unique_ptr<std::vector<float  > >  genPart_vy;      
  std::unique_ptr<std::vector<float  > >  genPart_vz;      

  // Event info
  std::unique_ptr<std::vector<uint64_t> > eventInfo_event;
  std::unique_ptr<std::vector<uint32_t> > eventInfo_run;
  std::unique_ptr<std::vector<uint32_t> > eventInfo_lumi;
  std::unique_ptr<std::vector<float  > >  eventInfo_npv;  // getTrueNumInteractions()
  std::unique_ptr<std::vector<int32_t> >  eventInfo_nvtx; // getPU_NumInteractions()
  std::unique_ptr<int32_t              >  eventInfo_size;



};

