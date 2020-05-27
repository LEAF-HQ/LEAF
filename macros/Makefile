CC = g++

#This assumes the last element of CMSSW_FWLITE_INCLUDE_PATH is the path to the external boost include directory
BOOSTINC := $(lastword $(subst :, ,$(CMSSW_FWLITE_INCLUDE_PATH)))

CFLAGS = -std=c++0x -Wall -lMinuit -I${CMSSW_RELEASE_BASE}/src/ -I${BOOSTINC} -I${MACROPATH}
CFLAGSDICT = -std=c++17 -fPIC -Wall -I${MACROPATH}
LFLAGS = -Wall -I. -lm -L${CMSSW_RELEASE_BASE}/lib/slc7_amd64_gcc700 -L${MACROLIBPATH}
ROOTLIBS = `root-config --cflags --ldflags --evelibs --glibs`
LIBSMAIN = $(ROOTLIBS) -lFWCoreFWLite -lDataFormatsFWLite -lDataFormatsPatCandidates -lDataFormatsCommon -lClassDictionaries

INCDIR   = include
SRCDIR   = src
OBJDIR   = obj
LIBDIR   = lib

SOURCES     := $(wildcard $(SRCDIR)/*.cc)
INCLUDES    := $(wildcard $(INCDIR)/*.h)
LIBOBJS     := $(wildcard $(LIBDIR)/*.so $(LIBDIR)/*.cxx $(LIBDIR)/*.pcm)
OBJECTS     := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

SOURCESTUP  := $(wildcard $(SRCDIR)/*.cxx)
OBJECTSTUP  := $(SOURCESTUP:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

all: Tuplizer main

main: libClassDictionaries.so $(OBJECTS)
	@echo "--> Creating main"
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@ $(LIBSMAIN)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@ for main"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

Tuplizer: libClassDictionaries.so $(OBJECTSTUP)
	@echo "--> Creating Tuplizer"
	@$(CC) $(OBJECTSTUP) $(LFLAGS) -o $@ $(LIBSMAIN)

$(OBJECTSTUP): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@echo "--> Creating object $@ for Tuplizer"
	@$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@ $(LIBSMAIN)

libClassDictionaries.so: $(LIBDIR)/ClassDictionaries.cxx
	@echo "--> Creating shared library with class dictionaries."
	@$(CC) $(CFLAGSDICT) -shared -o $(LIBDIR)/$@ $(ROOTLIBS) $^

$(LIBDIR)/ClassDictionaries.cxx: $(INCLUDES) include/Linkdef.hpp
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@echo "--> cleaning folders $(OBJDIR)/ and $(LIBDIR)/"
	@rm $(wildcard $(OBJDIR)/*.o) $(LIBOBJS)
