-include Makefile.common
-include Makefile.local


BINARIES    := $(wildcard $(BINDIR)/*)
CUSTOMLIBS  := $(foreach subdir,$(subdirs), -lLEAF$(subdir))
CUSTOMDICTS := $(foreach subdir,$(subdirs), -l$(subdir)Classes)



all: execs
	@echo "--> Successfully created all executables. Thanks Robin!"

execs: Analyzer Counter_NANOAOD Counter_NANOAOD_weights

scram: dict
	@cd $(ANALYZERPATH)
	@echo "--> Calling 'scram b' in $(ANALYZERPATH) with MAKEFLAGS=\"$(MAKEFLAGS)\""
	+@scram b
	@for d in $(subdirs); do ( $(MAKE) -C $(LEAFPATH)/$$d scram ) || exit 1; done

dict: $(DICTLIB)
	@echo "--> Creating all subdirectory dictionaries"
	@for d in $(subdirs); do ( $(MAKE) -C $(LEAFPATH)/$$d dict ) || exit 1; done

Analyzer: scram dict $(OBJDIR)/Analyzer.o
	@echo "--> Creating Analyzer"
	@$(CC) $(OBJDIR)/Analyzer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN) $(CUSTOMLIBS) $(CUSTOMDICTS)

Counter_NANOAOD: scram dict $(OBJDIR)/Counter_NANOAOD.o
	@echo "--> Creating Counter_NANOAOD"
	@$(CC) $(OBJDIR)/Counter_NANOAOD.o $(LFLAGS) -o $(BINDIR)/$@  $(LIBSMAIN)

Counter_NANOAOD_weights: scram dict $(OBJDIR)/Counter_NANOAOD_weights.o
	@echo "--> Creating Counter_NANOAOD_weights"
	@$(CC) $(OBJDIR)/Counter_NANOAOD_weights.o $(LFLAGS) -o $(BINDIR)/$@  $(LIBSMAIN)

$(OBJECTSEXE): $(OBJDIR)/%.o : $(EXECDIR)/%.cxx
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN) $(CUSTOMLIBS)

$(DICTLIB):
	@echo "--> Creating shared library with $@."
	@rootcling -f $(LIBDIR_CMSSW)/$@_dict.cxx -c -p $(INCLUDES) include/$@_Linkdef.hpp
	@$(CC) $(CFLAGSDICT) $(LFLAGS) -shared -o $(LIBDIR_CMSSW)/lib$@.so $(ROOTLIBS) $(CMSSWLIBS) $(LIBDIR_CMSSW)/$@_dict.cxx


clean:
	@echo "--> calling 'scram b clean' in subdirs"
	@for d in $(subdirs); do ( $(MAKE) -C $(LEAFPATH)/$$d clean ) || exit 1; done
	@echo "--> calling 'scram b clean' in $(ANALYZERPATH)"
	@cd $(ANALYZERPATH)
	@scram b clean
	@echo "--> Removing manually added libraries with class dictionaries"
	@for l in $(DICTLIB); do ( rm -f $(LIBDIR_CMSSW)/*$${l}*.*) || exit 1; done
	@for d in $(subdirs); do ( rm -f $(LIBDIR_CMSSW)/*$${d}*.*) || exit 1; done
	@echo "--> cleaning top-level folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
