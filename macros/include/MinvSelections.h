#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

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
