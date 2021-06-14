CXXFLAGS += -std=c++03 -O2 -s -Wall
CXXFLAGS += -D__USE_MINGW_ANSI_STDIO=1
CXXFLAGS += -I..
CXX      ?=  g++
#CXX       =  arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-g++



# list of tests for build
TESTS  = crc_test


ifeq ($(OS),Windows_NT)
    BIN_SUFFIX  = .exe
    BIN_TESTS   = $(addsuffix $(BIN_SUFFIX), $(TESTS))
else
    BIN_TESTS   = $(TESTS)
endif




.PHONY: all
all: $(BIN_TESTS)
	@for test in $(BIN_TESTS) ; do  \
        ./$$test ; \
    done



%$(BIN_SUFFIX): %.cpp ../ucrc_t.cpp ../ucrc_t.h
	$(CXX) $< ../ucrc_t.cpp -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"



.PHONY: asm
asm:
	$(CXX)  crc_test.cpp  $(CXXFLAGS) -S
	$(CXX)  ../ucrc_t.cpp $(CXXFLAGS) -S



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f *.s
	-@rm -f $(BIN_TESTS)




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   all    -  clean and build all tests"
	@echo "   asm    -  get ASM listing"
	@echo "   clean  -  remove all binary files"
	@echo "   help   -  This help"
