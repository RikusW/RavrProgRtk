
FLAGS = -DXLIB -Wall -g -I../
#-fpermissive 
#-Wl,-rpath,/home/rikus/Programming/Rtk
#LD_LIBRARY_PATH

all: RavrProgRtk

clean:
	rm -fv *.o
	rm -fv *~
	rm -fv RavrProgRtk RavrProgRtk_sisl.cpp cfg

#=========================================================#

cfg: cfg.cpp ../Rtk-gui/libRtk-gui.so
	g++ $(FLAGS) -o cfg cfg.cpp -lRtk-gui

#=========================================================#

RavrProgRtk_sisl.cpp: RavrProgRtk.h ../Rtk-gui/parse
	../Rtk-gui/parse RavrProgRtk.h > RavrProgRtk_sisl.cpp

RavrProgRtk: RavrProgRtk.h RavrProgRtk.cpp RavrProgRtk_sisl.cpp ../Rtk-gui/libRtk-gui.so ../RavrProg/libRavrProg.so
	g++ -o RavrProgRtk RavrProgRtk.cpp RavrProgRtk_sisl.cpp -lRtk-base -lRtk-gui -lRavrProg $(FLAGS)

#=========================================================#


