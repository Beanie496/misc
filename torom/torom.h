void handleArgs(int argc, char *argv[]);
char *torom(int num);
int strtonum(char *str);

typedef struct {
	char *firstArg;
} Args;

extern Args args;
