/*
 * File: servoIK.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:06:32
 */

/* Include Files */
#include <IKController/servoIK/rt_nonfinite.h>
#include <IKController/servoIK/servoIK.h>

/* Variable Definitions */
static double prev_alpha[6];

/* Function Definitions */

/*
 * SERVOIK
 * Arguments    : const double Q[6]
 *                const IK_Struct *ik
 *                double alpha[6]
 * Return Type  : void
 */
void servoIK(const double Q[6], const IK_Struct *ik, double alpha[6])
{
  double b_Q[3];
  double ct;
  double st;
  double b_ct;
  double b_st;
  double c_ct;
  double c_st;
  static double d_ct[9];
  double e_ct[9];
  double T[3];
  int i0;
  static const signed char iv0[3] = { 0, 0, 1 };

  static const signed char iv1[3] = { 0, 1, 0 };

  double f_ct[9];
  double dv0[9];
  int k;
  static const signed char iv2[3] = { 1, 0, 0 };

  int i1;
  double s;
  double R[9];
  double a;
  int i;
  int exitg1;
  double l;
  double scale;
  double pb[3];
  double absxk;
  double A;
  double B;
  double argum;
  double t;

  /*  Patrz -> Dysk Ti -> Steward_servo.pdf */
  /*  + Szufnarowski Steward Platform - low cost study */
  /* B³¹d w opracowaniu Steward_servo! Wektor Pi powinien byæ wyra¿ony w */
  /* uk³adzie Bazy, a nie, jak jak zapisano w Steward_servo.pdf, w uk³adzie */
  /* platformy. */
  /* Niezbêdna zmiana w parametrze B wzglêdem Szufnarowskiego, w opracowaniu */
  /* zak³adaj¹ ¿e serwa zwrócone s¹ do œrodka platformy! Tutaj, zwrócone na */
  /* zewn¹trz. */
  /* % Zmienne statyczne */
  /* global ik */
  /* % Tworzenie macierzy obrotu i wektora pozycji */
  /* Q2TR Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  T = Q(1:3) [1x3] */
  /*  [roll pitch yaw] = Q(4:5) */
  /*  ---- */
  /*  R = Rz(yaw)*Ry(pitch)*Rx(roll) */
  b_Q[0] = Q[0];
  b_Q[1] = Q[1];
  b_Q[2] = Q[2];

  /* RXYZ Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  if nargin < 2 */
  /*      t = roll; */
  /*      roll = t(1); */
  /*      pitch = t(2); */
  /*      yaw = t(3); */
  /*  end */
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
  ct = cos(Q[5]);
  st = sin(Q[5]);

  /* ROTY Rotation about Y axis */
  /*  */
  /*  R = ROTY(THETA) is an SO(3) rotation matrix (3x3) representing a rotation of THETA  */
  /*  radians about the y-axis. */
  /*  */
  /*  R = ROTY(THETA, 'deg') as above but THETA is in degrees. */
  /*  */
  /*  See also ROTX, ROTZ, ANGVEC2R, ROT2. */
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
  b_ct = cos(Q[4]);
  b_st = sin(Q[4]);

  /* ROTX Rotation about X axis */
  /*  */
  /*  R = ROTX(THETA) is an SO(3) rotation matrix (3x3) representing a rotation of THETA  */
  /*  radians about the x-axis. */
  /*  */
  /*  R = ROTX(THETA, 'deg') as above but THETA is in degrees. */
  /*  */
  /*  See also ROTY, ROTZ, ANGVEC2R, ROT2. */
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
  c_ct = cos(Q[3]);
  c_st = sin(Q[3]);
  d_ct[0] = ct;
  d_ct[3] = -st;
  d_ct[6] = 0.0;
  d_ct[1] = st;
  d_ct[4] = ct;
  d_ct[7] = 0.0;
  e_ct[0] = b_ct;
  e_ct[3] = 0.0;
  e_ct[6] = b_st;
  for (i0 = 0; i0 < 3; i0++) {
    T[i0] = b_Q[i0];
    d_ct[2 + 3 * i0] = iv0[i0];
    e_ct[1 + 3 * i0] = iv1[i0];
  }

  e_ct[2] = -b_st;
  e_ct[5] = 0.0;
  e_ct[8] = b_ct;
  for (i0 = 0; i0 < 3; i0++) {
    for (k = 0; k < 3; k++) {
      f_ct[i0 + 3 * k] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        f_ct[i0 + 3 * k] += d_ct[i0 + 3 * i1] * e_ct[i1 + 3 * k];
      }
    }

    dv0[3 * i0] = iv2[i0];
  }

  dv0[1] = 0.0;
  dv0[4] = c_ct;
  dv0[7] = -c_st;
  dv0[2] = 0.0;
  dv0[5] = c_st;
  dv0[8] = c_ct;
  for (i0 = 0; i0 < 3; i0++) {
    for (k = 0; k < 3; k++) {
      R[i0 + 3 * k] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        R[i0 + 3 * k] += f_ct[i0 + 3 * i1] * dv0[i1 + 3 * k];
      }
    }
  }

  T[2] += ik->h0;

  /* % Lokalne przypisanie parametrów platformy */
  s = ik->servo.s;

  /*  d³ugoœ popychacza */
  a = ik->servo.a;

  /*  d³ugoœæ orczyka */
  /*  wektor k¹tów mocowania przegubów bazy (silników) od */
  /*  osi X */
  /*  tablica wektorów pozycji przegubów platformy w uk³adzie platformy */
  /*  tablica wektorów pozycji przegubów bazy w uk³adzie bazy */
  /* % Obliczenia */
  for (i0 = 0; i0 < 6; i0++) {
    alpha[i0] = 0.0;
  }

  /* Alokacja pamiêci */
  i = 0;
  do {
    exitg1 = 0;
    if (i < 6) {
      /*  Dla ka¿dego z szeœciu serw */
      /*  wektor pozycji przegubu i-tego platformy w uk³adzie bazy */
      l = 0.0;
      scale = 2.2250738585072014E-308;
      for (k = 0; k < 3; k++) {
        absxk = 0.0;
        for (i0 = 0; i0 < 3; i0++) {
          absxk += R[k + 3 * i0] * ik->p[i + 6 * i0];
        }

        pb[k] = T[k] + absxk;
        b_Q[k] = pb[k] - ik->b[i + 6 * k];
        absxk = fabs(b_Q[k]);
        if (absxk > scale) {
          t = scale / absxk;
          l = 1.0 + l * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          l += t * t;
        }
      }

      l = scale * sqrt(l);

      /* d³ugoœæ nogi i-tej */
      /* %% Parametry pomocnicze - patrz Szufnarowski */
      A = 2.0 * a * (pb[2] - ik->b[12 + i]);
      B = -2.0 * a * (sin(ik->servo.beta[i]) * (pb[0] - ik->b[i]) - cos
                      (ik->servo.beta[i]) * (pb[1] - ik->b[6 + i]));
      argum = ((l * l - s * s) + a * a) / sqrt(A * A + B * B);

      /* argument arcsinusa */
      /* %% Je¿eli argument arcsinusa jest poza zakresem <-1,1> to brak */
      /* %% rozwi¹zania */
      if ((argum > 1.0) || (argum < -1.0)) {
        /*  Tutaj obs³u¿yæ przypadek gdy nie ma rozwi¹zania */
        /* warning('Complex servoIK solution found!\nInput vector \tQ=[%.3f %.3f %.3f %.3f %.3f %.3f]\nUsing \t\t\tQ=[%.3f %.3f %.3f %.3f %.3f %.3f] instead.',Q,prev_Q); */
        for (i0 = 0; i0 < 6; i0++) {
          alpha[i0] = prev_alpha[i0];
        }

        exitg1 = 1;
      } else {
        /* %% Obliczanie k¹tów dla silników parzystych i nieparzystych */
        if ((i - ((int)floor((1.0 + (double)i) / 2.0) << 1)) + 1 == 1) {
          /*  Silnik nieparzysty - odd, i = 1 3 5 */
          alpha[i] = asin(argum) - atan(B / A);
        } else {
          /*  Silnik parzysty - even, i = 2 4 6 */
          alpha[i] = 3.1415926535897931 + (asin(-argum) - atan(B / A));
        }

        i++;
      }
    } else {
      for (i0 = 0; i0 < 6; i0++) {
        prev_alpha[i0] = alpha[i0];
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void servoIK_init(void)
{
  int i2;
  static const double dv1[6] = { 0.0, 3.1416, 0.0, 3.1416, 0.0, 3.1416 };

  for (i2 = 0; i2 < 6; i2++) {
    prev_alpha[i2] = dv1[i2];
  }
}

/*
 * File trailer for servoIK.c
 *
 * [EOF]
 */
