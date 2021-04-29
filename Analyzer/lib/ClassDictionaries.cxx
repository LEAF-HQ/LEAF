// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME libdIClassDictionaries

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/Event.h"
#include "include/BTagCalibrationStandalone.h"
#include "include/ObjectIdUtils.h"
#include "include/MuonIds.h"
#include "include/massconfig.h"
#include "include/NElectronSelection.h"
#include "include/ScaleFactorApplicator.h"
#include "include/Particle.h"
#include "include/NTauSelection.h"
#include "include/STMETSelection.h"
#include "include/constants.h"
#include "include/GenEvent.h"
#include "include/FlagSelection.h"
#include "include/TauIds.h"
#include "include/Met.h"
#include "include/GenInfo.h"
#include "include/GenParticleHists.h"
#include "include/GenJet.h"
#include "include/NJetSelection.h"
#include "include/Tau.h"
#include "include/ElectronHists.h"
#include "include/Config.h"
#include "include/CleaningModules.h"
#include "include/TauHists.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/MinvSelections.h"
#include "include/ElectronIds.h"
#include "include/Flags.h"
#include "include/Selection.h"
#include "include/LumiWeightApplicator.h"
#include "include/FlavorParticle.h"
#include "include/NMuonSelection.h"
#include "include/BaseTool.h"
#include "include/BTaggingMCEfficiencyHists.h"
#include "include/useful_functions.h"
#include "include/JetIds.h"
#include "include/PreselectionHists.h"
#include "include/JetCorrections.h"
#include "include/MuonHists.h"
#include "include/Jet.h"
#include "include/LumiblockSelection.h"
#include "include/JetHists.h"
#include "include/Electron.h"
#include "include/RecoEvent.h"
#include "include/BTaggingScaleFactorApplicator.h"
#include "include/ElectronScaleFactorApplicator.h"
#include "include/BaseHists.h"
#include "include/Muon.h"
#include "include/METSelection.h"
#include "include/MuonScaleFactorApplicator.h"
#include "include/Registry.h"
#include "include/TriggerObject.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *Met_Dictionary();
   static void Met_TClassManip(TClass*);
   static void *new_Met(void *p = 0);
   static void *newArray_Met(Long_t size, void *p);
   static void delete_Met(void *p);
   static void deleteArray_Met(void *p);
   static void destruct_Met(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Met*)
   {
      ::Met *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Met));
      static ::ROOT::TGenericClassInfo 
         instance("Met", "include/Met.h", 8,
                  typeid(::Met), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Met_Dictionary, isa_proxy, 4,
                  sizeof(::Met) );
      instance.SetNew(&new_Met);
      instance.SetNewArray(&newArray_Met);
      instance.SetDelete(&delete_Met);
      instance.SetDeleteArray(&deleteArray_Met);
      instance.SetDestructor(&destruct_Met);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Met*)
   {
      return GenerateInitInstanceLocal((::Met*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Met*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Met_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Met*)0x0)->GetClass();
      Met_TClassManip(theClass);
   return theClass;
   }

   static void Met_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Particle_Dictionary();
   static void Particle_TClassManip(TClass*);
   static void *new_Particle(void *p = 0);
   static void *newArray_Particle(Long_t size, void *p);
   static void delete_Particle(void *p);
   static void deleteArray_Particle(void *p);
   static void destruct_Particle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Particle*)
   {
      ::Particle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Particle));
      static ::ROOT::TGenericClassInfo 
         instance("Particle", "include/Particle.h", 9,
                  typeid(::Particle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Particle_Dictionary, isa_proxy, 4,
                  sizeof(::Particle) );
      instance.SetNew(&new_Particle);
      instance.SetNewArray(&newArray_Particle);
      instance.SetDelete(&delete_Particle);
      instance.SetDeleteArray(&deleteArray_Particle);
      instance.SetDestructor(&destruct_Particle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Particle*)
   {
      return GenerateInitInstanceLocal((::Particle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Particle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Particle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Particle*)0x0)->GetClass();
      Particle_TClassManip(theClass);
   return theClass;
   }

   static void Particle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FlavorParticle_Dictionary();
   static void FlavorParticle_TClassManip(TClass*);
   static void *new_FlavorParticle(void *p = 0);
   static void *newArray_FlavorParticle(Long_t size, void *p);
   static void delete_FlavorParticle(void *p);
   static void deleteArray_FlavorParticle(void *p);
   static void destruct_FlavorParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FlavorParticle*)
   {
      ::FlavorParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FlavorParticle));
      static ::ROOT::TGenericClassInfo 
         instance("FlavorParticle", "include/FlavorParticle.h", 11,
                  typeid(::FlavorParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FlavorParticle_Dictionary, isa_proxy, 4,
                  sizeof(::FlavorParticle) );
      instance.SetNew(&new_FlavorParticle);
      instance.SetNewArray(&newArray_FlavorParticle);
      instance.SetDelete(&delete_FlavorParticle);
      instance.SetDeleteArray(&deleteArray_FlavorParticle);
      instance.SetDestructor(&destruct_FlavorParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FlavorParticle*)
   {
      return GenerateInitInstanceLocal((::FlavorParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FlavorParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FlavorParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FlavorParticle*)0x0)->GetClass();
      FlavorParticle_TClassManip(theClass);
   return theClass;
   }

   static void FlavorParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GenParticle_Dictionary();
   static void GenParticle_TClassManip(TClass*);
   static void *new_GenParticle(void *p = 0);
   static void *newArray_GenParticle(Long_t size, void *p);
   static void delete_GenParticle(void *p);
   static void deleteArray_GenParticle(void *p);
   static void destruct_GenParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenParticle*)
   {
      ::GenParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GenParticle));
      static ::ROOT::TGenericClassInfo 
         instance("GenParticle", "include/GenParticle.h", 11,
                  typeid(::GenParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GenParticle_Dictionary, isa_proxy, 4,
                  sizeof(::GenParticle) );
      instance.SetNew(&new_GenParticle);
      instance.SetNewArray(&newArray_GenParticle);
      instance.SetDelete(&delete_GenParticle);
      instance.SetDeleteArray(&deleteArray_GenParticle);
      instance.SetDestructor(&destruct_GenParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenParticle*)
   {
      return GenerateInitInstanceLocal((::GenParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GenParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GenParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GenParticle*)0x0)->GetClass();
      GenParticle_TClassManip(theClass);
   return theClass;
   }

   static void GenParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GenJet_Dictionary();
   static void GenJet_TClassManip(TClass*);
   static void *new_GenJet(void *p = 0);
   static void *newArray_GenJet(Long_t size, void *p);
   static void delete_GenJet(void *p);
   static void deleteArray_GenJet(void *p);
   static void destruct_GenJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenJet*)
   {
      ::GenJet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GenJet));
      static ::ROOT::TGenericClassInfo 
         instance("GenJet", "include/GenJet.h", 11,
                  typeid(::GenJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GenJet_Dictionary, isa_proxy, 4,
                  sizeof(::GenJet) );
      instance.SetNew(&new_GenJet);
      instance.SetNewArray(&newArray_GenJet);
      instance.SetDelete(&delete_GenJet);
      instance.SetDeleteArray(&deleteArray_GenJet);
      instance.SetDestructor(&destruct_GenJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenJet*)
   {
      return GenerateInitInstanceLocal((::GenJet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GenJet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GenJet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GenJet*)0x0)->GetClass();
      GenJet_TClassManip(theClass);
   return theClass;
   }

   static void GenJet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Event_Dictionary();
   static void Event_TClassManip(TClass*);
   static void *new_Event(void *p = 0);
   static void *newArray_Event(Long_t size, void *p);
   static void delete_Event(void *p);
   static void deleteArray_Event(void *p);
   static void destruct_Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Event*)
   {
      ::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Event));
      static ::ROOT::TGenericClassInfo 
         instance("Event", "include/Event.h", 16,
                  typeid(::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Event_Dictionary, isa_proxy, 4,
                  sizeof(::Event) );
      instance.SetNew(&new_Event);
      instance.SetNewArray(&newArray_Event);
      instance.SetDelete(&delete_Event);
      instance.SetDeleteArray(&deleteArray_Event);
      instance.SetDestructor(&destruct_Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Event*)
   {
      return GenerateInitInstanceLocal((::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Event_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Event*)0x0)->GetClass();
      Event_TClassManip(theClass);
   return theClass;
   }

   static void Event_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GenEvent_Dictionary();
   static void GenEvent_TClassManip(TClass*);
   static void *new_GenEvent(void *p = 0);
   static void *newArray_GenEvent(Long_t size, void *p);
   static void delete_GenEvent(void *p);
   static void deleteArray_GenEvent(void *p);
   static void destruct_GenEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenEvent*)
   {
      ::GenEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GenEvent));
      static ::ROOT::TGenericClassInfo 
         instance("GenEvent", "include/GenEvent.h", 17,
                  typeid(::GenEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GenEvent_Dictionary, isa_proxy, 4,
                  sizeof(::GenEvent) );
      instance.SetNew(&new_GenEvent);
      instance.SetNewArray(&newArray_GenEvent);
      instance.SetDelete(&delete_GenEvent);
      instance.SetDeleteArray(&deleteArray_GenEvent);
      instance.SetDestructor(&destruct_GenEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenEvent*)
   {
      return GenerateInitInstanceLocal((::GenEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GenEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GenEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GenEvent*)0x0)->GetClass();
      GenEvent_TClassManip(theClass);
   return theClass;
   }

   static void GenEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GenInfo_Dictionary();
   static void GenInfo_TClassManip(TClass*);
   static void *new_GenInfo(void *p = 0);
   static void *newArray_GenInfo(Long_t size, void *p);
   static void delete_GenInfo(void *p);
   static void deleteArray_GenInfo(void *p);
   static void destruct_GenInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenInfo*)
   {
      ::GenInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GenInfo));
      static ::ROOT::TGenericClassInfo 
         instance("GenInfo", "include/GenInfo.h", 5,
                  typeid(::GenInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GenInfo_Dictionary, isa_proxy, 4,
                  sizeof(::GenInfo) );
      instance.SetNew(&new_GenInfo);
      instance.SetNewArray(&newArray_GenInfo);
      instance.SetDelete(&delete_GenInfo);
      instance.SetDeleteArray(&deleteArray_GenInfo);
      instance.SetDestructor(&destruct_GenInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenInfo*)
   {
      return GenerateInitInstanceLocal((::GenInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GenInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GenInfo_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GenInfo*)0x0)->GetClass();
      GenInfo_TClassManip(theClass);
   return theClass;
   }

   static void GenInfo_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Flags_Dictionary();
   static void Flags_TClassManip(TClass*);
   static void *new_Flags(void *p = 0);
   static void *newArray_Flags(Long_t size, void *p);
   static void delete_Flags(void *p);
   static void deleteArray_Flags(void *p);
   static void destruct_Flags(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Flags*)
   {
      ::Flags *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Flags));
      static ::ROOT::TGenericClassInfo 
         instance("Flags", "include/Flags.h", 8,
                  typeid(::Flags), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Flags_Dictionary, isa_proxy, 4,
                  sizeof(::Flags) );
      instance.SetNew(&new_Flags);
      instance.SetNewArray(&newArray_Flags);
      instance.SetDelete(&delete_Flags);
      instance.SetDeleteArray(&deleteArray_Flags);
      instance.SetDestructor(&destruct_Flags);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Flags*)
   {
      return GenerateInitInstanceLocal((::Flags*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Flags*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Flags_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Flags*)0x0)->GetClass();
      Flags_TClassManip(theClass);
   return theClass;
   }

   static void Flags_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Jet_Dictionary();
   static void Jet_TClassManip(TClass*);
   static void *new_Jet(void *p = 0);
   static void *newArray_Jet(Long_t size, void *p);
   static void delete_Jet(void *p);
   static void deleteArray_Jet(void *p);
   static void destruct_Jet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Jet*)
   {
      ::Jet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Jet));
      static ::ROOT::TGenericClassInfo 
         instance("Jet", "include/Jet.h", 11,
                  typeid(::Jet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Jet_Dictionary, isa_proxy, 4,
                  sizeof(::Jet) );
      instance.SetNew(&new_Jet);
      instance.SetNewArray(&newArray_Jet);
      instance.SetDelete(&delete_Jet);
      instance.SetDeleteArray(&deleteArray_Jet);
      instance.SetDestructor(&destruct_Jet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Jet*)
   {
      return GenerateInitInstanceLocal((::Jet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Jet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Jet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Jet*)0x0)->GetClass();
      Jet_TClassManip(theClass);
   return theClass;
   }

   static void Jet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Tau_Dictionary();
   static void Tau_TClassManip(TClass*);
   static void *new_Tau(void *p = 0);
   static void *newArray_Tau(Long_t size, void *p);
   static void delete_Tau(void *p);
   static void deleteArray_Tau(void *p);
   static void destruct_Tau(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tau*)
   {
      ::Tau *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Tau));
      static ::ROOT::TGenericClassInfo 
         instance("Tau", "include/Tau.h", 11,
                  typeid(::Tau), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Tau_Dictionary, isa_proxy, 4,
                  sizeof(::Tau) );
      instance.SetNew(&new_Tau);
      instance.SetNewArray(&newArray_Tau);
      instance.SetDelete(&delete_Tau);
      instance.SetDeleteArray(&deleteArray_Tau);
      instance.SetDestructor(&destruct_Tau);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tau*)
   {
      return GenerateInitInstanceLocal((::Tau*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Tau*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Tau_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Tau*)0x0)->GetClass();
      Tau_TClassManip(theClass);
   return theClass;
   }

   static void Tau_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Muon_Dictionary();
   static void Muon_TClassManip(TClass*);
   static void *new_Muon(void *p = 0);
   static void *newArray_Muon(Long_t size, void *p);
   static void delete_Muon(void *p);
   static void deleteArray_Muon(void *p);
   static void destruct_Muon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Muon*)
   {
      ::Muon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Muon));
      static ::ROOT::TGenericClassInfo 
         instance("Muon", "include/Muon.h", 11,
                  typeid(::Muon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Muon_Dictionary, isa_proxy, 4,
                  sizeof(::Muon) );
      instance.SetNew(&new_Muon);
      instance.SetNewArray(&newArray_Muon);
      instance.SetDelete(&delete_Muon);
      instance.SetDeleteArray(&deleteArray_Muon);
      instance.SetDestructor(&destruct_Muon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Muon*)
   {
      return GenerateInitInstanceLocal((::Muon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Muon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Muon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Muon*)0x0)->GetClass();
      Muon_TClassManip(theClass);
   return theClass;
   }

   static void Muon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Electron_Dictionary();
   static void Electron_TClassManip(TClass*);
   static void *new_Electron(void *p = 0);
   static void *newArray_Electron(Long_t size, void *p);
   static void delete_Electron(void *p);
   static void deleteArray_Electron(void *p);
   static void destruct_Electron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Electron*)
   {
      ::Electron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Electron));
      static ::ROOT::TGenericClassInfo 
         instance("Electron", "include/Electron.h", 11,
                  typeid(::Electron), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Electron_Dictionary, isa_proxy, 4,
                  sizeof(::Electron) );
      instance.SetNew(&new_Electron);
      instance.SetNewArray(&newArray_Electron);
      instance.SetDelete(&delete_Electron);
      instance.SetDeleteArray(&deleteArray_Electron);
      instance.SetDestructor(&destruct_Electron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Electron*)
   {
      return GenerateInitInstanceLocal((::Electron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Electron*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Electron_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Electron*)0x0)->GetClass();
      Electron_TClassManip(theClass);
   return theClass;
   }

   static void Electron_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TriggerObject_Dictionary();
   static void TriggerObject_TClassManip(TClass*);
   static void *new_TriggerObject(void *p = 0);
   static void *newArray_TriggerObject(Long_t size, void *p);
   static void delete_TriggerObject(void *p);
   static void deleteArray_TriggerObject(void *p);
   static void destruct_TriggerObject(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TriggerObject*)
   {
      ::TriggerObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TriggerObject));
      static ::ROOT::TGenericClassInfo 
         instance("TriggerObject", "include/TriggerObject.h", 6,
                  typeid(::TriggerObject), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TriggerObject_Dictionary, isa_proxy, 4,
                  sizeof(::TriggerObject) );
      instance.SetNew(&new_TriggerObject);
      instance.SetNewArray(&newArray_TriggerObject);
      instance.SetDelete(&delete_TriggerObject);
      instance.SetDeleteArray(&deleteArray_TriggerObject);
      instance.SetDestructor(&destruct_TriggerObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TriggerObject*)
   {
      return GenerateInitInstanceLocal((::TriggerObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TriggerObject*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TriggerObject_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TriggerObject*)0x0)->GetClass();
      TriggerObject_TClassManip(theClass);
   return theClass;
   }

   static void TriggerObject_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RecoEvent_Dictionary();
   static void RecoEvent_TClassManip(TClass*);
   static void *new_RecoEvent(void *p = 0);
   static void *newArray_RecoEvent(Long_t size, void *p);
   static void delete_RecoEvent(void *p);
   static void deleteArray_RecoEvent(void *p);
   static void destruct_RecoEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RecoEvent*)
   {
      ::RecoEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::RecoEvent));
      static ::ROOT::TGenericClassInfo 
         instance("RecoEvent", "include/RecoEvent.h", 22,
                  typeid(::RecoEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RecoEvent_Dictionary, isa_proxy, 4,
                  sizeof(::RecoEvent) );
      instance.SetNew(&new_RecoEvent);
      instance.SetNewArray(&newArray_RecoEvent);
      instance.SetDelete(&delete_RecoEvent);
      instance.SetDeleteArray(&deleteArray_RecoEvent);
      instance.SetDestructor(&destruct_RecoEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RecoEvent*)
   {
      return GenerateInitInstanceLocal((::RecoEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RecoEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RecoEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::RecoEvent*)0x0)->GetClass();
      RecoEvent_TClassManip(theClass);
   return theClass;
   }

   static void RecoEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_Met(void *p) {
      return  p ? new(p) ::Met : new ::Met;
   }
   static void *newArray_Met(Long_t nElements, void *p) {
      return p ? new(p) ::Met[nElements] : new ::Met[nElements];
   }
   // Wrapper around operator delete
   static void delete_Met(void *p) {
      delete ((::Met*)p);
   }
   static void deleteArray_Met(void *p) {
      delete [] ((::Met*)p);
   }
   static void destruct_Met(void *p) {
      typedef ::Met current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Met

namespace ROOT {
   // Wrappers around operator new
   static void *new_Particle(void *p) {
      return  p ? new(p) ::Particle : new ::Particle;
   }
   static void *newArray_Particle(Long_t nElements, void *p) {
      return p ? new(p) ::Particle[nElements] : new ::Particle[nElements];
   }
   // Wrapper around operator delete
   static void delete_Particle(void *p) {
      delete ((::Particle*)p);
   }
   static void deleteArray_Particle(void *p) {
      delete [] ((::Particle*)p);
   }
   static void destruct_Particle(void *p) {
      typedef ::Particle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Particle

namespace ROOT {
   // Wrappers around operator new
   static void *new_FlavorParticle(void *p) {
      return  p ? new(p) ::FlavorParticle : new ::FlavorParticle;
   }
   static void *newArray_FlavorParticle(Long_t nElements, void *p) {
      return p ? new(p) ::FlavorParticle[nElements] : new ::FlavorParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_FlavorParticle(void *p) {
      delete ((::FlavorParticle*)p);
   }
   static void deleteArray_FlavorParticle(void *p) {
      delete [] ((::FlavorParticle*)p);
   }
   static void destruct_FlavorParticle(void *p) {
      typedef ::FlavorParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FlavorParticle

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenParticle(void *p) {
      return  p ? new(p) ::GenParticle : new ::GenParticle;
   }
   static void *newArray_GenParticle(Long_t nElements, void *p) {
      return p ? new(p) ::GenParticle[nElements] : new ::GenParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenParticle(void *p) {
      delete ((::GenParticle*)p);
   }
   static void deleteArray_GenParticle(void *p) {
      delete [] ((::GenParticle*)p);
   }
   static void destruct_GenParticle(void *p) {
      typedef ::GenParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GenParticle

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenJet(void *p) {
      return  p ? new(p) ::GenJet : new ::GenJet;
   }
   static void *newArray_GenJet(Long_t nElements, void *p) {
      return p ? new(p) ::GenJet[nElements] : new ::GenJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenJet(void *p) {
      delete ((::GenJet*)p);
   }
   static void deleteArray_GenJet(void *p) {
      delete [] ((::GenJet*)p);
   }
   static void destruct_GenJet(void *p) {
      typedef ::GenJet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GenJet

namespace ROOT {
   // Wrappers around operator new
   static void *new_Event(void *p) {
      return  p ? new(p) ::Event : new ::Event;
   }
   static void *newArray_Event(Long_t nElements, void *p) {
      return p ? new(p) ::Event[nElements] : new ::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Event(void *p) {
      delete ((::Event*)p);
   }
   static void deleteArray_Event(void *p) {
      delete [] ((::Event*)p);
   }
   static void destruct_Event(void *p) {
      typedef ::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Event

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenEvent(void *p) {
      return  p ? new(p) ::GenEvent : new ::GenEvent;
   }
   static void *newArray_GenEvent(Long_t nElements, void *p) {
      return p ? new(p) ::GenEvent[nElements] : new ::GenEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenEvent(void *p) {
      delete ((::GenEvent*)p);
   }
   static void deleteArray_GenEvent(void *p) {
      delete [] ((::GenEvent*)p);
   }
   static void destruct_GenEvent(void *p) {
      typedef ::GenEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GenEvent

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenInfo(void *p) {
      return  p ? new(p) ::GenInfo : new ::GenInfo;
   }
   static void *newArray_GenInfo(Long_t nElements, void *p) {
      return p ? new(p) ::GenInfo[nElements] : new ::GenInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenInfo(void *p) {
      delete ((::GenInfo*)p);
   }
   static void deleteArray_GenInfo(void *p) {
      delete [] ((::GenInfo*)p);
   }
   static void destruct_GenInfo(void *p) {
      typedef ::GenInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GenInfo

namespace ROOT {
   // Wrappers around operator new
   static void *new_Flags(void *p) {
      return  p ? new(p) ::Flags : new ::Flags;
   }
   static void *newArray_Flags(Long_t nElements, void *p) {
      return p ? new(p) ::Flags[nElements] : new ::Flags[nElements];
   }
   // Wrapper around operator delete
   static void delete_Flags(void *p) {
      delete ((::Flags*)p);
   }
   static void deleteArray_Flags(void *p) {
      delete [] ((::Flags*)p);
   }
   static void destruct_Flags(void *p) {
      typedef ::Flags current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Flags

namespace ROOT {
   // Wrappers around operator new
   static void *new_Jet(void *p) {
      return  p ? new(p) ::Jet : new ::Jet;
   }
   static void *newArray_Jet(Long_t nElements, void *p) {
      return p ? new(p) ::Jet[nElements] : new ::Jet[nElements];
   }
   // Wrapper around operator delete
   static void delete_Jet(void *p) {
      delete ((::Jet*)p);
   }
   static void deleteArray_Jet(void *p) {
      delete [] ((::Jet*)p);
   }
   static void destruct_Jet(void *p) {
      typedef ::Jet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Jet

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tau(void *p) {
      return  p ? new(p) ::Tau : new ::Tau;
   }
   static void *newArray_Tau(Long_t nElements, void *p) {
      return p ? new(p) ::Tau[nElements] : new ::Tau[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tau(void *p) {
      delete ((::Tau*)p);
   }
   static void deleteArray_Tau(void *p) {
      delete [] ((::Tau*)p);
   }
   static void destruct_Tau(void *p) {
      typedef ::Tau current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tau

namespace ROOT {
   // Wrappers around operator new
   static void *new_Muon(void *p) {
      return  p ? new(p) ::Muon : new ::Muon;
   }
   static void *newArray_Muon(Long_t nElements, void *p) {
      return p ? new(p) ::Muon[nElements] : new ::Muon[nElements];
   }
   // Wrapper around operator delete
   static void delete_Muon(void *p) {
      delete ((::Muon*)p);
   }
   static void deleteArray_Muon(void *p) {
      delete [] ((::Muon*)p);
   }
   static void destruct_Muon(void *p) {
      typedef ::Muon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Muon

namespace ROOT {
   // Wrappers around operator new
   static void *new_Electron(void *p) {
      return  p ? new(p) ::Electron : new ::Electron;
   }
   static void *newArray_Electron(Long_t nElements, void *p) {
      return p ? new(p) ::Electron[nElements] : new ::Electron[nElements];
   }
   // Wrapper around operator delete
   static void delete_Electron(void *p) {
      delete ((::Electron*)p);
   }
   static void deleteArray_Electron(void *p) {
      delete [] ((::Electron*)p);
   }
   static void destruct_Electron(void *p) {
      typedef ::Electron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Electron

namespace ROOT {
   // Wrappers around operator new
   static void *new_TriggerObject(void *p) {
      return  p ? new(p) ::TriggerObject : new ::TriggerObject;
   }
   static void *newArray_TriggerObject(Long_t nElements, void *p) {
      return p ? new(p) ::TriggerObject[nElements] : new ::TriggerObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_TriggerObject(void *p) {
      delete ((::TriggerObject*)p);
   }
   static void deleteArray_TriggerObject(void *p) {
      delete [] ((::TriggerObject*)p);
   }
   static void destruct_TriggerObject(void *p) {
      typedef ::TriggerObject current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TriggerObject

namespace ROOT {
   // Wrappers around operator new
   static void *new_RecoEvent(void *p) {
      return  p ? new(p) ::RecoEvent : new ::RecoEvent;
   }
   static void *newArray_RecoEvent(Long_t nElements, void *p) {
      return p ? new(p) ::RecoEvent[nElements] : new ::RecoEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_RecoEvent(void *p) {
      delete ((::RecoEvent*)p);
   }
   static void deleteArray_RecoEvent(void *p) {
      delete [] ((::RecoEvent*)p);
   }
   static void destruct_RecoEvent(void *p) {
      typedef ::RecoEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RecoEvent

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 216,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETriggerObjectgR_Dictionary();
   static void vectorlETriggerObjectgR_TClassManip(TClass*);
   static void *new_vectorlETriggerObjectgR(void *p = 0);
   static void *newArray_vectorlETriggerObjectgR(Long_t size, void *p);
   static void delete_vectorlETriggerObjectgR(void *p);
   static void deleteArray_vectorlETriggerObjectgR(void *p);
   static void destruct_vectorlETriggerObjectgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TriggerObject>*)
   {
      vector<TriggerObject> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TriggerObject>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TriggerObject>", -2, "vector", 216,
                  typeid(vector<TriggerObject>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETriggerObjectgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TriggerObject>) );
      instance.SetNew(&new_vectorlETriggerObjectgR);
      instance.SetNewArray(&newArray_vectorlETriggerObjectgR);
      instance.SetDelete(&delete_vectorlETriggerObjectgR);
      instance.SetDeleteArray(&deleteArray_vectorlETriggerObjectgR);
      instance.SetDestructor(&destruct_vectorlETriggerObjectgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TriggerObject> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TriggerObject>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETriggerObjectgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TriggerObject>*)0x0)->GetClass();
      vectorlETriggerObjectgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETriggerObjectgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETriggerObjectgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TriggerObject> : new vector<TriggerObject>;
   }
   static void *newArray_vectorlETriggerObjectgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TriggerObject>[nElements] : new vector<TriggerObject>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETriggerObjectgR(void *p) {
      delete ((vector<TriggerObject>*)p);
   }
   static void deleteArray_vectorlETriggerObjectgR(void *p) {
      delete [] ((vector<TriggerObject>*)p);
   }
   static void destruct_vectorlETriggerObjectgR(void *p) {
      typedef vector<TriggerObject> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TriggerObject>

namespace ROOT {
   static TClass *vectorlETaugR_Dictionary();
   static void vectorlETaugR_TClassManip(TClass*);
   static void *new_vectorlETaugR(void *p = 0);
   static void *newArray_vectorlETaugR(Long_t size, void *p);
   static void delete_vectorlETaugR(void *p);
   static void deleteArray_vectorlETaugR(void *p);
   static void destruct_vectorlETaugR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Tau>*)
   {
      vector<Tau> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Tau>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Tau>", -2, "vector", 216,
                  typeid(vector<Tau>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETaugR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Tau>) );
      instance.SetNew(&new_vectorlETaugR);
      instance.SetNewArray(&newArray_vectorlETaugR);
      instance.SetDelete(&delete_vectorlETaugR);
      instance.SetDeleteArray(&deleteArray_vectorlETaugR);
      instance.SetDestructor(&destruct_vectorlETaugR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Tau> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Tau>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETaugR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Tau>*)0x0)->GetClass();
      vectorlETaugR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETaugR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETaugR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Tau> : new vector<Tau>;
   }
   static void *newArray_vectorlETaugR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Tau>[nElements] : new vector<Tau>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETaugR(void *p) {
      delete ((vector<Tau>*)p);
   }
   static void deleteArray_vectorlETaugR(void *p) {
      delete [] ((vector<Tau>*)p);
   }
   static void destruct_vectorlETaugR(void *p) {
      typedef vector<Tau> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Tau>

namespace ROOT {
   static TClass *vectorlERecoEventgR_Dictionary();
   static void vectorlERecoEventgR_TClassManip(TClass*);
   static void *new_vectorlERecoEventgR(void *p = 0);
   static void *newArray_vectorlERecoEventgR(Long_t size, void *p);
   static void delete_vectorlERecoEventgR(void *p);
   static void deleteArray_vectorlERecoEventgR(void *p);
   static void destruct_vectorlERecoEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RecoEvent>*)
   {
      vector<RecoEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RecoEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RecoEvent>", -2, "vector", 216,
                  typeid(vector<RecoEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERecoEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<RecoEvent>) );
      instance.SetNew(&new_vectorlERecoEventgR);
      instance.SetNewArray(&newArray_vectorlERecoEventgR);
      instance.SetDelete(&delete_vectorlERecoEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlERecoEventgR);
      instance.SetDestructor(&destruct_vectorlERecoEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RecoEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<RecoEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERecoEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<RecoEvent>*)0x0)->GetClass();
      vectorlERecoEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERecoEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERecoEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<RecoEvent> : new vector<RecoEvent>;
   }
   static void *newArray_vectorlERecoEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<RecoEvent>[nElements] : new vector<RecoEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERecoEventgR(void *p) {
      delete ((vector<RecoEvent>*)p);
   }
   static void deleteArray_vectorlERecoEventgR(void *p) {
      delete [] ((vector<RecoEvent>*)p);
   }
   static void destruct_vectorlERecoEventgR(void *p) {
      typedef vector<RecoEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<RecoEvent>

namespace ROOT {
   static TClass *vectorlEParticlegR_Dictionary();
   static void vectorlEParticlegR_TClassManip(TClass*);
   static void *new_vectorlEParticlegR(void *p = 0);
   static void *newArray_vectorlEParticlegR(Long_t size, void *p);
   static void delete_vectorlEParticlegR(void *p);
   static void deleteArray_vectorlEParticlegR(void *p);
   static void destruct_vectorlEParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Particle>*)
   {
      vector<Particle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Particle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Particle>", -2, "vector", 216,
                  typeid(vector<Particle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Particle>) );
      instance.SetNew(&new_vectorlEParticlegR);
      instance.SetNewArray(&newArray_vectorlEParticlegR);
      instance.SetDelete(&delete_vectorlEParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEParticlegR);
      instance.SetDestructor(&destruct_vectorlEParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Particle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Particle>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Particle>*)0x0)->GetClass();
      vectorlEParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Particle> : new vector<Particle>;
   }
   static void *newArray_vectorlEParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Particle>[nElements] : new vector<Particle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEParticlegR(void *p) {
      delete ((vector<Particle>*)p);
   }
   static void deleteArray_vectorlEParticlegR(void *p) {
      delete [] ((vector<Particle>*)p);
   }
   static void destruct_vectorlEParticlegR(void *p) {
      typedef vector<Particle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Particle>

namespace ROOT {
   static TClass *vectorlEMuongR_Dictionary();
   static void vectorlEMuongR_TClassManip(TClass*);
   static void *new_vectorlEMuongR(void *p = 0);
   static void *newArray_vectorlEMuongR(Long_t size, void *p);
   static void delete_vectorlEMuongR(void *p);
   static void deleteArray_vectorlEMuongR(void *p);
   static void destruct_vectorlEMuongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Muon>*)
   {
      vector<Muon> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Muon>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Muon>", -2, "vector", 216,
                  typeid(vector<Muon>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMuongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Muon>) );
      instance.SetNew(&new_vectorlEMuongR);
      instance.SetNewArray(&newArray_vectorlEMuongR);
      instance.SetDelete(&delete_vectorlEMuongR);
      instance.SetDeleteArray(&deleteArray_vectorlEMuongR);
      instance.SetDestructor(&destruct_vectorlEMuongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Muon> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Muon>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMuongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Muon>*)0x0)->GetClass();
      vectorlEMuongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMuongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMuongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Muon> : new vector<Muon>;
   }
   static void *newArray_vectorlEMuongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Muon>[nElements] : new vector<Muon>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMuongR(void *p) {
      delete ((vector<Muon>*)p);
   }
   static void deleteArray_vectorlEMuongR(void *p) {
      delete [] ((vector<Muon>*)p);
   }
   static void destruct_vectorlEMuongR(void *p) {
      typedef vector<Muon> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Muon>

namespace ROOT {
   static TClass *vectorlEMetgR_Dictionary();
   static void vectorlEMetgR_TClassManip(TClass*);
   static void *new_vectorlEMetgR(void *p = 0);
   static void *newArray_vectorlEMetgR(Long_t size, void *p);
   static void delete_vectorlEMetgR(void *p);
   static void deleteArray_vectorlEMetgR(void *p);
   static void destruct_vectorlEMetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Met>*)
   {
      vector<Met> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Met>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Met>", -2, "vector", 216,
                  typeid(vector<Met>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Met>) );
      instance.SetNew(&new_vectorlEMetgR);
      instance.SetNewArray(&newArray_vectorlEMetgR);
      instance.SetDelete(&delete_vectorlEMetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMetgR);
      instance.SetDestructor(&destruct_vectorlEMetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Met> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Met>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Met>*)0x0)->GetClass();
      vectorlEMetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Met> : new vector<Met>;
   }
   static void *newArray_vectorlEMetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Met>[nElements] : new vector<Met>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMetgR(void *p) {
      delete ((vector<Met>*)p);
   }
   static void deleteArray_vectorlEMetgR(void *p) {
      delete [] ((vector<Met>*)p);
   }
   static void destruct_vectorlEMetgR(void *p) {
      typedef vector<Met> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Met>

namespace ROOT {
   static TClass *vectorlEJetgR_Dictionary();
   static void vectorlEJetgR_TClassManip(TClass*);
   static void *new_vectorlEJetgR(void *p = 0);
   static void *newArray_vectorlEJetgR(Long_t size, void *p);
   static void delete_vectorlEJetgR(void *p);
   static void deleteArray_vectorlEJetgR(void *p);
   static void destruct_vectorlEJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Jet>*)
   {
      vector<Jet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Jet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Jet>", -2, "vector", 216,
                  typeid(vector<Jet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEJetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Jet>) );
      instance.SetNew(&new_vectorlEJetgR);
      instance.SetNewArray(&newArray_vectorlEJetgR);
      instance.SetDelete(&delete_vectorlEJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEJetgR);
      instance.SetDestructor(&destruct_vectorlEJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Jet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Jet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Jet>*)0x0)->GetClass();
      vectorlEJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEJetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Jet> : new vector<Jet>;
   }
   static void *newArray_vectorlEJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Jet>[nElements] : new vector<Jet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEJetgR(void *p) {
      delete ((vector<Jet>*)p);
   }
   static void deleteArray_vectorlEJetgR(void *p) {
      delete [] ((vector<Jet>*)p);
   }
   static void destruct_vectorlEJetgR(void *p) {
      typedef vector<Jet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Jet>

namespace ROOT {
   static TClass *vectorlEGenParticlegR_Dictionary();
   static void vectorlEGenParticlegR_TClassManip(TClass*);
   static void *new_vectorlEGenParticlegR(void *p = 0);
   static void *newArray_vectorlEGenParticlegR(Long_t size, void *p);
   static void delete_vectorlEGenParticlegR(void *p);
   static void deleteArray_vectorlEGenParticlegR(void *p);
   static void destruct_vectorlEGenParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenParticle>*)
   {
      vector<GenParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenParticle>", -2, "vector", 216,
                  typeid(vector<GenParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GenParticle>) );
      instance.SetNew(&new_vectorlEGenParticlegR);
      instance.SetNewArray(&newArray_vectorlEGenParticlegR);
      instance.SetDelete(&delete_vectorlEGenParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenParticlegR);
      instance.SetDestructor(&destruct_vectorlEGenParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GenParticle>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GenParticle>*)0x0)->GetClass();
      vectorlEGenParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenParticle> : new vector<GenParticle>;
   }
   static void *newArray_vectorlEGenParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenParticle>[nElements] : new vector<GenParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenParticlegR(void *p) {
      delete ((vector<GenParticle>*)p);
   }
   static void deleteArray_vectorlEGenParticlegR(void *p) {
      delete [] ((vector<GenParticle>*)p);
   }
   static void destruct_vectorlEGenParticlegR(void *p) {
      typedef vector<GenParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GenParticle>

namespace ROOT {
   static TClass *vectorlEGenJetgR_Dictionary();
   static void vectorlEGenJetgR_TClassManip(TClass*);
   static void *new_vectorlEGenJetgR(void *p = 0);
   static void *newArray_vectorlEGenJetgR(Long_t size, void *p);
   static void delete_vectorlEGenJetgR(void *p);
   static void deleteArray_vectorlEGenJetgR(void *p);
   static void destruct_vectorlEGenJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenJet>*)
   {
      vector<GenJet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenJet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenJet>", -2, "vector", 216,
                  typeid(vector<GenJet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenJetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GenJet>) );
      instance.SetNew(&new_vectorlEGenJetgR);
      instance.SetNewArray(&newArray_vectorlEGenJetgR);
      instance.SetDelete(&delete_vectorlEGenJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenJetgR);
      instance.SetDestructor(&destruct_vectorlEGenJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenJet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GenJet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GenJet>*)0x0)->GetClass();
      vectorlEGenJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenJetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenJet> : new vector<GenJet>;
   }
   static void *newArray_vectorlEGenJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenJet>[nElements] : new vector<GenJet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenJetgR(void *p) {
      delete ((vector<GenJet>*)p);
   }
   static void deleteArray_vectorlEGenJetgR(void *p) {
      delete [] ((vector<GenJet>*)p);
   }
   static void destruct_vectorlEGenJetgR(void *p) {
      typedef vector<GenJet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GenJet>

namespace ROOT {
   static TClass *vectorlEGenInfogR_Dictionary();
   static void vectorlEGenInfogR_TClassManip(TClass*);
   static void *new_vectorlEGenInfogR(void *p = 0);
   static void *newArray_vectorlEGenInfogR(Long_t size, void *p);
   static void delete_vectorlEGenInfogR(void *p);
   static void deleteArray_vectorlEGenInfogR(void *p);
   static void destruct_vectorlEGenInfogR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenInfo>*)
   {
      vector<GenInfo> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenInfo>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenInfo>", -2, "vector", 216,
                  typeid(vector<GenInfo>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenInfogR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GenInfo>) );
      instance.SetNew(&new_vectorlEGenInfogR);
      instance.SetNewArray(&newArray_vectorlEGenInfogR);
      instance.SetDelete(&delete_vectorlEGenInfogR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenInfogR);
      instance.SetDestructor(&destruct_vectorlEGenInfogR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenInfo> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GenInfo>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenInfogR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GenInfo>*)0x0)->GetClass();
      vectorlEGenInfogR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenInfogR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenInfogR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenInfo> : new vector<GenInfo>;
   }
   static void *newArray_vectorlEGenInfogR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenInfo>[nElements] : new vector<GenInfo>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenInfogR(void *p) {
      delete ((vector<GenInfo>*)p);
   }
   static void deleteArray_vectorlEGenInfogR(void *p) {
      delete [] ((vector<GenInfo>*)p);
   }
   static void destruct_vectorlEGenInfogR(void *p) {
      typedef vector<GenInfo> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GenInfo>

namespace ROOT {
   static TClass *vectorlEGenEventgR_Dictionary();
   static void vectorlEGenEventgR_TClassManip(TClass*);
   static void *new_vectorlEGenEventgR(void *p = 0);
   static void *newArray_vectorlEGenEventgR(Long_t size, void *p);
   static void delete_vectorlEGenEventgR(void *p);
   static void deleteArray_vectorlEGenEventgR(void *p);
   static void destruct_vectorlEGenEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenEvent>*)
   {
      vector<GenEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenEvent>", -2, "vector", 216,
                  typeid(vector<GenEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GenEvent>) );
      instance.SetNew(&new_vectorlEGenEventgR);
      instance.SetNewArray(&newArray_vectorlEGenEventgR);
      instance.SetDelete(&delete_vectorlEGenEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenEventgR);
      instance.SetDestructor(&destruct_vectorlEGenEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GenEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GenEvent>*)0x0)->GetClass();
      vectorlEGenEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenEvent> : new vector<GenEvent>;
   }
   static void *newArray_vectorlEGenEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenEvent>[nElements] : new vector<GenEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenEventgR(void *p) {
      delete ((vector<GenEvent>*)p);
   }
   static void deleteArray_vectorlEGenEventgR(void *p) {
      delete [] ((vector<GenEvent>*)p);
   }
   static void destruct_vectorlEGenEventgR(void *p) {
      typedef vector<GenEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GenEvent>

namespace ROOT {
   static TClass *vectorlEFlavorParticlegR_Dictionary();
   static void vectorlEFlavorParticlegR_TClassManip(TClass*);
   static void *new_vectorlEFlavorParticlegR(void *p = 0);
   static void *newArray_vectorlEFlavorParticlegR(Long_t size, void *p);
   static void delete_vectorlEFlavorParticlegR(void *p);
   static void deleteArray_vectorlEFlavorParticlegR(void *p);
   static void destruct_vectorlEFlavorParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FlavorParticle>*)
   {
      vector<FlavorParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FlavorParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FlavorParticle>", -2, "vector", 216,
                  typeid(vector<FlavorParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFlavorParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<FlavorParticle>) );
      instance.SetNew(&new_vectorlEFlavorParticlegR);
      instance.SetNewArray(&newArray_vectorlEFlavorParticlegR);
      instance.SetDelete(&delete_vectorlEFlavorParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEFlavorParticlegR);
      instance.SetDestructor(&destruct_vectorlEFlavorParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FlavorParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<FlavorParticle>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFlavorParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<FlavorParticle>*)0x0)->GetClass();
      vectorlEFlavorParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFlavorParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFlavorParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FlavorParticle> : new vector<FlavorParticle>;
   }
   static void *newArray_vectorlEFlavorParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FlavorParticle>[nElements] : new vector<FlavorParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFlavorParticlegR(void *p) {
      delete ((vector<FlavorParticle>*)p);
   }
   static void deleteArray_vectorlEFlavorParticlegR(void *p) {
      delete [] ((vector<FlavorParticle>*)p);
   }
   static void destruct_vectorlEFlavorParticlegR(void *p) {
      typedef vector<FlavorParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<FlavorParticle>

namespace ROOT {
   static TClass *vectorlEFlagsgR_Dictionary();
   static void vectorlEFlagsgR_TClassManip(TClass*);
   static void *new_vectorlEFlagsgR(void *p = 0);
   static void *newArray_vectorlEFlagsgR(Long_t size, void *p);
   static void delete_vectorlEFlagsgR(void *p);
   static void deleteArray_vectorlEFlagsgR(void *p);
   static void destruct_vectorlEFlagsgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Flags>*)
   {
      vector<Flags> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Flags>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Flags>", -2, "vector", 216,
                  typeid(vector<Flags>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFlagsgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Flags>) );
      instance.SetNew(&new_vectorlEFlagsgR);
      instance.SetNewArray(&newArray_vectorlEFlagsgR);
      instance.SetDelete(&delete_vectorlEFlagsgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFlagsgR);
      instance.SetDestructor(&destruct_vectorlEFlagsgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Flags> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Flags>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFlagsgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Flags>*)0x0)->GetClass();
      vectorlEFlagsgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFlagsgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFlagsgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Flags> : new vector<Flags>;
   }
   static void *newArray_vectorlEFlagsgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Flags>[nElements] : new vector<Flags>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFlagsgR(void *p) {
      delete ((vector<Flags>*)p);
   }
   static void deleteArray_vectorlEFlagsgR(void *p) {
      delete [] ((vector<Flags>*)p);
   }
   static void destruct_vectorlEFlagsgR(void *p) {
      typedef vector<Flags> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Flags>

namespace ROOT {
   static TClass *vectorlEEventgR_Dictionary();
   static void vectorlEEventgR_TClassManip(TClass*);
   static void *new_vectorlEEventgR(void *p = 0);
   static void *newArray_vectorlEEventgR(Long_t size, void *p);
   static void delete_vectorlEEventgR(void *p);
   static void deleteArray_vectorlEEventgR(void *p);
   static void destruct_vectorlEEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Event>*)
   {
      vector<Event> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Event>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Event>", -2, "vector", 216,
                  typeid(vector<Event>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Event>) );
      instance.SetNew(&new_vectorlEEventgR);
      instance.SetNewArray(&newArray_vectorlEEventgR);
      instance.SetDelete(&delete_vectorlEEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEEventgR);
      instance.SetDestructor(&destruct_vectorlEEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Event> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Event>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Event>*)0x0)->GetClass();
      vectorlEEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Event> : new vector<Event>;
   }
   static void *newArray_vectorlEEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Event>[nElements] : new vector<Event>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEEventgR(void *p) {
      delete ((vector<Event>*)p);
   }
   static void deleteArray_vectorlEEventgR(void *p) {
      delete [] ((vector<Event>*)p);
   }
   static void destruct_vectorlEEventgR(void *p) {
      typedef vector<Event> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Event>

namespace ROOT {
   static TClass *vectorlEElectrongR_Dictionary();
   static void vectorlEElectrongR_TClassManip(TClass*);
   static void *new_vectorlEElectrongR(void *p = 0);
   static void *newArray_vectorlEElectrongR(Long_t size, void *p);
   static void delete_vectorlEElectrongR(void *p);
   static void deleteArray_vectorlEElectrongR(void *p);
   static void destruct_vectorlEElectrongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Electron>*)
   {
      vector<Electron> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Electron>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Electron>", -2, "vector", 216,
                  typeid(vector<Electron>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEElectrongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Electron>) );
      instance.SetNew(&new_vectorlEElectrongR);
      instance.SetNewArray(&newArray_vectorlEElectrongR);
      instance.SetDelete(&delete_vectorlEElectrongR);
      instance.SetDeleteArray(&deleteArray_vectorlEElectrongR);
      instance.SetDestructor(&destruct_vectorlEElectrongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Electron> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Electron>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEElectrongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Electron>*)0x0)->GetClass();
      vectorlEElectrongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEElectrongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEElectrongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Electron> : new vector<Electron>;
   }
   static void *newArray_vectorlEElectrongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Electron>[nElements] : new vector<Electron>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEElectrongR(void *p) {
      delete ((vector<Electron>*)p);
   }
   static void deleteArray_vectorlEElectrongR(void *p) {
      delete [] ((vector<Electron>*)p);
   }
   static void destruct_vectorlEElectrongR(void *p) {
      typedef vector<Electron> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Electron>

namespace ROOT {
   static TClass *maplETStringcOboolgR_Dictionary();
   static void maplETStringcOboolgR_TClassManip(TClass*);
   static void *new_maplETStringcOboolgR(void *p = 0);
   static void *newArray_maplETStringcOboolgR(Long_t size, void *p);
   static void delete_maplETStringcOboolgR(void *p);
   static void deleteArray_maplETStringcOboolgR(void *p);
   static void destruct_maplETStringcOboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,bool>*)
   {
      map<TString,bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,bool>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,bool>", -2, "map", 99,
                  typeid(map<TString,bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOboolgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,bool>) );
      instance.SetNew(&new_maplETStringcOboolgR);
      instance.SetNewArray(&newArray_maplETStringcOboolgR);
      instance.SetDelete(&delete_maplETStringcOboolgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOboolgR);
      instance.SetDestructor(&destruct_maplETStringcOboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,bool>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,bool>*)0x0)->GetClass();
      maplETStringcOboolgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,bool> : new map<TString,bool>;
   }
   static void *newArray_maplETStringcOboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,bool>[nElements] : new map<TString,bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOboolgR(void *p) {
      delete ((map<TString,bool>*)p);
   }
   static void deleteArray_maplETStringcOboolgR(void *p) {
      delete [] ((map<TString,bool>*)p);
   }
   static void destruct_maplETStringcOboolgR(void *p) {
      typedef map<TString,bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,bool>

namespace {
  void TriggerDictionaryInitialization_ClassDictionaries_Impl() {
    static const char* headers[] = {
"include/Event.h",
"include/BTagCalibrationStandalone.h",
"include/ObjectIdUtils.h",
"include/MuonIds.h",
"include/massconfig.h",
"include/NElectronSelection.h",
"include/ScaleFactorApplicator.h",
"include/Particle.h",
"include/NTauSelection.h",
"include/STMETSelection.h",
"include/constants.h",
"include/GenEvent.h",
"include/FlagSelection.h",
"include/TauIds.h",
"include/Met.h",
"include/GenInfo.h",
"include/GenParticleHists.h",
"include/GenJet.h",
"include/NJetSelection.h",
"include/Tau.h",
"include/ElectronHists.h",
"include/Config.h",
"include/CleaningModules.h",
"include/TauHists.h",
"include/AnalysisModule.h",
"include/GenParticle.h",
"include/MinvSelections.h",
"include/ElectronIds.h",
"include/Flags.h",
"include/Selection.h",
"include/LumiWeightApplicator.h",
"include/FlavorParticle.h",
"include/NMuonSelection.h",
"include/BaseTool.h",
"include/BTaggingMCEfficiencyHists.h",
"include/useful_functions.h",
"include/JetIds.h",
"include/PreselectionHists.h",
"include/JetCorrections.h",
"include/MuonHists.h",
"include/Jet.h",
"include/LumiblockSelection.h",
"include/JetHists.h",
"include/Electron.h",
"include/RecoEvent.h",
"include/BTaggingScaleFactorApplicator.h",
"include/ElectronScaleFactorApplicator.h",
"include/BaseHists.h",
"include/Muon.h",
"include/METSelection.h",
"include/MuonScaleFactorApplicator.h",
"include/Registry.h",
"include/TriggerObject.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc700/lcg/root/6.14.09-pafccj4/include",
"/work/areimers/LEAF/Analyzer/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ClassDictionaries dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$Analyzer/include/GenParticle.h")))  __attribute__((annotate("$clingAutoload$include/Event.h")))  GenParticle;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$Analyzer/include/GenJet.h")))  __attribute__((annotate("$clingAutoload$include/Event.h")))  GenJet;
class __attribute__((annotate("$clingAutoload$Analyzer/include/TriggerObject.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  TriggerObject;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Jet.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Jet;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Tau.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Tau;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Muon.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Muon;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Electron.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Electron;
class __attribute__((annotate("$clingAutoload$Analyzer/include/RecoEvent.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  RecoEvent;
class __attribute__((annotate("$clingAutoload$Analyzer/include/GenEvent.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenEvent;
class __attribute__((annotate("$clingAutoload$include/Event.h")))  Event;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Met.h")))  __attribute__((annotate("$clingAutoload$include/Event.h")))  Met;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Flags.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Flags;
class __attribute__((annotate("$clingAutoload$Analyzer/include/GenInfo.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenInfo;
class __attribute__((annotate("$clingAutoload$Analyzer/include/FlavorParticle.h")))  __attribute__((annotate("$clingAutoload$include/Event.h")))  FlavorParticle;
class __attribute__((annotate("$clingAutoload$Analyzer/include/Particle.h")))  __attribute__((annotate("$clingAutoload$include/Event.h")))  Particle;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ClassDictionaries dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/Event.h"
#include "include/BTagCalibrationStandalone.h"
#include "include/ObjectIdUtils.h"
#include "include/MuonIds.h"
#include "include/massconfig.h"
#include "include/NElectronSelection.h"
#include "include/ScaleFactorApplicator.h"
#include "include/Particle.h"
#include "include/NTauSelection.h"
#include "include/STMETSelection.h"
#include "include/constants.h"
#include "include/GenEvent.h"
#include "include/FlagSelection.h"
#include "include/TauIds.h"
#include "include/Met.h"
#include "include/GenInfo.h"
#include "include/GenParticleHists.h"
#include "include/GenJet.h"
#include "include/NJetSelection.h"
#include "include/Tau.h"
#include "include/ElectronHists.h"
#include "include/Config.h"
#include "include/CleaningModules.h"
#include "include/TauHists.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/MinvSelections.h"
#include "include/ElectronIds.h"
#include "include/Flags.h"
#include "include/Selection.h"
#include "include/LumiWeightApplicator.h"
#include "include/FlavorParticle.h"
#include "include/NMuonSelection.h"
#include "include/BaseTool.h"
#include "include/BTaggingMCEfficiencyHists.h"
#include "include/useful_functions.h"
#include "include/JetIds.h"
#include "include/PreselectionHists.h"
#include "include/JetCorrections.h"
#include "include/MuonHists.h"
#include "include/Jet.h"
#include "include/LumiblockSelection.h"
#include "include/JetHists.h"
#include "include/Electron.h"
#include "include/RecoEvent.h"
#include "include/BTaggingScaleFactorApplicator.h"
#include "include/ElectronScaleFactorApplicator.h"
#include "include/BaseHists.h"
#include "include/Muon.h"
#include "include/METSelection.h"
#include "include/MuonScaleFactorApplicator.h"
#include "include/Registry.h"
#include "include/TriggerObject.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Electron", payloadCode, "@",
"Event", payloadCode, "@",
"Flags", payloadCode, "@",
"FlavorParticle", payloadCode, "@",
"GenEvent", payloadCode, "@",
"GenInfo", payloadCode, "@",
"GenJet", payloadCode, "@",
"GenParticle", payloadCode, "@",
"Jet", payloadCode, "@",
"Met", payloadCode, "@",
"Muon", payloadCode, "@",
"Particle", payloadCode, "@",
"RecoEvent", payloadCode, "@",
"Tau", payloadCode, "@",
"TriggerObject", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ClassDictionaries",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ClassDictionaries_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ClassDictionaries_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ClassDictionaries() {
  TriggerDictionaryInitialization_ClassDictionaries_Impl();
}
