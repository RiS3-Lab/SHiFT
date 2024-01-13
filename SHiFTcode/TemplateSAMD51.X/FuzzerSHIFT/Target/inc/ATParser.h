/**
 * ATParser
 * AT commando parser helper for C (aimed at embedded devices)
 *
 * @license MIT
 * @link https://github.com/tschiemer/ATParser
 * @author Philip Tschiemer, filou.se
 */
#ifndef __AT_PARSER_H_
#define __AT_PARSER_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>


#ifndef AT_PARSER_MARKER_MAXLEN
#define AT_PARSER_MARKER_MAXLEN 10
#endif
#ifndef AT_PARSER_COMMAND_MAXLEN
#define AT_PARSER_COMMAND_MAXLEN 10
#endif
#ifndef AT_PARSER_ARGUMENTS_MAX_COUNT
#define AT_PARSER_ARGUMENTS_MAX_COUNT 10
#endif

int mainparser( char * input, uint8_t len  );
     
     
typedef enum {
	ATParserResultOK,
	ATParserResultError,
	ATParserResultNoResponse
} ATParserResult_t;

typedef ATParserResult_t ( *ATParserCallback )( uint8_t argc, uint8_t ** argv );
typedef ATParserResult_t ( *ATParserExecute )( void );

typedef struct
{
    uint8_t String[AT_PARSER_COMMAND_MAXLEN];
    uint8_t Length;
    ATParserCallback Get;
    ATParserCallback Set;
    ATParserExecute Execute;
    ATParserExecute Test;
} ATParserCommand_t;

typedef struct {
	uint8_t Marker[AT_PARSER_MARKER_MAXLEN];
	uint8_t MarkerLen;
	ATParserCommand_t * Commands;
	uint8_t CommandCount;
	ATParserExecute MarkerOnlyCallback;
} ATParser_t;


/**
 * Initialize parse structure (well, mostly just assign fields)
 *
 * @param parser
 * @param marker		Marker string denoting the beginning of each command (ie "AT")
 * @param markerLen		Length of the marker string
 * @param commands		pointer to commands buffer
 * @param commandCount	Count of commands in buffer
 * @param markerOnlyCallback (optional) Callback that is called in case only the marker string is given as parse input (ex. "AT");
 */
void ATParser_init( ATParser_t * parser, uint8_t * marker, uint8_t markerLen, ATParserCommand_t * commands, uint8_t commandCount, ATParserExecute markerOnlyCallback );

/**
 * Parses given command line w.r.t. defined commands.
 *
 * @TODO introduce case insensitivity for commands 
 *
 * NOTE: parses only one and only the first command found, ergo it is your responsibility to feed it only one command at a time
 *
 * REALLY IMPORTANT NOTE: for get/set commands with arguments the original buffer is modified such as to put null-characters after each argument
 *
 * IMPORTANT NOTE: for get/set commands with arguments, there is maximal number of arguments that can be passed down (@see AT_PARSER_ARGUMENTS_MAX_COUNT)
 *
 * @param parser	object
 * @param input		pointer to input buffer
 * @param inputLen	length of input buffer
 */
ATParserResult_t ATParser_parseString( ATParser_t * parser, uint8_t * input, uint8_t inputLen );

#ifdef __cplusplus
}
#endif

#endif /* __AT_PARSER_H_ */