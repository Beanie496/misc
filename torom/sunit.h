#ifndef SUNIT_INCLUDED
#define SUNIT_INCLUDED

#include <stdio.h>
#include <string.h>

#define BOLD            "\033[1m"
#define RED             "\033[31m"
#define GREEN           "\033[32m"
#define BLUE            "\033[34m"
#define RESET           "\033[m"

#define MSG_PASS(a, msg)\
	fprintf(stderr, GREEN BOLD "PASSED: " RESET __FILE__ ", %d: \'" #a\
			"\' " msg "\n", __LINE__)
#define MSG_FAIL(a, msg)\
	fprintf(stderr, RED BOLD "FAILED: " RESET __FILE__ ", %d: \'" #a\
			"\' " msg "\n", __LINE__)

#define ASSERT(a)\
do {\
	if (a)\
		MSG_PASS(a, "expected true");\
	else\
		MSG_FAIL(a, "expected true");\
	/* syntactic ugliness but it's necessary not to use stack space */\
	return (a != 0);\
} while (0)

#define ASSERT_EQ(a, b)\
do {\
	if (a == b)\
		MSG_PASS(a, "expected to equal \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected to equal \'" #b "\'");\
	return (a == b);\
} while (0)

#define ASSERT_NEQ(a, b)\
do {\
	if (a != b)\
		MSG_PASS(a, "expected not to equal \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected not to equal \'" #b "\'");\
	return (a != b);\
} while (0)

#define ASSERT_GT(a, b)\
do {\
	if (a > b)\
		MSG_PASS(a, "expected to be greater than \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected to be greater than \'" #b "\'");\
	return (a > b);\
} while (0)

#define ASSERT_LT(a, b)\
do {\
	if (a < b)\
		MSG_PASS(a, "expected to be less than \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected to be less than \'" #b "\'");\
	return (a < b);\
} while (0)

#define ASSERT_GEQ(a, b)\
do {\
	if (a >= b)\
		MSG_PASS(a, "expected to be greater than or equal to \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected to be greater than or equal to \'" #b "\'");\
	return (a >= b);\
} while (0)

#define ASSERT_LEQ(a, b)\
do {\
	if (a <= b)\
		MSG_PASS(a, "expected to be less than or equal to \'" #b "\'");\
	else\
		MSG_FAIL(a, "expected to be less than or equal to \'" #b "\'");\
	return (a <= b);\
} while (0)

#define ASSERT_STREQ(a, b)\
do {\
	if (!a) {\
		MSG_FAIL(a, "is null");\
		return 0;\
	}\
	if (!b) {\
		MSG_FAIL(b, "is null");\
		return 0;\
	}\
	if (!strcmp(a, b)) {\
		MSG_PASS(a, "expected to equal \'" #b "\'");\
		return 1;\
	} else {\
		MSG_FAIL(a, "expected to equal \'" #b "\'");\
		return 0;\
	}\
} while (0)

#define ASSERT_STRNEQ(a, b)\
do {\
	if (!a) {\
		MSG_FAIL(a, "is null");\
		return 0;\
	}\
	if (!b) {\
		MSG_FAIL(b, "is null");\
		return 0;\
	}\
	if (strcmp(a, b)) {\
		MSG_PASS(a, "expected not to equal \'" #b "\'");\
		return 1;\
	} else {\
		MSG_FAIL(a, "expected not to equal \'" #b "\'");\
		return 0;\
	}\
} while (0)

#define RUN_TEST(func)\
do {\
	testsRun++;\
	testsPassed += func();\
} while (0)

#define END_TESTING()\
	fprintf(stderr, GREEN BOLD "Passed: %d" RESET " | " RED BOLD "Failed: "\
			"%d" RESET " | " BLUE BOLD "Total: %d\n" RESET,\
			testsPassed, testsRun - testsPassed, testsRun)

extern int testsRun;
extern int testsPassed;

#endif
