#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


#define LIMIT 35


void filter(int p_left[]) {
    int prime;


    close(p_left[1]);


        if (read(p_left[0], &prime, sizeof(prime)) == 0) {
        close(p_left[0]);
        exit(0);
    }
    

    printf("prime %d\n", prime);
    

    int p_right[2];
    pipe(p_right);
    

    if (fork() == 0) {

        filter(p_right);
    } else {

        int next;
        close(p_right[0]); 
  
        while (read(p_left[0], &next, sizeof(next)) > 0) {
          
            if (next % prime != 0) {
                write(p_right[1], &next, sizeof(next));
            }
        }
        
        close(p_left[0]);
        close(p_right[1]);
        
        
        wait(0);
        exit(0);
    }
}

void primes() {
    int p[2]; 
    pipe(p);
    

    if (fork() == 0) {
        filter(p);
    } else {
      close(p[0]);  
        
        for (int i = 2; i <= LIMIT; i++) {
            write(p[1], &i, sizeof(i));
        }
        
        close(p[1]);
        

        wait(0);
    }
        exit(0);
}

int main(){
    primes();
    exit(0);
}
