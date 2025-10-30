#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "CLI.h"

static bool Test1Callback(Command_t command, uint8_t argc, char **argv)
{
	printf("Test 1\r\n");

	return true;
}

int main(void)
{
	if (InitialiseAP() != true)
	{
		printf("Failed to initialise cli\r\n");
		return 1;
	}

	if (SetPrompt("will>") != true)
	{
		printf("Failed to set prompt1\r\n");
		return 1;
	}

	if (RegisterHelp() != true)
	{
		printf("Failed to register help\r\n");
		return 1;
	}

	Command_t cmd = {.command = "test1",
					 .help = "Help for test1\r\n",
					 .function = Test1Callback};

	Flag_t flg = {.shortFlag = "-n",
				  .longFlag = "-none",
				  .help = "No help"};

	if (RegisterCommand(cmd) != true)
	{
		printf("Failed to set prompt1\r\n");
		return 1;
	}

	if (AddFlag(cmd, flg) != true)
	{
		printf("Failed to add flag\r\n");
		return 1;
	}

	executeCommand("test1", 0, NULL);
	executeCommand("help", 0, NULL);

	return 0;
}