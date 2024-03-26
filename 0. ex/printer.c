#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int jobs = 0;
int total_pages = 0;
void printer(int worker, int pages){
    printf("Worker %d printing Job: %d\n", worker, jobs);
    FILE *file = fopen("printer.txt", "a");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    int i;
    for(i=0;i<pages;i++){
        printf("Worker %d Job: %d \t Page %d of %d\n", worker, jobs, i+1, pages);
        fprintf(file, "Woker %d Job: %d \t Page %d of %d\n", worker, jobs, i+1, pages);
        usleep(333 * 1000);
        total_pages++;
    }
    fprintf(file, "-----------------------------\n");
    fclose(file);
    printf("Worker %d finished printing %d pages\n", worker, pages);
    jobs++;
}
void* routine(void* args){
    //to be implemented
    return NULL;
}
int main(){
    //you should add threads of course :)
    //how to generate random number from 1 to 6 ???
    srand(time(0));
    int x = 1 + rand() % 6;
    printf("Random number from 1 to 6: %d\n", x);
    //----------------------------------------------
    printer(0, 3);
    printer(1, 2);
    printf("Total Printed Pages: %d\n", total_pages);
    return 0;
}