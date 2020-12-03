-include Makefile.common
-include Makefile.local


BINARIES    := $(wildcard $(BINDIR)/*)
CUSTOMLIBS  := $(foreach subdir,$(subdirs), -l$(subdir))



all: Tuplizer Tuplizer_NANOAOD Counter_NANOAOD Plotter Analyzer
	@echo "--> Successfully created all executables. Thanks Robin!"

Analyzer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Analyzer.o
	@for d in $(subdirs); do ( $(MAKE) -C $$d lib ) || exit 1; done
	@echo "--> Creating Analyzer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Analyzer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN) $(CUSTOMLIBS)

Tuplizer: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Tuplizer.o
	@echo "--> Creating Tuplizer"
	@$(CC) $(OBJECTS) $(OBJDIR)/Tuplizer.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Tuplizer_NANOAOD: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Tuplizer_NANOAOD.o
	@echo "--> Creating Tuplizer_NANOAOD"
	@$(CC) $(OBJECTS) $(OBJDIR)/Tuplizer_NANOAOD.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

Counter_NANOAOD: libClassDictionaries.so $(OBJECTS) $(OBJDIR)/Counter_NANOAOD.o
	@echo "--> Creating Counter_NANOAOD"
	@$(CC) $(OBJECTS) $(OBJDIR)/Counter_NANOAOD.o $(LFLAGS) -o $(BINDIR)/$@ $(LIBSMAIN)

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
	@echo "--> Creating class dictionaries."
	@rootcling -f $@ -c -p $^


clean:
	@for d in $(subdirs); do ( $(MAKE) -C $$d clean ) || exit 1; done
	@echo "--> cleaning top-level folders $(OBJDIR)/, $(LIBDIR)/, and $(BINDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS) $(BINARIES)
