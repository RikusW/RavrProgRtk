
CXXFLAGS += -DXLIB -Wall -g -lRtk-base -lRtk-gui -I../

all: RavrProgRtk

clean:
	rm -fv *.o
	rm -fv *~
	rm -fv RavrProgRtk RavrProgRtk_sisl.cpp cfg

#=========================================================#
#Keep Rtk-parse output
.PRECIOUS: %_sisl.cpp

%_sisl.cpp: %.h
	../Rtk-gui/Rtk-parse $< > $@

#=========================================================#

cfg: cfg.cpp
	g++ -o $@ $^ $(CXXFLAGS)

#=========================================================#

RavrProgRtk: RavrProgRtk.o RavrProgRtk_sisl.o
	g++ -o $@ $^ $(CXXFLAGS) -lRavrProg

#=========================================================#


