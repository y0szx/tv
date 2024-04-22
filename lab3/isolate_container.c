#define _GNU_SOURCE 
#include <fcntl.h> 
#include <sched.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/mount.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
 
#define SIZE_STACK 1048576 
 
static char stack[SIZE_STACK]; 
static int start(void *arg); 
 
int main() { 
  int flags = CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD; 
  int options = 0; 
 
  waitpid(clone(start, stack + SIZE_STACK, flags, NULL), NULL, options); 
  return 0; 
} 
 
static int start(void *arg) { 
  printf("Container PID: %ld\n", (long)getpid()); 
  char name[10] = "proc"; 
 
  mount(name, "/proc", name, 0, NULL); 
  mount(NULL, "/", NULL, MS_PRIVATE | MS_REC, NULL); 
 
  char file_path[100] = "/sys/class/net/dummy0"; 
 
  int dummy_fd = open(file_path, O_WRONLY | O_CREAT, 0644); 
  char fail_create[100] = "Failed to create dummy0 interface"; 
  if (dummy_fd == -1) { 
    perror(fail_create); 
    exit(EXIT_FAILURE); 
  } 
  write(dummy_fd, "dummy0", 6); 
  close(dummy_fd); 
 
  char link_setup[100] = "ip link set dummy0 up"; 
  char addr_add[100] = "ip addr add 192.168.0.1/24 dev dummy0"; 
 
  system(link_setup); 
  system(addr_add); 
 
  char path[100] = "/bin/bash"; 
 
  execl(path, "bash", NULL); 
 
  return 0; 
}
