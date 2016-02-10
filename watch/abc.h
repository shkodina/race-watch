//---------------------------------------------------------------------------

#ifndef ABCH
#define ABCH
//---------------------------------------------------------------------------

typedef unsigned char uchar;
typedef unsigned char * puchar;

// L[6] = {6, },

uchar

// ��������� ���������

LA[6] = {5, 120, 20, 18, 20, 120},     // A
LB[6] = {5, 126, 74, 74, 76, 48},      // B
LC[6] = {5, 60, 66, 66, 66, 36},       // C
LD[6] = {5, 126, 66, 66, 66, 60},      // D
LE[5] = {4, 126, 74, 74, 66},          // E
LF[5] = {4, 126, 18, 18, 2},           // F
LG[6] = {5, 60, 66, 82, 82, 52},       // G
LH[5] = {4, 126, 16, 16, 126},         // H
LI[4] = {3, 66, 126, 66},              // I
LJ[5] = {4, 32, 66, 62, 2},            // J
LK[5] = {4, 126, 8, 20, 98},           // K
LL[5] = {4, 126, 64, 64, 96},          // L
LM[6] = {5, 126, 8, 16, 8, 126},       // M
LN[6] = {5, 126, 8, 16, 32, 126},      // N
LO[6] = {5, 60, 66, 66, 66, 60},       // O
LP[5] = {4, 126, 18, 18, 12},          // P
LQ[6] = {5, 60, 66, 82, 34, 92},       // Q
LR[5] = {4, 126, 18, 50, 76},          // R
LS[6] = {5, 36, 74, 82, 82, 36},       // S
LT[6] = {5, 6, 2, 126, 2, 6},          // T
LU[6] = {5, 62, 64, 64, 64, 62},       // U
LV[6] = {5, 30, 32, 64, 32, 30},       // V
LW[6] = {5, 62, 64, 60, 64, 62},       // W
LX[6] = {5, 98, 20, 8, 20, 98},        // X
LY[6] = {5, 14, 16, 96, 16, 14},       // Y
LZ[6] = {5, 98, 82, 74, 70, 66},       // Z

// ��������� ��������

LAl[5] = {4, 32, 84, 84, 120},     // a
LBl[4] = {3, 124, 80, 96},      // b
LCl[4] = {3, 56, 68, 40},       // C
LDl[4] = {3, 96, 80, 124},      // D
LEl[4] = {3, 56, 84, 76},          // E
LFl[5] = {4, 16, 120, 20, 4},           // F
LGl[5] = {4, 16, 168, 168, 112},       // G
LHl[4] = {3, 124, 16, 96},         // H
LIl[2] = {1, 116},              // I
LJl[4] = {3, 32, 64, 60},            // J
LKl[4] = {3, 124, 16, 108},           // K
LLl[2] = {1, 124},          // L
LMl[6] = {5, 124, 4, 120, 4, 120},       // M
LNl[4] = {3, 124, 4, 120},      // N
LOl[4] = {3, 56, 68, 56},       // O
LPl[4] = {3, 124, 20, 12},          // P
LQl[5] = {4, 56, 68, 36, 88},       // Q
LRl[4] = {3, 124, 4, 24},          // R
LSl[4] = {3, 72, 84, 36},       // S
LTl[4] = {3, 8, 60, 72},          // T
LUl[4] = {3, 60, 64, 60},       // U
LVl[4] = {3, 28, 96, 28},       // V
LWl[6] = {5, 60, 64, 56, 64, 60},       // W
LXl[5] = {4, 108, 16, 108},        // X
LYl[4] = {3, 76, 80, 60},       // Y
LZl[4] = {3, 100, 84, 76},       // Z

// ������� ���������

LRA[6] = {5, 120, 20, 18, 20, 120}, // �
LRB[5] = {4, 126, 74, 74, 50},      // �
LRV[6] = {5,126, 74, 74, 76, 48},   // �
LRG[5] = {4, 126, 2, 2, 6},         // �
LRD[6] = {5,96, 62, 34, 62, 96},    // �
LRE[6] = {5, 126, 74, 74, 66},      // �
LRHG[6] = {5, 118, 8, 126, 8, 118}, // �
LRZ[6] = {5, 36, 66, 74, 74, 52},   // �
LRI[6] = {5, 126, 32, 16, 8, 126},  // �
LRIi[6] = {5, 126, 32, 18, 8, 126}, // �
LRK[5] = {4, 126, 8, 20, 98},       // �
LRL[6] = {5,64, 62, 2, 2, 126},     // �
LRM[6] = {5, 126, 8, 16, 8, 126},   // �
LRN[5] = {4, 126, 8, 8, 126},       // �
LRO[6] = {5, 60, 66, 66, 66, 60},   // �
LRP[5] = {4, 126, 2, 2, 126},       // �
LRR[5] = {4, 126, 18, 18, 12},      // �
LRS[6] = {5, 60, 66, 66, 66, 36},   // �
LRT[6] = {5, 6, 2, 126, 2, 6},      // �
LRU[5] = {4, 38, 72, 72, 62},       // �
LRF[6] = {5, 24, 36, 126, 36, 24},   // �
LRH[6] = {5, 98, 20, 8, 20, 98},    // �
LRC[6] = {5, 126, 64, 64, 126, 192},// �
LR4[5] = {4, 14, 16, 16, 126},      // �
LRSH[6] = {5,126, 64, 120, 64, 126}, // �
LRSCH[7] = {6, 126, 64, 120, 64, 126, 192}, // �
LRTZ[6] = {5, 2, 126, 72, 72, 48},  // �
LRII[7] = {6, 126, 72, 72, 48, 0, 126},  // �
LRMZ[5] = {4, 126, 72, 72, 48},  // �
LREE[6] = {5,36, 66, 74, 74, 60},  // �
LRYU[7] = {6, 126, 16, 60, 66, 66, 60},  // �
LRYA[5] = {4, 76, 50, 18, 126},  // �

