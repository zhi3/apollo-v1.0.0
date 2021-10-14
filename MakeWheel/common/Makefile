CXX  = g++
CXXFLAGS += -fPIC

# Specify extensions of files to delete when cleaning
CLEANEXTS   = o so d

# Specify the source files, the target files, 
# and the install directory 
SOURCES     = apollo_app.cc
OUTPUTFILE  = libapollo_app.so
INSTALLDIR  = ../binaries

.PHONY: all
all: $(OUTPUTFILE)

# Build libgeorgeringo.so from george.o, ringo.o, 
# and georgeringo.o; subst is the search-and-replace 
# function demonstrated in Recipe 1.16
$(OUTPUTFILE): $(subst .cc,.o,$(SOURCES)) 
	$(CXX) $(CXXFLAGS) -shared -fPIC $(LDFLAGS) -o $@ $^

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean 
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm -rf example

# Generate dependencies of .cc files on .hpp files
include $(subst .cc,.d,$(SOURCES))

%.d: %.cc
	$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$


.PHONY: example
example:
	$(CXX) -o example example.cc -lapollo_app -L.

