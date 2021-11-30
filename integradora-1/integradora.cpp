#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include "promethean.h"

/**
 * @file integradora.cpp
 *
 * @brief Este archivo resuelve la actividad integradora 1 de TC2038.1
 *
 * @author Jorge Flores A01769059
 * @author Ruben Ruiz A01366792
 * @author Jemuel Flores A01367182
 * @author V. de la Cueva
 *
 */

int main() {

    /***** 0. Get file contents *****/
    std::string mcode1_content;
    std::string mcode2_content;
    std::string mcode3_content;
    std::string transmission1_content;
    std::string transmission2_content;
    
    mcode1_content = getFileContent("mcode1.txt");
    mcode2_content = getFileContent("mcode2.txt");
    mcode3_content = getFileContent("mcode3.txt");
    transmission1_content = getFileContent("transmission1.txt");
    transmission2_content = getFileContent("transmission2.txt");

    /***** 1. Look for mcodeN patterns in transmissionN texts *****/
    std::cout << "Parte 1 (true || false) (Posicion(es) iniciales donde se encuentra) (INDEX-1)" << '\n';
    std::vector<std::string> result_mcode1_in_transmission1;
    std::vector<std::string> result_mcode2_in_transmission1;
    std::vector<std::string> result_mcode3_in_transmission1;
    std::vector<std::string> result_mcode1_in_transmission2;
    std::vector<std::string> result_mcode2_in_transmission2;
    std::vector<std::string> result_mcode3_in_transmission2;

    findPattern(mcode1_content, transmission1_content, result_mcode1_in_transmission1);
    findPattern(mcode2_content, transmission1_content, result_mcode2_in_transmission1);
    findPattern(mcode3_content, transmission1_content, result_mcode3_in_transmission1);
    findPattern(mcode1_content, transmission2_content, result_mcode1_in_transmission2);
    findPattern(mcode2_content, transmission2_content, result_mcode2_in_transmission2);
    findPattern(mcode3_content, transmission2_content, result_mcode3_in_transmission2);

    /***** 2. Look for largest palindrome in transmissionN texts *****/
    std::cout << "Parte 2 (Posicion inicial, Longitud) (INDEX-1)" << '\n';
    std::pair<int,int> largest_palindrome1 = MANACHER(transmission1_content);
    std::pair<int,int> largest_palindrome2 = MANACHER(transmission2_content);

    std::cout << largest_palindrome1.first << " " << largest_palindrome1.second << '\n';
    std::cout << largest_palindrome2.first << " " << largest_palindrome2.second << '\n';

    /***** 3. Look for largest common substring in transmission texts *****/
    std::cout << "Parte 3 (Posicion inicial, Posicion Final) (INDEX-1)" << '\n';
    std::pair<int, int> location_lcs = LCS(transmission1_content, transmission2_content);
    std::cout << location_lcs.first << " " << location_lcs.second;

    /***** COMPLEJIDAD TOTAL = O(N) + O(N) + O(N) + O(N) + O(N) + O(N) + O(N) + O(N) + O(N*M) *****/
    /***** COMPLEJIDAD TOTAL = O(N*M) *****/

    return 0;

}