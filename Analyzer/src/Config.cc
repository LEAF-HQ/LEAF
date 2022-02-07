#include <TString.h>
#include <TFile.h>
#include <iostream>
#include <sys/stat.h>

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/BaseTool.h"
#include "LEAF/Analyzer/include/useful_functions.h"

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
      ds.year     = getDatasetYear(current_node);
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


  // Loop through additional inputs and store to vector
  // ==================================================


  xmlNode *addcolls = findNodeByName(root_element, "AdditionalInputs");
  if(addcolls){
    vector<TString> existing_collections = {};
    for (xmlNode* current_node = addcolls->children; current_node; current_node = current_node->next){
      if(current_node->type == XML_ELEMENT_NODE){

        // here we are looking at one <AdditionalInput> at a time
        additional_input ai;

        // read in the dataset and check if a corresponding nominal dataset was defined in the xml file. Otherwise, this is ill-defined
        xmlNode *dataset_node = findNodeByName(current_node, "Dataset");
        dataset ds;
        ds.name     = getDatasetName(dataset_node);
        ds.type     = getDatasetType(dataset_node);
        ds.year     = getDatasetYear(dataset_node);
        ds.lumi     = getDatasetLumi(dataset_node);

        bool is_defined_nominal_dataset = false;
        for(dataset nomds : m_datasets){
          if(nomds.name == ds.name) is_defined_nominal_dataset = true;
        }
        string errormsg = "Additional dataset with name " + (string)ds.name + " does not have a corresponding nominal dataset defined.";
        if(!is_defined_nominal_dataset) throw runtime_error(errormsg);

        // loop over infiles of this dataset
        for (xmlNode* current_inputfile = dataset_node->children; current_inputfile; current_inputfile = current_inputfile->next){
          if(current_inputfile->type == XML_ELEMENT_NODE){
            ds.infilenames.emplace_back(getInputFileFileName(current_inputfile));
          }
        }
        ai.ds = ds;

        // read in the collections that the above dataset should be used for
        for (xmlNode* collection_node = current_node->children; collection_node; collection_node = collection_node->next){
          if(collection_node->type == XML_ELEMENT_NODE){
            if(!xmlStrEqual(collection_node->name, (xmlChar*)"Collection")) continue;

            collection coll;
            coll.classname = getCollectionClassname(collection_node);
            coll.branchname = getCollectionBranchname(collection_node);
            TString message = "In Config: Additional collection with name ";
            message += coll.branchname;
            message += " already used.";
            for(TString bn : existing_collections){
              if(bn == coll.branchname){
                throw runtime_error((string)message);
              }
            }
            ai.collections.emplace_back(coll);
            existing_collections.emplace_back(coll.branchname);

          }
        }

        cout << green << "--> Requesting " << ai.collections.size() << " additional collections from this additional input, using a total of " << ai.ds.infilenames.size() << " additional input files:" << reset << endl;
        for(collection c: ai.collections){
          cout << green << "  --> Adding collection " << c.branchname << ", which contains objects of class " << c.classname << "." << reset << endl;
        }

        m_additionalinputs.emplace_back(ai);
      }
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

    // Chain all samples of the same dataset into a TChain, for the nominal sample and the additional inputs (if any)
    event_chain.reset(new TChain("AnalysisTree"));
    for(additional_input ai : m_additionalinputs){
      shared_ptr<TChain> ch;
      ch.reset(new TChain("AnalysisTree"));
      m_additional_event_chains.emplace_back(ch);
    }
    cout << green << "--> Loading " << dataset_infilenames().size() << " input files for sample " << dataset_name() << "." << reset << endl;
    for(size_t i=0; i<dataset_infilenames().size(); i++){
      TString infilename_nominal = dataset_infilenames().at(i);
      event_chain->Add(infilename_nominal);
    }

    for(size_t i=0; i<m_additionalinputs.size(); i++){
      additional_input ai = m_additionalinputs.at(i);
      for(TString infilename_add: ai.ds.infilenames){
        m_additional_event_chains.at(i)->Add(infilename_add);
        cout << "infilename_add: " << infilename_add << endl;
      }
      m_additional_event_chains.at(i)->BuildIndex("lumiblock", "number");
    }


    nevt = event_chain->GetEntries();
    cout << green << "--> Loaded " << dataset_infilenames().size() << " files containing " << nevt << " events." << reset << endl;


    // make sure outdir exists
    TString mkdircommand = "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-mkdir -p ";
    TString outfolder = output_directory();
    if(outfolder.Contains("/pnfs")){
      mkdircommand += se_director();
    }
    mkdircommand += outfolder;
    system((const char*)mkdircommand);

    // create output file and handle exception for /pnfs storage that is not immediately writeable
    TString filename_tmp = dataset_type() + "__" + dataset_name() + postfix() + "_tmp.root";
    TString outfilename_target = outfolder + "/" + filename_tmp;
    TString outfilename_tmp = outfilename_target;

    // this is PSI T3 specific, change in other environments!
    if(se_director() == "root://t3dcachedb03.psi.ch/") {
      string tmpworkdirname = "/scratch/" + (string)getenv("USER") + "/tmp_workdir";
      string command = "mkdir -p " + (string)tmpworkdirname;
      system(command.c_str());
      outfilename_tmp = tmpworkdirname + "/" + filename_tmp;
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

    TString command = "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f " + outfilename_tmp + " ";
    if(outfolder.Contains("/pnfs")){
      command += se_director();
    }
    command += outfilename_final + " > /dev/null";

    system((const char*)command);
    command = "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-rm " + outfilename_tmp + " > /dev/null";
    system((const char*)command);
    cout << green << "--> Wrote histograms and tree to file: " << outfilename_final << reset << endl << endl;

    increment_idx();
  }
}
