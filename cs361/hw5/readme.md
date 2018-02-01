# Homework 5 - pThreads and Sync

CS361 Computer Systems, Fall 2017

## Description

For this assignment, you are to write a simulation in which a number of threads access a group of shared buffers for both reading and writing purposes. Initially this will be done without the benefit of synchronization tools ( semaphores ) to illustrate the problems of race conditions, and then with the synchronization tools to solve the problems. ( A separate mutex will be used to coordinate writing to the screen. ) Optional enhancements allow for the use of pipes, message queues, and shared memory.

## Meta

Author: Gregory N. Schmit (gschmi4@uic.edu)

NetID: gschmi4

ACCC Account: temp150

Date: 5 December 2017

## Usage

    $ gcc raceTest.c -o raceTest
    $ ./raceTest nBuffers nWorkers [ sleepMin sleepMax ] [ -lock | -nolock ]
