# Lab 7 (Ultra Sonic) - Group 4

## Summary

We created the project from scratch and used seg7/seg7digit from previous labs to accomplish the following:

 - Device driver for the Ultrasonic Ranger
 - Event driven button and update methods that update the display

## Questions

 1. Work breakdown:
    - Greg (33%)
    - Esteban (33%)
    - Yara (33%)
 2. We added four driver functions:
    1. `void RangerInit();` - Initialization method
    2. `void RangerPing();` - Helper method that actually sends the signal
    3. `uint32_t RangerLag();` - Main function that returns the number of clocks that it took for the signal to bounce back
    4. `void RangerRead();` - Helper method that is now deprecated since we didn't use it in the final release
 3. We did some fairly easy arithmetic. Since the processor is a 50 MHz processor, dividing by 50,000 returns the milliseconds lag time. Dividing by two gets us the one-way lag. Then multiplying by 0.34 gives us the meters, and multiplying by 1000 gives the millimeters.
 4. The push button functions were event-driven similar to other labs.
 5. Appendix Questions:
    1. 6 16/32-bit GPTMs
    2. 6 32/64-bit GPTMs
    3. 12 pins
    4. 2, timer A and timer B
    5. WT3CCP0
    6. PD2
    7. Timer modes:
    8. One-Shot/Periodic
    9. Real-Time Clock
    10. Input-Edge Count
    11. Input-Edge Time
    12. PWM
    13. Input-Edge Count Mode
 6. Memory usage:
    - Flash: 13,834 bytes
    - SRAM:  1,340 bytes
 7. Our group took about 12 hours to complete this lab.

## Authors

 - Gregory N. Schmit
 - Esteban Garcia
 - Yara Merei
