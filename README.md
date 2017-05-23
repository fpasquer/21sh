# Shell Project

##Presentation

Shell Project is an sh-compatible command language interpreter that executes commands read from the standard input. Shell Project also incorporates useful features from the Bash shell.

Shell Project is not intended to be a conformant implementation of the IEEE POSIX specifications.

##Options

Shell Project does not interpret options when invoked.

##Builtins

###cd  -  change the working directory

	Synopsis:
	cd [directory]

	cd -

	Description:
	Change the shell working directory.
	The cd utility changes the working dirctory of the current shell execution environment by executing the following steps.
	
	1. If no directory operand is given and the HOME environment variable is empty or undefined, the cd utility will return an error.
	2. If no directory operand is given and the HOME environment variable is set to a non-empty value, the cd utility behaves as if the directory named in the HOME environment variable was specified as the directory operand.
	3.If the directory operand is given and is an invalid relative as well as absolute path, the cd utility will return an error.
	4.If the directory operand is given and is a valid relative or absolute path, the cd utility behaves like the chdir() function with the provided path converted to an absolute path as path argument. It will set the value of the PWD environment variable to said path. If the actions fail for any reason, the cd utility displays an appropriate error message and no further step is taken.

	If during the execution of the above steps, the PWD environment variable is changed, the OLDPWD environment variable is also changed to the value of the old working directory.

	Operands:

	-  This command changes to the previous working directory.


###env  -  run a program in a modified evironment

	Synopsis:
	env [OPTION] [NAME]=[VALUE] [COMMAND[ARG]...]

	Description:
	Set each NAME to VALUE in the environment and run command. Each NAME set this way will only be available to this command line, the environment will return to his prior state after the command is run.

	Options:

	-i start with an empty environment


###setenv  -  create or set value of an environment variable.

	Synopsis:
	setenv [NAME] [VALUE]

	Description:
	Set a new value for an environment variable if it exists, creates it if it doesnt.


###unsetenv  -  unset value and name of an environment variable.

	Synopsis:
	unsetenv [NAME]

	Description:
	Unsets the NAME environment variable if it exists.


###echo  -  write to the standard output

	Synopsis:
	echo [-n][LINE]

	Description:
	Display LINE on the standard output followed by a newline.

	Options:

	-n do not append a newline


###exit  -  exit the Project Shell

	Synopsis:
	exit

	Description:
	Exit the shell.


##Command line edition

		Arrow-left		: move to the left in command line

		Arrow-right		: move to the right in command line

		DEL				: Delete character under the cursor

		DEL-left		: Delecte character on the left

		TAB				: Autocomplete command

		HOME			: move to the start of command line

		END				: move to the end of command line

	SHIFT+Arrow-left	: move from a full word on the left in command line

	SHIFT+Arrow-right	: move from a full word on the right in command line

	
SHIFT ARROW UP    : up moves for lines

SHIFT ARROW DOWN  : down moves for lines

CTRL-t            : change to select mode

CTRL-l            : copy curs/selection

CTRL-u            : cut  curs/selection

CTRL-p            : past the last copy/cut

#History
Arrow-up          : last/prev history lines

Arrow-down        : next history lines

CTRL-r            : search in history

F1                : Del history
