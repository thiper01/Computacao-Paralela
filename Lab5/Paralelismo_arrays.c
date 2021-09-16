/*THIAGO PERISSINOTTI
  TIA: 41903447
*
  MULTIPLICAÇÃO DE UM ARRAY ALEATÓRIO POR 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define ARRAY_S 10

int v[ARRAY_S];

void* arrayX4 (void *arg) {
  int *processo = (int *)(arg);
  if(*processo == 1){
    for (int i = 0; i < ARRAY_S / 2; i++){
      v[i] = v[i] * 4;
    }
  }
  else {
      for (int i = ARRAY_S / 2; i < ARRAY_S; i++){
      v[i] = v[i] * 4;
    }
  }
  pthread_exit(arrayX4);
} 

int main() {
  pthread_t thread1, thread2;
  int a1 = 1;
  int a2 = 2;
  srand(time(0));

  printf("Array antes: \n");
  for(int i = 0; i < ARRAY_S; i++) {
    v[i] = rand() % 50;
  }
  for(int i = 0; i < ARRAY_S; i++) {
    printf("%d ", v[i]);
  }

  pthread_create(&thread1, NULL, arrayX4, (void *)(&a1));
  pthread_create(&thread2, NULL, arrayX4, (void *)(&a2));

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Array depois: \n");
  for(int i = 0; i < ARRAY_S; i++) {
    printf("%d ", v[i]);
  }

  exit(0);
}
