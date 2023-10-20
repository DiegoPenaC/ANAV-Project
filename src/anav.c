/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name:
 * GNumber:
 */

#include <sys/wait.h>
#include "logging.h"
#include "anav.h"
#include "parse.h"
#include "util.h"

/* Constants */
#define DEBUG 1 /* You can set this to 0 to turn off the debug parse information */
#define STOP_SHELL  0
#define RUN_SHELL   1

/* The entry of your text processor program */
int main() {
  char *cmd = NULL;
  int do_run_shell = RUN_SHELL;

  /* Intial Prompt and Welcome */
  log_anav_intro();
  log_anav_help();

  /* Shell looping here to accept user command and execute */
  while (do_run_shell == RUN_SHELL) {
    char *argv[MAXARGS+1] = {0};  /* Argument list */
    Instruction inst = {0};       /* Instruction structure: check parse.h */

    /* Print prompt */
    log_anav_prompt();

    /* Get Input - Allocates memory for the cmd copy */
    cmd = get_input(); 
    /* If the input is whitespace/invalid, get new input from the user. */
    if(cmd == NULL) {
      continue;
    }

    /* Check to see if this is the quit built-in */
    if(strncmp(cmd, "quit", 4) == 0) {
      /* This is a match, so we'll set the main loop to exit when you finish processing it */
      do_run_shell = STOP_SHELL;
      /* Note: You will need to print a message when quit is entered, 
       *       you can do it here, in your functions, or at the end of main.
       */
    }

    /* Parse the Command and Populate the Instruction and Arguments */
    initialize_command(&inst, argv);    /* initialize arg lists and instruction */
    parse(cmd, &inst, argv);            /* call provided parse() */

    if (DEBUG) {  /* display parse result, redefine DEBUG to turn it off */
      debug_print_parse(cmd, &inst, argv, "main (after parse)");
    }

    /*.===============================================.
     *| Add your code below this line to continue. 
     *| - The command has been parsed and you have cmd, inst, and argv filled with data.
     *| - Very highly recommended to start calling your own functions after this point.
     *o===============================================*/


    /*.===============================================.
     *| After your code: We cleanup before Looping to the next command.
     *| free_command WILL free the cmd, inst and argv data.
     *| Make sure you've copied any needed information to your Task first.
     *| Hint: You can use the util.c functions for copying this information.
     *o===============================================*/
    free_command(cmd, &inst, argv);
    cmd = NULL;
  }

  return 0;
}
