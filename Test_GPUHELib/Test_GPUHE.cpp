/* 
 * File:   Test_GPUHE.cpp
 * Author: ethan
 *
 * Created on October 15, 2014, 11:20 AM
 */

#include <cstdlib>
#include "FHE.h"
#include "EncryptedArray.h"
#include "timing.h"
#include <NTL/lzz_pXFactoring.h>
#include <NTL/ZZX.h>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <string>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	if(argc != 2) {
		cout << "Usage: Test_GPUHE_* <choosen m>" << endl;
		exit(1);
	}
    
    long m=0, p=65537, r=1, L=16, c=3, w=64, d=0, security=128;
    ZZX G;
    
    m = FindM(security, L, c, p, d, 0, atoi(argv[1]), true);

	//cout << "Creating context" << endl;
    FHEcontext context(m, p, r);

	//cout << "Building Mod Chain" << endl;
    buildModChain(context, L, c);

	//cout << "Creating secret key" << endl;
    FHESecKey secretKey(context);
    const FHEPubKey& publicKey = secretKey;
    
	//cout << "Getting factors" << endl;
    G = context.alMod.getFactorsOverZZ()[0];
    
	//cout << "Generating Secret Key" << endl;
    secretKey.GenSecKey(w);
    
	//cout << "Adding Some 1D Matricies" << endl;
    addSome1DMatrices(secretKey);
    
    //cout << "Generated key" << endl;
    
    EncryptedArray ea(context, G);
    
    long nslots = ea.size();

	cout << "nslots: " << nslots << endl;
    
    vector<long> v1;
    for(int i = 0 ; i < nslots; i++) {
        v1.push_back(i);
    }
    Ctxt ct1(publicKey);
    ea.encrypt(ct1, publicKey, v1);

    vector<long> v2;
    Ctxt ct2(publicKey);
    for(int i = 0 ; i < nslots; i++) {
        v2.push_back(i);
    }
    ea.encrypt(ct2, publicKey, v2);
    
    //ADDITION
    setTimersOn();
    FHE_NTIMER_START(AdditionCircuit);
    
    Ctxt ctSum = ct1;
    ctSum += ct2;
    
    vector<long> res;
    ea.decrypt(ctSum, secretKey, res);

    for(int i = 0; i < res.size(); i ++) {
		if(res[i] == (v1[i] + v2[i]) % p) {
        		//cout << v1[i] << " + " << v2[i] << " = " << res[i] << endl;
		}
		else {
			cout << "Error at index " << i << ", value " << res[i] << " != " << (v1[i] + v2[i]) % p << endl;
		} 
    }
    
    FHE_NTIMER_STOP(AdditionCircuit);
	
	//SUBTRACTION
    FHE_NTIMER_START(SubtractionCircuit);
    
    Ctxt ctSub = ct1;
    ctSub -= ct2;
    
    ea.decrypt(ctSub, secretKey, res);

    for(int i = 0; i < res.size(); i ++) {
		if(res[i] == (v1[i] - v2[i]) % p) {
        		//cout << v1[i] << " + " << v2[i] << " = " << res[i] << endl;
		}
		else {
			cout << "Error at index " << i << ", value " << res[i] << " != " << (v1[i] + v2[i]) % p << endl;
		} 
    }
    
    FHE_NTIMER_STOP(SubtractionCircuit);
	
	//MULTIPLICATION
	FHE_NTIMER_START(MultiplicationCircuit);
    
    Ctxt ctProd = ct1;
    ctProd *= ct2;
    
    ea.decrypt(ctProd, secretKey, res);

    for(int i = 0; i < res.size(); i ++) {
		if(res[i] == (v1[i] * v2[i]) % p) {
        		//cout << v1[i] << " + " << v2[i] << " = " << res[i] << endl;
		}
		else {
			cout << "Error at index " << i << ", value " << res[i] << " != " << (v1[i] + v2[i]) % p << endl;
		} 
    }
    
   FHE_NTIMER_STOP(MultiplicationCircuit);
    
     cerr << endl;
	printAllTimers();
	cerr << endl;

    return 0;
}

