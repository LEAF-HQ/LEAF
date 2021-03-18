#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/RecoEvent.h"

using namespace std;

// Container class for all quantities
class $MYEVENTCLASS : public RecoEvent{

public:
  // Constructors, destructor
  $MYEVENTCLASS();
  ~$MYEVENTCLASS();

  void clear();
  void reset();

};
