#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforo1;
sem_t semaforo2;
sem_t semaforo3;
int repeticao;

void *thr_Hidrogenio(void *arg){
    int i = 0;
    int aux = 0;
    int contador = 0;

    for (;;){
        printf("H");
        aux++;
        if (aux == 2){
            aux = 0;
            contador++;
            sem_post(&semaforo1);
            sem_wait(&semaforo3);
        }

        if (contador == repeticao){
            sem_post(&semaforo1);
            pthread_exit(NULL);
        }
    }
}

void *thr_Enxofre(void *arg){
    int aux = 0;
    int contador = 0;

    sem_wait(&semaforo1);
    for (;;){
        printf("S");
        aux++;
        if (aux == 1){
            aux = 0;
            contador++;
            sem_post(&semaforo2);
            sem_wait(&semaforo1);
        }
        if (contador == repeticao){
            sem_post(&semaforo2);
            pthread_exit(NULL);
        }
    }
}

void *thr_Oxigenio(void *arg){
    int aux = 0;
    int contador = 0;

    sem_wait(&semaforo2);
    for (;;){

        printf("O");
        aux++;
        if (aux == 4){
            aux = 0;
            contador++;
            printf("\n");
            sem_post(&semaforo3);
            sem_wait(&semaforo2);
        }
        if (contador == repeticao)
            pthread_exit(NULL);
    }
}

int main(void){
    pthread_t t1, t2, t3;

    printf("Numero de repeticoes: ");
    scanf("%d", &repeticao);

    // 3 Semáforos para cada elemento
    sem_init(&semaforo1, 0, 0);
    sem_init(&semaforo2, 0, 0);
    sem_init(&semaforo3, 0, 0);

    pthread_create(&t3, NULL, *thr_Oxigenio, NULL);
    pthread_create(&t2, NULL, *thr_Enxofre, NULL);
    pthread_create(&t1, NULL, *thr_Hidrogenio, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&semaforo1);
    sem_destroy(&semaforo2);
    sem_destroy(&semaforo3);

    return 0;
}
