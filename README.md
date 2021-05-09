# DSA Project Group 44 - Assignment Shell

## The Project

The assignment shell is compiled using the following lines of code :

~~~bash 
cd location_of_the_repo_on_your_machine\DSA-project-group-44\Project\dsa
~~~


~~~bash
gcc main.c utils/switchfolder/switchfolder.c utils/createfolder/createfolder.c utils/updatefolder/updatefolder.c utils/setupfolder/setupfolder.c utils/testfolder/testfolder.c utils/submitfolder/submitfolder.c utils/comparefolder/comparefolder.c utils/usefolder/usefolder.c utils/parse/parse.c utils/execute/execute.c 
 ~~~


We scan the command in ```main.c``` and turn the string into a series of arguments or tokens using the ``` parse(char *cmd, char **params, char *use_string)``` function. 

The ``` parse(char *cmd, char **params, char *use_string)``` function removes unnecessary whitespace, escape sequence characters and stores each word of the command string into a list of tokens. 

Each token in a string which is processed by the ```int execute(char **params, char*commands_str[], int (*commands_func[])(char **))``` function. 

The execute function forks a child process, identifies what set of instructions, be it custom or in-built, the token calls on and runs them in the child process. 

The prompt shows the absolute path address of the directory the user is currently in (using the ```getcwd()```) function as well as any folder the user might be “using” selected via the ```usefolder(char **args)``` function in <>. 

The shell supports 8 custom made commands as well as almost all standard bash shell commands.

<br>

 ### switch
 <br>

 The ```usefolder(char **args)``` command functions like the standard bash command ```cd```, with the added ability to access sibling folders without having to ```cd``` into their shared parent directory. For example, for the given file structure. It is called by ```switch```.

<br>

~~~bash
folderC
    folderA
      folderD
    folderB
~~~~

<br>
Suppose we are in folderA
<br>

~~~bash
$Group44Shell/folderC/folderA>switch folderB 
~~~

~~~bash
$Group44Shell/folderC/folderB>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA>switch folderD 
~~~

~~~bash
$Group44Shell/folderC/folderA/folderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA>switch .. 
~~~

~~~bash
$Group44Shell/folderC>
~~~

<br>

### use
<br>

The ```usefolder(char **args)``` function saves the argument file’s absolute path address and indicates its name in brackets at the end of the Group44Shell prompt. If any command is passed without its argument, it defaults to our saved file’s absolute path address. It is called by ```use```.

<br>

For example, for the given file structure.


~~~bash
folderC
    folderA
      folderD
    folderB
~~~~

<br>
Suppose we are in folderA
<br>

~~~bash
$Group44Shell/folderC/folderA>use folderD
~~~

~~~bash
$Group44Shell/folderC/folderA<FolderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA<folderD>switch folderB
~~~

~~~bash
$Group44Shell/folderC/folderB<FolderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderB<FolderD>switch
~~~

~~~bash
$Group44Shell/folderC/folderA/folderD<FolderD>
~~~

<br>

### test
<br>

The ```testfolder(char **args)``` function goes to the folder given as an argument to the ```setup``` command and runs the ```submitter.py``` present in the ```dist``` folder, if it exists. The output of the ```submitter.py```, containing all the errors and outputs, is then stored in ```testLog.txt``` file in the main working directory.

For example, for the given file structure.


~~~bash
folderA
    dist
      submitter.py    
~~~~

<br>

Now, if we type the following in the prompt:
~~~bash
test folderA
~~~
 <br>
 The program will run the ```submitter.py``` file and create a file ```testLog.txt``` with the output.
 <br>
 Hence, the new directory structure will be
 ~~~bash
folderA
    dist
      submitter.py 
testLog.txt   
~~~~

<br>

### setup
<br>

The ```setupfolder(char **args)``` function reads an indented file ```setup.txt``` from the ```Downloads``` folder present in the current working directory and then creates a folder structure in correspondence with it.

The argument to the ```setup``` command must match with the root directory mentioned at the top of the ```setup.txt```.
<br>
Also the ```setup.txt``` file must be indented by using tab spaces.
<br>

For example, if the ```setup.txt``` file is:

~~~bash
assignment
  q1
  	solution
			main1
		testcases
		q12
			main2
	q2
		solution
	q3
~~~

Then, to create this structure, the command should be:

~~~bash
setup assignment
~~~
This will create a directory ```assignment``` in the working directory with all the sub-directories.
<br>




