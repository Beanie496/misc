void handleArgs(int argc, char *argv[]);
int strtonum(char *str);

typedef struct {
	char *firstArg;
} Args;

extern Args args;
