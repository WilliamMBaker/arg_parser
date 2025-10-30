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

#define UNUSED(x) (void)(x)

// == PRIVATE VARIABLES =======================================================

char prompt[MAX_PROMPT_LEN] = ""; // Terminal input prompt
Command_t *commands = NULL;		  // Registered commands
uint8_t numberOfCommands = 0;	  // Number or registered commands

// == PRIVATE FUNCTIONS DEFINITIONS ===========================================

static bool CheckNameClash(Command_t newCmd);
static bool CheckFlagClash(Command_t cmd, Flag_t newFlag);
static bool GetCommandIndex(Command_t cmd, uint8_t *idx);
static bool Help(Command_t command, uint8_t argc, char **argv);

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
		printf("Strlen\r\n");
		return false;
	}

	if (strcpy(prompt, newPrompt) == NULL)
	{
		printf("Strcpy\r\n");
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

	if (CheckNameClash(cmd) != true)
	{
		printf("check name clash\r\n");
		return false;
	}

	Command_t *ptr = realloc(commands, (numberOfCommands + 1) * sizeof(Command_t));
	if (ptr == NULL)
	{
		return false;
	}

	commands = ptr;
	memcpy(&commands[numberOfCommands], &cmd, sizeof(Command_t));
	numberOfCommands++;

	return true;
}

bool AddFlag(Command_t targetCmd, Flag_t flag)
{
	uint8_t idx;

	if (GetCommandIndex(targetCmd, &idx) != true)
	{
		printf("No command by that name, failed to add flag\r\n");
		return false;
	}

	if (commands[idx].numberOfFlags == MAX_SUPPORTED_SIZE)
	{
		return false;
	}

	if (CheckFlagClash(commands[idx], flag) != true)
	{
		printf("flag name clash\r\n");
		return false;
	}

	Flag_t *ptr = realloc(commands[idx].flags, (commands[idx].numberOfFlags + 1) * sizeof(Flag_t));
	if (ptr == NULL)
	{
		printf("failed ralloc\r\n");
		return false;
	}

	commands[idx].flags = ptr;
	memcpy(&commands[idx].flags[commands[idx].numberOfFlags], &flag, sizeof(Flag_t));
	commands[idx].numberOfFlags++;

	return true;
}

bool executeCommand(const char *name, uint8_t argc, char **argv)
{
	for (uint8_t i = 0; i < numberOfCommands; i++)
	{
		if (strcmp(commands[i].command, name) == 0)
		{
			if (commands[i].function)
			{
				commands[i].function(commands[i], argc, argv);
				return true;
			}
		}
	}
	printf("Command not found: %s\r\n", name);
	return false;
}

bool RegisterHelp(void)
{
	Command_t helpCmd = {
		.command = "help",
		.help = "Help command.\r\n",
		.function = Help};

	if (RegisterCommand(helpCmd) != true)
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
		if (strcmp(commands[cmdIdx].command, newCmd.command) == 0)
		{
			return false;
		}
	}

	return true;
}

static bool CheckFlagClash(Command_t cmd, Flag_t newFlag)
{
	for (uint8_t flagIdx = 0; flagIdx < cmd.numberOfFlags; flagIdx++)
	{
		if (strcmp(cmd.flags[flagIdx].shortFlag, newFlag.shortFlag) == 0 ||
			strcmp(cmd.flags[flagIdx].longFlag, newFlag.longFlag) == 0)
		{
			return false;
		}
	}

	return true;
}

static bool GetCommandIndex(Command_t cmd, uint8_t *idx)
{
	for (uint8_t cmdIdx = 0; cmdIdx < numberOfCommands; cmdIdx++)
	{
		if (strcmp(commands[cmdIdx].command, cmd.command) == 0)
		{
			*idx = cmdIdx;
			return true;
		}
	}

	return false;
}

static bool Help(Command_t command, uint8_t argc, char **argv)
{
	UNUSED(command);
	printf("Help:\r\n");

	for (uint8_t cmdIdx = 0; cmdIdx < numberOfCommands; cmdIdx++)
	{
		printf("\t%s\t%s",
			   commands[cmdIdx].command,
			   commands[cmdIdx].help);

		for (uint8_t flagIdx = 0; flagIdx < commands[cmdIdx].numberOfFlags; flagIdx++)
		{
			printf("\t\t(%s | %s)\t%s\r\n",
				   commands[cmdIdx].flags[flagIdx].shortFlag,
				   commands[cmdIdx].flags[flagIdx].longFlag,
				   commands[cmdIdx].flags[flagIdx].help);
		}
	}

	return true;
}