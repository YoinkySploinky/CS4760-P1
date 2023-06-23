#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])  {

//Converts the cstring value from oss's -t value back to an int
  int iterations = atoi(argv[1]);
  
  cout << "Worker has started with " << iterations << " iterations" << endl;
  
  for (int i = 0; i < iterations; i++) {
  
    cout << "Worker PID: " << getpid() << " PPID: " << getppid() << " Iteration: " << i+1 << " before sleeping" << endl;
    sleep(1);
    cout << "Worker PID: " << getpid() << " PPID: " << getppid() << " Iteration: " << i+1 << " after sleeping" << endl; 
  }

  return 0;

}