#include <TMultiGraph.h>
#include <TPad.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TStyle.h>
#include "../include/cosmetics.h"



TPad* SetupPad() {
  Float_t yplot = 0.65;
  Float_t yratio = 0.34;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);

  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y1, y2, y3;                           //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3-yplot;                                //     |     pad1    |
  y1 = y2-yratio;                               //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_pad = new TPad("pad1", "Control Plots 2", x1, y1, x2, y3);

  m_pad->SetTopMargin(0.05);
  m_pad->SetBottomMargin(0.14);
  m_pad->SetLeftMargin(0.14);
  m_pad->SetRightMargin(0.05);

  return m_pad;
}

TPad* SetupRatioPad() {
  Float_t yplot = 0.65;
  Float_t yratio = 0.34;
  Float_t yspace = 0.02;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);

  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y1, y2, y3;                           //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3 - yplot - yspace/2.;                  //     |     pad1    |
  y1 = y2 + yspace/2. - yratio;                 //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_rp = new TPad("rp1", "Ratio2", x1, y1, x2, y2);

  m_rp->SetTopMargin(0.0);
  m_rp->SetBottomMargin(0.35);
  m_rp->SetLeftMargin(0.15);
  m_rp->SetRightMargin(0.05);

  return m_rp;
}

TPad* SetupRatioPadTop() {
  Float_t yplot = 0.65;
  Float_t yspace = 0.02;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y2, y3;                               //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3 - yplot + yspace/2.;                  //     |     pad1    |
  //                                            //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_rp_top = new TPad("pad1", "Control Plots 2", x1, y2, x2, y3);


  m_rp_top->SetTopMargin(0.07);
  m_rp_top->SetBottomMargin(0.0);
  m_rp_top->SetLeftMargin(0.15);
  m_rp_top->SetRightMargin(0.05);

  return m_rp_top;
}

void HistCosmetics(TH1* hist, bool ratio) {
  hist->SetLineWidth(2);
  //hist->SetMarkerStyle(8);
  //hist->SetMarkerSize(0.4);
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  hist->GetYaxis()->SetNdivisions(505);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset

  if (ratio)
  {
    hist->GetYaxis()->SetTitleOffset(1.75);
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetXaxis()->SetTickSize(0.07);
    hist->GetYaxis()->SetTitleSize(15);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetRangeUser(0.3, 1.7);
    hist->GetYaxis()->SetLabelSize(14);
  }
  else
  {
    hist->GetXaxis()->SetTitleOffset(1.05);
    hist->GetYaxis()->SetTitleOffset(1.55);
  }
}

void HistCosmetics(TGraph* hist, bool ratio) {
  hist->SetLineWidth(2);
  //hist->SetMarkerStyle(8);
  //hist->SetMarkerSize(0.4);
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  hist->GetYaxis()->SetNdivisions(505);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset

  if (ratio)
  {
    hist->GetYaxis()->SetTitleOffset(1.75);
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetXaxis()->SetTickSize(0.07);
    hist->GetYaxis()->SetTitleSize(15);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetRangeUser(0.3, 1.7);
    hist->GetYaxis()->SetLabelSize(14);
  }
  else
  {
    hist->GetXaxis()->SetTitleOffset(1.05);
    hist->GetYaxis()->SetTitleOffset(1.55);
  }
}


void HistCosmetics(TMultiGraph* hist, bool ratio) {
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  hist->GetYaxis()->SetNdivisions(505);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset

  if (ratio)
  {
    hist->GetYaxis()->SetTitleOffset(1.75);
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetXaxis()->SetTickSize(0.07);
    hist->GetYaxis()->SetTitleSize(15);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetRangeUser(0.3, 1.7);
    hist->GetYaxis()->SetLabelSize(14);
  }
  else
  {
    hist->GetXaxis()->SetTitleOffset(1.05);
    hist->GetYaxis()->SetTitleOffset(1.55);
  }
}
