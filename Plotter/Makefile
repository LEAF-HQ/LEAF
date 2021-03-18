CC = g++

CFLAGS = -std=c++17 -Wall -I${CMSSW_RELEASE_BASE}/src/ -I${LEAFPATH} `xml2-config --cflags`
LFLAGS = -Wall -I. -lm -lz -lMinuit -L${CMSSW_RELEASE_BASE}/lib/slc7_amd64_gcc700 `xml2-config --libs`
ROOTLIBS = `root-config --cflags --ldflags --evelibs --glibs`
LIBSMAIN = $(ROOTLIBS) -lstdc++fs

INCDIR   = include
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES     := $(wildcard $(SRCDIR)/*.cc)
INCLUDES    := $(wildcard $(INCDIR)/*.h)
BINARIES    := $(wildcard $(BINDIR)/*)
OBJECTS     := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

SOURCESEXE  := $(wildcard $(SRCDIR)/*.cxx)
OBJECTSEXE  := $(SOURCESEXE:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)


all: Plotter
	@echo "--> Successfully compiled the plotter! Thanks Robin!"


Plotter: $(OBJECTS) $(OBJDIR)/Plotter.o
	@echo "--> Creating Plotter"
	@$(CC) $(OBJECTS) $(OBJDIR)/Plotter.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

$(OBJECTSEXE): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)


clean:
	@for d in $(subdirs); do ( $(MAKE) -C $$d clean ) || exit 1; done
	@echo "--> cleaning top-level folders $(OBJDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(BINARIES)
