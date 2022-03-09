#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct arguments {
	int N, P, X;
	int thread_id;
	int *numar_aparitii;
	int *v;
	int *suma_partiala;
	pthread_barrier_t *bariera;
} arguments;

void get_args(int argc, char **argv, int *N, int *P, int *X)
{
	if(argc < 4) {
		printf("Numar insuficient de parametri: ./practic N P X\n");
		exit(1);
	}

	*N = atoi(argv[1]);
	*P = atoi(argv[2]);
	*X = atoi(argv[3]);
}

void *thread_function(void *arg)
{
	struct arguments argumente = *(struct arguments *)arg;

	int start = argumente.thread_id * (double) argumente.N / argumente.P;
	int end   = fmin((argumente.thread_id + 1) * (double) argumente.N / argumente.P, argumente.N);

	argumente.numar_aparitii[argumente.thread_id] = 0;
	argumente.suma_partiala[argumente.thread_id] = 0;
	for(int i = start; i < end; i++) {
		if (argumente.v[i] == argumente.X) {
			argumente.numar_aparitii[argumente.thread_id]++;
			argumente.suma_partiala[argumente.thread_id] += i;
		}
	}

	pthread_barrier_wait(argumente.bariera);

	if (argumente.thread_id == 0) {
		int suma_finala = 0;
		int aparitii_finale = 0;
		for (int i = 0; i < argumente.P; i++) {
			suma_finala += argumente.suma_partiala[i];
			aparitii_finale += argumente.numar_aparitii[i];
		}

		printf("%d %d\n", aparitii_finale, suma_finala);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int N, P, X;
	
	get_args(argc, argv, &N, &P, &X);

	pthread_t tid[P];
	struct arguments argumente[P];
	int numar_aparitii[P];
	int suma_partiala[P];
	int v[N];
	pthread_barrier_t bariera;
	pthread_barrier_init(&bariera, NULL, P);

	for (int i = 0; i < N; i++) {
		v[i] = (i + 3) % 5;
	}

	// se creeaza thread-urile
	for (int i = 0; i < P; i++) {
		argumente[i].thread_id = i;
		argumente[i].numar_aparitii = numar_aparitii;
		argumente[i].v = v;
		argumente[i].suma_partiala = suma_partiala;
		argumente[i].N = N;
		argumente[i].P = P;
		argumente[i].X = X;
		argumente[i].bariera = &bariera;
		pthread_create(&tid[i], NULL, thread_function, &argumente[i]);
	}

	// se asteapta thread-urile
	for (int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_barrier_destroy(&bariera);

	return 0;
}
