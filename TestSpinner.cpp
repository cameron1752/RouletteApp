/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSpinner.cpp
 * Author: Cammy
 * 
 * Created on February 1, 2020, 2:55 PM
 */

#include "TestSpinner.h"
#include "Spinner.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include<sstream>

using namespace std;
// expected distribution
const float expected = {1/.38};
// testData struct to hold values for test analysis
TestSpinner::testData testResults;
// number of test spins [good test is 1,000,000]
int spins = 1000000;

TestSpinner::TestSpinner() {
    // declare spinner object
    Spinner sp;
    // initialize random seed
    sp.initialize();
    // declare new spininfo struct
    Spinner::spinInfo testSpin;
    
    // remove previous tests text file to get fresh results
    remove("testData.txt");
    
    // for number of tests spin that roulette table
    for (int test = 0; test < spins; ++test){
        // to capture first 100 for analysis
        if (test < 100){
            // assign our spinInfo object to the result of the spin
            testSpin = sp.spin();
            // save first 100 and tick the counter for that number
            testResults.firstCouple[test] = testSpin.theNumber;
            // increase the numbers array
            testResults.numbers[testSpin.theNumber]++;
            // increase the colors array
            testResults.colors[testSpin.color]++;
            // increase the side array
            testResults.side[testSpin.EON]++;
            // increase the type array
            testResults.type[testSpin.MPN]++;
        } else {
            // assign our spinInfo object to the result of the spin
            testSpin = sp.spin();
            // increase the counter for that number
            testResults.numbers[testSpin.theNumber]++;
            // increase the colors array
            testResults.colors[testSpin.color]++;
            // increase the side array
            testResults.side[testSpin.EON]++;
            // increase the type array
            testResults.type[testSpin.MPN]++;
        } // end random number test if
        
    } // end spins for loop
    
    // pass / fail validation
    if (randomTest() && numbDist() && colorDist() && sideDist() && typeDist() ){
        // if all true (and pass)
        cout << " " << endl;
        cout << "Overall Test Result: Pass" << endl;
        writeData("Overall Test Result: Pass");
    } else {
        // else 
        cout << " " << endl;
        cout << "Overall Test Result: Fail" << endl;
        writeData("Overall Test Result: Fail");
    } // end pass / fail validation
}

// writes test data to text document
void TestSpinner::writeData(string stuff){
    ofstream outputFile;
    outputFile.open("testData.txt",std::ofstream::app);
    outputFile << stuff;
    outputFile.close();
}

// calculates the actual distribution of each number by dividing occurences by number of spins
bool TestSpinner::numbDist(){
    // stringstream declaration
    stringstream stuff;
    // boolean value to validate pass/fail of test
    bool val = true;
    
    // for loop iterates over the real number distribution and calculates the actual distribution as percentage
    for (int i = 0; i < 38; i++){
        // cast int number dist to float value
        float numba = testResults.numbers[i] * 1.0;
        // calculate percentage
        testResults.actual[i] = (numba / (float)spins  * 100.0);
        
        // determines if each number pass/fails on tolerance of .3 %
        if (passFail(testResults.actual[i], i) == false) {
            // if passFail returns false set validation flag to false
            val = false;
        } // end validation if
    } // end for iteration

    // print to terminal
    cout << "Number of spins: " << spins << endl;
    cout << "Number generation tests: " << endl;
    cout << "Test" << setw(15) << "Occurrences" << setw(8) << "Actual" << setw(10) << "Expected" << setw(15) << "Pass/Fail" << endl;
    
    // load string stream to print to .txt file
    stuff << "Number of spins: " << (spins) << " \n";
    // write to .txt file
    writeData(stuff.str());
    // clear string stream
    stuff.str(std::string());
    // load string stream to print to .txt file
    stuff << "Number generation tests: " << " \n";
    // write to .txt file
    writeData(stuff.str());
    // clear string stream
    stuff.str(std::string());
    // load string stream to print to .txt file
    stuff << "Test" << "\t" << "Occurrences" << "\t" << "Actual" << "\t" << "Expected" << "\t" << "Pass/Fail" << " \n";
    // write to .txt file
    writeData(stuff.str());
    // clear string stream
    stuff.str(std::string());
    
    // for loop iterates over number distribution tests and prints to console and .txt file
    for (int i = 0; i < 38; ++i){
        // print to terminal
        cout << i << setw(15) << testResults.numbers[i] << setw(13) << testResults.actual[i] << setw(9) << expected << setw(10) << testResults.passOrFail[i] << endl;
        // load string stream to print to .txt file
        stuff << i << "\t" << testResults.numbers[i] << "\t" << "\t" << testResults.actual[i] << "\t" << expected << "\t" << "\t" << testResults.passOrFail[i] << " \n";
        // write to .txt file
        writeData(stuff.str());
        // clear string stream
        stuff.str(std::string());
    } // end iteration loop
    
    return val;
} // end numbDist

// if the actual distribution is between the tolerance level
bool TestSpinner::passFail(float actual, int i){
    // if the actual percentage is +- .3 of the expected it passes
    if (actual < (expected + .3) && actual > (expected - .3)){
        // sets the index of the number for the pass/fail array to pass
        testResults.passOrFail[i] = "Pass";
        return true;
    } else {
        // sets the index of the number for the pass/fail array to fail
        testResults.passOrFail[i] = "Fail";
        return false;
    } // end if else
} // end passFail

