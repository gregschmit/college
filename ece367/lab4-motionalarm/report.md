# Lab 4 (Motion Alarm) - Group 4

## Summary

We modified the provided `main.c`, and created `motion.h` and `motion.asm` to implement three features:

 - Device driver for motion input (`motion.h`/`motion.asm`)
 - Alarm system in `main.c` that is enabled and disabled using buttons `SW1` and `SW2`, respectively
 - Buzzer function that buzzes for 3 seconds after detecting motion, and then backs off for 3 seconds to prevent trigger loops

## Questions

 1. Work breakdown:
    - Greg (33%)
    - Esteban (33%)
    - Yara (33%)
 2. We implemented two methods: `motionInit` and `motionCheck`. We chose these because we need to initialize the device and check the condition of the motion sensor (input device).
 3. We adjusted main to implement a system daemon called `systemDaemon` which has the system loop and is responsible for buzzing the buzzer if the conditions are right, and setting the alarm if there is motion detected and the backoff timer is expired. Two other daemons run (`alarmDaemon` and `buttonDaemon`) that monitor and run methods for button control and alarm functions.
 4. Memory:
    - Flash: 12,512 Bytes
    - SRAM:   1,316 Bytes
 5. 2 hours

## Authors

 - Gregory N. Schmit
 - Esteban Garcia
 - Yara Merei
