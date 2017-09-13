/*
 * File: structInitFnc.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:00:10
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "structInitFnc.h"

/* Function Definitions */

/*
 * % Base Init
 * %% Obliczanie k¹tów mocowania silników
 * Arguments    : const Steward_Struct *steward
 *                struct0_T *ik
 * Return Type  : void
 */
void structInitFnc(const Steward_Struct *steward, struct0_T *ik)
{
  double base_q[6];
  double platform_q[6];
  int i0;
  int i;
  double ct;
  double st;
  double b_steward[3];
  double b_ct[9];
  static const signed char iv0[3] = { 0, 0, 1 };

  double a;
  double A[3];
  double b_a;
  int i1;

  /*  base = steward.base; */
  /*  platform = steward.platform; */
  /*  drive = steward.drive; */
  for (i0 = 0; i0 < 6; i0++) {
    base_q[i0] = 0.0;
    platform_q[i0] = 0.0;
  }

  base_q[0] = steward->base.alpha / 2.0;

  /* % Platform Init */
  /* %% Obliczanie k¹tów mocowania popychaczy */
  platform_q[0] = steward->platform.alpha / 2.0;
  for (i = 0; i < 5; i++) {
    if ((i - ((int)floor((2.0 + (double)i) / 2.0) << 1)) + 2 == 1) {
      /*  silnik nieparzysty */
      base_q[i + 1] = base_q[i] + steward->base.alpha;
    } else {
      /*  silnik parzysty */
      base_q[i + 1] = (base_q[i] - steward->base.alpha) + 2.0943951023931953;
    }

    if ((i - ((int)floor((2.0 + (double)i) / 2.0) << 1)) + 2 == 1) {
      /*  silnik nieparzysty */
      platform_q[i + 1] = platform_q[i] + steward->platform.alpha;
    } else {
      /*  silnik parzysty */
      platform_q[i + 1] = (platform_q[i] - steward->platform.alpha) +
        2.0943951023931953;
    }
  }

  /* % IK parameters */
  /* %% alokacja pamiêci */
  /* ik.b = cell(6,1); % tablica wektorów pozycji silników w uk³adzie bazy */
  /* ik.p = cell(6,1); % tablica wektorów pozycji mocowania popychaczy w */
  /* uk³adzie platformy */
  memset(&ik->b[0], 0, 18U * sizeof(double));
  memset(&ik->p[0], 0, 18U * sizeof(double));
  ik->h0 = 0.0;

  /* %% Obliczenia */
  /* %% Wpisanie parametrów */
  /* ik.h0 = platform.h; % wysokoœæ zerowa */
  ik->servo.a = steward->drive.a;

  /*  d³ugoœæ orczyka */
  ik->servo.s = steward->drive.s;

  /*  d³ugoœæ popychacza */
  for (i = 0; i < 6; i++) {
    /*  Dla ka¿dego z szeœciu serw */
    /* %%Obliczanie pozycji i-tego silnika w uk³adzie bazy */
    ik->b[i] = steward->base.r * cos(base_q[i]);
    ik->b[6 + i] = steward->base.r * sin(base_q[i]);
    ik->b[12 + i] = 0.0;

    /* ik.b{i} = [xb yb 0]'; % wpisanie wektora pozycji silnika do tablicy */
    /* %%Obliczanie pozycji mocowania i-tego popychacza w uk³adzie platformy */
    ik->p[i] = steward->platform.r * cos(platform_q[i]);
    ik->p[6 + i] = steward->platform.r * sin(platform_q[i]);
    ik->p[12 + i] = 0.0;

    /* ik.p{i} = [xp yp 0]'; % wpisanie wektora pozycji popychacza do tablicy */
    /* %% Obliczanie wysokoœci platformy dla alpha = 0 */
    if (1 + i == 3) {
      /* ROTZ Rotation about Z axis */
      /*  */
      /*  R = ROTZ(THETA) is an SO(3) rotation matrix (3x3) representing a rotation of THETA  */
      /*  radians about the z-axis. */
      /*  */
      /*  R = ROTZ(THETA, 'deg') as above but THETA is in degrees. */
      /*  */
      /*  See also ROTX, ROTY, ANGVEC2R, ROT2. */
      /*  Copyright (C) 1993-2015, by Peter I. Corke */
      /*  */
      /*  This file is part of The Robotics Toolbox for MATLAB (RTB). */
      /*   */
      /*  RTB is free software: you can redistribute it and/or modify */
      /*  it under the terms of the GNU Lesser General Public License as published by */
      /*  the Free Software Foundation, either version 3 of the License, or */
      /*  (at your option) any later version. */
      /*   */
      /*  RTB is distributed in the hope that it will be useful, */
      /*  but WITHOUT ANY WARRANTY; without even the implied warranty of */
      /*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
      /*  GNU Lesser General Public License for more details. */
      /*   */
      /*  You should have received a copy of the GNU Leser General Public License */
      /*  along with RTB.  If not, see <http://www.gnu.org/licenses/>. */
      /*  */
      /*  http://www.petercorke.com */
      ct = cos(base_q[i] + 1.5707963267948966);
      st = sin(base_q[i] + 1.5707963267948966);
      b_steward[0] = steward->drive.a;
      b_steward[1] = 0.0;
      b_steward[2] = 0.0;
      b_ct[0] = ct;
      b_ct[3] = -st;
      b_ct[6] = 0.0;
      b_ct[1] = st;
      b_ct[4] = ct;
      b_ct[7] = 0.0;
      for (i0 = 0; i0 < 3; i0++) {
        b_ct[2 + 3 * i0] = iv0[i0];
      }

      for (i0 = 0; i0 < 3; i0++) {
        A[i0] = 0.0;
        for (i1 = 0; i1 < 3; i1++) {
          A[i0] += b_ct[i0 + 3 * i1] * b_steward[i1];
        }
      }

      a = (ik->p[i] - ik->b[i]) - A[0];
      b_a = (ik->p[6 + i] - ik->b[6 + i]) - A[1];
      ik->h0 = sqrt((steward->drive.s * steward->drive.s - a * a) - b_a * b_a);
    }

    ik->servo.beta[i] = base_q[i];
  }

  /*  k¹ty miêdzy poszczególnymi silnikami a osi¹ X */
}

/*
 * File trailer for structInitFnc.c
 *
 * [EOF]
 */
