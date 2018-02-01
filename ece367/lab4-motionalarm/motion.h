/*
 * motion.h: Basic driver functions for the buzzer.
 * This code is designed for Lab 4 Motion Detection Alarm
 *
 *  Created on: Feb 20, 2017
 *      Author: schmitgreg
 */

#ifndef MOTION_H_
#define MOTION_H_

// Initialize the buzzer
void motionInit();

// Check to see if motion is active
int32_t motionCheck();

#endif /* MOTION_H_ */
