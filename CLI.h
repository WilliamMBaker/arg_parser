#ifndef _ARG_PARSER_H
#define _ARG_PARSER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _Flag_t
{
	char *shortFlag; // e.g. -h
	char *longFlag;	 // e.g. -help
} Flag_t;

typedef struct _Command_t
{
	char *command;		   // Command name
	char *help;			   // Hint of how command is to be used
	void *function;		   // Callback function
	Flag_t *flags;		   // Flag modifiers list
	uint8_t numberOfFlags; // Number of flags
} Command_t;

bool InitialiseAP(void);
bool SetPrompt(char *prompt);
bool RegisterCommand(Command_t cmd);
bool AddFlag(Command_t targetCmd, Flag_t flag);

#endif // _ARG_PARSER_H