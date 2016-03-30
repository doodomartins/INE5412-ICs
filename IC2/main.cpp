#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHARED_OBJ_NAME     "/oioioi1234"
#define MAX_MSG_LENGTH      18

struct message_struct {
    pid_t sender;
    int type;
    char content[MAX_MSG_LENGTH];
};

using namespace std;
int main() {
    int shared_object;
    int shared_seg_size = sizeof(struct message_struct);   
    struct message_struct *shared_message;  
    pid_t pid;

    cout << "Parent process " << getpid() << " is creating a child process" << endl;
    
    /* duplicate process */
    pid = fork();
    /* if error in duplicating */
    if(pid < 0){
        return -1;
    }
    
    /* if child-process running then */
    if(pid == 0){

        cout << "Child process " << getpid() << " is creating a shared memory object to write a message in" << endl;

        /*
			O_CREAT Cria o objeto compartilhado.
			O_RDWR Abre o objeto para leitura e escrita.
			O_EXCL Para retornar um erro caso ja exista um objeto com esse nome
			mode_t S_IRWXU Para o proprietário ler e escrever
        */

        shared_object = shm_open(SHARED_OBJ_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRWXU);/* create shared object */
        if (shared_object < 0) {	
            cout << "Error "<< shared_object << " creating shared object" << endl;
            return -1;
        }
        /*  make room for the shared object to fit a message*/
        ftruncate(shared_object, shared_seg_size);
       
        /* map the shared onject to memory */
        /*
        	PROT_READ | PROT_WRITE Proteção para leitura e escrita.
        	MAP_SHARED Para memória compartilhada.
        */
        shared_message = (struct message_struct *) mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_object, 0);

        if (shared_message == NULL) {
            cout << "Error in memory map" << endl;
            return -1;
        }
        /* producing a message on the shared segment */
        shared_message->type = 1;
	    shared_message->sender = getpid();
	    strcpy(shared_message->content, "message to be sent");
        cout << "Child process " << getpid() << " wrote message '" << shared_message->content << "' in memory" << endl;
        return 0;
    } 


    /* if parent-process running then */
    if(pid > 0){
        cout << "Parent process " << getpid() << " is waiting for child to exit" << endl;
        /* wait for child process to exit and get its status */

        int status, err = 0;
        err = waitpid(pid, &status, 0);
       
	    /* if status is not success */
        if(WEXITSTATUS(status) < 0){
	        cout << "Parent process " << getpid() << " is exiting since child could not write message in memory" << endl;
	        return -1;
	    }
	
        cout << "Parent process " << getpid() << " will read message from process " << pid << " finished with status "<< WEXITSTATUS(status) << endl;
        /* create the shared object to read from */
        shared_object = shm_open(SHARED_OBJ_NAME, O_RDWR, S_IRWXU); 
        
        if (shared_object < 0) {
            cout << "Error in shm_open()" << endl;
            return -1;
        }
 
        /* map the shared object to memory */
        shared_message = (struct message_struct *) mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_object, 0);
 
        if (shared_message == NULL) {
            cout << "Error in memory map" << endl;
            return -1;
        }

        cout << "Parent process " << getpid() << " read the message '" << shared_message->content << "' from sender " << shared_message->sender << " in memory " << endl;
   
        int removed = shm_unlink(SHARED_OBJ_NAME);
        if (removed != 0) {
            cout << "Error removing the shared object" << endl;
            return -1;
        }
    }
}