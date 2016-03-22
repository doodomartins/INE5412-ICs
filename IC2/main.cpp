#include <iostream>
    2 #include <unistd.h>
    3 #include <fcntl.h>
    4 #include <cstring>
    5 #include <sys/mman.h>
    6 #include <sys/types.h>
    7 #include <sys/stat.h>
    8 #include <sys/wait.h>
    9 
   10 #define SHARED_OBJ_NAME     "/oioioi1234"
   11 #define MAX_MSG_LENGTH      /* max length */
   12 
   13 struct message_struct {
   14     pid_t sender;
   15     int type;
   16     char content[MAX_MSG_LENGTH];
   17 };
   18 
   19 using namespace std;
   20 int main() {
   21     int shared_object;
   22     int shared_seg_size = sizeof(struct message_struct);   
   23     struct message_struct *shared_message;  
   24 
   25     cout << "Parent process " << /* process ID */ << " is creating a child process" << endl;
   26     
   27     /* duplicate process */
   28     
   29     /* if error in duplicating */
   30         return -1;
   31         
   32     /* if child-process running then */
   33         cout << "Child process " << /* process ID */ << " is creating a shared memory object to write a message in" << endl;
   34         shared_object = /* create shared object */
   35         if (shared_object < 0) {
   36             cout << "Error "<< shared_object << " creating shared object" << endl;
   37             return -1;
   38         }
   39         /*  make room for the shared object to fit a message*/
   40         //...
   41         shared_message = (struct message_struct *) /* map the shared onject to memory */
   42         if (shared_message == NULL) {
   43             cout << "Error in memory map" << endl;
   44             return -1;
   45         }
   46         /* producing a message on the shared segment */
   47         shared_message->type = 1;
   48 	    shared_message->sender = /* process ID */
   49 	    strcpy(shared_message->content, /* message to be sent */);
   50         cout << "Child process " << /* process ID */ << " wrote message '" << shared_message->content << "' in memory" << endl;
   51         return 0;
   52       
   53     /* if parent-process running then */
   54         cout << "Parent process " << /* process ID */ << " is waiting for child to exit" << endl;
   55         /* wait for child process to exit and get its status */
   56 	    /* if status is not success */
   57 	        cout << "Parent process " << /* process ID */ << " is exiting since child could not write message in memory" << endl;
   58 	        return -1;
   59 	
   60         cout << "Parent process " << /* process ID */ << " will read message from process " << /* child process ID */ << " finished with status "<< /* status of finished child process */ << endl;
   61         shared_object = /* create the shared object to read from */
   62         if (shared_object < 0) {
   63             cout << "Error in shm_open()" << endl;
   64             return -1;
   65         }
   66             
   67         shared_message = (struct message_struct *)/* map the shared object to memory */
   68         if (shared_message == NULL) {
   69             cout << "Error in memory map" << endl;
   70             return -1;
   71         }
   72 
   73         cout << "Parent process " << /* process ID */ << " read the message '" << shared_message->content << "' from sender " << shared_message->sender << " in memory " << endl;
   74    
   75         int removed = /* remove the shared object */
   76         if (removed != 0) {
   77             cout << "Error removing the shared object" << endl;
   78             return -1;
   79         }
   80     }
   81 }