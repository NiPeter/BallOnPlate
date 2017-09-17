/*
 * File: servoIK.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:06:32
 */

#ifndef SERVOIK_H
#define SERVOIK_H

/* Include Files */
#include <IKController/servoIK/rtwtypes.h>
#include <IKController/servoIK/servoIK_types.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

/* Function Declarations */
extern void servoIK(const double Q[6], const IK_Struct *ik, double alpha[6]);
extern void servoIK_init(void);

#endif

/*
 * File trailer for servoIK.h
 *
 * [EOF]
 */
