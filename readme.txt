Name: Trent Hollenkamp-Geragosian
Project: Project 1
Date: 1/31/2023


Usage: ./oss [-h] -n proc -s simul -t iter
There are no default options

Issues with getopt() in that the default option was never procing when no params where given in the command line (ex. entering just ./oss). To get around this I had an argc checker at the very beggining to insure that if only one arg was given to error out.
When forking the child processes the program will wait -s times but will then do the next series of children in a batch (ex. if -n is 9 and -s is 3 the program will do 3 children and when finished will do the next three all at once instead of feeding them in one at a time.) I don't know if this is cause the server completes the children so fast I can't tell if there is a gap in the next process starting.

