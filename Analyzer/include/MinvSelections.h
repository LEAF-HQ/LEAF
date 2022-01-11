#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class MemuSelection: public Selection<RecoEvent>{
public:
  explicit MemuSelection(const Config & cfg, int mmin_, int mmax_);
  virtual bool passes(RecoEvent & event) override;

private:
  double mmin, mmax;

};

class MetauSelection: public Selection<RecoEvent>{
public:
  explicit MetauSelection(const Config & cfg, int mmin_, int mmax_);
  virtual bool passes(RecoEvent & event) override;

private:
  double mmin, mmax;

};

class MmutauSelection: public Selection<RecoEvent>{
public:
  explicit MmutauSelection(const Config & cfg, int mmin_, int mmax_);
  virtual bool passes(RecoEvent & event) override;

private:
  double mmin, mmax;

};

class MtautauSelection: public Selection<RecoEvent>{
public:
  explicit MtautauSelection(const Config & cfg, int mmin_, int mmax_);
  virtual bool passes(RecoEvent & event) override;

private:
  double mmin, mmax;

};

class MmumuSelection: public Selection<RecoEvent>{
public:
  explicit MmumuSelection(const Config & cfg, int mmin_, int mmax_);
  virtual bool passes(RecoEvent & event) override;

private:
  double mmin, mmax;

};
