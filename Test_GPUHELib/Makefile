CC =		g++
LDFLAGS = 	-g -O

#master
MASTER_FHE_LIB =	/home/ethan/Thesis/GPUHELib/HElib-master/src/fhe.a
MASTER_SRC =		/home/ethan/Thesis/GPUHELib/HElib-master/src
MASTER_LIBS = 		-L/usr/local/lib/ -lntl -lgmp	

#modified
MODIFIED_FHE_LIB = 	/home/ethan/Thesis/GPUHELib/HElib-modified/fhe.a
MODIFIED_SRC = 		/home/ethan/Thesis/GPUHELib/HElib-modified
MODIFIED_LIBS = 	-L/usr/local/lib/ -lntl -lgmp -L/usr/local/cuda/lib -lcuda -L/usr/local/cuda/lib64 -lcudart

all:
	make master
	make modified

master:	Test_GPUHE.cpp
	$(CC) $(LDFLAGS) Test_GPUHE.cpp $(MASTER_FHE_LIB) -I$(MASTER_SRC) -o Test_GPUHE_HELib_master $(MASTER_LIBS)

modified:	Test_GPUHE.cpp
	$(CC) $(LDFLAGS) Test_GPUHE.cpp $(MODIFIED_FHE_LIB) -I$(MODIFIED_SRC) -o Test_GPUHE_HELib_modified $(MODIFIED_LIBS)

clean:
	rm Test_GPUHE_HELib_master Test_GPUHE_HELib_modified
