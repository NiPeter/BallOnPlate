/*
 * File: servoIK_initialize.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:06:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "servoIK.h"
#include "servoIK_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void servoIK_initialize(void)
{
  rt_InitInfAndNaN(8U);
  servoIK_init();
}

/*
 * File trailer for servoIK_initialize.c
 *
 * [EOF]
 */
