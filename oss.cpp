#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/wait.h>


using namespace std;

int main(int argc, char *argv[])  {

//Had issues with default selection in switch decided to have an argc catch at the beginning to insure that more than one option is given
  if (argc == 1) {
  
    cout << "Error! No parameters given, enter ./oss -h for how to operate this program" << endl;
    exit(1);

  }
  
  int opt, optCounter = 0;
  int nValue, sValue, tValue;

//opt function to collect command line params  
  while ((opt = getopt ( argc, argv, "hr:n:s:t:" ) ) != -1) {
    
    optCounter++;
    
    switch(opt) {
    
      case 'h':
        cout << "Usage: ./oss -n proc -s simul -t iter" << endl;
        cout << "-n: The number of child processes to be made." << endl;
        cout << "-s: The number of simultaneous child processes. This number cannot be higher than 18." << endl;
        cout << "-t: The number of iterations the child process will go through when called." << endl;
        exit(1);
      
      case 'n':
        nValue = atoi(optarg);
        if (nValue < 0) {
          while(nValue < 0) {
            cout << "Error! -n value was a negative number! Please provide a number equal to or greater than 0: ";
            cin >> nValue;
          }
        }
        break;
        
      case 's':
        sValue = atoi(optarg);
        if (sValue < 0 || sValue > 18) {
          while(sValue < 0 || sValue > 18) {
            cout << "Error! -s value was a negative number or greater than 18! Please provide a number equal to or greater than 0 and less than 19: ";
            cin >> sValue;
          }
        }
        break;
      
      case 't':
        tValue = atoi(optarg);
        if (tValue < 0) {
          while(tValue < 0) {
            cout << "Error! -t value was a negative number! Please provide a number equal to or greater than 0: ";
            cin >> tValue;
          }
        }
        break;
    }
  
  }
  if (( argc > 1) && (optCounter < (3))) { 
  
        cout << "Error! There are no defaults for this program! One of the parameters was not set! Please use -h for proper usage of .oss" << endl;
        exit(1);
        
    } 
  
//Since project was built in cpp use snprintf to convert the -t value to a cstring so it can be passed to the exec() function
//This is done due the tValue being able to modified in code so I believe we are not able to pull from argv[]
  char str[50];
  snprintf(str, sizeof(str), "%d", tValue);
  char *args[]={"./worker", str, NULL};
  
//Loop for -n times, if the for loop reaches the -s value it will wait() until children are done before continuing
  for (int i = 0; i < nValue; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      execvp(args[0],args);
      cout << "Exec failed! Terminating" << endl;
      exit(1);
    }
    else {
      if (i == sValue-1) {
        sValue++;
        wait(NULL);
      }
    }
  }
  
//catch all wait() for when -s > -n and to ensure that all children still have a parent id
  while(wait(NULL) > 0);
  cout << "Oss finished" << endl;
  return 0;
  
}