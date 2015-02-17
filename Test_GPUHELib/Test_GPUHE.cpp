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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    long m=0, p=257, r=1, L=16, c=3, w=64, d=0, security=128;
    ZZX G;
    
    m = FindM(security, L, c, p, d, 0, 0);
    
    FHEcontext context(m, p, r);
    buildModChain(context, L, c);
    FHESecKey secretKey(context);
    const FHEPubKey& publicKey = secretKey;
    
    G = context.alMod.getFactorsOverZZ()[0];
    
    secretKey.GenSecKey(w);
    
    addSome1DMatrices(secretKey);
    
    cout << "Generated key" << endl;
    
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
    
    Ctxt ctSum = ct1;
    Ctxt ctProd = ct1;
    
    setTimersOn();
    ctSum += ct2;
    ctProd *= ct2;
    
    vector<long> res;
    ea.decrypt(ctSum, secretKey, res);

    cout << "All computations are modulo " << p << "." << endl;
    for(int i = 0; i < res.size(); i ++) {
        cout << v1[i] << " + " << v2[i] << " = " << res[i] << endl;
    }

    ea.decrypt(ctProd, secretKey, res);
    //for(int i = 0; i < res.size(); i ++) {
    //    cout << v1[i] << " * " << v2[i] << " = " << res[i] << endl;
    //}

    return 0;
}

