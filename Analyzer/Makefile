-include Makefile.common
-include Makefile.local


BINARIES    := $(wildcard $(BINDIR)/*)
CUSTOMLIBS  := $(foreach subdir,$(subdirs), -L$(subdir))


all: Tuplizer_MINIAOD Counter_NANOAOD Counter_NANOAOD_weights Analyzer
	@echo "--> Successfully created all executables. Thanks Robin!"

Analyzer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Analyzer.o
	@for d in $(subdirs); do ( $(MAKE) -C $$d lib ) || exit 1; done
	@echo "--> Creating Analyzer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Analyzer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN) $(CUSTOMLIBS)

Tuplizer_MINIAOD: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Tuplizer_MINIAOD.o
	@echo "--> Creating Tuplizer_MINIAOD"
	@$(CC) $(OBJECTS) $(OBJDIR)/Tuplizer_MINIAOD.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Counter_NANOAOD: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Counter_NANOAOD.o
	@echo "--> Creating Counter_NANOAOD"
	@$(CC) $(OBJECTS) $(OBJDIR)/Counter_NANOAOD.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Counter_NANOAOD_weights: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Counter_NANOAOD_weights.o
	@echo "--> Creating Counter_NANOAOD_weights"
	@$(CC) $(OBJECTS) $(OBJDIR)/Counter_NANOAOD_weights.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)

$(OBJECTSEXE): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)




libClassDictionaries.so: $(LIBDIR)/ClassDictionaries.cxx
	@echo "--> Creating shared library with class dictionaries."
	@$(CC) $(CFLAGSDICT) $(LFLAGS) -shared -o $(LIBDIR)/$@ $(ROOTLIBS) $(CMSSWLIBS) $^

$(LIBDIR)/ClassDictionaries.cxx: $(INCLUDES) include/Linkdef.hpp
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@for d in $(subdirs); do ( $(MAKE) -C $$d clean ) || exit 1; done
	@echo "--> cleaning top-level folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
