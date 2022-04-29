#include <TString.h>
#include <TFile.h>
#include <iostream>
#include <sys/stat.h>

#include "LEAF/Plotter/include/PlotterConfig.h"
#include "LEAF/Analyzer/include/useful_functions.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>


using namespace std;

PlotterConfig::PlotterConfig(TString configfilename){
  if(m_is_init) throw runtime_error("PlotterConfig object already initialized. Abort.");

  validateConfigFile(configfilename);
  xmlDoc *doc = xmlReadFile(configfilename, NULL, XML_PARSE_DTDATTR | XML_PARSE_NOENT | XML_PARSE_DTDVALID);
  xmlNode *root_element = xmlDocGetRootElement(doc);

  // Read general job information
  // ============================

  // get file configs
  xmlNode *node_file_config = findNodeByName(root_element, "FileConfiguration");
  m_output_directory = getNodeProperty(node_file_config, "OutputDirectory");
  m_input_directory  = getNodeProperty(node_file_config, "InputDirectory");
  m_se_director      = getNodeProperty(node_file_config, "SEDirector");
  m_prefix           = getNodeProperty(node_file_config, "PreFix");

  // get plotting configs
  xmlNode *node_plotting_config = findNodeByName(root_element, "PlottingConfiguration");
  m_lumitext  = getNodeProperty(node_plotting_config, "lumitext");
  m_blind     = ("true" == getNodeProperty(node_plotting_config, "blind"));
  m_logY      = ("true" == getNodeProperty(node_plotting_config, "logY"));
  m_normalize = ("true" == getNodeProperty(node_plotting_config, "normalize"));
  m_singlePDF = ("true" == getNodeProperty(node_plotting_config, "singlePDF"));
  m_numerator = getNodeProperty(node_plotting_config, "numerator");

  // Loop through InputDatasets and extract their information
  // ========================================================

  xmlNode *node_inputdatasets = findNodeByName(root_element, "InputDatasets");

  for (xmlNode* current_node = node_inputdatasets->children; current_node; current_node = current_node->next){
    if(current_node->type == XML_ELEMENT_NODE){

      double this_scalefactor = 1.;
      if(getNodeProperty(current_node, "ScaleFactor") != ""){
        this_scalefactor = stod(getNodeProperty(current_node, "ScaleFactor"));
      }
      PlottingDataset ds(
        getNodeProperty(current_node, "Name"),
        stoi(getNodeProperty(current_node, "Color")),
        stoi(getNodeProperty(current_node, "Linestyle")),
        getNodeProperty(current_node, "Legend"),
        getNodeProperty(current_node, "Type"),
        ("true" == getNodeProperty(current_node, "Stack")),
        this_scalefactor,
        m_input_directory + "/" + (TString)getNodeProperty(current_node, "Type") + "__" + (TString)getNodeProperty(current_node, "Name") + ".root"
      );

      m_datasets.emplace_back(ds);
    }
  }



  xmlFreeDoc(doc);
  xmlCleanupParser();
  m_is_init = true;
}
