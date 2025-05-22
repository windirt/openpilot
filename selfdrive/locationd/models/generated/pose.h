#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6728567055571296281);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1359217107745375791);
void pose_H_mod_fun(double *state, double *out_7644618563595227330);
void pose_f_fun(double *state, double dt, double *out_5814374477757895690);
void pose_F_fun(double *state, double dt, double *out_3565903804308195890);
void pose_h_4(double *state, double *unused, double *out_5629826972556855355);
void pose_H_4(double *state, double *unused, double *out_3872811353751319758);
void pose_h_10(double *state, double *unused, double *out_47996974574044037);
void pose_H_10(double *state, double *unused, double *out_5983294384287388784);
void pose_h_13(double *state, double *unused, double *out_7941151597873080648);
void pose_H_13(double *state, double *unused, double *out_660537528418986957);
void pose_h_14(double *state, double *unused, double *out_1102431323715996841);
void pose_H_14(double *state, double *unused, double *out_6955599786046692054);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}