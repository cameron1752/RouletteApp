/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSpinner.h
 * Author: Cammy
 *
 * Created on February 1, 2020, 2:55 PM
 */

#ifndef TESTSPINNER_H
#define TESTSPINNER_H
#include <string>
#include <iostream>
#include <sstream>

class TestSpinner {
public:
    TestSpinner();
    struct testData{
        int colors[3];
        int side[3];
        int type[3];
        int firstCouple[100];
        int numbers[38];
        float actual[38];
        std::string passOrFail[38];
    };
    
private:
    bool numbDist();
    bool passFail(float actual, int i);
    bool randomTest();
    bool colorDist();
    bool sideDist();
    bool typeDist();
    void writeData(std::string stuff);
};

#endif /* TESTSPINNER_H */

