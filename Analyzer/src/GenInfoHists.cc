#include "LEAF/Analyzer/include/GenInfoHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"
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



  string pdfname = "NNPDF31_lo_as_0130";
  LHAPDF::initPDFSet(1, (std::string)(pdfname+".LHgrid"));
  pdf = LHAPDF::mkPDF( (std::string) pdfname, 0);

  string pdfname_new = "NNPDF31_nnlo_hessian_pdfas";
  LHAPDF::initPDFSet(1, (std::string)(pdfname_new+".LHgrid"));
  pdf_new = LHAPDF::mkPDF( (std::string) pdfname_new, 0);


  hptmet = book<TH1F>("ptmet", ";gen. p_{T}^{miss} [GeV]; Events / bin", 100, 0, 1000);
  hphimet = book<TH1F>("phimet", ";#phi(gen. p_{T}^{miss}); Events / bin", 60, -3.5, 3.5);

  hgeninfoid1 = book<TH1F>("geninfoid1", ";ID of initial state 1; Events / bin", 11, -5.5, 5.5);
  hgeninfoid2 = book<TH1F>("geninfoid2", ";ID of initial state 2; Events / bin", 11, -5.5, 5.5);
  hgeninfox1 = book<TH1F>("geninfox1", ";x of initial state 1; Events / bin", 50, 0, 1);
  hgeninfox2 = book<TH1F>("geninfox2", ";x of initial state 2; Events / bin", 50, 0, 1);
  hgeninfoxall = book<TH1F>("geninfoxall", ";all x (both partons together); Events / bin", 50, 0, 1);
  hgeninfoxb = book<TH1F>("geninfoxb", ";x of all b(bar) quarks; Events / bin", 50, 0, 1);
  hgeninfoxc = book<TH1F>("geninfoxc", ";x of all c(bar) quarks; Events / bin", 50, 0, 1);
  hgeninfoxpdf1 = book<TH1F>("geninfoxpdf1", ";xpdf of initial state 1(" + (TString)pdfname + "); Events / bin", 100, 0, 20);
  hgeninfoxpdf2 = book<TH1F>("geninfoxpdf2", ";xpdf of initial state 2(" + (TString)pdfname + "); Events / bin", 100, 0, 20);
  hgeninfoxpdf1_rebin1 = book<TH1F>("geninfoxpdf1_rebin1", ";xpdf of initial state 1(" + (TString)pdfname + "); Events / bin", 40, 0, 20);
  hgeninfoxpdf2_rebin1 = book<TH1F>("geninfoxpdf2_rebin1", ";xpdf of initial state 2(" + (TString)pdfname + "); Events / bin", 40, 0, 20);
  hgeninfoxpdf1_rebin2 = book<TH1F>("geninfoxpdf1_rebin2", ";xpdf of initial state 1(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdf2_rebin2 = book<TH1F>("geninfoxpdf2_rebin2", ";xpdf of initial state 2(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdf1_rebin3 = book<TH1F>("geninfoxpdf1_rebin3", ";xpdf of initial state 1(" + (TString)pdfname + "); Events / bin", 40, 0, 0.2);
  hgeninfoxpdf2_rebin3 = book<TH1F>("geninfoxpdf2_rebin3", ";xpdf of initial state 2(" + (TString)pdfname + "); Events / bin", 40, 0, 0.2);
  hgeninfoxpdfall = book<TH1F>("geninfoxpdfall", ";all xpdf (both partons together)(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdfb = book<TH1F>("geninfoxpdfb", ";xpdf of all b(bar) quarks(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdfc = book<TH1F>("geninfoxpdfc", ";xpdf of all c(bar) quarks(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdfproduct = book<TH1F>("geninfoxpdfproduct", ";xpdf1 * xpdf2(" + (TString)pdfname + "); Events / bin", 100, 0, 20);
  hgeninfoxpdfproduct_rebin1 = book<TH1F>("geninfoxpdfproduct_rebin1", ";xpdf1 * xpdf2(" + (TString)pdfname + "); Events / bin", 40, 0, 20);
  hgeninfoxpdfproduct_rebin2 = book<TH1F>("geninfoxpdfproduct_rebin2", ";xpdf1 * xpdf2(" + (TString)pdfname + "); Events / bin", 40, 0, 2);
  hgeninfoxpdfproduct_rebin3 = book<TH1F>("geninfoxpdfproduct_rebin3", ";xpdf1 * xpdf2(" + (TString)pdfname + "); Events / bin", 40, 0, 0.2);
  hgeninfoxpdfproduct_rebin4 = book<TH1F>("geninfoxpdfproduct_rebin4", ";xpdf1 * xpdf2(" + (TString)pdfname + "); Events / bin", 4000, 0, 20);

  hnewpdf_geninfoxpdf1 = book<TH1F>("newpdf_geninfoxpdf1", ";new xpdf of initial state 1(" + (TString)pdfname_new + "); Events / bin", 100, 0, 20);
  hnewpdf_geninfoxpdf2 = book<TH1F>("newpdf_geninfoxpdf2", ";new xpdf of initial state 2(" + (TString)pdfname_new + "); Events / bin", 100, 0, 20);
  hnewpdf_geninfoxpdf1_rebin1 = book<TH1F>("newpdf_geninfoxpdf1_rebin1", ";new xpdf of initial state 1(" + (TString)pdfname_new + "); Events / bin", 40, 0, 20);
  hnewpdf_geninfoxpdf2_rebin1 = book<TH1F>("newpdf_geninfoxpdf2_rebin1", ";new xpdf of initial state 2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 20);
  hnewpdf_geninfoxpdf1_rebin2 = book<TH1F>("newpdf_geninfoxpdf1_rebin2", ";new xpdf of initial state 1(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdf2_rebin2 = book<TH1F>("newpdf_geninfoxpdf2_rebin2", ";new xpdf of initial state 2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdf1_rebin3 = book<TH1F>("newpdf_geninfoxpdf1_rebin3", ";new xpdf of initial state 1(" + (TString)pdfname_new + "); Events / bin", 40, 0, 0.2);
  hnewpdf_geninfoxpdf2_rebin3 = book<TH1F>("newpdf_geninfoxpdf2_rebin3", ";new xpdf of initial state 2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 0.2);
  hnewpdf_geninfoxpdfall = book<TH1F>("newpdf_geninfoxpdfall", ";all new xpdf (both partons together)(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdfb = book<TH1F>("newpdf_geninfoxpdfb", ";new xpdf of all b(bar) quarks(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdfc = book<TH1F>("newpdf_geninfoxpdfc", ";new xpdf of all c(bar) quarks(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdfproduct = book<TH1F>("newpdf_geninfoxpdfproduct", ";new xpdf1 * xpdf2(" + (TString)pdfname_new + "); Events / bin", 100, 0, 20);
  hnewpdf_geninfoxpdfproduct_rebin1 = book<TH1F>("newpdf_geninfoxpdfproduct_rebin1", ";new xpdf1 * new xpdf2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 20);
  hnewpdf_geninfoxpdfproduct_rebin2 = book<TH1F>("newpdf_geninfoxpdfproduct_rebin2", ";new xpdf1 * new xpdf2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 2);
  hnewpdf_geninfoxpdfproduct_rebin3 = book<TH1F>("newpdf_geninfoxpdfproduct_rebin3", ";new xpdf1 * new xpdf2(" + (TString)pdfname_new + "); Events / bin", 40, 0, 0.2);
  hnewpdf_geninfoxpdfproduct_rebin4 = book<TH1F>("newpdf_geninfoxpdfproduct_rebin4", ";new xpdf1 * new xpdf2(" + (TString)pdfname_new + "); Events / bin", 4000, 0, 20);

  hgeninfoscalepdf = book<TH1F>("geninfoscalepdf", ";PDF scale; Events / bin", 200, 0, 3000);

  hsumweights = book<TH1F>("sumweights", ";bincontent = sum of event weights; Events / bin", 1, 0.5, 1.5);


}

void GenInfoHists::fill(const RecoEvent & event){
  if(event.is_data) return;
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
  hgeninfoxall->Fill(event.geninfo->x1(), weight);
  hgeninfoxall->Fill(event.geninfo->x2(), weight);
  if(abs(event.geninfo->id1()) == 5) hgeninfoxb->Fill(event.geninfo->x1(), weight);
  if(abs(event.geninfo->id2()) == 5) hgeninfoxb->Fill(event.geninfo->x2(), weight);
  if(abs(event.geninfo->id1()) == 4) hgeninfoxc->Fill(event.geninfo->x1(), weight);
  if(abs(event.geninfo->id2()) == 4) hgeninfoxc->Fill(event.geninfo->x2(), weight);
  hgeninfoscalepdf->Fill(event.geninfo->scale_pdf(), weight);

  double xpdf1 = pdf->xfxQ(event.geninfo->id1(), event.geninfo->x1(), event.geninfo->scale_pdf());
  double xpdf2 = pdf->xfxQ(event.geninfo->id2(), event.geninfo->x2(), event.geninfo->scale_pdf());
  double xpdf1_new = pdf_new->xfxQ(event.geninfo->id1(), event.geninfo->x1(), event.geninfo->scale_pdf());
  double xpdf2_new = pdf_new->xfxQ(event.geninfo->id2(), event.geninfo->x2(), event.geninfo->scale_pdf());

  hgeninfoxpdf1->Fill(xpdf1, weight);
  hgeninfoxpdf2->Fill(xpdf2, weight);
  hgeninfoxpdf1_rebin1->Fill(xpdf1, weight);
  hgeninfoxpdf2_rebin1->Fill(xpdf2, weight);
  hgeninfoxpdf1_rebin2->Fill(xpdf1, weight);
  hgeninfoxpdf2_rebin2->Fill(xpdf2, weight);
  hgeninfoxpdf1_rebin3->Fill(xpdf1, weight);
  hgeninfoxpdf2_rebin3->Fill(xpdf2, weight);
  hgeninfoxpdfproduct->Fill(xpdf1*xpdf2, weight);
  hgeninfoxpdfproduct_rebin1->Fill(xpdf1*xpdf2, weight);
  hgeninfoxpdfproduct_rebin2->Fill(xpdf1*xpdf2, weight);
  hgeninfoxpdfproduct_rebin3->Fill(xpdf1*xpdf2, weight);
  hgeninfoxpdfproduct_rebin4->Fill(xpdf1*xpdf2, weight);

  hgeninfoxpdfall->Fill(xpdf1, weight);
  hgeninfoxpdfall->Fill(xpdf2, weight);
  if(abs(event.geninfo->id1()) == 5) hgeninfoxpdfb->Fill(xpdf1, weight);
  if(abs(event.geninfo->id2()) == 5) hgeninfoxpdfb->Fill(xpdf2, weight);
  if(abs(event.geninfo->id1()) == 4) hgeninfoxpdfc->Fill(xpdf1, weight);
  if(abs(event.geninfo->id2()) == 4) hgeninfoxpdfc->Fill(xpdf2, weight);


  hnewpdf_geninfoxpdf1->Fill(xpdf1_new, weight);
  hnewpdf_geninfoxpdf2->Fill(xpdf2_new, weight);
  hnewpdf_geninfoxpdf1_rebin1->Fill(xpdf1_new, weight);
  hnewpdf_geninfoxpdf2_rebin1->Fill(xpdf2_new, weight);
  hnewpdf_geninfoxpdf1_rebin2->Fill(xpdf1_new, weight);
  hnewpdf_geninfoxpdf2_rebin2->Fill(xpdf2_new, weight);
  hnewpdf_geninfoxpdf1_rebin3->Fill(xpdf1_new, weight);
  hnewpdf_geninfoxpdf2_rebin3->Fill(xpdf2_new, weight);
  hnewpdf_geninfoxpdfproduct->Fill(xpdf1_new*xpdf2_new, weight);
  hnewpdf_geninfoxpdfproduct_rebin1->Fill(xpdf1_new*xpdf2_new, weight);
  hnewpdf_geninfoxpdfproduct_rebin2->Fill(xpdf1_new*xpdf2_new, weight);
  hnewpdf_geninfoxpdfproduct_rebin3->Fill(xpdf1_new*xpdf2_new, weight);
  hnewpdf_geninfoxpdfproduct_rebin4->Fill(xpdf1_new*xpdf2_new, weight);

  hnewpdf_geninfoxpdfall->Fill(xpdf1_new, weight);
  hnewpdf_geninfoxpdfall->Fill(xpdf2_new, weight);
  if(abs(event.geninfo->id1()) == 5) hnewpdf_geninfoxpdfb->Fill(xpdf1_new, weight);
  if(abs(event.geninfo->id2()) == 5) hnewpdf_geninfoxpdfb->Fill(xpdf2_new, weight);
  if(abs(event.geninfo->id1()) == 4) hnewpdf_geninfoxpdfc->Fill(xpdf1_new, weight);
  if(abs(event.geninfo->id2()) == 4) hnewpdf_geninfoxpdfc->Fill(xpdf2_new, weight);


  hsumweights->Fill(1, weight);
}
