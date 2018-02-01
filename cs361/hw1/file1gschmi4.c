/*
 * Author: Gregory N. Schmit (gschmi4@uic.edu)
 */

#include "stdio.h"

#define MY_N 12

char file1Hello[] = "Hello", *file1World = "World";
int file1Global, file1GlobalArray[MY_N], *file1GlobalPtr, file1InitGlobal = MY_N, file1InitGlobalArray[MY_N] = {MY_N}, *file1InitGlobalPtr = &file1InitGlobal;
static float file1StaticGlobal, file1StaticGlobalArray[MY_N], *file1StaticGlobalPtr, file1StaticInitGlobal = MY_N, file1StaticInitGlobalArray[MY_N] = {MY_N}, *file1StaticInitGlobalPtr = &file1StaticInitGlobal;

extern char file2Hello[];
extern char *file2World;
extern int file2Global;
extern int file2GlobalArray[];
extern int *file2GlobalPtr;
extern int file2InitGlobal;
extern int file2InitGlobalArray[];
extern int *file2InitGlobalPtr;

double func1(int func1_arg1, int *func1_arg2);
extern double func2(int func2_arg1, int *func2_arg2);

int main(int argc, char **argv)
{
  char mainLocal, mainLocalArray[MY_N], *mainLocalPtr, mainInitLocal = MY_N, mainInitLocalArray[MY_N] = {MY_N}, *mainInitLocalPtr = &mainInitLocal;
  static int mainStaticLocal, mainStaticLocalArray[MY_N], *mainStaticLocalPtr, mainStaticInitLocal = MY_N, mainStaticInitLocalArray[MY_N] = {MY_N}, *mainStaticInitLocalPtr = &mainStaticInitLocal;

  printf("Gregory N. Schmit - gschmi4\n");

  file1Global = MY_N;
  float total = func1(file1Global, (int*)&file1Global) + func2(file1Global, (int*)&file1Global);

  // init
  mainLocal = MY_N;
  mainLocalPtr = &mainLocal;
  mainStaticLocal = MY_N;
  mainStaticLocalPtr = &mainStaticLocal;
  int i;
  for (i=0; i<MY_N; i++) {
    mainLocalArray[i] = MY_N;
    mainInitLocalArray[i] = 0;
    mainStaticLocalArray[i] = MY_N;
    mainStaticInitLocalArray[i] = 0;
  }
  mainInitLocalArray[0] = MY_N;
  mainStaticInitLocalArray[0] = MY_N;

  total += \
    file1Global + \
    *file1GlobalPtr + \
    file1InitGlobal + \
    *file1InitGlobalPtr + \
    file1StaticGlobal + \
    *file1StaticGlobalPtr + \
    file1StaticInitGlobal + \
    *file1StaticInitGlobalPtr + \
    file2Global + \
    *file2GlobalPtr + \
    file2InitGlobal + \
    *file2InitGlobalPtr + \
    mainLocal + \
    *mainLocalPtr + \
    mainInitLocal + \
    *mainInitLocalPtr + \
    mainStaticLocal + \
    *mainStaticLocalPtr + \
    mainStaticInitLocal + \
    *mainStaticInitLocalPtr;
  for (i=0; i<MY_N; i++) {
    total += \
      file1GlobalArray[i] + \
      file1InitGlobalArray[i] + \
      file1StaticGlobalArray[i] + \
      file1StaticInitGlobalArray[i] + \
      file2GlobalArray[i] + \
      file2InitGlobalArray[i] + \
      mainLocalArray[i] + \
      mainInitLocalArray[i] + \
      mainStaticLocalArray[i] + \
      mainStaticInitLocalArray[i];
  }
  printf("%s %s from main\n", file1Hello, file1World);
  printf("main total: %f\n", total);

  return 0;
}

double func1(int func1_arg1, int *func1_arg2)
{
  char func1Local, func1LocalArray[MY_N], *func1LocalPtr, func1InitLocal = MY_N, func1InitLocalArray[MY_N] = {MY_N}, *func1InitLocalPtr = &func1InitLocal;
  static int func1StaticLocal, func1StaticLocalArray[MY_N], *func1StaticLocalPtr, func1StaticInitLocal = MY_N, func1StaticInitLocalArray[MY_N] = {MY_N}, *func1StaticInitLocalPtr = &func1StaticInitLocal;

  // init
  file1Global = MY_N;
  file1GlobalPtr = &file1Global;
  file1StaticGlobal = MY_N;
  file1StaticGlobalPtr = &file1StaticGlobal;
  file2Global = MY_N;
  file2GlobalPtr = &file2Global;
  func1Local = MY_N;
  func1LocalPtr = &func1Local;
  func1StaticLocal = MY_N;
  func1StaticLocalPtr = &func1StaticLocal;
  int i;
  for (i=0; i<MY_N; i++) {
    file1GlobalArray[i] = MY_N;
    file1InitGlobalArray[i] = 0;
    file1StaticGlobalArray[i] = MY_N;
    file1StaticInitGlobalArray[i] = 0;
    file2GlobalArray[i] = MY_N;
    file2InitGlobalArray[i] = 0;
    func1LocalArray[i] = MY_N;
    func1InitLocalArray[i] = 0;
    func1StaticLocalArray[i] = MY_N;
    func1StaticInitLocalArray[i] = 0;
  }
  file1InitGlobalArray[0] = MY_N;
  file1StaticInitGlobalArray[0] = MY_N;
  file2InitGlobalArray[0] = MY_N;
  func1InitLocalArray[0] = MY_N;
  func1StaticInitLocalArray[0] = MY_N;

  // total
  float total = \
    func1_arg1 + \
    *func1_arg2 + \
    file1Global + \
    *file1GlobalPtr + \
    file1InitGlobal + \
    *file1InitGlobalPtr + \
    file1StaticGlobal + \
    *file1StaticGlobalPtr + \
    file1StaticInitGlobal + \
    *file1StaticInitGlobalPtr + \
    file2Global + \
    *file2GlobalPtr + \
    file2InitGlobal + \
    *file2InitGlobalPtr + \
    func1Local + \
    *func1LocalPtr + \
    func1InitLocal + \
    *func1InitLocalPtr + \
    func1StaticLocal + \
    *func1StaticLocalPtr + \
    func1StaticInitLocal + \
    *func1StaticInitLocalPtr;
  for (i=0; i<MY_N; i++) {
    total += \
      file1GlobalArray[i] + \
      file1InitGlobalArray[i] + \
      file1StaticGlobalArray[i] + \
      file1StaticInitGlobalArray[i] + \
      file2GlobalArray[i] + \
      file2InitGlobalArray[i] + \
      func1LocalArray[i] + \
      func1InitLocalArray[i] + \
      func1StaticLocalArray[i] + \
      func1StaticInitLocalArray[i];
  }
  printf("%s %s from func1\n", file1Hello, file1World);
  printf("func1 total: %f\n", total);

  return total;
}
