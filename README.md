# DSA Project Group 44 - Assignment Shell

## The Project

The assignment shell is compiled using the following lines of code :

~~~bash 
$> cd location_of_the_repo_on_your_machine\DSA-project-group-44\Project\dsa
$> cmake a
$> ./Shell
 ~~~

<br>
<br>

We scan the command in ```main.c``` and turn the string into a series of arguments or tokens using the ``` parse(char *cmd, char **params, char *use_string)``` function. 

The ``` parse(char *cmd, char **params, char *use_string)``` function removes both unecessary whitespace both leading the string and within the string, removes escape sequence characters and stores each word of the command string into a list of tokens. 

Each token in a string which is processed by the ```int execute(char **params, char*commands_str[], int (*commands_func[])(char **))``` function. 

The execute function forks a child process, identifies what set of instructions, be it custom or in-built, the token calls on and runs them in the child process. 

The prompt shows the absolute path address of the directory the user is currently in (using the ```getcwd()```) function as well as any folder the user might be “using” selected via the ```usefolder(char **args)``` function in <>. 

The shell supports 8 custom made commands as well as almost all standard bash shell commands.

<br>

### Error Handling in execute

<br>

If the Shell fails to fork a child process it returns ```fork: error_description```

If the command doesn't exist in bash or isn't one of the 8 custom defined functions, the shell returns ```Command not found: name_of_invalid_command```

If there is an error in executing the command the shell returns ```Shell: command_name error_description```

<br>

 ### switch
 <br>

 The ```usefolder(char **args)``` command functions like the standard bash command ```cd```, with the added ability to access sibling folders without having to ```cd``` into their shared parent directory. It is called by ```switch```. For example, for the given file structure. 

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
$Group44Shell/folderC/folderB>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA>switch folderD 
$Group44Shell/folderC/folderA/folderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA>switch .. 
$Group44Shell/folderC>
~~~

<br>

### use
<br>

The ```usefolder(char **args)``` function saves the argument file’s name and indicates it in brackets at the end of the Group44Shell prompt. If any command is passed without its argument, it defaults to our saved file’s name. It is called by ```use```.

<br>

For example, for the given file structure.


~~~bash
folderC
    folderA
      folderD
	  folderE
    folderB
~~~~

<br>
Suppose we are in folderA
<br>

~~~bash
$Group44Shell/folderC/folderA>use folderD
$Group44Shell/folderC/folderA<FolderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA<folderD>switch folderB
$Group44Shell/folderC/folderB<FolderD>
~~~

<br>

~~~bash
$Group44Shell/folderC/folderA/folderE<FolderD>switch
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
 
 <br>
 
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
<br>

### create

<br>

1. The ```create <assignment>``` command had 2 functions one to create the folder named assignment in the current directory using ```mkdir``` standard bash command and other function is to copy the contents of the dist folder and the problem statement from Downloads folder to the  newly created assignment folder using ```cp```  standard bash command

<br>

~~~bash
$shell/Project/dsa> create assignment1
assignment1 is created and downloaded the required files
~~~

#### ERROR CASE 

<br>

1. If assignment1 folder is already exist in current directory then

~~~bash
$shell/Project/dsa> create assignment1
mkdir: cannot create directory ‘/Project/dsa/assignment1’: File exists
~~~

<br>

### update

<br>

1. The ```update <assignment>``` command had 2 functions one to delete the dist files in assignment folder using ```rm``` standard bash command and other function is copy the contents of Downloads folder using  ```cp```  standard bash command which updates the contents of the dist folder and the problem statement in selected assignment 

#Note: if any files that are needed to update from downloads other than dist files then make sure that the files have same old name

<br>

~~~bash$
shell/Project/dsa>update assignment1
assignment2 is updated, old files are deleted & new files are downloaded
~~~

#### ERROR CASE 

1. If assignment1 folder doesn’t exist in current directory

~~~bash
$shell/Project/dsa>update assignment1
rm: cannot remove '/Project/dsa/assignment2/dist': No such file or directory
~~~


### submit
Submitfolder finds the file name in the current directory and create a zip file for it.
~~~bash
Folder C
	Folder A
		Folder D
~~~
~~~bash
$Group44Shell/folderC/folderA>submit folder D
~~~
It zips the file and pastes it in the Download directory.
~~~bash
$Group44Shell/Download-directory/folderD.zip
~~~

ERROR HANDLING
~~~bash
$Group44Shell/folderC/folderA>submit folder E
~~~
The output will be ```No such Folder```

### compare
Compare finds the file name in the current directory and compare it with the zip file in the ```Downloads``` directory.
~~~bash
FolderC
	FolderA
		FolderD
~~~
~~~bash
$Group44Shell/folderC/folderA>compare folderD folderD.zip
~~~
~~~bash
Files dir1.txt and Downloads/dir2.txt are identical
~~~
It will create ```dir1.txt``` and ```Downloads/dir2.txt``` and will contain the files in the folder and the zip file of the folder. 
```diff``` will be used to print the files that are different in both folders.
<br>
ERROR HANDLING
~~~bash
$Group44Shell/folderC/folderA>compare folder E
~~~
The output will be ```NO SUCH FILE TO COMPARE```








