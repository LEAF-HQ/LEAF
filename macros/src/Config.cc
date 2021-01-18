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

// #include <boost/filesystem.hpp>

using namespace std;

Config::Config(TString configfilename){
  if(m_is_init) throw runtime_error("Config object already initialized. Abort.");

  validateConfigFile(configfilename);
  xmlDoc *doc = xmlReadFile(configfilename, NULL, XML_PARSE_DTDATTR | XML_PARSE_NOENT | XML_PARSE_DTDVALID);
  xmlNode *root_element = xmlDocGetRootElement(doc);

  // Read general job information
  // ============================

  m_output_directory = getJobOutputpath(root_element);
  m_se_director = getJobSEDirector(root_element);
  m_postfix = getJobPostfix(root_element);
  m_target_lumi = getJobTargetlumi(root_element);
  m_analysis_tool = getJobAnalysisTool(root_element);
  m_nevt_max = getJobNEventsMax(root_element);
  if(m_nevt_max == 0) throw runtime_error("Apparently, 'NEventsMax = 0' has been specified in the config file. This is an invalid value, either set it to <0 (running on all events) or >0, then stopping after the specified number of events.");
  m_nevt_skip = getJobNEventsSkip(root_element);
  if(m_nevt_skip < 0) throw runtime_error("Apparently, 'NEventsSkip < 0' has been specified in the config file. This is an invalid value, set it to >= 0.");


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


    // make sure outdir exists
    TString outfolder = output_directory();
    TString mkdircommand = "mkdir -p " + outfolder;
    system((const char*)mkdircommand);

    // create output file and handle exception for /pnfs storage that is not immediately writeable
    TString filename_tmp = dataset_type() + "__" + dataset_name() + postfix() + "_tmp.root";
    TString outfilename_target = outfolder + "/" + filename_tmp;

    // this is PSI T3 specific, change in other environments!
    TString outfilename_tmp = "";
    TString env_USER = getenv("USER");
    if(outfilename_target.Contains("/pnfs")){
      TString tmpworkdirname = "/scratch/" + env_USER + "/tmp_workdir";
      string command = "mkdir -p " + (string)tmpworkdirname;
      system(command.c_str());
      outfilename_tmp = tmpworkdirname + "/" + filename_tmp;
    }
    else{
      outfilename_tmp = outfilename_target;
    }

    outfile.reset(new TFile(outfilename_tmp, "RECREATE"));

    // create output tree
    outputtree = new TTree("AnalysisTree", "Events that passed the selection so far");

    // create instance of AnalysisTool and process this sample
    string toolname = analysis_tool();
    unique_ptr<BaseTool> analysis = ToolRegistry::build(toolname, *this);
    analysis->ProcessDataset(*this);

    // write output histograms and trees
    outfile->cd();
    analysis->WriteHistograms(*this);
    outputtree->OptimizeBaskets();
    outputtree->Write("", TObject::kOverwrite);
    outfile->Close();

    //rename tmp file
    TString outfilename_final = outfilename_target;
    outfilename_final.ReplaceAll("_tmp.root", ".root");

    string command = "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f " + (string)outfilename_tmp + " " + (string)se_director() + (string)outfilename_final;// + " > /dev/null";
    cout << "copy command: " << command << endl;
    system(command.c_str());
    command = (string)"LD_LIBRARY_PATH='' PYTHONPATH='' gfal-rm " + (string)outfilename_tmp;// + " > /dev/null";
    system(command.c_str());
    cout << green << "--> Wrote histograms and tree to file: " << outfilename_final << reset << endl << endl;

    increment_idx();
  }
}
