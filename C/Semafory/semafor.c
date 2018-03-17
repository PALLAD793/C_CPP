#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>

/* POSIX semaphores */

#define QUEUE_SIZE 5
#define ITEMS_TO_PRODUCE 10

unsigned int K = 0; /*ilosc producentow */
unsigned int M = 0; /* ilosc kolejek */


sem_t * allocateEmpty() /* wolne miejsca */
{
  static int shmid = 0;
  if (shmid == 0)
    shmid = shmget(IPC_PRIVATE, sizeof(sem_t), SHM_W|SHM_R);
  if (shmid < 0)
  {
    printf ("shmget error\n");
    abort();
  }
  sem_t * empty = shmat(shmid, NULL, 0); /* NULL - system sam wybiera wolny adres */
  return empty;
}

sem_t * allocateFull() /* zajete miejsca */
{
  static int shmid = 0;
  if (shmid == 0)
    shmid = shmget(IPC_PRIVATE, sizeof(sem_t), SHM_W|SHM_R);
  if (shmid < 0)
  {
    printf ("shmget error\n");
    abort();
  }
  sem_t * full = shmat(shmid, NULL, 0);
  return full;
}

sem_t ** allocateMutex() /* tablica z mutexami dla kolejek */
{
  unsigned int i = 0;

  static int shmid = 0;
  static int shmid2 = 0;

  if (shmid == 0)
  {
    shmid = shmget(IPC_PRIVATE, M*sizeof(sem_t*), SHM_W|SHM_R);
  }
  if (shmid < 0)
  {
    printf ("shmget error\n");
    abort();
  }
  sem_t ** mutex = shmat(shmid,NULL, 0);

  for (i=0; i<M; ++i)
  {
    if (shmid2 == 0)
      shmid2 = shmget(IPC_PRIVATE, sizeof(sem_t), SHM_W|SHM_R);
    if (shmid2 < 0)
    {
      printf ("shmget error\n");
      abort();
    }
    mutex[i] = shmat(shmid2, NULL, 0);
  }

  return mutex;
}

int ** allocateTable() /* tablica ze wskaznikami na kolejki */
{
  static int shmid = 0;
  if (shmid == 0)
    shmid = shmget(IPC_PRIVATE, M*sizeof(int*), SHM_W|SHM_R);
  if (shmid < 0)
  {
    printf ("shmget error\n");
    abort();
  }
  int ** table = shmat(shmid, NULL, 0);
  return table;
}

int  * allocateQueue() /* w queue[0] jest liczba elementow w kolejce */
{
  static int shmid = 0;
  if (shmid == 0)
    shmid = shmget(IPC_PRIVATE, QUEUE_SIZE+1, SHM_W|SHM_R);
  if (shmid < 0)
  {
    printf ("shmget error\n");
    abort();
  }
  int * queue = shmat(shmid, NULL, 0);
  return queue;
}

void initialize()
{
  unsigned int i;

  sem_t * empty = allocateEmpty();
  sem_init(empty, 1, M*QUEUE_SIZE); /* != 0 - shared within processes */

  sem_t * full = allocateFull();
  sem_init(full, 1, 0);

  sem_t ** mutex = allocateMutex();
  for(i=0; i<M; ++i)
  {
    sem_init(mutex[i], 1, 1);
  }

  int ** table = allocateTable();
  for(i=0; i<M; ++i)
  {
    int * queue = allocateQueue();
    queue[0] = 0; /*liczba elementow w kolejce */
    table[i] = queue;
  }
}

void addElement(int ** table, unsigned int nr, int element)
{
  int place_to_put;
  place_to_put = table[nr][0]+1;
  table[nr][place_to_put] = element;
  ++(table[nr][0]);
  printf ("Wstawiono element do kolejki nr %d\n", nr);
}

int getElement(int ** table, unsigned int nr) /* LIFO */
{
  int element;
  unsigned int place_to_get = table[nr][0];
  element = table[nr][place_to_get];
  --(table[nr][0]);
  printf ("Wyjeto element z kolejki nr %d\n", nr);
  return element;
}

