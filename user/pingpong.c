#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
   int p[2];
   int p2[2];
   pipe(p);
   pipe(p2);
   char buffer[1];
   int pid = fork();
   write(p[1], &buffer, 1);
   close(p[0]);
   if (pid == 0) {
     read(p[0], &buffer, 1);
     close(p[1]);
     printf("%d: received ping\n", getpid());
     write(p2[1], &buffer, 1);
     close(p2[0]);
     exit(0);
   } else {
     read(p2[0], &buffer, 1);
     close(p2[1]);
     printf("%d: received pong\n", getpid());
     exit(0);
   }
   exit(0);
}
