#ifndef SUNIT_INCLUDED
#define SUNIT_INCLUDED

#include <stdio.h>
#include <string.h>

#define BOLD            "\033[1m"
#define RED             "\033[31m"
#define GREEN           "\033[32m"
#define BLUE            "\033[34m"
#define RESET           "\033[m"

#define PASS\
	GREEN BOLD "PASSED: " RESET 

#define FAIL\
	RED BOLD "FAILED: " RESET

#define OUTCOME(a, msg, result)\
	fprintf(stderr, result __FILE__ ", %d: \'" #a "\' " msg "\n", __LINE__)


#define ASSERT(a)\
do {\
	if (a) {\
		OUTCOME(a, "expected true", PASS);\
	} else {\
		OUTCOME(a, "expected true", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_EQ(a, b)\
do {\
	if (a == b) {\
		OUTCOME(a, "expected to equal \'" #b "\'", PASS);\
	} else {\
		OUTCOME(a, "expected to equal \'" #b "\'", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_NEQ(a, b)\
do {\
	if (a != b) {\
		OUTCOME(a, "expected not to equal \'" #b "\'", PASS);\
	} else {\
		OUTCOME(a, "expected not to equal \'" #b "\'", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_GT(a, b)\
do {\
	if (a > b) {\
		OUTCOME(a, "expected to be greater than \'" #b "\'", PASS);\
	} else {\
		OUTCOME(a, "expected to be greater than \'" #b "\'", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_LT(a, b)\
do {\
	if (a < b) {\
		OUTCOME(a, "expected to be less than \'" #b "\'", PASS);\
	} else {\
		OUTCOME(a, "expected to be less than \'" #b "\'", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_GEQ(a, b)\
do {\
	if (a >= b) {\
		OUTCOME(a, "expected to be greater than or equal to \'" #b\
				"\'", PASS);\
	} else {\
		OUTCOME(a, "expected to be greater than or equal to \'" #b\
				"\'", FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_LEQ(a, b)\
do {\
	if (a <= b) {\
		OUTCOME(a, "expected to be less than or equal to \'" #b "\'",\
				PASS);\
	} else {\
		OUTCOME(a, "expected to be less than or equal to \'" #b "\'",\
				FAIL);\
		return 0;\
	}\
} while (0)

#define ASSERT_STREQ(a, b)\
do {\
	if (!a) {\
		OUTCOME(a, "is null", FAIL);\
		return 0;\
	}\
	if (!b) {\
		OUTCOME(b, "is null", FAIL);\
		return 0;\
	}\
	if (!strcmp(a, b)) {\
		fprintf(stderr, PASS __FILE__ ", %d: \'" #a "\' (%s) "\
			       "expected to equal \'" #b "\' (%s)\n",\
				__LINE__, a, b);\
	} else {\
		fprintf(stderr, FAIL __FILE__ ", %d: \'" #a "\' (%s) "\
			       "expected to equal \'" #b "\' (%s)\n",\
				__LINE__, a, b);\
		return 0;\
	}\
} while (0)

#define ASSERT_STRNEQ(a, b)\
do {\
	if (!a) {\
		OUTCOME(a, "is null", FAIL);\
		return 0;\
	}\
	if (!b) {\
		OUTCOME(b, "is null", FAIL);\
		return 0;\
	}\
	if (strcmp(a, b)) {\
		fprintf(stderr, PASS __FILE__ ", %d: \'" #a "\' (%s) "\
			       "expected not to equal \'" #b "\' (%s)\n",\
				__LINE__, a, b);\
	} else {\
		fprintf(stderr, PASS __FILE__ ", %d: \'" #a "\' (%s) "\
			       "expected not to equal \'" #b "\' (%s)\n",\
				__LINE__, a, b);\
		return 0;\
	}\
} while (0)

#define RUN_TEST(func)\
do {\
	fprintf(stderr, BLUE "Running test " BOLD #func RESET "\n");\
	testsRun++;\
	testsPassed += func();\
} while (0)

#define TEST_SUMMARY()\
	fprintf(stderr, GREEN BOLD "Passed: %d" RESET " | " RED BOLD "Failed: "\
			"%d" RESET " | " BLUE BOLD "Total: %d\n" RESET,\
			testsPassed, testsRun - testsPassed, testsRun)

extern int testsRun;
extern int testsPassed;

#endif
