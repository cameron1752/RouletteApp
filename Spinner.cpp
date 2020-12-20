/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spinner.cpp
 * Author: Cammy
 * 
 * Created on February 1, 2020, 1:02 PM
 */

#include "Spinner.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

Spinner::Spinner() {

}

void Spinner::initialize(){
    srand(time(NULL));
}

Spinner::spinInfo Spinner::spin(){
    
    spinInfo SI;
    
    SI.theNumber = rand() % 38;
    
    SI.color = getColor(SI.theNumber);
    
    SI.EON = getSide(SI.theNumber);
    
    SI.MPN = getType(SI.theNumber);
    
    //cout << "number: " << SI.theNumber << " is " << SI.color << " and " << SI.EON << " and " << SI.MPN <<endl;
    
    return SI;
}

// function takes input number from roll and determines the color based on values given in requirements
int Spinner::getColor(int number){
    
    if ((number > 0 && number < 11) || (number > 18 && number < 29)){
        // odd numbers are red even numbers are black
        if (number % 2 == 0){
            return black;
        } else {
            return red;
        }
    } else if ((number > 10 && number < 19) || (number > 28 && number < 37)){
        // odd numbers are black even numbers are red
        if (number % 2 == 0){
            return red;
        } else {
            return black;
        }
    } else{
        // should only be numbers 37 (00) and 0 but they are green
            return green;
        
    }
    
} // end getColor

// function takes input number from roll and determines if even odd or neither type using mod 2
int Spinner::getSide(int number){
    
    if (number == 0 || number == 37){
        return neither;
    } else if (number % 2 == 0){
        return even;
    } else {
        return odd;
    }
} // end get side

// function takes input number from roll and determines type of number based on requriements
int Spinner::getType(int number){
    
    // if Manque (1-18)
    if (number > 0 && number < 19){
        return Manque;
    // if Passe (19-36)
    } else if (number > 18 && number < 37){
        return Passe;
    // if 0 or 00 (37[or anything else]) 
    } else{
        return none;
    }
}