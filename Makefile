
FLAGS = -DXLIB -Wall -g -fpermissive 
#-Wl,-rpath,/home/rikus/Programming/Rtk
#LD_LIBRARY_PATH

all: RavrProgRtk

clean:
	rm -fv *.o
	rm -fv *~
	rm -fv RavrProgRtk RavrProgRtk_sisl.cpp

#=========================================================#

cfg: cfg.cpp ../Rtk/libRtk.so
	g++ $(FLAGS) -o cfg cfg.cpp -lRtk -lX11

#=========================================================#

RavrProgRtk_sisl.cpp: RavrProgRtk.h ../Rtk/parse
	../Rtk/parse RavrProgRtk.h > RavrProgRtk_sisl.cpp

RavrProgRtk: RavrProgRtk.h RavrProgRtk.cpp RavrProgRtk_sisl.cpp ../Rtk/libRtk.so ../RavrProg/libRavrProg.so
	g++ -o RavrProgRtk RavrProgRtk.cpp RavrProgRtk_sisl.cpp -lRtk -lRavrProg $(FLAGS)

#=========================================================#


