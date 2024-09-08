#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUF_SIZE 512
#define ARG_LIMIT 32

int main(int argc, char *argv[]) {
if (argc < 2) {
    printf("Usage: xargs <command>\n");
exit(1);
}

    char buf[BUF_SIZE];
int n;
    char *xargv[ARG_LIMIT];

for (int i = 1; i < argc; i++) {
    xargv[i - 1] = argv[i];
}

int xargc = argc - 1;

while ((n = read(0, buf, sizeof(buf))) > 0) {
int start = 0;
for (int i = 0; i < n; i++) {
    if (buf[i] == '\n') {
buf[i] = 0;

if (xargc + 1 >= ARG_LIMIT) {
    printf("Error: too many arguments\n");
exit(1);
}

    xargv[xargc] = buf + start;
xargv[xargc + 1] = 0;

if (fork() == 0) {
    exec(xargv[0], xargv);
    exit(1);
} else {
wait(0);
}

start = i + 1;
    xargc++;
    }
}
}

    exit(0);
}