// ������� ��������

LRAl[5] = {4, 32, 84, 84, 120},     // �
LRBl[4] = {3, 124, 84, 100},        // �
LRVl[4] = {3, 124, 84, 108},        // �
LRGl[4] = {3, 124, 4, 4},           // �
LRDl[6] = {5, 96, 62, 34, 62, 96},           // �
LREl[4] = {3, 56, 84, 76},          // �
LRHGl[6] = {5, 68, 40, 124, 40, 68},// �
LRZl[5] = {4, 40, 68, 84, 40},      // �
LRIl[5] = {4, 124, 32, 16, 124},    // �
LRIil[5] = {4, 124, 32, 16, 124},   // �
LRKl[4] = {3, 124, 16, 108},        // �
LRLl[5] = {4, 64, 56, 4, 124},      // �
LRMl[6] = {5, 124, 8, 112, 8, 124}, // �
LRNl[4] = {3, 124, 16, 124},        // �
LROl[4] = {3, 56, 68, 56},          // �
LRPl[4] = {3, 124, 4, 120},         // �
LRRl[4] = {3, 124, 20, 12},         // �
LRSl[4] = {3, 56, 68, 40},          // �
LRTl[4] = {3, 4, 124, 4},           // �
LRUl[4] = {3, 76, 80, 60},          // �
LRFl[6] = {5, 16, 40, 124, 40, 16}, // �
LRHl[4] = {3, 108, 16, 108},        // �
LRCl[5] = {4, 124, 64, 124, 192},   // �
LR4l[4] = {3, 12, 16, 124},         // �
LRSHl[6] = {5,124, 64, 112, 64, 124},   // �
LRSCHl[7] = {6, 124, 64, 112, 64, 124, 192},// �
LRTZl[5] = {4, 4, 124, 80, 96},         // �
LRIIl[6] = {5, 124, 80, 96, 0, 124},    // �
LRMZl[4] = {3, 124, 80, 96},          // �
LREEl[5] = {4, 40, 68, 84, 56},          // �
LRYUl[6] = {5, 124, 16, 56, 68, 56},    // �
LRYAl[5] = {4, 92, 36, 124},            // �

// ����� ����������

SPASE[3] = {2, 0, 0},
DPOINT[2] = {1, 40},
BACKSLESH[3] = {2, 112, 14},
OPOINT[2] = {1, 64},

// �����

LN0[5] = {4, 60, 66, 66, 60},
LN1[3] = {2, 4, 126},
LN2[5] = {4, 68, 98, 82, 76},
LN3[5] = {4, 36, 66, 74, 52},
LN4[5] = {4, 14, 8, 8, 126},
LN5[5] = {4, 78, 74, 74, 50},
LN6[5] = {4, 60, 74, 74, 50},
LN7[5] = {4, 2, 114, 10, 6},
LN8[5] = {4, 52, 74, 74, 52},
LN9[5] = {4, 76, 82, 82, 60};


puchar Alphabate[255] =
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,          // 1 - 10
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 11 - 20
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 21 - 30
0, SPASE, 0, 0, 0, 0, 0, 0, 0, 0,           // 31 - 40
0, 0, 0, 0, 0, OPOINT, BACKSLESH, LN0, LN1, LN2,           // 41 - 50
LN3, LN4, LN5, LN6, LN7, LN8, LN9, DPOINT, 0, 0,  // 51 - 60
0, 0, 0, 0, LA, LB, LC, LD, LE, LF,     // 61 - 70
LG, LH, LI, LJ, LK, LL, LM, LN, LO, LP, // 71 - 80
LQ, LR, LS, LT, LU, LV, LW, LX, LY, LZ, // 81 - 90
0, 0, 0, 0, 0, 0, LAl, LBl, LCl, LDl,     // 91 - 100
LEl, LFl, LGl, LHl, LIl, LJl, LKl, LLl, LMl, LNl,  // 101 - 110
LOl, LPl, LQl, LRl, LSl, LTl, LUl, LVl, LWl, LXl, // 111 - 120
LYl, LZl, 0, 0, 0, 0, 0, 0, 0, 0,           // 121 - 130
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 131 - 140
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 141 - 150
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 151 - 160
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 161 - 170
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 171 - 180
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,           // 181 - 190
0, LRA, LRB, LRV, LRG, LRD, LRE, LRHG, LRZ, LRI, // 191 - 200
LRIi, LRK, LRL, LRM, LRN, LRO, LRP, LRR, LRS, LRT, // 201 - 210
LRU, LRF, LRH, LRC, LR4, LRSH, LRSCH, LRTZ, LRII, LRMZ, // 211 - 220
LREE, LRYU, LRYA, LRAl, LRBl, LRVl, LRGl, LRDl, LREl, LRHGl,  // 221 - 230
LRZl, LRIl, LRIil, LRKl, LRLl, LRMl, LRNl, LROl, LRPl, LRRl, // 231 - 240
LRSl, LRTl, LRUl, LRFl, LRHl, LRCl, LR4l, LRSHl, LRSCHl, LRTZl, // 241 - 250
LRIIl, LRMZl, LREEl, LRYUl, LRYAl }; // 251 - 255



//---------------------------------------------------------------------------
#endif //ABCH