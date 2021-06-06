#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//VARIABLES
    char input[513]; //store line of input
    char* inputPtr; //used with strtok (extract commands)
	const char cmdSplit[3] = ";\n"; //split lines into commands
    const char argSplit[3] = "\t "; //split commands into arguments

    char command[513]; //store one command
	char* cmdPtr; //used with strtok (extract command/first argument)
    char* baseCmd; //name of command to run, use for specific commands
	
	bool exitFlag = 0; //determine when to exit shell
	int counter = 0; //FIXME - prevent crash

	/* TYPE OF SHELL
	0 - interactive mode (user input)
	1 - batch mode (batch file) */
	bool inputType;
	FILE *batchFile; //get batch file
	//END OF VARIABLES

	//DETERMINE RUNNING MODE (INTERACTIVE OR BATCH)
	if (argc == 1) //no command-line argument - interactive mode
	{
		inputType = 0;
	}
	else if (argc == 2) //one argument (file) - batch mode
	{
		inputType = 1;

		//open batch file
		batchFile = fopen(argv[1],"r");
		if (batchFile == NULL) //couldn't open batch file / doesn't exit
		{
			fprintf(stderr,"The batch file does not exist or cannot be opened.\n");
			return 0;
		}

	}
	else //invalid number of arguments - print to stderr and exit
	{
		fprintf(stderr,"Invalid number of command-line arguments.\n");
		fprintf(stderr,"For interactive mode, run \"newshell\".\n");
		fprintf(stderr,"For batch mode, run \"newshell [name of batch file]\".\n");
		return 0;
	}
	//END OF DETERMINING RUNNING MODE

    //FIXME - DEMO
    printf("This is a test of some features required for Major 2.\n");
    printf("The program will accept user or batch file input based on the number of command-line\n");
    printf("arguments, and it will handle errors with the batch file or EOF for either mode.\n");
    printf("Each line will be split into commands (which are separated by \",\"), and the base\n");
    printf("command of each command will be extracted (for use with built-in commands). Regular\n");
    printf("commands like \"ls -l\" are not executed yet, but the full command is currently stored\n");
    printf("in the string \"command\" (extra spaces will have to be removed when extracting arguments\n");
    printf("\n Note: The program will currently stop after entering either \"exit\" or 10 commands\n");
    printf("(the command limit is to prevent infinite loop issues for now)\n"); 

	//PROCESS COMMANDS LINE-BY-LINE
	while (counter < 10) //FIXME - prevent infinite loop
	{
        counter++; //FIXME - prevent infinite loop

		//EXIT PROGRAM IF NEEDED (closes batch file)
		if (exitFlag == 1)
		{
			//close batch file if opened (batch mode)
			if (inputType == 1)
			{
				fclose(batchFile);
			}
			exit(0); //exit
		}
		//END OF EXIT SECTION

		//READ LINE OF INPUT
		if (inputType == 0) //interactive
		{
			printf("$ ");
			fgets(input,513,stdin); //read 513-1=512 chars

			if (feof(stdin)) //if CTRL-D by user
			{
				printf("EOF - exiting shell...\n");
				exitFlag = 1;
				continue;
			}
		}
		else //batch file
		{
			fgets(input,513,batchFile); //read 513-1=512 chars

			if (feof(batchFile)) //end of batch file
			{
				printf("EOF - exiting shell...\n");
				exitFlag = 1;
				continue;
			}

		}
		//END OF READING LINE OF INPUT

		//SPLIT COMMANDS BASED ON ";" and "\n" (doesn't remove spaces within commands)
        inputPtr = input; //need for strtok_r()
		while ( cmdPtr = strtok_r(inputPtr,cmdSplit,&inputPtr) ) //get each command from line
        {
            strncpy(command, cmdPtr, 512); //copy command to array
            baseCmd = strtok(cmdPtr, argSplit); //get the base command

            /* Input redirection/pipe code could probably be ran here
               by doing a strchr() on the variable "command" (cmdPtr is
               changed by strtok in order to get the base command "baseCmd",
               which can be used for built-in commands. */

            if (baseCmd == NULL) //empty command, like "cmd1;   ;cmd3"
            { 
                continue; //ignore empty commands
            }
            else if (strcmp(baseCmd, "exit") == 0) //built-in command "exit"
            {
                /* Exit after full line of input done - set flag to exit
                   after full line of input processed. */
                exitFlag = 1; 
                continue;
            }
            
            /* Other built-in commands would probably go here
             with an "else" clause leading to the standard processing of
             arguments and fork-exec-wait setup. */

            //FIXME - DEMO
            printf("The full command was: %s\n", command);
            printf("The base command is: %s\n", baseCmd);
            printf("Use strtok on \"cmdPtr\" to get subsqeuent arguments for built-in commands.\n");
            printf("If you need the full command, use \"command\", since \"cmdPtr\" is modified by strtok.\n\n");

        }
		//END OF SPLITTING COMMANDS

	} //END OF PROCESSING COMMANDS LINE-BY-LINE
    printf("Counter currently prevents infinite loop - 10 lines processed.\n");
	// (PROGRAM EXIT DONE AT TOP - exitFlag)

	return 0;
}
