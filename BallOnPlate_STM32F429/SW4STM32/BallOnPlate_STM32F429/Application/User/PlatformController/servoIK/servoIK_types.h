/*
 * File: servoIK_types.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:06:32
 */

#ifndef SERVOIK_TYPES_H
#define SERVOIK_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_Servo_Struct
#define typedef_Servo_Struct

typedef struct {
  double a;
  double s;
  double beta[6];
} Servo_Struct;

#endif                                 /*typedef_Servo_Struct*/

#ifndef typedef_IK_Struct
#define typedef_IK_Struct

typedef struct {
  double b[18];
  double p[18];
  double h0;
  Servo_Struct servo;
} IK_Struct;

#endif                                 /*typedef_IK_Struct*/
#endif

/*
 * File trailer for servoIK_types.h
 *
 * [EOF]
 */
