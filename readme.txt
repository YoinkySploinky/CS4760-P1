Name: Trent Hollenkamp-Geragosian
Project: Project 1
Date: 1/31/2023


Usage: ./oss [-h] -n proc -s simul -t iter
There are no default options

Issues with getopt() in that the default option was never procing when no params where given in the command line (ex. entering just ./oss). To get around this I had an argc checker at the very beggining to insure that if only one arg was given to error out.
When forking the child processes the program will wait -s times but will then do the next series of children in a batch (ex. if -n is 9 and -s is 3 the program will do 3 children and when finished will do the next three all at once instead of feeding them in one at a time.) I don't know if this is cause the server completes the children so fast I can't tell if there is a gap in the next process starting.

Skeleton multiple processes
Purpose
This is your warm up project building on your knowledge from CMPSCI 2750. The goal of this project is to become familiar
with the environment in hoare while creating a setup for future projects. Additionally, you should understand the different
steps of compilation and linking, and creating your executable.
Task
In this project you will be writing a makefile to compile two source files into two separate executables. One of the executables
will be called oss, generated at least partially from the source file oss.c. The other executable will be called worker, generated
at least partially from the source file called worker.c.
The worker executable is never executed directly. Instead, oss will be launching that executable at various times.
Note you MUST have a makefile that compiles and creates these executables at the same time. This will require the use of the
”all” command in your makefile to compile multiple executables from the same makefile.
We will first discuss what the worker executable does, but keep in mind that it will never be called by itself directly (though
you can do so to test).
worker, the children
The worker takes in one command line argument. For example, if you were running it directly you would call it like:
./worker 5
As it is being called with the number 5, it would do 5 iterations over a loop.
So what does it do in that loop? Each iteration it will output its PID, its parents PID, and what iteration of the loop it is in. For
example, suppose its PID is 6577, its parents PID is 6576 and it is the 3rd iteration of the loop, it would output:
WORKER PID:6577 PPID:6576 Iteration:3 before sleeping
After doing this output, it should do sleep(1), to sleep for one second, and then output:
WORKER PID:6577 PPID:6576 Iteration:3 after sleeping
You should test this by itself, but it will not be called by itself normally.
Linux System Calls 2
oss, the parent
The task of oss is to launch a certain number of worker processes with particular parameters. These numbers are determined
by its own command line arguments.
Your solution will be invoked using the following command:
oss [-h] [-n proc] [-s simul] [-t iter]
The proc parameter stands for number of total children to launch, iter is the number to pass to the worker process and the simul
parameter indicates how many children to allow to run simultaneously.
For example, if I wanted to launch oss such that it would launch 5 worker processes, never allow more than 3 to be running at
the same time, and then have each of the workers do 7 iterations, it would be called with:
oss -n 5 -s 3 -t 7
If called with the -h parameter, it should simply output a help message (indicating how it is supposed to be run) and then
terminating.
So now that I know what parameters it should run with, what should it do? oss when launched should go into a loop and
start doing a fork() and then an exec() call to launch worker processes. However, it should only do this up to simul number of
times. In our above example, we would launch no more than 3 initially. The oss would then wait() until one of the children had
finished before launching another.
Implementation details
It is required for this project that you use version control (git), a Makefile, and a README. Your README file should consist,
at a minimum, of a description of how to compile and run your project, any outstanding problems that it still has, and any
problems you encountered.
Your makefile should also compile BOTH executables every time. This requires the use of the all prefix.
Suggested implementation steps
1. Set up your git repository, if you have not already done so. You should periodically check your code into the git repository
(once a day, or whenever you make and test substantial changes). [Day 1]
2. Create your Makefile and barebones skeleton of oss and worker. Make sure that if you change either one, the makefile
will compile both. [Day 2]
3. Write code to parse options and receive the command parameters. Study getopt(3), if you do not know how to do it.
The man page also has an example to guide you. [Day 3]
4. Implement the worker taking in an option and doing its loop and output. [Day 4]
5. Implement oss to fork() and then exec() off one worker to do its task and wait() until it is done. [Day 5]
6. Get oss to fork off workers up until the -n parameter [Day 6-7]
7. Implement the simultaneous restriction [Day 8-9]
8. Testing and make sure your README file indicates how to run your project. Give a one-line example that would let me
know how to run it. DO NOT SIMPLY COPY/PASTE THIS DOCUMENT INTO THE README [Day 10+]
Linux System Calls 3
Criteria for success
Please follow the guidelines. Start small, implement one functionality, test. Do not wait until the last minute and contact me if
you are having issues.
Grading
1. Overall submission: 10 pts. Program compiles and upon reading, seems to be able to solve the assigned problem.
2. Code readability: 10 pts. The code must be readable, with appropriate comments. Author and date should be identified.
3. Command line parsing: 10 pts. Program is able to parse the command line appropriately, assigning defaults as needed;
issues help if needed.
4. Makefile: 10 pts. Makefile works, compiles both files even if both are changed or one is changed. Also ensure your
Makefile can do a clean.
5. README: 10 pts. Must address any special things you did, or if you missed anything.
6. Conformance to specifications: 50 pts. Does your application do the task.
Submission
Handin an electronic copy of all the sources, README, Makefile(s), and results. Create your programs in a directory called
username.1 where username is your login name on hoare. Once you are done with everything, remove the executables and
object files, and issue the following commands:
chmod 700 username.1
cp -p -r username.1 /home/hauschild/cs4760/assignment1
If you have to resubmit, add a .2 to the end of your directory name and copy that over.
Do not forget Makefile (with suffix or pattern rules), your versioning files (.git subdircetory), and README for the assign-
ment. If you do not use version control, you will lose 10 points. I want to see the log of how the program files are modified.
Therefore, you should use some logging mechanism, such as git, and let me know about it in your README. You must check
in the files at least once a day while you are working on them. I do not like to see any extensions on Makefile and README
files.
Before the final submission, perform a make clean and keep the latest source checked out in your directory.
