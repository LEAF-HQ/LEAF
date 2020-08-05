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
#include "include/ObjectIdUtils.h"
#include "include/massconfig.h"
#include "include/GenContent.h"
#include "include/Particle.h"
#include "include/Registry.h"
#include "include/Config.h"
#include "include/GenHists.h"
#include "include/Met.h"
#include "include/GenJet.h"
#include "include/constants.h"
#include "include/CleaningModules.h"
#include "include/Event.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/cosmetics.h"
#include "include/BaseTool.h"
#include "include/PlottingTool.h"
#include "include/useful_functions.h"

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
         instance("Met", "include/Met.h", 7,
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
   static TClass *GenContent_Dictionary();
   static void GenContent_TClassManip(TClass*);
   static void *new_GenContent(void *p = 0);
   static void *newArray_GenContent(Long_t size, void *p);
   static void delete_GenContent(void *p);
   static void deleteArray_GenContent(void *p);
   static void destruct_GenContent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenContent*)
   {
      ::GenContent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GenContent));
      static ::ROOT::TGenericClassInfo 
         instance("GenContent", "include/GenContent.h", 15,
                  typeid(::GenContent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GenContent_Dictionary, isa_proxy, 4,
                  sizeof(::GenContent) );
      instance.SetNew(&new_GenContent);
      instance.SetNewArray(&newArray_GenContent);
      instance.SetDelete(&delete_GenContent);
      instance.SetDeleteArray(&deleteArray_GenContent);
      instance.SetDestructor(&destruct_GenContent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenContent*)
   {
      return GenerateInitInstanceLocal((::GenContent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GenContent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GenContent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GenContent*)0x0)->GetClass();
      GenContent_TClassManip(theClass);
   return theClass;
   }

   static void GenContent_TClassManip(TClass* ){
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
         instance("Event", "include/Event.h", 14,
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
   static void *new_GenContent(void *p) {
      return  p ? new(p) ::GenContent : new ::GenContent;
   }
   static void *newArray_GenContent(Long_t nElements, void *p) {
      return p ? new(p) ::GenContent[nElements] : new ::GenContent[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenContent(void *p) {
      delete ((::GenContent*)p);
   }
   static void deleteArray_GenContent(void *p) {
      delete [] ((::GenContent*)p);
   }
   static void destruct_GenContent(void *p) {
      typedef ::GenContent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GenContent

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
   static TClass *vectorlEGenContentgR_Dictionary();
   static void vectorlEGenContentgR_TClassManip(TClass*);
   static void *new_vectorlEGenContentgR(void *p = 0);
   static void *newArray_vectorlEGenContentgR(Long_t size, void *p);
   static void delete_vectorlEGenContentgR(void *p);
   static void deleteArray_vectorlEGenContentgR(void *p);
   static void destruct_vectorlEGenContentgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenContent>*)
   {
      vector<GenContent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenContent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenContent>", -2, "vector", 216,
                  typeid(vector<GenContent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenContentgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GenContent>) );
      instance.SetNew(&new_vectorlEGenContentgR);
      instance.SetNewArray(&newArray_vectorlEGenContentgR);
      instance.SetDelete(&delete_vectorlEGenContentgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenContentgR);
      instance.SetDestructor(&destruct_vectorlEGenContentgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenContent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GenContent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenContentgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GenContent>*)0x0)->GetClass();
      vectorlEGenContentgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenContentgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenContentgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenContent> : new vector<GenContent>;
   }
   static void *newArray_vectorlEGenContentgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GenContent>[nElements] : new vector<GenContent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenContentgR(void *p) {
      delete ((vector<GenContent>*)p);
   }
   static void deleteArray_vectorlEGenContentgR(void *p) {
      delete [] ((vector<GenContent>*)p);
   }
   static void destruct_vectorlEGenContentgR(void *p) {
      typedef vector<GenContent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GenContent>

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

namespace {
  void TriggerDictionaryInitialization_ClassDictionaries_Impl() {
    static const char* headers[] = {
"include/ObjectIdUtils.h",
"include/massconfig.h",
"include/GenContent.h",
"include/Particle.h",
"include/Registry.h",
"include/Config.h",
"include/GenHists.h",
"include/Met.h",
"include/GenJet.h",
"include/constants.h",
"include/CleaningModules.h",
"include/Event.h",
"include/AnalysisModule.h",
"include/GenParticle.h",
"include/cosmetics.h",
"include/BaseTool.h",
"include/PlottingTool.h",
"include/useful_functions.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc700/lcg/root/6.14.09-pafccj4/include",
"/work/areimers/LQDM/macros/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ClassDictionaries dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/GenParticle.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenParticle;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$include/GenJet.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenJet;
class __attribute__((annotate("$clingAutoload$include/GenContent.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenContent;
class __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Event;
class __attribute__((annotate("$clingAutoload$include/Met.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Met;
class __attribute__((annotate("$clingAutoload$include/GenParticle.h")))  __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Particle;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ClassDictionaries dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/ObjectIdUtils.h"
#include "include/massconfig.h"
#include "include/GenContent.h"
#include "include/Particle.h"
#include "include/Registry.h"
#include "include/Config.h"
#include "include/GenHists.h"
#include "include/Met.h"
#include "include/GenJet.h"
#include "include/constants.h"
#include "include/CleaningModules.h"
#include "include/Event.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/cosmetics.h"
#include "include/BaseTool.h"
#include "include/PlottingTool.h"
#include "include/useful_functions.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Event", payloadCode, "@",
"GenContent", payloadCode, "@",
"GenJet", payloadCode, "@",
"GenParticle", payloadCode, "@",
"Met", payloadCode, "@",
"Particle", payloadCode, "@",
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
