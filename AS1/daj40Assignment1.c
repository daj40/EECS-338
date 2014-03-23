#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char hostname[255];
	struct timeval tv;
	struct rusage res;
	pid_t pid, wpid;
	//main process 
	int A = 100,
		i,
		status,	
		thisisapid = getpid();
	// fork 3 children
	for(i = 0; i < 3; i++) {
		pid = fork();
		if(pid == -1) {
			} else if(pid == 0) { // execute children
				thisisapid = getpid();
				sleep(i);
				A += 100;
				printf("\t%d: A = %d\n", getpid(), A);
			if(i == 0) { //Child One
				printf("username = %s\n", getlogin());
				printf("\t%d: ppid = %d\n", thisisapid, getppid());
				printf("\t%d: hostname = %s\n", thisisapid, hostname);
			} else if(i == 1) { // Child two
				printf("\t%d: time = %s", thisisapid, ctime(&tv.tv_sec));
				printf("\t%d: userid = %d\n", thisisapid, getuid());
			} else if(i == 2) { // Child three
				printf("\t%d: groupid = %d\n", thisisapid, getgid());
				printf("\t%d: user time = %ld.%06lds\n", thisisapid,
					res.ru_utime.tv_sec,
					(long) res.ru_utime.tv_usec);
				printf("\t%d: sys time = %ld.%06lds\n", thisisapid,
					res.ru_stime.tv_sec,
					(long) res.ru_stime.tv_usec);
				printf("\t%d: max resident set size = %ld\n", thisisapid,res.ru_maxrss);
				printf("\t%d: shared memory = %ld\n", thisisapid, res.ru_ixrss);
				printf("\t%d: unshared data = %ld\n", thisisapid, res.ru_idrss);
				printf("\t%d: unshared stack = %ld\n", thisisapid, res.ru_isrss);
				printf("\t%d: page reclaims = %ld\n", thisisapid, res.ru_minflt);
				printf("\t%d: page faults = %ld\n", thisisapid, res.ru_majflt);
				printf("\t%d: swaps = %ld\n", thisisapid, res.ru_nswap);
				printf("\t%d: block inputs = %ld\n", thisisapid, res.ru_inblock);
				printf("\t%d: block outputs = %ld\n", thisisapid, res.ru_oublock);
				printf("\t%d: messages sent = %ld\n", thisisapid, res.ru_msgsnd);
				printf("\t%d: messages received = %ld\n", thisisapid, res.ru_msgrcv);
				printf("\t%d: signals received = %ld\n", thisisapid, res.ru_nsignals);
				printf("\t%d: voluntary context switches = %ld\n", thisisapid, res.ru_nvcsw);
				printf("\t%d: involuntary context switches = %ld\n", thisisapid, res.ru_nivcsw);
			}
			fflush(stdout);
			_exit(-1);
		}
	}

	// wait for children to complete
	while((wpid = wait(&status)) > 0) {
		printf("%d: %d exit with status %d\n\n", thisisapid, (int)wpid, status);
		fflush(stdout);
	}
	printf("%d: A = %d\n\n", thisisapid, A);
	fflush(stdout);
}