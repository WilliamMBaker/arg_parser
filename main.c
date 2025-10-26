#include <stdio.h>
#include <stdint.h>
#include "CLI.h"

static void Test1Callback(uint8_t argc, char **argv)
{
	printf("Test 1\r\n");
}

static void RegisterTest1Cmd(void)
{
	Command_t cmd = {
		.command = "test1",
		.help = "Test1 help.",
		.function = Test1Callback};
	RegisterCommand(cmd);
}

int main(void)
{
	InitialiseAP();
	SetPrompt("will>");

	return 0;
}