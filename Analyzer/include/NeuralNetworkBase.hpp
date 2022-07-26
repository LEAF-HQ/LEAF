#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/Config.h"

// save diagnostic state
#pragma GCC diagnostic push
// turn off the specific warning. Can also use "-Wall"
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#pragma GCC diagnostic pop

// adapted from https://github.com/UHH2/UHH2/blob/RunII_106X_v2/common/include/NeuralNetworkBase.hpp


class NeuralNetworkBase: public AnalysisModule<RecoEvent> {
public:
    explicit NeuralNetworkBase(const Config & cfg, const std::string & ModelName, const std::string& ConfigName);
    virtual bool process(RecoEvent & event) override;
    virtual void CreateInputs(RecoEvent & event);
    std::vector<tensorflow::Tensor> GetInputs() const{return NNInputs;}
    std::vector<tensorflow::Tensor> GetOutputs() const{return NNoutputs;}

protected:
    tensorflow::Session* NNsession;
    std::map<std::string, std::vector<int>> LayerInputs;
    std::vector<std::string> LayerOutputs;
    std::vector<tensorflow::Tensor> NNInputs;
    std::vector<tensorflow::Tensor> NNoutputs;
};
