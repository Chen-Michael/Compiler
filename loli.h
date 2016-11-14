FILE *fin;
enum {cacheLength = 100, idLength = 50, reservedLength = 3};
char idCache[idLength + 1];
char charCache[cacheLength];
char ch = ' ';
char prevCh = ' ';

enum symbol{
	null, ident, excep, number,
	addi, subs, mult, divi, assign,
	gt, ge, lt, le, equ, nequ,
	input, output,
	comma, chara, strings, semicon, lparen, rparen, lbrac, rbrac,
	rMin,
	rBreak, rChar, rContinue, rElse, rExtern, rIf, rIn, rInt, rOut, rReturn, rString, rVoid, rWhile,
	rMax
};

char reservedName[reservedLength][idLength] = {
	"int", "if", "else"
};

enum symbol reservedSymbol[reservedLength] = {
	rInt, rIf, rElse
};

int lineNumber = 0;
int lineLength = 0;
int cacheIndex = 0;

struct tokenStruct *headToken    = NULL;
struct tokenStruct *currentToken = NULL;
struct tokenStruct *prevToken    = NULL;

typedef struct tokenStruct {
	int type;
	char *name;
	int value;
	struct tokenStruct *prev;
	struct tokenStruct *next;
} token;