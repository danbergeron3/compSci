#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *arv[]) {
	//create first pipe fd1
	int fd1[2];
	if(pipe(fd1) == -1) {
		fprintf(stderr, "pipe error fd1\n");
		return 1;
	}
	// fork first child
	pid_t pid = fork(); // create first child for sort
	if (pid < 0) {
	// fork error
		fprintf(stderr, "fork error\n");
		return 1;
	}
	if (pid == 0) { // first child process, run sort
		
		// tie write end of pipe fd1 to standard output (file descriptor 1)
		dup2(fd1[1],  STDOUT_FILENO);
		// close read end of pipe fd1
		close(fd1[0]);
		// start the sort command using execlp
		execlp("/usr/bin/sort", "sort", NULL);
		// should not get here
		fprintf(stderr, "execlp error\n");
		return 1;
	}
	//create second pipe fd2
	int fd2[2];
	if(pipe(fd2) == -1) {
		fprintf(stderr, "pipe error fd2\n");
		return 1;
	}
	// fork second child
	pid = fork(); // create second child for uniq
	if (pid < 0) {
		fprintf(stderr, "fork error\n");
		return 1;
		// fork error
	}
	if (pid == 0) { // second child process, run uniq
		// tie read end of fd1 to standard input (file descriptor 0)
		dup2(fd1[0], STDIN_FILENO);
		// tie write end of fd2 to standard output (file descriptor 1)
		dup2(fd2[1], STDOUT_FILENO);
		// close write end of pipe fd1
		close(fd1[1]);
		// close read end of pipe fd2
		close(fd2[0]);
		// start the uniq command using execlp
		execlp("/usr/bin/uniq", "uniq", NULL);
		// should not get here
		fprintf(stderr, "execlp error\n");
		return 1;
	}
	// fork third child
	pid = fork(); // create third child for wc -l
	if (pid < 0) {
		// fork error
		fprintf(stderr, "fork Error\n");
		return 1;
	}
	if (pid == 0) { // third child process, run wc -l
		// tie read end of fd2 to standard input (file descriptor 0)
		dup2(fd2[0], STDIN_FILENO);
		// Close write end of pipe fd2
        close(fd2[1]);
        // Close read end of pipe fd1
        close(fd1[0]);
        // Close write end of pipe fd1
        close(fd1[1]);
		// start the wc -l command using execlp
		execlp("/usr/bin/wc", "wc", "-l", NULL);
		// should not get here
		fprintf(stderr, "execlp error\n");
		return 1;
	}
	// parent process code
	// close both ends of pipes fd1 and fd2
	close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
	// wait for third process to end.
	waitpid(pid, NULL, 0);
}
