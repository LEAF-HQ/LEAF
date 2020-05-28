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
#include "include/Particle.h"
#include "include/constants.h"
#include "include/GenHists.h"
#include "include/Met.h"
#include "include/GenJet.h"
#include "include/CleaningModules.h"
#include "include/Event.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/cosmetics.h"
#include "include/PlottingTool.h"
#include "include/GenlevelTool.h"
#include "include/useful_functions.h"

// Header files passed via #pragma extra_include

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

namespace {
  void TriggerDictionaryInitialization_ClassDictionaries_Impl() {
    static const char* headers[] = {
"include/ObjectIdUtils.h",
"include/massconfig.h",
"include/Particle.h",
"include/constants.h",
"include/GenHists.h",
"include/Met.h",
"include/GenJet.h",
"include/CleaningModules.h",
"include/Event.h",
"include/AnalysisModule.h",
"include/GenParticle.h",
"include/cosmetics.h",
"include/PlottingTool.h",
"include/GenlevelTool.h",
"include/useful_functions.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc700/lcg/root/6.12.07-gnimlf5/include",
"/work/areimers/LQDM/macros/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ClassDictionaries dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenJet;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  GenParticle;
class __attribute__((annotate("$clingAutoload$include/Met.h")))  Met;
class __attribute__((annotate("$clingAutoload$include/ObjectIdUtils.h")))  Particle;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ClassDictionaries dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/ObjectIdUtils.h"
#include "include/massconfig.h"
#include "include/Particle.h"
#include "include/constants.h"
#include "include/GenHists.h"
#include "include/Met.h"
#include "include/GenJet.h"
#include "include/CleaningModules.h"
#include "include/Event.h"
#include "include/AnalysisModule.h"
#include "include/GenParticle.h"
#include "include/cosmetics.h"
#include "include/PlottingTool.h"
#include "include/GenlevelTool.h"
#include "include/useful_functions.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"GenJet", payloadCode, "@",
"GenParticle", payloadCode, "@",
"Met", payloadCode, "@",
"Particle", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ClassDictionaries",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ClassDictionaries_Impl, {}, classesHeaders);
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
