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