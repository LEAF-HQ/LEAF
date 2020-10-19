#include "$MYANALYSISNAME/include/$MYEVENTCLASS.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include <TH1D.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

$MYEVENTCLASS::$MYEVENTCLASS(){
}

$MYEVENTCLASS::~$MYEVENTCLASS(){
}

void $MYEVENTCLASS::clear(){
  RecoEvent::clear();
}

void $MYEVENTCLASS::reset(){
  RecoEvent::reset();
}
