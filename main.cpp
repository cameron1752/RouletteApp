/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Cammy
 *
 * Created on February 1, 2020, 12:59 PM
 */

#include <cstdlib>
#include <iostream>
#include "Spinner.h"
#include "TestSpinner.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Spinner sp;
    sp.initialize();
    int x = 10;
    for (int i = 0; i < x; ++i){
        sp.spin(); 
    }
    
    TestSpinner spT;
    
    return 0;
}

