CC =		g++
LDFLAGS = 	-g -O

#master
MASTER_FHE_LIB =	../HElib-master/src/fhe.a
MASTER_SRC =		../../ntl-8.1.2/local/include -I../HElib-master/src
MASTER_LIBS = 		-L/usr/local/lib/ -L../../ntl-8.1.2/local/lib/ -L../../gmp-6.0.0/local/lib/ -lntl -lgmp	-L/usr/local/cuda/lib -lcuda -L/usr/local/cuda/lib64 -lcudart

#modified
MODIFIED_FHE_LIB = 	../HElib-modified/src/fhe.a
MODIFIED_SRC = 		../../ntl-8.1.2/local/include -I../HElib-modified/src
MODIFIED_LIBS = 	-L/usr/local/lib/ -L../../ntl-8.1.2/local/lib/ -L../../gmp-6.0.0/local/lib/ -lntl -lgmp -L/usr/local/cuda/lib -lcuda -L/usr/local/cuda/lib64 -lcudart

all:
	make master
	make modified

master:		Test_GPUHE.cpp
	$(CC) $(LDFLAGS) Test_GPUHE.cpp $(MASTER_FHE_LIB) -I$(MASTER_SRC) -o Test_GPUHE_HELib_master $(MASTER_LIBS)

modified:	Test_GPUHE.cpp
	$(CC) $(LDFLAGS) Test_GPUHE.cpp $(MODIFIED_FHE_LIB) -I$(MODIFIED_SRC) -o Test_GPUHE_HELib_modified $(MODIFIED_LIBS)

clean:
	rm Test_GPUHE_HELib_master Test_GPUHE_HELib_modified
