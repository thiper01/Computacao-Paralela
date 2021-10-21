/* 
  Thiago Perissinotti
  41903447
 Link do GitHub:
 https://github.com/thiper01/Computacao-Paralela/tree/main/Lab7
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int threads;
double soma;
long long num = 100000;
double pi_res;

void* Thread_sum(void* rank){
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = num/threads;
  long long my_first_i = my_n*my_rank;
  long long my_last_i = my_first_i + my_n;

  if(my_first_i % 2 == 0){
  factor = 1.0;
  }
  else{
    factor = - 1.0;
  }
  for(i = my_first_i; i < my_last_i; i++, factor = -factor){
    soma += factor/(2*i+1);
  }
  pi_res = soma*4;
  return NULL;
}

int main(int argc, char* argv[]) //main
{
    long thread;
    pthread_t* thread_handles;
    printf("Digite o número de threads a serem utilizados: ");
    scanf("%d", &threads);

    thread_handles = malloc(threads*sizeof(pthread_t));

    for(thread = 0;thread < threads;thread++) //cria as pthreads
    {
        pthread_create(&thread_handles[thread],NULL,Thread_sum,(void*)thread);
    }
    printf("Chamando a função\n");
    for(thread = 0;thread < threads;thread++) //Realiza as pthread de fato
    {
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);
    
    printf("pi = %lf", pi_res);

    return 0;
}
