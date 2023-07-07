#include <stdlib.h>

#include "sunit.h"
#include "torom.h"

static void runAllTests(void);
static int checkFirstArgIsRead();
static int checkFirstArgIsConvertedToNumber();

int testsRun;
int testsPassed;

int main(int argc, char *argv[])
{
	handleArgs(argc, argv);
	runAllTests();
	
	return 0;
}

void runAllTests(void)
{
	RUN_TEST(checkFirstArgIsRead);
	RUN_TEST(checkFirstArgIsConvertedToNumber);
	END_TESTING();
}

int checkFirstArgIsRead()
{
	ASSERT_STREQ(args.firstArg, "12345");
}

int checkFirstArgIsConvertedToNumber()
{
	int num = strtonum(args.firstArg);
	char *str = malloc(sizeof(char) * (strlen(args.firstArg) + 1));
	sprintf(str, "%d", num);
	ASSERT_STREQ(str, args.firstArg);
}
