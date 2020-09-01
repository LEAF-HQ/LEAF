#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/GenEvent.h"
#include "include/BaseHists.h"

using namespace std;

class GenHists : public BaseHists{

public:
  // Constructors, destructor
  GenHists(TString dir_);
  GenHists(const GenHists &) = default;
  GenHists & operator = (const GenHists &) = default;
  ~GenHists() = default;

  // Main functions
  void fill(const GenEvent & event);


protected:

  shared_ptr<TH1F> hnlq, hnpsi, hnchi, hnjets, hnbhard, hntauhard, hntauvis, hmlq1, hmlq2, hmpsi1, hmpsi2, hmchi1, hmchi2, hptlq1, hptlq2, hptpsi1, hptpsi2, hptchi1, hptchi2, hetalq1, hetalq2, hetapsi1, hetapsi2, hetachi1, hetachi2, hphilq1, hphilq2, hphipsi1, hphipsi2, hphichi1, hphichi2, hptjet1, hptjet2, hptjet3, hptbhard1, hptbhard2, hpttauhard1, hpttauhard2, hpttauvis1, hpttauvis2, hetajet1, hetajet2, hetajet3, hetabhard1, hetabhard2, hetatauhard1, hetatauhard2, hetatauvis1, hetatauvis2, hphijet1, hphijet2, hphijet3, hphibhard1, hphibhard2, hphitauhard1, hphitauhard2, hphitauvis1, hphitauvis2, hmjet1, hmjet2, hmjet3, hmbhard1, hmbhard2, hmtauhard1, hmtauhard2, hmtauvis1, hmtauvis2, hdrminj1tauvis, hdrminj2tauvis, hdrj1b1, hdrj1b2, hdrj2b1, hdrj2b2, hptmet, hphimet, hptmetfrominvis, hphimetfrominvis, hst, hstmet, hstmetfrominvis, hmj1tauvis1, hsumweights;

};
