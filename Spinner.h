/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spinner.h
 * Author: Cammy
 *
 * Created on February 1, 2020, 1:02 PM
 */

#ifndef SPINNER_H
#define SPINNER_H

class Spinner {
public:
    Spinner();
    void initialize();
    
    struct spinInfo{
        int theNumber;
        int color; // 0 - red 1 - black 2 - green
        int EON; // Even, odd, or not 0 - even 1 - odd 2 - not
        int MPN; // Manque (1-18) Passe (19-36), or neither 0 - manque 1 - passe 2 - neither
    };
    spinInfo spin();
    
    
private:
    
    int getColor(int number);
    int getSide(int number);
    int getType(int number);
    
    enum Color{
        red, black, green
    };
    enum Side{
        even, odd, neither
    };
    enum Type{
        Manque, Passe, none
    };
};

#endif /* SPINNER_H */

