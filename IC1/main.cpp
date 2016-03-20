#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 
#include <sys/wait.h>
// #include <sys/>

using namespace std;
int main ()
{
   // include declarations you need
   int count = 0;
   int i;
   pid_t pid;
   /* Repeat 5 times */
   for(i = 0; i < 5; i++){
      cout << "Parent process " << getpid() << ": Creating child" << endl;
      /* Duplicate this process */
      pid = fork();
      /* If there was an error on duplication then */
      if(pid < 0){
         cout << "Error on fork()" << endl;
         return -1; 
      } 
      /* If child-process is running then */
      if(pid == 0){
         cout << "Child process " << getpid() << ": Running" << endl;
         count++;
         /* Sleep for 1 second */
         sleep(1);
         cout << "Child process " << getpid() << ": Exiting with status " << count << endl;
         /*Faz com que todos processos que são filhos acabem aqui.*/
         return count;
      }
   }


   /* if this is the parent-process then */
   cout << "Parent process " << getpid() << ": Waiting children to exit" << endl;
   int errno, status, sum = 0;
   /* Parent-process waits for all children to exit, adding each status to the sum variable */
   /* O primeiro parametro é 0 pois estou fazendo o waitpid() em todos os processos filhos. */
   
   while(waitpid(0, &status, ECHILD) != -1){
      sum += WEXITSTATUS(status);
   }

   cout << "Parent process " << getpid() << ": Exiting with sum " <<sum << endl;
   /*  */
   return count;
}