// random test function
bool TestSpinner::randomTest(){
    // boolean value for pass / fail generation
    bool val = true;
    // first 10 numbers generate 10 random numbers after re-seeding it
    // generate 10 numbers 10 times with 10 unique seeds
    struct randomTest{
        int currentTen[10];
        int nextTen[10];
    };
    // struct for test Data
    randomTest randomInfo;
 
    for (int k = 0; k < 5; ++k){ 
        // declare spinner object
        Spinner sp;
        // initialize random seed
        sp.initialize();
    
       // for loop for loading first 10 values
        for (int i = 0; i < 10; ++i){
            randomInfo.currentTen[i] = sp.spin().theNumber;
//            cout << testData.currentTen[i] << endl;
        }
       
        cout << " " << endl;
       
        // loop over the array and load next 10 values
        for (int i = 0; i < 10; ++i){
            randomInfo.nextTen[i] = sp.spin().theNumber;
//            cout << testData.nextTen[i] << endl;
        }
        
        // compare currentTen i and i+1 and nextTen i and i+1
        for (int i = 0; i < 10; ++i){
            // cout << testData.currentTen[i] << " " << testData.nextTen[i] << endl;
            if (randomInfo.currentTen[i] == randomInfo.nextTen[i] && randomInfo.currentTen[i+1] == randomInfo.nextTen[i+1] && randomInfo.currentTen[i+2] == randomInfo.nextTen[i+2]){
                return val = false;
                writeData("Random generation test: Fail");
            }
        }
    }
    
    if (val == true){
        writeData("Random generation test: Pass \n");
    }
    
    return val;
} // end randomTest()

// function to calculate color distribution
bool TestSpinner::colorDist(){
    // string stream to hold data to write
    stringstream stuff;
    // boolean variable for validation of tests
    bool val = true;
    // column names and possible colors
    string colName[3] = {"red  ", "black", "green"};
    // expected percentage of colors
    float expColor[3] = {18/.38, 18/.38, 2/.38};
    
    // for loop calculates the percentage of occurence of each color divides distribution by number of spins
    for (int i = 0; i < 3; i++){
        // percentage calculation
        float actual = ((float)testResults.colors[i] / (float)spins) * 100.0;
        // string to write to console and text file
        string passFail;
        
        // validation test for actual percentage to be w/in +- .3 percent of expected distribution
        if (actual < (expColor[i] + .3) && actual > (expColor[i] - .3)){
            passFail = "Pass";
        } else {
            passFail = "Fail";
            val = false;
        }
        
        // write to console
        cout << colName[i] << setw(13) << testResults.colors[i] << setw(12) << actual << setw(9) << expColor[i] << setw(10) << passFail << endl;
        // write to text file
        stuff << colName[i] << "\t" << testResults.colors[i] << "\t" << "\t" << actual << "\t" << expColor[i] << "\t" << "\t" << passFail << " \n";
        writeData(stuff.str());
        // clear string stream
        stuff.str(std::string());
    } // end calculation for loop
    return val;
} // end colorDist

// function determines the distribution of the number values for even odd or not
bool TestSpinner::sideDist(){
    // string stream to hold data to write
    stringstream stuff;
    // boolean variable for validation of tests
    bool val = true;
    // column names and possible outcomes
    string colName[3] = {"even","odd ","not "};
    // expected distribution
    float expDist[3] = {18/.38, 18/.38, 2/.38};
    
    // for loop calculates the actual percentage distrubtion for even odd or not
    for (int i = 0; i < 3; i++){
        // calculation of side distribution divided by number of spins
        float actual = ((float)testResults.side[i] / (float)spins) * 100.0;
        // variable to write to console and string w/
        string passFail;
        
        // validation of data check if within +- .3 of expected we're good
        if (actual < (expDist[i] + .3) && actual > (expDist[i] - .3)){
            passFail = "Pass";
        } else {
            passFail = "Fail";
            val = false;
        }
        
        // write to console
        cout << colName[i] << setw(14) << testResults.colors[i] << setw(12) << actual << setw(9) << expDist[i] << setw(10) << passFail << endl;
        
        // load our string stream
        stuff << colName[i] << "\t" << testResults.colors[i] << "\t" << "\t" << actual << "\t" << expDist[i] << "\t" << "\t" << passFail << " \n";
        // write to text file
        writeData(stuff.str());
        // clear string stream
        stuff.str(std::string());
    } // end calculation for loop
    return val;
} // end sideDist

// function determines distribution of manque passe or neither numbers
bool TestSpinner::typeDist(){
    // string stream to hold data to write
    stringstream stuff;
    // boolean variable for validation of tests
    bool val = true;
    // column names and possible outcomes
    string colName[3] = {"Manque ", "Passe  ", "Neither"};
    // expected distribution
    float expDist[3] = {18/.38, 18/.38, 2/.38};
    
    // for loop to calculate distribution percentages
    for (int i = 0; i < 3; i++){
        // type distribution divided by total number of spins
        float actual = ((float)testResults.type[i] / (float)spins) * 100.0;
        // variable to write to console w/
        string passFail;
        
        // determines our data integrity, w/in +- .3 of our expected value is good to go
        if (actual < (expDist[i] + .3) && actual > (expDist[i] - .3)){
            passFail = "Pass";
        } else {
            passFail = "Fail";
            val = false;
        }
        
        // write to console
        cout << colName[i] << setw(11) << testResults.colors[i] << setw(12) << actual << setw(9) << expDist[i] << setw(10) << passFail << endl;
        
        // load string stream for text file
        stuff << colName[i] << "\t" << testResults.colors[i] << "\t" << "\t" << actual << "\t" << expDist[i] << "\t" << "\t" << passFail << " \n";
        // write data to text file
        writeData(stuff.str());
        // clear string stream 
        stuff.str(std::string());
    } // end for loop
    return val;
} // end typeDist