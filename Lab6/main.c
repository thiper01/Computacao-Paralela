/* 
  Thiago Perissinotti
  41903447

 Link do GitHub:
 https://github.com/thiper01/Computacao-Paralela/tree/main/Lab6
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count = 3;// igual ao tamanho da matriz
const int a = 3;//linhas de matriz A
const int b = 3;//colunas de matriz x
const int A[3][3] = {
  {1,2,3}, 
  {4,5,6}, 
  {7,8,9}
  };
int x[3] = {10,100,50};
int m_result[3];//matriz resultado, tem que ser do mesmo tamanho de colunas que x

void *Pth_mat_vect(void* rank){
  long my_rank = (long) rank;
  int i, j;

  int local_m = a/thread_count;
  int my_first_row = my_rank*local_m;
  int my_last_row = (my_rank+1)*local_m - 1;
  
  for(i = my_first_row; i <= my_last_row; i++){
    m_result[i] = 0.0;
    for(j = 0; j < b; j++){
      m_result[i] += A[i][j]*x[j];

    }
  }
  return NULL;
} 

int main(int argc, char* argv[])
{
    long thread;
    pthread_t* thread_handles;

    thread_handles = malloc(thread_count*sizeof(pthread_t));

    for(thread = 0;thread < thread_count;thread++) //cria as pthreads
    {
        pthread_create(&thread_handles[thread],NULL,Pth_mat_vect,(void*)thread);
    }
    printf("Chamando a função\n");
    for(thread = 0;thread < thread_count;thread++) //Realiza as pthread de fato
    {
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);
    int i;

    for(i = 0; i < thread_count; i++){ //Imprime valores de y
      printf("y[%d] = ", i);
      printf("%d\n", m_result[i]);
    
    }
  
    return 0;
}


