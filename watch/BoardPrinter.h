//---------------------------------------------------------------------------

#ifndef BoardPrinterH
#define BoardPrinterH
//---------------------------------------------------------------------------

#define BOARDCHIPMAX 8
#define BOARDCHIPMEMLEN 32

#define BOARDMEMLEN 256 // 8 * 32

#define BOARDCHIPCOLORMEM 16
#define BOARDCOLORMEMLEN 128 // 8 * 16

#define BOARDCHIPGREENMEMSTART 0
#define BOARDCHIPREDMEMSTART 16

#define COLOR_GREEN     0x01
#define COLOR_RED       0x02
#define COLOR_YELOW     0x03


//extern uchar GreenBoardMatrix[BOARDCOLORMEMLEN];
//extern uchar RedBoardMatrix[BOARDCOLORMEMLEN];
//extern uchar BoardMatrix[BOARDMEMLEN];
//extern std::string usermessage;
//extern std::string systemmessage;

void print2line(    char * message1top, char mes1len, char color1s,
                    char * message2bot, char mes2len, char color2s);
void print4line(    char * message1topleft, char mes1len, char color1s,
                    char * message2topright, char mes2len, char color2s,
                    char * message3botleft, char mes3len, char color3s,
                    char * message4botright, char mes4len, char color4s);

void cleanMatrix(unsigned char * matrix, int len);
void cleanAllBoardMatrix();
    
void putGreenColorMatrixAsString();
void putRedColorMatrixAsString();

void print1LongLine(char * message1top, char meslen, char color1s, char line);
void print1ShortLine(char * message, char meslen, char color, char line);

unsigned char * getMainMatrix();

#endif
