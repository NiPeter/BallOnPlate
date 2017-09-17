/*
 * File: structInitFnc_types.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:00:10
 */

#ifndef STRUCTINITFNC_TYPES_H
#define STRUCTINITFNC_TYPES_H

/* Include Files */
#include <IKController/structInitFnc/rtwtypes.h>

/* Type Definitions */
#ifndef typedef_Base_Struct
#define typedef_Base_Struct

typedef struct {
  double r;
  double alpha;
} Base_Struct;

#endif                                 /*typedef_Base_Struct*/

#ifndef typedef_Drive_Struct
#define typedef_Drive_Struct

typedef struct {
  double a;
  double s;
} Drive_Struct;

#endif                                 /*typedef_Drive_Struct*/

#ifndef typedef_Platform_Struct
#define typedef_Platform_Struct

typedef struct {
  double r;
  double alpha;
} Platform_Struct;

#endif                                 /*typedef_Platform_Struct*/

#ifndef typedef_Steward_Struct
#define typedef_Steward_Struct

typedef struct {
  Base_Struct base;
  Platform_Struct platform;
  Drive_Struct drive;
} Steward_Struct;

#endif                                 /*typedef_Steward_Struct*/

#ifndef typedef_struct1_T
#define typedef_struct1_T

typedef struct {
  double a;
  double s;
  double beta[6];
} struct1_T;

#endif                                 /*typedef_struct1_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  double b[18];
  double p[18];
  double h0;
  struct1_T servo;
} struct0_T;

#endif                                 /*typedef_struct0_T*/
#endif

/*
 * File trailer for structInitFnc_types.h
 *
 * [EOF]
 */
