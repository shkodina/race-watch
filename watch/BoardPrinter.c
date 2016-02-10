//---------------------------------------------------------------------------

#include "abc.h"
#include "BoardPrinter.h"

static uchar GreenBoardMatrix[BOARDCOLORMEMLEN];
static uchar RedBoardMatrix[BOARDCOLORMEMLEN];
static uchar BoardMatrix[BOARDMEMLEN];

const static uchar GREEN_COLOR = COLOR_GREEN;
const static uchar RED_COLOR = COLOR_RED;
const static uchar YELOW_COLOR = COLOR_YELOW;


//***************************************************************************

uchar * getMainMatrix()
{
	return BoardMatrix;
}

//***************************************************************************

void cleanMatrix(uchar * matrix, int len)
{
    for (int i = 0; i < len; i++)
        matrix[i] = 0;
}

//***************************************************************************

void cleanAllBoardMatrix()
{
    for (int i = 0; i < BOARDCOLORMEMLEN; i++){
        GreenBoardMatrix[i] = 0;
        RedBoardMatrix[i] = 0;
        BoardMatrix[i] = 0;
        BoardMatrix[i + BOARDCOLORMEMLEN] = 0; // ��� ��� ����� �������
                                                //  ����� ������ �������
    }
}

//****************************************************************************

void print1LongLine(  char * message, char meslen, 
                                    char color1s,
                                    char line)
{
    unsigned int    color_matrix_index = 0,
                    color_matrix_end = 0;

    // ��� ������� �������� ���� ��� ������� � ��� ��� �������� �������
    // � ����������� �������� ������ ��������� ��� ����������� �������
    // ���������� � 0 � �� ����� ��� ����������� ��� ������� ���� ��� 1

    // ������� ������ ������

    if (line == 1){
        color_matrix_index = 0;
        color_matrix_end = BOARDCOLORMEMLEN / 2;
    }

    if (line == 2){
        color_matrix_index = BOARDCOLORMEMLEN / 2;
        color_matrix_end = BOARDCOLORMEMLEN;
    }


    for (unsigned int i = 0; i < meslen; i++){
        int lpos = (unsigned char)(message[i]) - 1;
        if (lpos > 255)
            continue;
        puchar letter = Alphabate[lpos];
        if (!letter)
            continue;
        for (unsigned char j = 1; j <= (unsigned char)(letter[0]); j++ ){
            if ((color1s & GREEN_COLOR) == GREEN_COLOR)
                GreenBoardMatrix[color_matrix_index] = letter[j];  // ������� � �������
            if ((color1s & COLOR_RED) == COLOR_RED)
                RedBoardMatrix[color_matrix_index] = letter[j]; // ������� � �������
            color_matrix_index++;
            // �������� ����� �� ������ �����������
            if (color_matrix_index >= color_matrix_end)
              break;
        }
        color_matrix_index++; // �������� �������
        // �������� ����� �� ������ �����������
        if (color_matrix_index >= color_matrix_end)
          break;
    }
}

//****************************************************************************

void print1ShortLine(char * message, char meslen, char color, char line)
{
    unsigned int    color_matrix_index = 0,
                    color_matrix_end = 0;

    // ��� ������� �������� ���� ��� ������� � ��� ��� �������� �������
    // � ����������� �������� ������ ��������� ��� ����������� �������
    // ���������� � 0 � �� ����� ��� ����������� ��� ������� ���� ��� 1

    // ������� ������� ������
    color_matrix_index = (BOARDCOLORMEMLEN / 4) * line - BOARDCOLORMEMLEN / 4;
    color_matrix_end = (BOARDCOLORMEMLEN / 4) * line;

    for (unsigned int i = 0; i < meslen; i++){
        int lpos = (unsigned char)(message[i]) - 1;
        if (lpos > 255)
            continue;
        puchar letter = Alphabate[lpos];
        if (!letter)
            continue;
        for (unsigned char j = 1; j <= (unsigned char)(letter[0]); j++ ){
            if ((color & GREEN_COLOR) == GREEN_COLOR)
                GreenBoardMatrix[color_matrix_index] = letter[j];  // ������� � �������
            if ((color & COLOR_RED) == COLOR_RED)
                RedBoardMatrix[color_matrix_index] = letter[j]; // ������� � �������
            color_matrix_index++;
            // �������� ����� �� ������ �����������
            if (color_matrix_index >= color_matrix_end)
              break;
        }
        color_matrix_index++; // �������� �������
        // �������� ����� �� ������ �����������
        if (color_matrix_index >= color_matrix_end)
          break;
    }
}

