/*
 * Author: Gregory N. Schmit (gschmi4@uic.edu)
 */

#include "stdio.h"

#define MY_N 12

char file2Hello[] = "Hello", *file2World = "World";
int file2Global, file2GlobalArray[MY_N], *file2GlobalPtr, file2InitGlobal = MY_N, file2InitGlobalArray[MY_N] = {MY_N}, *file2InitGlobalPtr = &file2InitGlobal;
static float file2StaticGlobal, file2StaticGlobalArray[MY_N], *file2StaticGlobalPtr, file2StaticInitGlobal = MY_N, file2StaticInitGlobalArray[MY_N] = {MY_N}, *file2StaticInitGlobalPtr = &file2StaticInitGlobal;

extern char file1Hello[];
extern char *file1World;
extern int file1Global;
extern int file1GlobalArray[];
extern int *file1GlobalPtr;
extern int file1InitGlobal;
extern int file1InitGlobalArray[];
extern int *file1InitGlobalPtr;

static double func3(const int func3_arg1, int *func3_arg2);

double func2(int func2_arg1, int *func2_arg2)
{
  char func2Local, func2LocalArray[MY_N], *func2LocalPtr, func2InitLocal = MY_N, func2InitLocalArray[MY_N] = {MY_N}, *func2InitLocalPtr = &func2InitLocal;
  static int func2StaticLocal, func2StaticLocalArray[MY_N], *func2StaticLocalPtr, func2StaticInitLocal = MY_N, func2StaticInitLocalArray[MY_N] = {MY_N}, *func2StaticInitLocalPtr = &func2StaticInitLocal;

  float total = func3(func2_arg1, func2_arg2);

  // init
  func2Local = MY_N;
  func2LocalPtr = &func2Local;
  func2StaticLocal = MY_N;
  func2StaticLocalPtr = &func2StaticLocal;
  int i;
  for (i=0; i<MY_N; i++) {
    func2LocalArray[i] = MY_N;
    func2InitLocalArray[i] = 0;
    func2StaticLocalArray[i] = MY_N;
    func2StaticInitLocalArray[i] = 0;
  }
  func2InitLocalArray[0] = MY_N;
  func2StaticInitLocalArray[0] = MY_N;

  total += \
    func2_arg1 + \
    *func2_arg2 + \
    file2Global + \
    *file2GlobalPtr + \
    file2InitGlobal + \
    *file2InitGlobalPtr + \
    file2StaticGlobal + \
    *file2StaticGlobalPtr + \
    file2StaticInitGlobal + \
    *file2StaticInitGlobalPtr + \
    file1Global + \
    *file1GlobalPtr + \
    file1InitGlobal + \
    *file1InitGlobalPtr + \
    func2Local + \
    *func2LocalPtr + \
    func2InitLocal + \
    *func2InitLocalPtr + \
    func2StaticLocal + \
    *func2StaticLocalPtr + \
    func2StaticInitLocal + \
    *func2StaticInitLocalPtr;
  for (i=0; i<MY_N; i++) {
    total += \
      file2GlobalArray[i] + \
      file2InitGlobalArray[i] + \
      file2StaticGlobalArray[i] + \
      file2StaticInitGlobalArray[i] + \
      file1GlobalArray[i] + \
      file1InitGlobalArray[i] + \
      func2LocalArray[i] + \
      func2InitLocalArray[i] + \
      func2StaticLocalArray[i] + \
      func2StaticInitLocalArray[i];
  }
  printf("%s %s from func2\n", file2Hello, file2World);
  printf("func2 total: %f\n", total);

  return total;
}

static double func3(const int func3_arg1, int *func3_arg2)
{
  char func3Local, func3LocalArray[MY_N], *func3LocalPtr, func3InitLocal = MY_N, func3InitLocalArray[MY_N] = {MY_N}, *func3InitLocalPtr = &func3InitLocal;
  static int func3StaticLocal, func3StaticLocalArray[MY_N], *func3StaticLocalPtr, func3StaticInitLocal = MY_N, func3StaticInitLocalArray[MY_N] = {MY_N}, *func3StaticInitLocalPtr = &func3StaticInitLocal;

  // init
  //file2Global = MY_N;
  //file2GlobalPtr = &file2Global;
  file2StaticGlobal = MY_N;
  file2StaticGlobalPtr = &file2StaticGlobal;
  //file1Global = MY_N;
  //file1GlobalPtr = &file1Global;
  func3Local = MY_N;
  func3LocalPtr = &func3Local;
  func3StaticLocal = MY_N;
  func3StaticLocalPtr = &func3StaticLocal;
  int i;
  for (i=0; i<MY_N; i++) {
    //file2GlobalArray[i] = MY_N;
    //file2InitGlobalArray[i] = 0;
    file2StaticGlobalArray[i] = MY_N;
    file2StaticInitGlobalArray[i] = 0;
    //file1GlobalArray[i] = MY_N;
    //file1InitGlobalArray[i] = 0;
    func3LocalArray[i] = MY_N;
    func3InitLocalArray[i] = 0;
    func3StaticLocalArray[i] = MY_N;
    func3StaticInitLocalArray[i] = 0;
  }
  //file2InitGlobalArray[0] = MY_N;
  file2StaticInitGlobalArray[0] = MY_N;
  //file1InitGlobalArray[0] = MY_N;
  func3InitLocalArray[0] = MY_N;
  func3StaticInitLocalArray[0] = MY_N;

  // total
  float total = \
    func3_arg1 + \
    *func3_arg2 + \
    file2Global + \
    *file2GlobalPtr + \
    file2InitGlobal + \
    *file2InitGlobalPtr + \
    file2StaticGlobal + \
    *file2StaticGlobalPtr + \
    file2StaticInitGlobal + \
    *file2StaticInitGlobalPtr + \
    file1Global + \
    *file1GlobalPtr + \
    file1InitGlobal + \
    *file1InitGlobalPtr + \
    func3Local + \
    *func3LocalPtr + \
    func3InitLocal + \
    *func3InitLocalPtr + \
    func3StaticLocal + \
    *func3StaticLocalPtr + \
    func3StaticInitLocal + \
    *func3StaticInitLocalPtr;
  for (i=0; i<MY_N; i++) {
    total += \
      file2GlobalArray[i] + \
      file2InitGlobalArray[i] + \
      file2StaticGlobalArray[i] + \
      file2StaticInitGlobalArray[i] + \
      file1GlobalArray[i] + \
      file1InitGlobalArray[i] + \
      func3LocalArray[i] + \
      func3InitLocalArray[i] + \
      func3StaticLocalArray[i] + \
      func3StaticInitLocalArray[i];
  }
  printf("%s %s from func3\n", file2Hello, file2World);
  printf("func3 total: %f\n", total);

  return total;
}
