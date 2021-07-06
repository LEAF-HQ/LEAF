#include "Analyzer/include/GenInfoHists.h"
#include "Analyzer/include/constants.h"
#include "Analyzer/include/useful_functions.h"
#include <TH1F.h>
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

GenInfoHists::GenInfoHists(TString dir_) : BaseHists(dir_){


  hptmet = book<TH1F>("ptmet", ";E_{T}^{miss} (GenMET) [GeV]; Events / bin", 100, 0, 1000);
  hphimet = book<TH1F>("phimet", ";#phi(E_{T}^{miss} (GenMET)); Events / bin", 60, -3.5, 3.5);

  hgeninfoid1 = book<TH1F>("geninfoid1", ";ID of initial state 1; Events / bin", 11, -5.5, 5.5);
  hgeninfoid2 = book<TH1F>("geninfoid2", ";ID of initial state 2; Events / bin", 11, -5.5, 5.5);
  hgeninfox1 = book<TH1F>("geninfox1", ";x of initial state 1; Events / bin", 50, 0, 1);
  hgeninfox2 = book<TH1F>("geninfox2", ";x of initial state 2; Events / bin", 50, 0, 1);
  hgeninfoxpdf1 = book<TH1F>("geninfoxpdf1", ";xpdf of initial state 1; Events / bin", 500, 0, 100);
  hgeninfoxpdf2 = book<TH1F>("geninfoxpdf2", ";xpdf of initial state 2; Events / bin", 500, 0, 100);
  hgeninfoxpdfproduct = book<TH1F>("geninfoxpdfproduct", ";xpdf1 * xpdf2; Events / bin", 500, 0, 100);
  hgeninfoscalepdf = book<TH1F>("geninfoscalepdf", ";PDF scale; Events / bin", 200, 0, 3000);

  hsumweights = book<TH1F>("sumweights", ";bincontent = sum of event weights; Events / bin", 1, 0.5, 1.5);


  string pdfname = "NNPDF31_lo_as_0130";
  LHAPDF::initPDFSet(1, (std::string)(pdfname+".LHgrid"));
  pdf = LHAPDF::mkPDF( (std::string) pdfname, 0);

}

void GenInfoHists::fill(const RecoEvent & event){
  double weight = event.weight;




  // Event-based variables
  // =====================

  // MET
  hptmet->Fill(event.genmet->pt(), weight);
  hphimet->Fill(event.genmet->phi(), weight);

  // GenInfo
  hgeninfoid1->Fill(event.geninfo->id1(), weight);
  hgeninfoid2->Fill(event.geninfo->id2(), weight);
  hgeninfox1->Fill(event.geninfo->x1(), weight);
  hgeninfox2->Fill(event.geninfo->x2(), weight);
  hgeninfoscalepdf->Fill(event.geninfo->scale_pdf(), weight);

  double xpdf1 = pdf->xfxQ(event.geninfo->id1(), event.geninfo->x1(), event.geninfo->scale_pdf());
  double xpdf2 = pdf->xfxQ(event.geninfo->id2(), event.geninfo->x2(), event.geninfo->scale_pdf());

  hgeninfoxpdf1->Fill(xpdf1, weight);
  hgeninfoxpdf2->Fill(xpdf2, weight);
  hgeninfoxpdfproduct->Fill(xpdf1*xpdf2, weight);

  // cout << "q2: " << event.geninfo->scale_pdf() << endl;
  // cout << "id1: " << event.geninfo->id1() << ", x1: " << event.geninfo->x1() << ", xpdf1: " << xpdf1 << endl;
  // cout << "id2: " << event.geninfo->id2() << ", x2: " << event.geninfo->x2() << ", xpdf2: " << xpdf2 << endl;
  // cout << "xpdf1 * xpdf2: " << xpdf1 * xpdf2 << endl << endl;


  // cout << " event.geninfo->id1(): " << event.geninfo->id1() << endl;
  // cout << " event.geninfo->id2(): " << event.geninfo->id2() << endl;
  // cout << " event.geninfo->x1(): " << event.geninfo->x1() << endl;
  // cout << " event.geninfo->x2(): " << event.geninfo->x2() << endl;
  // cout << " event.geninfo->xpdf1(): " << event.geninfo->xpdf1() << endl;
  // cout << " event.geninfo->xpdf2(): " << event.geninfo->xpdf2() << endl;
  // cout << " event.geninfo->scale_pdf(): " << event.geninfo->scale_pdf() << endl;


  hsumweights->Fill(1, weight);
}
