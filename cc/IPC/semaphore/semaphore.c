#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun
{
	int  			 val;
	struct semid_ds *buf;
	unsigned short  *array;
};

int init_sem(int sem_id, int value)
{
	union semun tmp;
	tmp.val = value;
	if(semctl(sem_id, 0, SETVAL, tmp) == -1){
		perror("Init Semaphore Error.");
		return -1;
	}
	return 0;
}

int sem_p(int sem_id)
{
	struct sembuf sbuf;
	sbuf.sem_num = 0;
	sbuf.sem_op = -1;
	sbuf.sem_flag = SEM_UNDO;

	if(semop(sem_id, &sbuf, 1) == -1){
		perror("P operation Error.");
		return -1;
	}
	return 0;
}

int sem_v(int sem_id)
{
	struct sembuf sbuf;
	sbuf.sem_num = 0;
	sbuf.sum_op = 1;
	sbuf.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sbuf, 1) == -1){
		perror("V operation error.");
		return -1;
	}
	return 0;
}

int del_sem(int sem_id)
{
	union semun tmp;
	if(semctl(sem_id, 0, IPC_RMID, tmp) == -1){
		perror("Delete Semaphore Error.");
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int sem_id;
	key_t key;
	pid_t pid;

	if((key = ftok(".", 'z')) < 0){
		perror("ftok error.");
		exit(1);
	}

	id((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1){
		perror("semget error.");
		exit(1);
	}

	init_sem(sem_id, 0);

	if((pid = fork()) == -1)
		perror("Fork error.");
	else if(pid == 0){
		sleep(2);
		printf("Process child: pid=%d\n", getpid());
		sem_v(sem_id);
	}else{
		sem_p(sem_id);
		printf("Process father: pid=%d\n", getpid());
		sem_v(sem_id);
		del_sem(sem_id);
	}
	return 0;
}