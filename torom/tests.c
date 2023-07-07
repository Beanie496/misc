#include "sunit.h"
#include "torom.h"

static void runAllTests(void);
static int checkFirstArgIsRead();

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
	END_TESTING();
}

int checkFirstArgIsRead()
{
	ASSERT_STREQ(args.firstArg, "12345");
}
