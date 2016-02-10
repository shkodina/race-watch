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
        BoardMatrix[i + BOARDCOLORMEMLEN] = 0; // так как общая матрица
                                                //  вдвое больше цветной
    }
}

//****************************************************************************

void print1LongLine(  char * message, char meslen, 
                                    char color1s,
                                    char line)
{
    unsigned int    color_matrix_index = 0,
                    color_matrix_end = 0;

    // тут берется реальный анси код символа и его код является адресом
    // в самодельном алфавите только учитываем что самодельный алфавит
    // адресуется с 0 в то время как минимальный код символа анси это 1

    // соберем первую строку

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
                GreenBoardMatrix[color_matrix_index] = letter[j];  // запишем в зеленую
            if ((color1s & COLOR_RED) == COLOR_RED)
                RedBoardMatrix[color_matrix_index] = letter[j]; // запишем в красную
            color_matrix_index++;
            // возможно место на полосе закончилось
            if (color_matrix_index >= color_matrix_end)
              break;
        }
        color_matrix_index++; // разделим символы
        // возможно место на полосе закончилось
        if (color_matrix_index >= color_matrix_end)
          break;
    }
}

//****************************************************************************

void print1ShortLine(char * message, char meslen, char color, char line)
{
    unsigned int    color_matrix_index = 0,
                    color_matrix_end = 0;

    // тут берется реальный анси код символа и его код является адресом
    // в самодельном алфавите только учитываем что самодельный алфавит
    // адресуется с 0 в то время как минимальный код символа анси это 1

    // зададим границы памяти
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
                GreenBoardMatrix[color_matrix_index] = letter[j];  // запишем в зеленую
            if ((color & COLOR_RED) == COLOR_RED)
                RedBoardMatrix[color_matrix_index] = letter[j]; // запишем в красную
            color_matrix_index++;
            // возможно место на полосе закончилось
            if (color_matrix_index >= color_matrix_end)
              break;
        }
        color_matrix_index++; // разделим символы
        // возможно место на полосе закончилось
        if (color_matrix_index >= color_matrix_end)
          break;
    }
}

//****************************************************************************

void print2line ( char * message1top, char mes1len, char color1,
                  char * message2bot, char mes2len, char color2)
{
    cleanAllBoardMatrix();

    // соберем первую строку
    print1LongLine(message1top, mes1len, color1, 1);

    // соберем вторую строку
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

    // соберем первую строку
    print1ShortLine(message1topleft, mes1len, color1s, 1);

    // соберем вторую строку
    print1ShortLine(message2topright, mes2len, color2s, 2);

    // соберем третью строку
    print1ShortLine(message3botleft, mes3len, color3s, 3);

    // соберем четвертую строку
    print1ShortLine(message4botright, mes4len, color4s, 4);

    putGreenColorMatrixAsString();
    putRedColorMatrixAsString();

}

//****************************************************************************

void putGreenColorMatrixAsString()
{
    // функция расчитана на 8 чип всего
    // т е одна линия одной доски
    int bmp = 0;
    for (int i = 0; i < BOARDCOLORMEMLEN; i++){
        BoardMatrix[bmp++] = GreenBoardMatrix[i];
        if(bmp == BOARDCHIPCOLORMEM)        // переход с 1 на 2-ой чип
            bmp = BOARDCHIPCOLORMEM * 2;
        if(bmp == (BOARDCHIPCOLORMEM * 3))  // переход с 2 на 5-ый чип
            bmp = (BOARDCHIPCOLORMEM * 8);
        if(bmp == (BOARDCHIPCOLORMEM * 9))  // переход с 5 на 6-ой чип
            bmp = (BOARDCHIPCOLORMEM * 10);
        if(bmp == (BOARDCHIPCOLORMEM * 11)) // переход с 6 на 3-ий чип
            bmp = (BOARDCHIPCOLORMEM * 4);
        if(bmp == (BOARDCHIPCOLORMEM * 5))  // переход с 3 на 4-ий чип
            bmp = (BOARDCHIPCOLORMEM * 6);
        if(bmp == (BOARDCHIPCOLORMEM * 7))  // переход с 4 на 7-ий чип
            bmp = (BOARDCHIPCOLORMEM * 12);
        if(bmp == (BOARDCHIPCOLORMEM * 13))  // переход с 7 на 8-ий чип
            bmp = (BOARDCHIPCOLORMEM * 14);

    }
}

//****************************************************************************

void putRedColorMatrixAsString()
{
    // функция расчитана на 8 чип всего
    // т е одна линия одной доски
    int bmp = BOARDCHIPCOLORMEM;
    for (int i = 0; i < BOARDCOLORMEMLEN; i++){
        BoardMatrix[bmp++] = RedBoardMatrix[i];
        if(bmp == (BOARDCHIPCOLORMEM * 2))        // переход с 1 на 2-ой чип
            bmp = (BOARDCHIPCOLORMEM * 3);
        if(bmp == (BOARDCHIPCOLORMEM * 4))  // переход с 2 на 5-ый чип
            bmp = (BOARDCHIPCOLORMEM * 9);
        if(bmp == (BOARDCHIPCOLORMEM * 10))  // переход с 5 на 6-ой чип
            bmp = (BOARDCHIPCOLORMEM * 11);
        if(bmp == (BOARDCHIPCOLORMEM * 12)) // переход с 6 на 3-ий чип
            bmp = (BOARDCHIPCOLORMEM * 5);
        if(bmp == (BOARDCHIPCOLORMEM * 6))  // переход с 3 на 4-ий чип
            bmp = (BOARDCHIPCOLORMEM * 7);
        if(bmp == (BOARDCHIPCOLORMEM * 8))  // переход с 4 на 7-ий чип
            bmp = (BOARDCHIPCOLORMEM * 13);
        if(bmp == (BOARDCHIPCOLORMEM * 14))  // переход с 7 на 8-ий чип
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
