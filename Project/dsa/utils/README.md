//////////////////////////FOR UTILS/COMMANDS AND THEIR ERROR HANDLING CASES


///////////CREATE
1. The create <assignment> command had 2 functions one to create the folder named assignment in the current directory using ‘mkdir‘ standard bash command and other function is to copy the contents of Downloads folder to the  newly created assignment folder using ‘cp’  standard bash command

$shell/Project/dsa> create assignment1
assignment1 is created and downloaded the required files

ERROR CASE 
1. If assignment1 folder is already exist in current directory then

$shell/Project/dsa> create assignment1
mkdir: cannot create directory ‘/Project/dsa/assignment1’: File exists



///////////UPDATE
1. The update <assignment> command had 2 functions one to delete the dist files in assignment folder using ‘rm’ standard bash command and other function is copy the contents of Downloads folder using  ‘cp’  standard bash command 
Note: if any files that are needed to update from downloads other than dist files then make sure that the files have same old name

$shell/Project/dsa>update assignment1
assignment2 is updated, old files are deleted & new files are downloaded

ERROR CASE 
1. If assignment1 folder doesn’t exist in current directory

$shell/Project/dsa>update assignment1
rm: cannot remove '/Project/dsa/assignment2/dist': No such file or directory
 




///////////COMPARE




///////////SETUP




///////////SUBMIT




///////////SWITCH




///////////TEST




///////////USE