//****************************************************************************

void print2line ( char * message1top, char mes1len, char color1,
                  char * message2bot, char mes2len, char color2)
{
    cleanAllBoardMatrix();

    // ������� ������ ������
    print1LongLine(message1top, mes1len, color1, 1);

    // ������� ������ ������
    print1LongLine(message2bot, mes2len, color2, 2);

    putGreenColorMatrixAsString();
    putRedColorMatrixAsString();

}

//****************************************************************************

void print4line ( char * message1topleft, char mes1len, char color1s,
                  char * message2topright, char mes2len, char color2s,
                  char * message3botleft, char mes3len, char color3s,
                  char * message4botright, char mes4len, char color4s)
{
    cleanAllBoardMatrix();

    // ������� ������ ������
    print1ShortLine(message1topleft, mes1len, color1s, 1);

    // ������� ������ ������
    print1ShortLine(message2topright, mes2len, color2s, 2);

    // ������� ������ ������
    print1ShortLine(message3botleft, mes3len, color3s, 3);

    // ������� ��������� ������
    print1ShortLine(message4botright, mes4len, color4s, 4);

    putGreenColorMatrixAsString();
    putRedColorMatrixAsString();

}

//****************************************************************************

void putGreenColorMatrixAsString()
{
    // ������� ��������� �� 8 ��� �����
    // � � ���� ����� ����� �����
    int bmp = 0;
    for (int i = 0; i < BOARDCOLORMEMLEN; i++){
        BoardMatrix[bmp++] = GreenBoardMatrix[i];
        if(bmp == BOARDCHIPCOLORMEM)        // ������� � 1 �� 2-�� ���
            bmp = BOARDCHIPCOLORMEM * 2;
        if(bmp == (BOARDCHIPCOLORMEM * 3))  // ������� � 2 �� 5-�� ���
            bmp = (BOARDCHIPCOLORMEM * 8);
        if(bmp == (BOARDCHIPCOLORMEM * 9))  // ������� � 5 �� 6-�� ���
            bmp = (BOARDCHIPCOLORMEM * 10);
        if(bmp == (BOARDCHIPCOLORMEM * 11)) // ������� � 6 �� 3-�� ���
            bmp = (BOARDCHIPCOLORMEM * 4);
        if(bmp == (BOARDCHIPCOLORMEM * 5))  // ������� � 3 �� 4-�� ���
            bmp = (BOARDCHIPCOLORMEM * 6);
        if(bmp == (BOARDCHIPCOLORMEM * 7))  // ������� � 4 �� 7-�� ���
            bmp = (BOARDCHIPCOLORMEM * 12);
        if(bmp == (BOARDCHIPCOLORMEM * 13))  // ������� � 7 �� 8-�� ���
            bmp = (BOARDCHIPCOLORMEM * 14);

    }
}

//****************************************************************************

void putRedColorMatrixAsString()
{
    // ������� ��������� �� 8 ��� �����
    // � � ���� ����� ����� �����
    int bmp = BOARDCHIPCOLORMEM;
    for (int i = 0; i < BOARDCOLORMEMLEN; i++){
        BoardMatrix[bmp++] = RedBoardMatrix[i];
        if(bmp == (BOARDCHIPCOLORMEM * 2))        // ������� � 1 �� 2-�� ���
            bmp = (BOARDCHIPCOLORMEM * 3);
        if(bmp == (BOARDCHIPCOLORMEM * 4))  // ������� � 2 �� 5-�� ���
            bmp = (BOARDCHIPCOLORMEM * 9);
        if(bmp == (BOARDCHIPCOLORMEM * 10))  // ������� � 5 �� 6-�� ���
            bmp = (BOARDCHIPCOLORMEM * 11);
        if(bmp == (BOARDCHIPCOLORMEM * 12)) // ������� � 6 �� 3-�� ���
            bmp = (BOARDCHIPCOLORMEM * 5);
        if(bmp == (BOARDCHIPCOLORMEM * 6))  // ������� � 3 �� 4-�� ���
            bmp = (BOARDCHIPCOLORMEM * 7);
        if(bmp == (BOARDCHIPCOLORMEM * 8))  // ������� � 4 �� 7-�� ���
            bmp = (BOARDCHIPCOLORMEM * 13);
        if(bmp == (BOARDCHIPCOLORMEM * 14))  // ������� � 7 �� 8-�� ���
            bmp = (BOARDCHIPCOLORMEM * 15);

    }
}
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
