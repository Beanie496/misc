#include <stdlib.h>

#include "sunit.h"
#include "torom.h"

static void runAllTests(void);
static int firstArgIsConvertedToNumber();
static int eachBaseNumberIsConvertedCorrectly();
static int twoOfEachBaseNumberIsConvertedCorrectly();

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
	RUN_TEST(firstArgIsConvertedToNumber);
	RUN_TEST(eachBaseNumberIsConvertedCorrectly);
	RUN_TEST(twoOfEachBaseNumberIsConvertedCorrectly);
	TEST_SUMMARY();
}

int firstArgIsConvertedToNumber()
{
	int argAsNum = strtonum(args.firstArg);
	char *arg = malloc(sizeof(char) * (strlen(args.firstArg) + 1));
	sprintf(arg, "%d", argAsNum);
	ASSERT_STREQ(arg, args.firstArg);
	free(arg);
	return 1;
}

int eachBaseNumberIsConvertedCorrectly()
{
	ASSERT_STREQ(torom(1000), "M");
	ASSERT_STREQ(torom(500), "D");
	ASSERT_STREQ(torom(100), "C");
	ASSERT_STREQ(torom(50), "L");
	ASSERT_STREQ(torom(10), "X");
	ASSERT_STREQ(torom(5), "V");
	ASSERT_STREQ(torom(1), "I");
	return 1;
}