unsigned int queueForProducer(int ** table) /* szukamy kolejki z najmniejsza iloscia elementow, do niej wlozy producent */
{
  unsigned int i=0;
  unsigned int smallest;
  unsigned int queue_nr = 0;
  smallest = table[0][0];
    printf("start for producer: kolejka nr %d, ma %d elementow\n", i, table[i][0]);
  for (i=1; i<M; ++i)
  {
    if (table[i][0] < smallest)
    {
      smallest = table[i][0];
      queue_nr = i;
      printf("queue for producer: changed number : %d\n", queue_nr);
    }
      printf("for producer: kolejka nr %d, ma %d elementow\n", i, table[i][0]);
  }
  printf("queue number for producer: %d\n", queue_nr);
  return queue_nr;
}

unsigned int queueForConsumer(int ** table) /* szukamy kolejki z najwieksza iloscia elementow, z niej wezmie konsument */
{
  unsigned int i = 0;
  unsigned int fullest;
  unsigned int queue_nr = 0;
  fullest = table[0][0];
    printf("start for consumer: kolejka nr %d, ma %d elementow\n", i, table[i][0]);
  for (i=1; i<M; ++i)
  {
    if (table[i][0] > fullest)
    {
      fullest = table[i][0];
      queue_nr = i;
      printf("queue for consumer: changed number : %d\n", queue_nr);
    }
      printf("for consumer: kolejka nr %d, ma %d elementow\n", i, table[i][0]);
  }
  printf("queue number for consumer: %d\n", queue_nr);
  return queue_nr;
}

void consumer()
{
  printf ("Consumer starts working\n");
  unsigned int taken_elements = 0;
  unsigned int nr = 0;
  unsigned int return_element = 0;
  unsigned int i =0;

  sem_t * empty = allocateEmpty();
  sem_t * full = allocateFull();
  sem_t ** mutex = allocateMutex();
  int ** table = allocateTable();
  for(i=0; i<M; ++i)
  {
    int * queue = allocateQueue();
    queue[0] = 0; /*liczba elementow w kolejce */
    table[i] = queue;
  }
printf("K: consumer(): %d\n", K);
  while (taken_elements < K*ITEMS_TO_PRODUCE)
  {
    usleep(250000);
    sem_wait(full);
    nr = queueForConsumer(table);
    sem_wait(mutex[nr]);
    return_element = getElement(table, nr);
    sem_post(mutex[nr]);
    sem_post(empty);
  /*  printf ("Konsumer wyjal element z kolejki nr %d", nr);*/
    taken_elements++;
  }
}

void producer()
{
  printf ("Producer starts working\n");
  unsigned int produced_items = 0;
  unsigned int nr = 0;
  int product = 10;
  unsigned int i =0;

  sem_t * empty = allocateEmpty();
  sem_t * full = allocateFull();
  sem_t ** mutex = allocateMutex();
  int ** table = allocateTable();
  for(i=0; i<M; ++i)
  {
    int * queue = allocateQueue();
    queue[0] = 0; /*liczba elementow w kolejce */
    table[i] = queue;
  }

  while (produced_items < ITEMS_TO_PRODUCE)
  {
    usleep(250000);
    sem_wait(empty);
    nr = queueForProducer(table);
    sem_wait(mutex[nr]);
    addElement(table, nr, product);
    sem_post(mutex[nr]);
    sem_post(full);
  /*  printf ("Producent wlozyl element do kolejki nr %d", nr);*/
    ++produced_items;
  }
}

void createConsumer()
{
  int ret = fork();

  if(ret == 0) /* if child */
  {
    consumer();
    exit(0);
  }
}

void createProducer()
{
  int ret = fork();

  if (ret == 0)
  {
    producer();
    exit(0);
  }
}

int main (int argc, char* argv[])  /* argumenty: ilosc producentow, ilosc buforow */
{
  unsigned int i;

  if (argc != 3)
  {
    printf("Niewlasciwa ilosc argumentow.");
  }

  K = atoi (argv[1]);
  M = atoi (argv[2]);

  initialize();

  createConsumer();

  for (i=0; i<K; ++i)
  {
    createProducer();
  }

  while(wait(NULL)>0); /*czeka az wszystkie dzieci skoncza sie wykonywac, zwraca -1 gdy nie ma dzieci */
  return 0;
}
