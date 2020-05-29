CC = g++

#This assumes the last element of CMSSW_FWLITE_INCLUDE_PATH is the path to the external boost include directory
BOOSTINC := $(lastword $(subst :, ,$(CMSSW_FWLITE_INCLUDE_PATH)))

# CFLAGS = -std=c++0x -Wall -lMinuit -I${CMSSW_RELEASE_BASE}/src/ -I${BOOSTINC} -I${MACROPATH}
CFLAGS = -std=c++17 -Wall -lMinuit -I${CMSSW_RELEASE_BASE}/src/ -I${BOOSTINC} -I${MACROPATH}
CFLAGSDICT = -std=c++17 -fPIC -Wall -I${MACROPATH}
LFLAGS = -Wall -I. -lm -L${CMSSW_RELEASE_BASE}/lib/slc7_amd64_gcc700 -L${MACROLIBPATH}
ROOTLIBS = `root-config --cflags --ldflags --evelibs --glibs`
LIBSMAIN = $(ROOTLIBS) -lstdc++fs -lFWCoreFWLite -lDataFormatsFWLite -lDataFormatsPatCandidates -lDataFormatsCommon -lClassDictionaries

INCDIR   = include
SRCDIR   = src
OBJDIR   = obj
LIBDIR   = lib
BINDIR   = bin

BINARIES    := $(wildcard $(BINDIR)/*)

SOURCES     := $(wildcard $(SRCDIR)/*.cc)
INCLUDES    := $(wildcard $(INCDIR)/*.h)
LIBOBJS     := $(wildcard $(LIBDIR)/*.so $(LIBDIR)/*.cxx $(LIBDIR)/*.pcm)
OBJECTS     := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

SOURCESEXE  := $(wildcard $(SRCDIR)/*.cxx)
OBJECTSEXE  := $(SOURCESEXE:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

# Tuplizer only needs a few sources, giving them by hand avoids compiling the entire folder
SOURCESTUP  := $(SRCDIR)/useful_functions.cc $(SRCDIR)/Event.cc 
OBJECTSTUP  := $(SOURCESTUP:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

all: Tuplizer main
	@echo "--> Successfully created all executables. Thanks Robin!"

main: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/main.o
	@echo "--> Creating main"
	@$(CC) $(OBJECTS) $(OBJDIR)/main.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Tuplizer: $(OBJDIR)/Tuplizer.o libClassDictionaries.so $(OBJECTSTUP)
	@echo "--> Creating Tuplizer"
	@$(CC) $(OBJECTSTUP) $(OBJDIR)/Tuplizer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

# $(OBJECTSEXE): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
# 	@echo "--> Creating object $@"
# 	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

$(OBJDIR)/Tuplizer.o: $(SRCDIR)/Tuplizer.cxx
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

$(OBJDIR)/main.o: $(SRCDIR)/main.cxx
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
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS)
