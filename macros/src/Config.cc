#include <TString.h>
#include <TFile.h>
#include <iostream>
#include <sys/stat.h>

#include "include/Config.h"
#include "include/BaseTool.h"
#include "include/useful_functions.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

using namespace std;

Config::Config(TString configfilename){
  if(m_is_init) throw runtime_error("Config object already initialized. Abort.");

  validateConfigFile(configfilename);
  xmlDoc *doc = xmlReadFile(configfilename, NULL, XML_PARSE_DTDATTR | XML_PARSE_NOENT | XML_PARSE_DTDVALID);
  xmlNode *root_element = xmlDocGetRootElement(doc);

  // Read general job information
  // ============================

  m_output_directory = getJobOutputpath(root_element);
  m_postfix = getJobPostfix(root_element);
  m_target_lumi = getJobTargetlumi(root_element);
  m_analysis_tool = getJobAnalysisTool(root_element);


  // Loop through InputDatasets and extract their information
  // ========================================================

  xmlNode *inputdatasets = findNodeByName(root_element, "InputDatasets");

  for (xmlNode* current_node = inputdatasets->children; current_node; current_node = current_node->next){
    if(current_node->type == XML_ELEMENT_NODE){
      dataset ds;
      ds.name     = getDatasetName(current_node);
      ds.type     = getDatasetType(current_node);
      ds.lumi     = getDatasetLumi(current_node);

      // loop over infiles of this dataset
      for (xmlNode* current_inputfile = current_node->children; current_inputfile; current_inputfile = current_inputfile->next){
        if(current_inputfile->type == XML_ELEMENT_NODE){
          ds.infilenames.emplace_back(getInputFileFileName(current_inputfile));
        }
      }
      m_datasets.emplace_back(ds);
    }
  }


  // Loop through additional variables and store to map
  // ==================================================

  xmlNode *addvars = findNodeByName(root_element, "AdditionalVariables");
  for (xmlNode* current_node = addvars->children; current_node; current_node = current_node->next){
    if(current_node->type == XML_ELEMENT_NODE){
      string name = getVariableName(current_node);
      string value = getVariableValue(current_node);
      TString message = "In Config: Additional variable with name ";
      message += name;
      message += " already used.";
      if(has(name)) throw runtime_error((string)message);
      m_additionalvariables[name] = value;
    }
  }


  xmlFreeDoc(doc);
  xmlCleanupParser();
  m_is_init = true;
}


void Config::process_datasets(){
  if(!m_is_init) throw runtime_error("Trying to process the datasets with an uninitialized Config instance. Abort.");

  // loop through samples
  while(idx() < n_datasets()){

    // Chain all samples of the same dataset into a TChain
    event_chain.reset(new TChain("AnalysisTree"));
    cout << green << "--> Loading " << dataset_infilenames().size() << " input files for sample " << dataset_name() << "." << reset << endl;
    for(size_t i=0; i<dataset_infilenames().size(); i++){
      event_chain->Add(dataset_infilenames().at(i));
    }
    nevt = event_chain->GetEntries();
    cout << green << "--> Loaded " << dataset_infilenames().size() << " files containing " << nevt << " events." << reset << endl;

    // create output tree
    outputtree = new TTree("AnalysisTree", "Events that passed the selection so far");

    // create instance of AnalysisTool and process this sample
    string toolname = analysis_tool();
    unique_ptr<BaseTool> analysis = ToolRegistry::build(toolname, *this);
    analysis->ProcessDataset(*this);


    // make sure outdir exists
    TString outfolder = output_directory();
    mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

    // create output file
    TString outfilename = outfolder + "/" + dataset_type() + "__" + dataset_name() + ".root";
    outfile.reset(new TFile(outfilename, "RECREATE"));

    // write output histograms and trees
    analysis->WriteHistograms(*this);
    outputtree->Write();
    outfile->Close();
    cout << green << "--> Wrote histograms and tree to file: " << outfile->GetName() << reset << endl << endl;

    increment_idx();
  }
}
