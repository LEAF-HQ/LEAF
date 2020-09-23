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
LIBSMAIN = $(ROOTLIBS) -lstdc++fs ${CMSSWLIBS} -lClassDictionaries -lxml2
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

all: Tuplizer Tuplizer_NANOAOD Plotter Analyzer
	@echo "--> Successfully created all executables. Thanks Robin!"

Analyzer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Analyzer.o
	@echo "--> Creating Analyzer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Analyzer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Tuplizer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Tuplizer.o
	@echo "--> Creating Tuplizer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Tuplizer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Tuplizer_NANOAOD: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Tuplizer_NANOAOD.o
	@echo "--> Creating Tuplizer_NANOAOD"
	@$(CC) $(OBJECTS) $(OBJDIR)/Tuplizer_NANOAOD.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Plotter: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Plotter.o
	@echo "--> Creating Plotter"
	@$(CC) $(OBJECTS) $(OBJDIR)/Plotter.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

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
#$(LIBDIR)/ClassDictionaries.cxx: include/allclasses.hpp include/Linkdef.hpp
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@echo "--> cleaning folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
