#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_530426474289865084);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3528263188346649627);
void car_H_mod_fun(double *state, double *out_1334736071766327151);
void car_f_fun(double *state, double dt, double *out_636033605388933144);
void car_F_fun(double *state, double dt, double *out_4839326599696126478);
void car_h_25(double *state, double *unused, double *out_8896755623891100661);
void car_H_25(double *state, double *unused, double *out_6586601961207532654);
void car_h_24(double *state, double *unused, double *out_2966722848322860196);
void car_H_24(double *state, double *unused, double *out_5205936654393833205);
void car_h_30(double *state, double *unused, double *out_5259306095637078311);
void car_H_30(double *state, double *unused, double *out_2058905631079924456);
void car_h_26(double *state, double *unused, double *out_2654900774828380660);
void car_H_26(double *state, double *unused, double *out_2845098642333476430);
void car_h_27(double *state, double *unused, double *out_308592942086259253);
void car_H_27(double *state, double *unused, double *out_4282499702263867673);
void car_h_29(double *state, double *unused, double *out_33398879801753364);
void car_H_29(double *state, double *unused, double *out_2569136975394316640);
void car_h_28(double *state, double *unused, double *out_5569692545472455835);
void car_H_28(double *state, double *unused, double *out_2513262041675213934);
void car_h_31(double *state, double *unused, double *out_1211962911467733034);
void car_H_31(double *state, double *unused, double *out_2218890540100124954);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}