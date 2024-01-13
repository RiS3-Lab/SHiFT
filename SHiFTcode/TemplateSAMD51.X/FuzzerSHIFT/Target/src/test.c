
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ATParser.h"
//#include "main.h"
//#include "stdio.h"
//#include "afl.h"
//#include "stdlib.h"
//#include "McuASAN.h"

/*
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES 0
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_SOFT 1
#include "printf/printf/printf.h"
*/





typedef struct {
	char desc[200];
	char cmd[100];
} TestCase_t;

TestCase_t TestCases[8] = {
	{
		">> marker only\n",
		"AT"
	},
	{
		"\n>> get command (optional arguments)\n",
		"AT+FOO?"
	},
	{
		"\0", //
		"AT+FOO?1,2,3,4"
	},
	{
		"\n>> set command (at least one argument required)\n",
		"AT+FOO=long,arguments, note-the-space"
	},
	{
		"\n>> execute command (no arguments)\n",
		"AT+FOO"
	},
	{
		"\n>> test command (no arguments)\n",
		"AT+FOO=?"
	},
	{
		"\n>> only first marker match is considered (note: the second command is considered an argument of the first, so it is in your responsibility to enter only one command)\n",
		"1234 bla AT+FOO=1  AT+FOO=2"
	},
	{
		"\n>> end is trimmed w.r.t. \\r, \\n, space, \\t\n",
		"AT+FOO=1,2,3 \t   \r\n\r\n"
	}
};

ATParserResult_t at( void )
{
	printf("Hello world!\n");
	return ATParserResultOK;
}

ATParserResult_t foo_get( uint8_t argc, uint8_t ** argv )
{
	printf("get argc=%d\n", argc);
	for( uint8_t i = 0; i < argc; i++)
	{
		printf("\t arg%d = %s\n", i, (char*)argv[i]);
	}
	if (argc == 0)
	{
		printf("because there are no arguments we return an error from within the get handler\n");
		return ATParserResultError;
	}
	return ATParserResultOK;
}

ATParserResult_t foo_set( uint8_t argc, uint8_t ** argv )
{
	printf("set argc=%d\n", argc);
	for( uint8_t i = 0; i < argc; i++)
	{
		printf("\t arg%d = %s\n", i, (char*)argv[i]);
	}
	return ATParserResultOK;
}

ATParserResult_t foo_exec( void )
{
	printf("exec\n");
	return ATParserResultOK;
}

ATParserResult_t foo_test( void )
{
	printf("test (note: there is no response text)\n");
	return ATParserResultNoResponse;
}

ATParser_t ATParser;
ATParserCommand_t Commands[1] = {
	{ "+FOO", 4, foo_get, foo_set, foo_exec, foo_test }
};


void processInput( char * input, uint8_t len  )
{
	uint8_t n = len;
	//printf("> INPUT=%s\n", input );
	ATParserResult_t result = ATParser_parseString( &ATParser, (uint8_t*)input, n );
	switch(result)
	{
		case ATParserResultOK:
			printf( "OK\n" );
			break;

		case ATParserResultError:
			printf( "ERROR\n" );
			break;

		case ATParserResultNoResponse:
		default:
			break;
	}
}

int mainparser( char * input, uint8_t len  )
{
	ATParser_init( &ATParser, (uint8_t*)"AT", 2, (ATParserCommand_t*)&Commands, 1, at );
	processInput(input, len );
	return 0;
}