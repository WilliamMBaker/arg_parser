#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"

// == PRIVATE DEFINES =========================================================

#define COMMAND_SIZE sizeof(Command_t)
#define FLAG_SIZE sizeof(Flag_t)
#define MAX_SUPPORTED_SIZE 0xFF // uint8_t maximum
#define MAX_PROMPT_LEN 10
#define DEFAULT_PROMPT "cli>"

// == PRIVATE VARIABLES =======================================================

char prompt[MAX_PROMPT_LEN] = ""; // Terminal input prompt
Command_t *commands = NULL;		  // Registered commands
uint8_t numberOfCommands = 0;	  // Number or registered commands

// == PRIVATE FUNCTIONS DEFINITIONS ===========================================

static bool CheckNameClash(Command_t newCmd);

// == PUBLIC FUNCTIONS ========================================================

bool InitialiseAP(void)
{
	if (SetPrompt(DEFAULT_PROMPT) != true)
	{
		return false;
	}

	return true;
}

bool SetPrompt(char *newPrompt)
{
	if (strlen(newPrompt) > MAX_PROMPT_LEN)
	{
		return false;
	}

	if (strcpy(prompt, newPrompt))
	{
		return false;
	}

	return true;
}

bool RegisterCommand(Command_t cmd)
{
	if (numberOfCommands == MAX_SUPPORTED_SIZE)
	{
		return false;
	}

	if (CheckNameClash(cmd))
	{
		return false;
	}

	void *ptr = (Command_t *)realloc(commands, numberOfCommands + 1);
	if (ptr == NULL)
	{
		return false; // Cannot asign memory, command not registered
	}

	memcpy(commands + (numberOfCommands * COMMAND_SIZE), (const void *)&cmd, sizeof(Command_t));

	numberOfCommands++;

	return true;
}

bool AddFlag(Command_t targetCmd, Flag_t flag)
{
	if (targetCmd.numberOfFlags == MAX_SUPPORTED_SIZE)
	{
		return false;
	}

	return true;
}

// == PRIVATE FUNCTIONS =======================================================

static bool CheckNameClash(Command_t newCmd)
{
	for (uint8_t cmdIdx = 0; cmdIdx < numberOfCommands; cmdIdx++)
	{
		char *cmd = (commands + (cmdIdx * COMMAND_SIZE))->command;
		if (strcmp(cmd, newCmd.command) != 0)
		{
			return false;
		}
	}

	return true;
}