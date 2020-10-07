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
#include "include/TestEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TestEvent_Dictionary();
   static void TestEvent_TClassManip(TClass*);
   static void *new_TestEvent(void *p = 0);
   static void *newArray_TestEvent(Long_t size, void *p);
   static void delete_TestEvent(void *p);
   static void deleteArray_TestEvent(void *p);
   static void destruct_TestEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TestEvent*)
   {
      ::TestEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TestEvent));
      static ::ROOT::TGenericClassInfo 
         instance("TestEvent", "include/TestEvent.h", 14,
                  typeid(::TestEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TestEvent_Dictionary, isa_proxy, 4,
                  sizeof(::TestEvent) );
      instance.SetNew(&new_TestEvent);
      instance.SetNewArray(&newArray_TestEvent);
      instance.SetDelete(&delete_TestEvent);
      instance.SetDeleteArray(&deleteArray_TestEvent);
      instance.SetDestructor(&destruct_TestEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TestEvent*)
   {
      return GenerateInitInstanceLocal((::TestEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TestEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TestEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TestEvent*)0x0)->GetClass();
      TestEvent_TClassManip(theClass);
   return theClass;
   }

   static void TestEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_TestEvent(void *p) {
      return  p ? new(p) ::TestEvent : new ::TestEvent;
   }
   static void *newArray_TestEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TestEvent[nElements] : new ::TestEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TestEvent(void *p) {
      delete ((::TestEvent*)p);
   }
   static void deleteArray_TestEvent(void *p) {
      delete [] ((::TestEvent*)p);
   }
   static void destruct_TestEvent(void *p) {
      typedef ::TestEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TestEvent

namespace ROOT {
   static TClass *vectorlETestEventgR_Dictionary();
   static void vectorlETestEventgR_TClassManip(TClass*);
   static void *new_vectorlETestEventgR(void *p = 0);
   static void *newArray_vectorlETestEventgR(Long_t size, void *p);
   static void delete_vectorlETestEventgR(void *p);
   static void deleteArray_vectorlETestEventgR(void *p);
   static void destruct_vectorlETestEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TestEvent>*)
   {
      vector<TestEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TestEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TestEvent>", -2, "vector", 216,
                  typeid(vector<TestEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETestEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TestEvent>) );
      instance.SetNew(&new_vectorlETestEventgR);
      instance.SetNewArray(&newArray_vectorlETestEventgR);
      instance.SetDelete(&delete_vectorlETestEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlETestEventgR);
      instance.SetDestructor(&destruct_vectorlETestEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TestEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TestEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETestEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TestEvent>*)0x0)->GetClass();
      vectorlETestEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETestEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETestEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TestEvent> : new vector<TestEvent>;
   }
   static void *newArray_vectorlETestEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TestEvent>[nElements] : new vector<TestEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETestEventgR(void *p) {
      delete ((vector<TestEvent>*)p);
   }
   static void deleteArray_vectorlETestEventgR(void *p) {
      delete [] ((vector<TestEvent>*)p);
   }
   static void destruct_vectorlETestEventgR(void *p) {
      typedef vector<TestEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TestEvent>

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
                  &vectorlEElectrongR_Dictionary, isa_proxy, 0,
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

namespace {
  void TriggerDictionaryInitialization_ClassDictionaries_Impl() {
    static const char* headers[] = {
"include/TestEvent.h",
0
    };
    static const char* includePaths[] = {
"/work/areimers/LQDM/macros",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc700/lcg/root/6.14.09-pafccj4/include",
"/work/areimers/LQDM/macros/LQDMSearch/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ClassDictionaries dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/TestEvent.h")))  TestEvent;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ClassDictionaries dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/TestEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TestEvent", payloadCode, "@",
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
