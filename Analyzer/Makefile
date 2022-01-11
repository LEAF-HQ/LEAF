-include Makefile.common
-include Makefile.local


BINARIES    := $(wildcard $(BINDIR)/*)
CUSTOMLIBS  := $(foreach subdir,$(subdirs), -lLEAF$(subdir))
CUSTOMDICTS := $(foreach subdir,$(subdirs), -l$(subdir)ClassDictionaries)



all: execs
	@echo "--> Successfully created all executables. Thanks Robin!"

execs: scram dict Analyzer Counter_NANOAOD Counter_NANOAOD_weights

scram: dict
	@export MAKEFLAGS="$(MAKEFLAGS)"
	@cd $(ANALYZERPATH)
	@echo "--> Calling 'scram b' in $(ANALYZERPATH) with MAKEFLAGS=\"$(MAKEFLAGS)\""
	+@scram b
	@for d in $(subdirs); do ( cd $(LEAFPATH)/$$d; scram b $(MAKEFLAGS) ) || exit 1; done

dict: libClassDictionaries.so
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

libClassDictionaries.so: $(LIBDIR)/ClassDictionaries.cxx
	@echo "--> Creating shared library with class dictionaries."
	@$(CC) $(CFLAGSDICT) $(LFLAGS) -shared -o $(LIBDIR)/$@ $(ROOTLIBS) $(CMSSWLIBS) $^
	@echo "--> Copying library with class dictionary to local CMSSW library folder: $(LIBDIR_CMSSW)"
	@cp $(LIBDIR)/$@ $(LIBDIR_CMSSW)/

$(LIBDIR)/ClassDictionaries.cxx: $(INCLUDES) include/Linkdef.hpp
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@echo "--> calling 'scram b clean' in subdirs"
	@for d in $(subdirs); do ( cd $(LEAFPATH)/$$d; scram b clean ) || exit 1; done
	@echo "--> calling 'scram b clean' in $(ANALYZERPATH)"
	@cd $(ANALYZERPATH)
	@scram b clean
	@echo "--> Removing manually added libraries with class dictionaries"
	@if [ -f "$(LIBDIR_CMSSW)/libClassDictionaries.so" ]; then rm $(LIBDIR_CMSSW)/libClassDictionaries.so; fi
	@for d in $(subdirs); do ( if [ -f "$$(echo $(LIBDIR_CMSSW)/lib$${d}ClassDictionaries.so)" ]; then rm "$$(echo $(LIBDIR_CMSSW)/lib$${d}ClassDictionaries.so)"; fi ); done
	@echo "--> cleaning top-level folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
