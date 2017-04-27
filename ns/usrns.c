#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/capability.h>

#define STACK_SIZE (1024*1024)

static char child_stack[STACK_SIZE];

char * const child_args[] ={
  "/bin/bash",
  NULL
};

int child_main(void *args) {
  printf("in child process!\n");
  cap_t cap;
  printf("euid=%ld, egid=%ld\n", (long)geteuid(), (long)getegid());
  cap = cap_get_proc();
  printf("cap: %s\n", cap_to_text(cap, NULL));
  execv(child_args[0], child_args);
  return 1;
}

int main() {
  printf("start in main program\n");
  int child_pid = clone(child_main, child_stack+STACK_SIZE, CLONE_NEWUSER |SIGCHLD, NULL);
  waitpid(child_pid, NULL, 0);
  printf("end in main program\n");
  return 0;
}
