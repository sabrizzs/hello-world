#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void nem_eu_nem_de_ninguem(char *file_path){
    int result = chmod(file_path, 000);
    if (result != 0) {
        perror("Erro");
    }
}

void soh_eumesmo(char *file_path){
    if(chmod(file_path, 0700) == -1){
        perror("Erro");
    }
}

void rodaeolhe(char *program_path){
    pid_t pid = fork();
    int status;

    if(pid<0){
        perror("Erro ao criar processo filho");
        return;
    }
    if(pid == 0){
        if (execve(program_path, NULL, NULL) == -1) {
            perror("Falha no execve()");
            exit(1);
        }
    } else {
        wait(&status);
        printf("Programa '%s' retornou com codigo %d.\n", program_path, WEXITSTATUS(status));
    } 
}

void sohroda(char *program_path){
    pid_t pid = fork();
    
    if(pid<0){
        perror("Erro ao criar processo filho");
        return;
    }

    if(pid == 0){
        close(STDIN_FILENO);
        if (execve(program_path, NULL, NULL) == -1) {
            perror("Falha no execve()");
            exit(1);
        }
    }
}

int main(void){
    char command[50];
    char path[200];

    while(1){

        scanf("%s", command);
        scanf("%s", path);

        if(strcmp(command,"nem_eu_nem_de_ninguem")==0)
            nem_eu_nem_de_ninguem(path);
        
        else if(strcmp(command,"soh_eumesmo")==0)
            soh_eumesmo(path);

        else if(strcmp(command,"rodaeolhe")==0)
            rodaeolhe(path);  

        else if(strcmp(command,"sohroda")==0)
            sohroda(path);
        
        else{
            printf("Comando incorreto, execucao do programa finalizado.\n");
            break;
        }
    }
}