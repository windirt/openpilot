#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6728567055571296281) {
   out_6728567055571296281[0] = delta_x[0] + nom_x[0];
   out_6728567055571296281[1] = delta_x[1] + nom_x[1];
   out_6728567055571296281[2] = delta_x[2] + nom_x[2];
   out_6728567055571296281[3] = delta_x[3] + nom_x[3];
   out_6728567055571296281[4] = delta_x[4] + nom_x[4];
   out_6728567055571296281[5] = delta_x[5] + nom_x[5];
   out_6728567055571296281[6] = delta_x[6] + nom_x[6];
   out_6728567055571296281[7] = delta_x[7] + nom_x[7];
   out_6728567055571296281[8] = delta_x[8] + nom_x[8];
   out_6728567055571296281[9] = delta_x[9] + nom_x[9];
   out_6728567055571296281[10] = delta_x[10] + nom_x[10];
   out_6728567055571296281[11] = delta_x[11] + nom_x[11];
   out_6728567055571296281[12] = delta_x[12] + nom_x[12];
   out_6728567055571296281[13] = delta_x[13] + nom_x[13];
   out_6728567055571296281[14] = delta_x[14] + nom_x[14];
   out_6728567055571296281[15] = delta_x[15] + nom_x[15];
   out_6728567055571296281[16] = delta_x[16] + nom_x[16];
   out_6728567055571296281[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1359217107745375791) {
   out_1359217107745375791[0] = -nom_x[0] + true_x[0];
   out_1359217107745375791[1] = -nom_x[1] + true_x[1];
   out_1359217107745375791[2] = -nom_x[2] + true_x[2];
   out_1359217107745375791[3] = -nom_x[3] + true_x[3];
   out_1359217107745375791[4] = -nom_x[4] + true_x[4];
   out_1359217107745375791[5] = -nom_x[5] + true_x[5];
   out_1359217107745375791[6] = -nom_x[6] + true_x[6];
   out_1359217107745375791[7] = -nom_x[7] + true_x[7];
   out_1359217107745375791[8] = -nom_x[8] + true_x[8];
   out_1359217107745375791[9] = -nom_x[9] + true_x[9];
   out_1359217107745375791[10] = -nom_x[10] + true_x[10];
   out_1359217107745375791[11] = -nom_x[11] + true_x[11];
   out_1359217107745375791[12] = -nom_x[12] + true_x[12];
   out_1359217107745375791[13] = -nom_x[13] + true_x[13];
   out_1359217107745375791[14] = -nom_x[14] + true_x[14];
   out_1359217107745375791[15] = -nom_x[15] + true_x[15];
   out_1359217107745375791[16] = -nom_x[16] + true_x[16];
   out_1359217107745375791[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7644618563595227330) {
   out_7644618563595227330[0] = 1.0;
   out_7644618563595227330[1] = 0.0;
   out_7644618563595227330[2] = 0.0;
   out_7644618563595227330[3] = 0.0;
   out_7644618563595227330[4] = 0.0;
   out_7644618563595227330[5] = 0.0;
   out_7644618563595227330[6] = 0.0;
   out_7644618563595227330[7] = 0.0;
   out_7644618563595227330[8] = 0.0;
   out_7644618563595227330[9] = 0.0;
   out_7644618563595227330[10] = 0.0;
   out_7644618563595227330[11] = 0.0;
   out_7644618563595227330[12] = 0.0;
   out_7644618563595227330[13] = 0.0;
   out_7644618563595227330[14] = 0.0;
   out_7644618563595227330[15] = 0.0;
   out_7644618563595227330[16] = 0.0;
   out_7644618563595227330[17] = 0.0;
   out_7644618563595227330[18] = 0.0;
   out_7644618563595227330[19] = 1.0;
   out_7644618563595227330[20] = 0.0;
   out_7644618563595227330[21] = 0.0;
   out_7644618563595227330[22] = 0.0;
   out_7644618563595227330[23] = 0.0;
   out_7644618563595227330[24] = 0.0;
   out_7644618563595227330[25] = 0.0;
   out_7644618563595227330[26] = 0.0;
   out_7644618563595227330[27] = 0.0;
   out_7644618563595227330[28] = 0.0;
   out_7644618563595227330[29] = 0.0;
   out_7644618563595227330[30] = 0.0;
   out_7644618563595227330[31] = 0.0;
   out_7644618563595227330[32] = 0.0;
   out_7644618563595227330[33] = 0.0;
   out_7644618563595227330[34] = 0.0;
   out_7644618563595227330[35] = 0.0;
   out_7644618563595227330[36] = 0.0;
   out_7644618563595227330[37] = 0.0;
   out_7644618563595227330[38] = 1.0;
   out_7644618563595227330[39] = 0.0;
   out_7644618563595227330[40] = 0.0;
   out_7644618563595227330[41] = 0.0;
   out_7644618563595227330[42] = 0.0;
   out_7644618563595227330[43] = 0.0;
   out_7644618563595227330[44] = 0.0;
   out_7644618563595227330[45] = 0.0;
   out_7644618563595227330[46] = 0.0;
   out_7644618563595227330[47] = 0.0;
   out_7644618563595227330[48] = 0.0;
   out_7644618563595227330[49] = 0.0;
   out_7644618563595227330[50] = 0.0;
   out_7644618563595227330[51] = 0.0;
   out_7644618563595227330[52] = 0.0;
   out_7644618563595227330[53] = 0.0;
   out_7644618563595227330[54] = 0.0;
   out_7644618563595227330[55] = 0.0;
   out_7644618563595227330[56] = 0.0;
   out_7644618563595227330[57] = 1.0;
   out_7644618563595227330[58] = 0.0;
   out_7644618563595227330[59] = 0.0;
   out_7644618563595227330[60] = 0.0;
   out_7644618563595227330[61] = 0.0;
   out_7644618563595227330[62] = 0.0;
   out_7644618563595227330[63] = 0.0;
   out_7644618563595227330[64] = 0.0;
   out_7644618563595227330[65] = 0.0;
   out_7644618563595227330[66] = 0.0;
   out_7644618563595227330[67] = 0.0;
   out_7644618563595227330[68] = 0.0;
   out_7644618563595227330[69] = 0.0;
   out_7644618563595227330[70] = 0.0;
   out_7644618563595227330[71] = 0.0;
   out_7644618563595227330[72] = 0.0;
   out_7644618563595227330[73] = 0.0;
   out_7644618563595227330[74] = 0.0;
   out_7644618563595227330[75] = 0.0;
   out_7644618563595227330[76] = 1.0;
   out_7644618563595227330[77] = 0.0;
   out_7644618563595227330[78] = 0.0;
   out_7644618563595227330[79] = 0.0;
   out_7644618563595227330[80] = 0.0;
   out_7644618563595227330[81] = 0.0;
   out_7644618563595227330[82] = 0.0;
   out_7644618563595227330[83] = 0.0;
   out_7644618563595227330[84] = 0.0;
   out_7644618563595227330[85] = 0.0;
   out_7644618563595227330[86] = 0.0;
   out_7644618563595227330[87] = 0.0;
   out_7644618563595227330[88] = 0.0;
   out_7644618563595227330[89] = 0.0;
   out_7644618563595227330[90] = 0.0;
   out_7644618563595227330[91] = 0.0;
   out_7644618563595227330[92] = 0.0;
   out_7644618563595227330[93] = 0.0;
   out_7644618563595227330[94] = 0.0;
   out_7644618563595227330[95] = 1.0;
   out_7644618563595227330[96] = 0.0;
   out_7644618563595227330[97] = 0.0;
   out_7644618563595227330[98] = 0.0;
   out_7644618563595227330[99] = 0.0;
   out_7644618563595227330[100] = 0.0;
   out_7644618563595227330[101] = 0.0;
   out_7644618563595227330[102] = 0.0;
   out_7644618563595227330[103] = 0.0;
   out_7644618563595227330[104] = 0.0;
   out_7644618563595227330[105] = 0.0;
   out_7644618563595227330[106] = 0.0;
   out_7644618563595227330[107] = 0.0;
   out_7644618563595227330[108] = 0.0;
   out_7644618563595227330[109] = 0.0;
   out_7644618563595227330[110] = 0.0;
   out_7644618563595227330[111] = 0.0;
   out_7644618563595227330[112] = 0.0;
   out_7644618563595227330[113] = 0.0;
   out_7644618563595227330[114] = 1.0;
   out_7644618563595227330[115] = 0.0;
   out_7644618563595227330[116] = 0.0;
   out_7644618563595227330[117] = 0.0;
   out_7644618563595227330[118] = 0.0;
   out_7644618563595227330[119] = 0.0;
   out_7644618563595227330[120] = 0.0;
   out_7644618563595227330[121] = 0.0;
   out_7644618563595227330[122] = 0.0;
   out_7644618563595227330[123] = 0.0;
   out_7644618563595227330[124] = 0.0;
   out_7644618563595227330[125] = 0.0;
   out_7644618563595227330[126] = 0.0;
   out_7644618563595227330[127] = 0.0;
   out_7644618563595227330[128] = 0.0;
   out_7644618563595227330[129] = 0.0;
   out_7644618563595227330[130] = 0.0;
   out_7644618563595227330[131] = 0.0;
   out_7644618563595227330[132] = 0.0;
   out_7644618563595227330[133] = 1.0;
   out_7644618563595227330[134] = 0.0;
   out_7644618563595227330[135] = 0.0;
   out_7644618563595227330[136] = 0.0;
   out_7644618563595227330[137] = 0.0;
   out_7644618563595227330[138] = 0.0;
   out_7644618563595227330[139] = 0.0;
   out_7644618563595227330[140] = 0.0;
   out_7644618563595227330[141] = 0.0;
   out_7644618563595227330[142] = 0.0;
   out_7644618563595227330[143] = 0.0;
   out_7644618563595227330[144] = 0.0;
   out_7644618563595227330[145] = 0.0;
   out_7644618563595227330[146] = 0.0;
   out_7644618563595227330[147] = 0.0;
   out_7644618563595227330[148] = 0.0;
   out_7644618563595227330[149] = 0.0;
   out_7644618563595227330[150] = 0.0;
   out_7644618563595227330[151] = 0.0;
   out_7644618563595227330[152] = 1.0;
   out_7644618563595227330[153] = 0.0;
   out_7644618563595227330[154] = 0.0;
   out_7644618563595227330[155] = 0.0;
   out_7644618563595227330[156] = 0.0;
   out_7644618563595227330[157] = 0.0;
   out_7644618563595227330[158] = 0.0;
   out_7644618563595227330[159] = 0.0;
   out_7644618563595227330[160] = 0.0;
   out_7644618563595227330[161] = 0.0;
   out_7644618563595227330[162] = 0.0;
   out_7644618563595227330[163] = 0.0;
   out_7644618563595227330[164] = 0.0;
   out_7644618563595227330[165] = 0.0;
   out_7644618563595227330[166] = 0.0;
   out_7644618563595227330[167] = 0.0;
   out_7644618563595227330[168] = 0.0;
   out_7644618563595227330[169] = 0.0;
   out_7644618563595227330[170] = 0.0;
   out_7644618563595227330[171] = 1.0;
   out_7644618563595227330[172] = 0.0;
   out_7644618563595227330[173] = 0.0;
   out_7644618563595227330[174] = 0.0;
   out_7644618563595227330[175] = 0.0;
   out_7644618563595227330[176] = 0.0;
   out_7644618563595227330[177] = 0.0;
   out_7644618563595227330[178] = 0.0;
   out_7644618563595227330[179] = 0.0;
   out_7644618563595227330[180] = 0.0;
   out_7644618563595227330[181] = 0.0;
   out_7644618563595227330[182] = 0.0;
   out_7644618563595227330[183] = 0.0;
   out_7644618563595227330[184] = 0.0;
   out_7644618563595227330[185] = 0.0;
   out_7644618563595227330[186] = 0.0;
   out_7644618563595227330[187] = 0.0;
   out_7644618563595227330[188] = 0.0;
   out_7644618563595227330[189] = 0.0;
   out_7644618563595227330[190] = 1.0;
   out_7644618563595227330[191] = 0.0;
   out_7644618563595227330[192] = 0.0;
   out_7644618563595227330[193] = 0.0;
   out_7644618563595227330[194] = 0.0;
   out_7644618563595227330[195] = 0.0;
   out_7644618563595227330[196] = 0.0;
   out_7644618563595227330[197] = 0.0;
   out_7644618563595227330[198] = 0.0;
   out_7644618563595227330[199] = 0.0;
   out_7644618563595227330[200] = 0.0;
   out_7644618563595227330[201] = 0.0;
   out_7644618563595227330[202] = 0.0;
   out_7644618563595227330[203] = 0.0;
   out_7644618563595227330[204] = 0.0;
   out_7644618563595227330[205] = 0.0;
   out_7644618563595227330[206] = 0.0;
   out_7644618563595227330[207] = 0.0;
   out_7644618563595227330[208] = 0.0;
   out_7644618563595227330[209] = 1.0;
   out_7644618563595227330[210] = 0.0;
   out_7644618563595227330[211] = 0.0;
   out_7644618563595227330[212] = 0.0;
   out_7644618563595227330[213] = 0.0;
   out_7644618563595227330[214] = 0.0;
   out_7644618563595227330[215] = 0.0;
   out_7644618563595227330[216] = 0.0;
   out_7644618563595227330[217] = 0.0;
   out_7644618563595227330[218] = 0.0;
   out_7644618563595227330[219] = 0.0;
   out_7644618563595227330[220] = 0.0;
   out_7644618563595227330[221] = 0.0;
   out_7644618563595227330[222] = 0.0;
   out_7644618563595227330[223] = 0.0;
   out_7644618563595227330[224] = 0.0;
   out_7644618563595227330[225] = 0.0;
   out_7644618563595227330[226] = 0.0;
   out_7644618563595227330[227] = 0.0;
   out_7644618563595227330[228] = 1.0;
   out_7644618563595227330[229] = 0.0;
   out_7644618563595227330[230] = 0.0;
   out_7644618563595227330[231] = 0.0;
   out_7644618563595227330[232] = 0.0;
   out_7644618563595227330[233] = 0.0;
   out_7644618563595227330[234] = 0.0;
   out_7644618563595227330[235] = 0.0;
   out_7644618563595227330[236] = 0.0;
   out_7644618563595227330[237] = 0.0;
   out_7644618563595227330[238] = 0.0;
   out_7644618563595227330[239] = 0.0;
   out_7644618563595227330[240] = 0.0;
   out_7644618563595227330[241] = 0.0;
   out_7644618563595227330[242] = 0.0;
   out_7644618563595227330[243] = 0.0;
   out_7644618563595227330[244] = 0.0;
   out_7644618563595227330[245] = 0.0;
   out_7644618563595227330[246] = 0.0;
   out_7644618563595227330[247] = 1.0;
   out_7644618563595227330[248] = 0.0;
   out_7644618563595227330[249] = 0.0;
   out_7644618563595227330[250] = 0.0;
   out_7644618563595227330[251] = 0.0;
   out_7644618563595227330[252] = 0.0;
   out_7644618563595227330[253] = 0.0;
   out_7644618563595227330[254] = 0.0;
   out_7644618563595227330[255] = 0.0;
   out_7644618563595227330[256] = 0.0;
   out_7644618563595227330[257] = 0.0;
   out_7644618563595227330[258] = 0.0;
   out_7644618563595227330[259] = 0.0;
   out_7644618563595227330[260] = 0.0;
   out_7644618563595227330[261] = 0.0;
   out_7644618563595227330[262] = 0.0;
   out_7644618563595227330[263] = 0.0;
   out_7644618563595227330[264] = 0.0;
   out_7644618563595227330[265] = 0.0;
   out_7644618563595227330[266] = 1.0;
   out_7644618563595227330[267] = 0.0;
   out_7644618563595227330[268] = 0.0;
   out_7644618563595227330[269] = 0.0;
   out_7644618563595227330[270] = 0.0;
   out_7644618563595227330[271] = 0.0;
   out_7644618563595227330[272] = 0.0;
   out_7644618563595227330[273] = 0.0;
   out_7644618563595227330[274] = 0.0;
   out_7644618563595227330[275] = 0.0;
   out_7644618563595227330[276] = 0.0;
   out_7644618563595227330[277] = 0.0;
   out_7644618563595227330[278] = 0.0;
   out_7644618563595227330[279] = 0.0;
   out_7644618563595227330[280] = 0.0;
   out_7644618563595227330[281] = 0.0;
   out_7644618563595227330[282] = 0.0;
   out_7644618563595227330[283] = 0.0;
   out_7644618563595227330[284] = 0.0;
   out_7644618563595227330[285] = 1.0;
   out_7644618563595227330[286] = 0.0;
   out_7644618563595227330[287] = 0.0;
   out_7644618563595227330[288] = 0.0;
   out_7644618563595227330[289] = 0.0;
   out_7644618563595227330[290] = 0.0;
   out_7644618563595227330[291] = 0.0;
   out_7644618563595227330[292] = 0.0;
   out_7644618563595227330[293] = 0.0;
   out_7644618563595227330[294] = 0.0;
   out_7644618563595227330[295] = 0.0;
   out_7644618563595227330[296] = 0.0;
   out_7644618563595227330[297] = 0.0;
   out_7644618563595227330[298] = 0.0;
   out_7644618563595227330[299] = 0.0;
   out_7644618563595227330[300] = 0.0;
   out_7644618563595227330[301] = 0.0;
   out_7644618563595227330[302] = 0.0;
   out_7644618563595227330[303] = 0.0;
   out_7644618563595227330[304] = 1.0;
   out_7644618563595227330[305] = 0.0;
   out_7644618563595227330[306] = 0.0;
   out_7644618563595227330[307] = 0.0;
   out_7644618563595227330[308] = 0.0;
   out_7644618563595227330[309] = 0.0;
   out_7644618563595227330[310] = 0.0;
   out_7644618563595227330[311] = 0.0;
   out_7644618563595227330[312] = 0.0;
   out_7644618563595227330[313] = 0.0;
   out_7644618563595227330[314] = 0.0;
   out_7644618563595227330[315] = 0.0;
   out_7644618563595227330[316] = 0.0;
   out_7644618563595227330[317] = 0.0;
   out_7644618563595227330[318] = 0.0;
   out_7644618563595227330[319] = 0.0;
   out_7644618563595227330[320] = 0.0;
   out_7644618563595227330[321] = 0.0;
   out_7644618563595227330[322] = 0.0;
   out_7644618563595227330[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5814374477757895690) {
   out_5814374477757895690[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5814374477757895690[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5814374477757895690[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5814374477757895690[3] = dt*state[12] + state[3];
   out_5814374477757895690[4] = dt*state[13] + state[4];
   out_5814374477757895690[5] = dt*state[14] + state[5];
   out_5814374477757895690[6] = state[6];
   out_5814374477757895690[7] = state[7];
   out_5814374477757895690[8] = state[8];
   out_5814374477757895690[9] = state[9];
   out_5814374477757895690[10] = state[10];
   out_5814374477757895690[11] = state[11];
   out_5814374477757895690[12] = state[12];
   out_5814374477757895690[13] = state[13];
   out_5814374477757895690[14] = state[14];
   out_5814374477757895690[15] = state[15];
   out_5814374477757895690[16] = state[16];
   out_5814374477757895690[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3565903804308195890) {
   out_3565903804308195890[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565903804308195890[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565903804308195890[2] = 0;
   out_3565903804308195890[3] = 0;
   out_3565903804308195890[4] = 0;
   out_3565903804308195890[5] = 0;
   out_3565903804308195890[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565903804308195890[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565903804308195890[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565903804308195890[9] = 0;
   out_3565903804308195890[10] = 0;
   out_3565903804308195890[11] = 0;
   out_3565903804308195890[12] = 0;
   out_3565903804308195890[13] = 0;
   out_3565903804308195890[14] = 0;
   out_3565903804308195890[15] = 0;
   out_3565903804308195890[16] = 0;
   out_3565903804308195890[17] = 0;
   out_3565903804308195890[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565903804308195890[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565903804308195890[20] = 0;
   out_3565903804308195890[21] = 0;
   out_3565903804308195890[22] = 0;
   out_3565903804308195890[23] = 0;
   out_3565903804308195890[24] = 0;
   out_3565903804308195890[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565903804308195890[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565903804308195890[27] = 0;
   out_3565903804308195890[28] = 0;
   out_3565903804308195890[29] = 0;
   out_3565903804308195890[30] = 0;
   out_3565903804308195890[31] = 0;
   out_3565903804308195890[32] = 0;
   out_3565903804308195890[33] = 0;
   out_3565903804308195890[34] = 0;
   out_3565903804308195890[35] = 0;
   out_3565903804308195890[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565903804308195890[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565903804308195890[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565903804308195890[39] = 0;
   out_3565903804308195890[40] = 0;
   out_3565903804308195890[41] = 0;
   out_3565903804308195890[42] = 0;
   out_3565903804308195890[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565903804308195890[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565903804308195890[45] = 0;
   out_3565903804308195890[46] = 0;
   out_3565903804308195890[47] = 0;
   out_3565903804308195890[48] = 0;
   out_3565903804308195890[49] = 0;
   out_3565903804308195890[50] = 0;
   out_3565903804308195890[51] = 0;
   out_3565903804308195890[52] = 0;
   out_3565903804308195890[53] = 0;
   out_3565903804308195890[54] = 0;
   out_3565903804308195890[55] = 0;
   out_3565903804308195890[56] = 0;
   out_3565903804308195890[57] = 1;
   out_3565903804308195890[58] = 0;
   out_3565903804308195890[59] = 0;
   out_3565903804308195890[60] = 0;
   out_3565903804308195890[61] = 0;
   out_3565903804308195890[62] = 0;
   out_3565903804308195890[63] = 0;
   out_3565903804308195890[64] = 0;
   out_3565903804308195890[65] = 0;
   out_3565903804308195890[66] = dt;
   out_3565903804308195890[67] = 0;
   out_3565903804308195890[68] = 0;
   out_3565903804308195890[69] = 0;
   out_3565903804308195890[70] = 0;
   out_3565903804308195890[71] = 0;
   out_3565903804308195890[72] = 0;
   out_3565903804308195890[73] = 0;
   out_3565903804308195890[74] = 0;
   out_3565903804308195890[75] = 0;
   out_3565903804308195890[76] = 1;
   out_3565903804308195890[77] = 0;
   out_3565903804308195890[78] = 0;
   out_3565903804308195890[79] = 0;
   out_3565903804308195890[80] = 0;
   out_3565903804308195890[81] = 0;
   out_3565903804308195890[82] = 0;
   out_3565903804308195890[83] = 0;
   out_3565903804308195890[84] = 0;
   out_3565903804308195890[85] = dt;
   out_3565903804308195890[86] = 0;
   out_3565903804308195890[87] = 0;
   out_3565903804308195890[88] = 0;
   out_3565903804308195890[89] = 0;
   out_3565903804308195890[90] = 0;
   out_3565903804308195890[91] = 0;
   out_3565903804308195890[92] = 0;
   out_3565903804308195890[93] = 0;
   out_3565903804308195890[94] = 0;
   out_3565903804308195890[95] = 1;
   out_3565903804308195890[96] = 0;
   out_3565903804308195890[97] = 0;
   out_3565903804308195890[98] = 0;
   out_3565903804308195890[99] = 0;
   out_3565903804308195890[100] = 0;
   out_3565903804308195890[101] = 0;
   out_3565903804308195890[102] = 0;
   out_3565903804308195890[103] = 0;
   out_3565903804308195890[104] = dt;
   out_3565903804308195890[105] = 0;
   out_3565903804308195890[106] = 0;
   out_3565903804308195890[107] = 0;
   out_3565903804308195890[108] = 0;
   out_3565903804308195890[109] = 0;
   out_3565903804308195890[110] = 0;
   out_3565903804308195890[111] = 0;
   out_3565903804308195890[112] = 0;
   out_3565903804308195890[113] = 0;
   out_3565903804308195890[114] = 1;
   out_3565903804308195890[115] = 0;
   out_3565903804308195890[116] = 0;
   out_3565903804308195890[117] = 0;
   out_3565903804308195890[118] = 0;
   out_3565903804308195890[119] = 0;
   out_3565903804308195890[120] = 0;
   out_3565903804308195890[121] = 0;
   out_3565903804308195890[122] = 0;
   out_3565903804308195890[123] = 0;
   out_3565903804308195890[124] = 0;
   out_3565903804308195890[125] = 0;
   out_3565903804308195890[126] = 0;
   out_3565903804308195890[127] = 0;
   out_3565903804308195890[128] = 0;
   out_3565903804308195890[129] = 0;
   out_3565903804308195890[130] = 0;
   out_3565903804308195890[131] = 0;
   out_3565903804308195890[132] = 0;
   out_3565903804308195890[133] = 1;
   out_3565903804308195890[134] = 0;
   out_3565903804308195890[135] = 0;
   out_3565903804308195890[136] = 0;
   out_3565903804308195890[137] = 0;
   out_3565903804308195890[138] = 0;
   out_3565903804308195890[139] = 0;
   out_3565903804308195890[140] = 0;
   out_3565903804308195890[141] = 0;
   out_3565903804308195890[142] = 0;
   out_3565903804308195890[143] = 0;
   out_3565903804308195890[144] = 0;
   out_3565903804308195890[145] = 0;
   out_3565903804308195890[146] = 0;
   out_3565903804308195890[147] = 0;
   out_3565903804308195890[148] = 0;
   out_3565903804308195890[149] = 0;
   out_3565903804308195890[150] = 0;
   out_3565903804308195890[151] = 0;
   out_3565903804308195890[152] = 1;
   out_3565903804308195890[153] = 0;
   out_3565903804308195890[154] = 0;
   out_3565903804308195890[155] = 0;
   out_3565903804308195890[156] = 0;
   out_3565903804308195890[157] = 0;
   out_3565903804308195890[158] = 0;
   out_3565903804308195890[159] = 0;
   out_3565903804308195890[160] = 0;
   out_3565903804308195890[161] = 0;
   out_3565903804308195890[162] = 0;
   out_3565903804308195890[163] = 0;
   out_3565903804308195890[164] = 0;
   out_3565903804308195890[165] = 0;
   out_3565903804308195890[166] = 0;
   out_3565903804308195890[167] = 0;
   out_3565903804308195890[168] = 0;
   out_3565903804308195890[169] = 0;
   out_3565903804308195890[170] = 0;
   out_3565903804308195890[171] = 1;
   out_3565903804308195890[172] = 0;
   out_3565903804308195890[173] = 0;
   out_3565903804308195890[174] = 0;
   out_3565903804308195890[175] = 0;
   out_3565903804308195890[176] = 0;
   out_3565903804308195890[177] = 0;
   out_3565903804308195890[178] = 0;
   out_3565903804308195890[179] = 0;
   out_3565903804308195890[180] = 0;
   out_3565903804308195890[181] = 0;
   out_3565903804308195890[182] = 0;
   out_3565903804308195890[183] = 0;
   out_3565903804308195890[184] = 0;
   out_3565903804308195890[185] = 0;
   out_3565903804308195890[186] = 0;
   out_3565903804308195890[187] = 0;
   out_3565903804308195890[188] = 0;
   out_3565903804308195890[189] = 0;
   out_3565903804308195890[190] = 1;
   out_3565903804308195890[191] = 0;
   out_3565903804308195890[192] = 0;
   out_3565903804308195890[193] = 0;
   out_3565903804308195890[194] = 0;
   out_3565903804308195890[195] = 0;
   out_3565903804308195890[196] = 0;
   out_3565903804308195890[197] = 0;
   out_3565903804308195890[198] = 0;
   out_3565903804308195890[199] = 0;
   out_3565903804308195890[200] = 0;
   out_3565903804308195890[201] = 0;
   out_3565903804308195890[202] = 0;
   out_3565903804308195890[203] = 0;
   out_3565903804308195890[204] = 0;
   out_3565903804308195890[205] = 0;
   out_3565903804308195890[206] = 0;
   out_3565903804308195890[207] = 0;
   out_3565903804308195890[208] = 0;
   out_3565903804308195890[209] = 1;
   out_3565903804308195890[210] = 0;
   out_3565903804308195890[211] = 0;
   out_3565903804308195890[212] = 0;
   out_3565903804308195890[213] = 0;
   out_3565903804308195890[214] = 0;
   out_3565903804308195890[215] = 0;
   out_3565903804308195890[216] = 0;
   out_3565903804308195890[217] = 0;
   out_3565903804308195890[218] = 0;
   out_3565903804308195890[219] = 0;
   out_3565903804308195890[220] = 0;
   out_3565903804308195890[221] = 0;
   out_3565903804308195890[222] = 0;
   out_3565903804308195890[223] = 0;
   out_3565903804308195890[224] = 0;
   out_3565903804308195890[225] = 0;
   out_3565903804308195890[226] = 0;
   out_3565903804308195890[227] = 0;
   out_3565903804308195890[228] = 1;
   out_3565903804308195890[229] = 0;
   out_3565903804308195890[230] = 0;
   out_3565903804308195890[231] = 0;
   out_3565903804308195890[232] = 0;
   out_3565903804308195890[233] = 0;
   out_3565903804308195890[234] = 0;
   out_3565903804308195890[235] = 0;
   out_3565903804308195890[236] = 0;
   out_3565903804308195890[237] = 0;
   out_3565903804308195890[238] = 0;
   out_3565903804308195890[239] = 0;
   out_3565903804308195890[240] = 0;
   out_3565903804308195890[241] = 0;
   out_3565903804308195890[242] = 0;
   out_3565903804308195890[243] = 0;
   out_3565903804308195890[244] = 0;
   out_3565903804308195890[245] = 0;
   out_3565903804308195890[246] = 0;
   out_3565903804308195890[247] = 1;
   out_3565903804308195890[248] = 0;
   out_3565903804308195890[249] = 0;
   out_3565903804308195890[250] = 0;
   out_3565903804308195890[251] = 0;
   out_3565903804308195890[252] = 0;
   out_3565903804308195890[253] = 0;
   out_3565903804308195890[254] = 0;
   out_3565903804308195890[255] = 0;
   out_3565903804308195890[256] = 0;
   out_3565903804308195890[257] = 0;
   out_3565903804308195890[258] = 0;
   out_3565903804308195890[259] = 0;
   out_3565903804308195890[260] = 0;
   out_3565903804308195890[261] = 0;
   out_3565903804308195890[262] = 0;
   out_3565903804308195890[263] = 0;
   out_3565903804308195890[264] = 0;
   out_3565903804308195890[265] = 0;
   out_3565903804308195890[266] = 1;
   out_3565903804308195890[267] = 0;
   out_3565903804308195890[268] = 0;
   out_3565903804308195890[269] = 0;
   out_3565903804308195890[270] = 0;
   out_3565903804308195890[271] = 0;
   out_3565903804308195890[272] = 0;
   out_3565903804308195890[273] = 0;
   out_3565903804308195890[274] = 0;
   out_3565903804308195890[275] = 0;
   out_3565903804308195890[276] = 0;
   out_3565903804308195890[277] = 0;
   out_3565903804308195890[278] = 0;
   out_3565903804308195890[279] = 0;
   out_3565903804308195890[280] = 0;
   out_3565903804308195890[281] = 0;
   out_3565903804308195890[282] = 0;
   out_3565903804308195890[283] = 0;
   out_3565903804308195890[284] = 0;
   out_3565903804308195890[285] = 1;
   out_3565903804308195890[286] = 0;
   out_3565903804308195890[287] = 0;
   out_3565903804308195890[288] = 0;
   out_3565903804308195890[289] = 0;
   out_3565903804308195890[290] = 0;
   out_3565903804308195890[291] = 0;
   out_3565903804308195890[292] = 0;
   out_3565903804308195890[293] = 0;
   out_3565903804308195890[294] = 0;
   out_3565903804308195890[295] = 0;
   out_3565903804308195890[296] = 0;
   out_3565903804308195890[297] = 0;
   out_3565903804308195890[298] = 0;
   out_3565903804308195890[299] = 0;
   out_3565903804308195890[300] = 0;
   out_3565903804308195890[301] = 0;
   out_3565903804308195890[302] = 0;
   out_3565903804308195890[303] = 0;
   out_3565903804308195890[304] = 1;
   out_3565903804308195890[305] = 0;
   out_3565903804308195890[306] = 0;
   out_3565903804308195890[307] = 0;
   out_3565903804308195890[308] = 0;
   out_3565903804308195890[309] = 0;
   out_3565903804308195890[310] = 0;
   out_3565903804308195890[311] = 0;
   out_3565903804308195890[312] = 0;
   out_3565903804308195890[313] = 0;
   out_3565903804308195890[314] = 0;
   out_3565903804308195890[315] = 0;
   out_3565903804308195890[316] = 0;
   out_3565903804308195890[317] = 0;
   out_3565903804308195890[318] = 0;
   out_3565903804308195890[319] = 0;
   out_3565903804308195890[320] = 0;
   out_3565903804308195890[321] = 0;
   out_3565903804308195890[322] = 0;
   out_3565903804308195890[323] = 1;
}
void h_4(double *state, double *unused, double *out_5629826972556855355) {
   out_5629826972556855355[0] = state[6] + state[9];
   out_5629826972556855355[1] = state[7] + state[10];
   out_5629826972556855355[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3872811353751319758) {
   out_3872811353751319758[0] = 0;
   out_3872811353751319758[1] = 0;
   out_3872811353751319758[2] = 0;
   out_3872811353751319758[3] = 0;
   out_3872811353751319758[4] = 0;
   out_3872811353751319758[5] = 0;
   out_3872811353751319758[6] = 1;
   out_3872811353751319758[7] = 0;
   out_3872811353751319758[8] = 0;
   out_3872811353751319758[9] = 1;
   out_3872811353751319758[10] = 0;
   out_3872811353751319758[11] = 0;
   out_3872811353751319758[12] = 0;
   out_3872811353751319758[13] = 0;
   out_3872811353751319758[14] = 0;
   out_3872811353751319758[15] = 0;
   out_3872811353751319758[16] = 0;
   out_3872811353751319758[17] = 0;
   out_3872811353751319758[18] = 0;
   out_3872811353751319758[19] = 0;
   out_3872811353751319758[20] = 0;
   out_3872811353751319758[21] = 0;
   out_3872811353751319758[22] = 0;
   out_3872811353751319758[23] = 0;
   out_3872811353751319758[24] = 0;
   out_3872811353751319758[25] = 1;
   out_3872811353751319758[26] = 0;
   out_3872811353751319758[27] = 0;
   out_3872811353751319758[28] = 1;
   out_3872811353751319758[29] = 0;
   out_3872811353751319758[30] = 0;
   out_3872811353751319758[31] = 0;
   out_3872811353751319758[32] = 0;
   out_3872811353751319758[33] = 0;
   out_3872811353751319758[34] = 0;
   out_3872811353751319758[35] = 0;
   out_3872811353751319758[36] = 0;
   out_3872811353751319758[37] = 0;
   out_3872811353751319758[38] = 0;
   out_3872811353751319758[39] = 0;
   out_3872811353751319758[40] = 0;
   out_3872811353751319758[41] = 0;
   out_3872811353751319758[42] = 0;
   out_3872811353751319758[43] = 0;
   out_3872811353751319758[44] = 1;
   out_3872811353751319758[45] = 0;
   out_3872811353751319758[46] = 0;
   out_3872811353751319758[47] = 1;
   out_3872811353751319758[48] = 0;
   out_3872811353751319758[49] = 0;
   out_3872811353751319758[50] = 0;
   out_3872811353751319758[51] = 0;
   out_3872811353751319758[52] = 0;
   out_3872811353751319758[53] = 0;
}
void h_10(double *state, double *unused, double *out_47996974574044037) {
   out_47996974574044037[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_47996974574044037[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_47996974574044037[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5983294384287388784) {
   out_5983294384287388784[0] = 0;
   out_5983294384287388784[1] = 9.8100000000000005*cos(state[1]);
   out_5983294384287388784[2] = 0;
   out_5983294384287388784[3] = 0;
   out_5983294384287388784[4] = -state[8];
   out_5983294384287388784[5] = state[7];
   out_5983294384287388784[6] = 0;
   out_5983294384287388784[7] = state[5];
   out_5983294384287388784[8] = -state[4];
   out_5983294384287388784[9] = 0;
   out_5983294384287388784[10] = 0;
   out_5983294384287388784[11] = 0;
   out_5983294384287388784[12] = 1;
   out_5983294384287388784[13] = 0;
   out_5983294384287388784[14] = 0;
   out_5983294384287388784[15] = 1;
   out_5983294384287388784[16] = 0;
   out_5983294384287388784[17] = 0;
   out_5983294384287388784[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5983294384287388784[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5983294384287388784[20] = 0;
   out_5983294384287388784[21] = state[8];
   out_5983294384287388784[22] = 0;
   out_5983294384287388784[23] = -state[6];
   out_5983294384287388784[24] = -state[5];
   out_5983294384287388784[25] = 0;
   out_5983294384287388784[26] = state[3];
   out_5983294384287388784[27] = 0;
   out_5983294384287388784[28] = 0;
   out_5983294384287388784[29] = 0;
   out_5983294384287388784[30] = 0;
   out_5983294384287388784[31] = 1;
   out_5983294384287388784[32] = 0;
   out_5983294384287388784[33] = 0;
   out_5983294384287388784[34] = 1;
   out_5983294384287388784[35] = 0;
   out_5983294384287388784[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5983294384287388784[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5983294384287388784[38] = 0;
   out_5983294384287388784[39] = -state[7];
   out_5983294384287388784[40] = state[6];
   out_5983294384287388784[41] = 0;
   out_5983294384287388784[42] = state[4];
   out_5983294384287388784[43] = -state[3];
   out_5983294384287388784[44] = 0;
   out_5983294384287388784[45] = 0;
   out_5983294384287388784[46] = 0;
   out_5983294384287388784[47] = 0;
   out_5983294384287388784[48] = 0;
   out_5983294384287388784[49] = 0;
   out_5983294384287388784[50] = 1;
   out_5983294384287388784[51] = 0;
   out_5983294384287388784[52] = 0;
   out_5983294384287388784[53] = 1;
}
void h_13(double *state, double *unused, double *out_7941151597873080648) {
   out_7941151597873080648[0] = state[3];
   out_7941151597873080648[1] = state[4];
   out_7941151597873080648[2] = state[5];
}
void H_13(double *state, double *unused, double *out_660537528418986957) {
   out_660537528418986957[0] = 0;
   out_660537528418986957[1] = 0;
   out_660537528418986957[2] = 0;
   out_660537528418986957[3] = 1;
   out_660537528418986957[4] = 0;
   out_660537528418986957[5] = 0;
   out_660537528418986957[6] = 0;
   out_660537528418986957[7] = 0;
   out_660537528418986957[8] = 0;
   out_660537528418986957[9] = 0;
   out_660537528418986957[10] = 0;
   out_660537528418986957[11] = 0;
   out_660537528418986957[12] = 0;
   out_660537528418986957[13] = 0;
   out_660537528418986957[14] = 0;
   out_660537528418986957[15] = 0;
   out_660537528418986957[16] = 0;
   out_660537528418986957[17] = 0;
   out_660537528418986957[18] = 0;
   out_660537528418986957[19] = 0;
   out_660537528418986957[20] = 0;
   out_660537528418986957[21] = 0;
   out_660537528418986957[22] = 1;
   out_660537528418986957[23] = 0;
   out_660537528418986957[24] = 0;
   out_660537528418986957[25] = 0;
   out_660537528418986957[26] = 0;
   out_660537528418986957[27] = 0;
   out_660537528418986957[28] = 0;
   out_660537528418986957[29] = 0;
   out_660537528418986957[30] = 0;
   out_660537528418986957[31] = 0;
   out_660537528418986957[32] = 0;
   out_660537528418986957[33] = 0;
   out_660537528418986957[34] = 0;
   out_660537528418986957[35] = 0;
   out_660537528418986957[36] = 0;
   out_660537528418986957[37] = 0;
   out_660537528418986957[38] = 0;
   out_660537528418986957[39] = 0;
   out_660537528418986957[40] = 0;
   out_660537528418986957[41] = 1;
   out_660537528418986957[42] = 0;
   out_660537528418986957[43] = 0;
   out_660537528418986957[44] = 0;
   out_660537528418986957[45] = 0;
   out_660537528418986957[46] = 0;
   out_660537528418986957[47] = 0;
   out_660537528418986957[48] = 0;
   out_660537528418986957[49] = 0;
   out_660537528418986957[50] = 0;
   out_660537528418986957[51] = 0;
   out_660537528418986957[52] = 0;
   out_660537528418986957[53] = 0;
}
void h_14(double *state, double *unused, double *out_1102431323715996841) {
   out_1102431323715996841[0] = state[6];
   out_1102431323715996841[1] = state[7];
   out_1102431323715996841[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6955599786046692054) {
   out_6955599786046692054[0] = 0;
   out_6955599786046692054[1] = 0;
   out_6955599786046692054[2] = 0;
   out_6955599786046692054[3] = 0;
   out_6955599786046692054[4] = 0;
   out_6955599786046692054[5] = 0;
   out_6955599786046692054[6] = 1;
   out_6955599786046692054[7] = 0;
   out_6955599786046692054[8] = 0;
   out_6955599786046692054[9] = 0;
   out_6955599786046692054[10] = 0;
   out_6955599786046692054[11] = 0;
   out_6955599786046692054[12] = 0;
   out_6955599786046692054[13] = 0;
   out_6955599786046692054[14] = 0;
   out_6955599786046692054[15] = 0;
   out_6955599786046692054[16] = 0;
   out_6955599786046692054[17] = 0;
   out_6955599786046692054[18] = 0;
   out_6955599786046692054[19] = 0;
   out_6955599786046692054[20] = 0;
   out_6955599786046692054[21] = 0;
   out_6955599786046692054[22] = 0;
   out_6955599786046692054[23] = 0;
   out_6955599786046692054[24] = 0;
   out_6955599786046692054[25] = 1;
   out_6955599786046692054[26] = 0;
   out_6955599786046692054[27] = 0;
   out_6955599786046692054[28] = 0;
   out_6955599786046692054[29] = 0;
   out_6955599786046692054[30] = 0;
   out_6955599786046692054[31] = 0;
   out_6955599786046692054[32] = 0;
   out_6955599786046692054[33] = 0;
   out_6955599786046692054[34] = 0;
   out_6955599786046692054[35] = 0;
   out_6955599786046692054[36] = 0;
   out_6955599786046692054[37] = 0;
   out_6955599786046692054[38] = 0;
   out_6955599786046692054[39] = 0;
   out_6955599786046692054[40] = 0;
   out_6955599786046692054[41] = 0;
   out_6955599786046692054[42] = 0;
   out_6955599786046692054[43] = 0;
   out_6955599786046692054[44] = 1;
   out_6955599786046692054[45] = 0;
   out_6955599786046692054[46] = 0;
   out_6955599786046692054[47] = 0;
   out_6955599786046692054[48] = 0;
   out_6955599786046692054[49] = 0;
   out_6955599786046692054[50] = 0;
   out_6955599786046692054[51] = 0;
   out_6955599786046692054[52] = 0;
   out_6955599786046692054[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_6728567055571296281) {
  err_fun(nom_x, delta_x, out_6728567055571296281);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1359217107745375791) {
  inv_err_fun(nom_x, true_x, out_1359217107745375791);
}
void pose_H_mod_fun(double *state, double *out_7644618563595227330) {
  H_mod_fun(state, out_7644618563595227330);
}
void pose_f_fun(double *state, double dt, double *out_5814374477757895690) {
  f_fun(state,  dt, out_5814374477757895690);
}
void pose_F_fun(double *state, double dt, double *out_3565903804308195890) {
  F_fun(state,  dt, out_3565903804308195890);
}
void pose_h_4(double *state, double *unused, double *out_5629826972556855355) {
  h_4(state, unused, out_5629826972556855355);
}
void pose_H_4(double *state, double *unused, double *out_3872811353751319758) {
  H_4(state, unused, out_3872811353751319758);
}
void pose_h_10(double *state, double *unused, double *out_47996974574044037) {
  h_10(state, unused, out_47996974574044037);
}
void pose_H_10(double *state, double *unused, double *out_5983294384287388784) {
  H_10(state, unused, out_5983294384287388784);
}
void pose_h_13(double *state, double *unused, double *out_7941151597873080648) {
  h_13(state, unused, out_7941151597873080648);
}
void pose_H_13(double *state, double *unused, double *out_660537528418986957) {
  H_13(state, unused, out_660537528418986957);
}
void pose_h_14(double *state, double *unused, double *out_1102431323715996841) {
  h_14(state, unused, out_1102431323715996841);
}
void pose_H_14(double *state, double *unused, double *out_6955599786046692054) {
  H_14(state, unused, out_6955599786046692054);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
