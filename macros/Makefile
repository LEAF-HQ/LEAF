CC = g++

#This assumes the last element of CMSSW_FWLITE_INCLUDE_PATH is the path to the external boost include directory
BOOSTINC := $(lastword $(subst :, ,$(CMSSW_FWLITE_INCLUDE_PATH)))
LIBINCLUDES := $(subst :, -L,$(MACROLIBPATH))

CFLAGS = -std=c++17 -Wall -I${CMSSW_RELEASE_BASE}/src/ -I${BOOSTINC} -I${MACROPATH} `xml2-config --cflags`
CFLAGSDICT = -std=c++17 -fPIC -Wall -I${MACROPATH} `xml2-config --cflags`
# `xml2-config --cflags`
LFLAGS = -Wall -I. -lm -lz -lMinuit -L${CMSSW_RELEASE_BASE}/lib/slc7_amd64_gcc700 -L${LIBINCLUDES} `xml2-config --libs`
ROOTLIBS = `root-config --cflags --ldflags --evelibs --glibs`
CMSSWLIBS= -lFWCoreUtilities -lDataFormatsHepMCCandidate -lDataFormatsCandidate -lGenVector -lFWCoreFWLite -lDataFormatsFWLite -lDataFormatsPatCandidates -lDataFormatsCommon
LIBSMAIN = $(ROOTLIBS) -lstdc++fs ${CMSSWLIBS} -lClassDictionaries -lxml2 #-lPugiXML
LIBSPLOT = $(ROOTLIBS) -lstdc++fs ${CMSSWLIBS}

INCDIR   = include
SRCDIR   = src
OBJDIR   = obj
LIBDIR   = lib
BINDIR   = bin

BINARIES    := $(wildcard $(BINDIR)/*)

SOURCES     := $(wildcard $(SRCDIR)/*.cc)
INCLUDES    := $(wildcard $(INCDIR)/*.h)
LIBOBJS     := $(wildcard $(LIBDIR)/*.so $(LIBDIR)/*.cxx $(LIBDIR)/*.pcm $(LIBDIR)/*.cxx_tmp*)
OBJECTS     := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

SOURCESEXE  := $(wildcard $(SRCDIR)/*.cxx)
OBJECTSEXE  := $(SOURCESEXE:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

# Tuplizer only needs a few sources, giving them by hand avoids compiling the entire folder
SOURCESTUP  := $(SRCDIR)/useful_functions.cc $(SRCDIR)/Event.cc
OBJECTSTUP  := $(SOURCESTUP:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

# Plotter also only needs a few sources, giving them by hand avoids compiling the entire folder
SOURCESPLOT  := $(SRCDIR)/useful_functions.cc $(SRCDIR)/PlottingTool.cc $(SRCDIR)/cosmetics.cc $(SRCDIR)/PlotGenlevel.cc
OBJECTSPLOT  := $(SOURCESPLOT:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

all: Tuplizer Plotter Analyzer
	@echo "--> Successfully created all executables. Thanks Robin!"

Analyzer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Analyzer.o
	@echo "--> Creating Analyzer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Analyzer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Tuplizer: libClassDictionaries.so $(OBJECTSTUP) $(OBJDIR)/Tuplizer.o
	@echo "--> Creating Tuplizer"
	@$(CC) $(OBJECTSTUP) $(OBJDIR)/Tuplizer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Plotter: $(OBJECTSPLOT) $(OBJDIR)/Plotter.o
	@echo "--> Creating Plotter"
	@$(CC) $(OBJECTSPLOT) $(OBJDIR)/Plotter.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSPLOT)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

$(OBJECTSEXE): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)




libClassDictionaries.so: $(LIBDIR)/ClassDictionaries.cxx
	@echo "--> Creating shared library with class dictionaries."
	@$(CC) $(CFLAGSDICT) -shared -o $(LIBDIR)/$@ $(ROOTLIBS) $^

$(LIBDIR)/ClassDictionaries.cxx: $(INCLUDES) include/Linkdef.hpp
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@echo "--> cleaning folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
