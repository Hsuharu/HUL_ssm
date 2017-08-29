CPPFLAGS += $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --glibs)
EXTRALIBS += $(ROOTLIBS)

all:decode4

decode4: decode4.o
	$(CXX) -o decode4 decode4.o $(EXTRALIBS)

decode4.o: decode4.C
	$(CXX) -c decode4.C $(CPPFLAGS)
