#ifndef _ARG_PARSER_H
#define _ARG_PARSER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _Flag_t
{
	char *shortFlag; // e.g. -h
	char *longFlag;	 // e.g. -help
	char *help;		 // Hint
	bool takesArg;	 // Delimited by space, next string is argument attached to flag. Defaults to false
} Flag_t;

typedef bool (*CommandCallback_t)(uint8_t argc, char **argv);

typedef struct _Command_t
{
	char *command;				// Command name
	char *help;					// Hint of how command is to be used
	CommandCallback_t function; // Callback function
	Flag_t *flags;				// Flag modifiers list
	uint8_t numberOfFlags;		// Number of flags
} Command_t;

bool InitialiseAP(void);
bool SetPrompt(char *prompt);
bool RegisterCommand(Command_t cmd);
bool AddFlag(Command_t targetCmd, Flag_t flag);
bool executeCommand(const char *name, uint8_t argc, char **argv);
bool RegisterHelp(void);

#endif // _ARG_PARSER_H