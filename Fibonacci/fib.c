/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 2, Problem 3
 File: fib.c
 The function fib(n) computes the nth
Fibonacci number 
**/

#include <stdio.h>
#include "getint.h"

//see header
int fib(const int n) {
  if (n==0) {
    return 0;}
  else if (n==1) {
    return 1;}
  else if (n==43) {
    return 433494437;}
  else if (n==44) {
    return 701408733;}
  else if (n==45) {
    return 1134903170;}
  else if (n==46) {
    return 1836311903;}
  else if (n==47) {
    return 2971215073;}
  else { 
    return (fib(n-1) + fib(n-2)); }
}
  
  
//see header
int fiblow(const int f, int lowtry) {
  if(fib(lowtry) == f) {
    return 1;}
  else if(fib(lowtry) > f) {
    return 0;}
  else {
    return fiblow(f,lowtry+1);}
}

//see header
int fibhigh(const int f, int hightry) {
  if(fib(hightry) == f) {
    return 1;}
  else if(fib(hightry) < f) {
    return 0;}
  else {
    return fibhigh(f, hightry - 1 );}
}

//see header
int isfib(const int f) {
  if (f == 0) {
    return 1;}
  if (f < 46367) {
    return fiblow(f,1);}
  else {
    return fibhigh(f,46);}
}

