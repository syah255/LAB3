#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(void) {
   
     void sigint_handler(int sig);
     char s[200];

     if (signal(SIGINT, sigint_handler) == SIG_ERR){
          perror("signal");
          exit(1);
        }


    int number;
    int pipefd[2];
    int buffer;
    pipe(pipefd);

    pid_t pid = fork();

    if(pid == 0) {
        close(pipefd[0]);
        printf("enter a number to determine whether it is a prime number or not: ");
        scanf("%d", &number);
        write(pipefd[1], &number, sizeof(number));
        printf("Passing control back to parent...\n");

        exit(EXIT_SUCCESS);
                 }

    else if(pid > 0) {
        printf("Passing control to child process...\n");
        wait(NULL);
        close(pipefd[1]);
        read(pipefd[0], &buffer, sizeof(int));
        close(pipefd[0]);

        if(buffer <= 3) {
            if(buffer == 1||buffer == 0 ) {
                printf("%d is not a prime number.\n", buffer);
            }
            else {
                printf("%d is a prime number.\n", buffer);
            }
            
            exit(EXIT_SUCCESS);
                        }

          if(buffer > 3) {
            for(int i = 2; i <= buffer / 2; i++) {
                if(buffer % i == 0) {
                    printf("%d is not a prime number.\n", buffer);
                    exit(EXIT_SUCCESS);}
                else {
                    printf("%d is a prime number.\n",buffer);
                    exit(EXIT_SUCCESS);
                           }
                       }
             }

           printf("Job is done.\n");
             }
            else {
                   perror("Error");
             }

    return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
  printf("\nThis is a special signal handler for SIGINT! \n");
}

