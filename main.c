#include <stdio.h>
#include <stdlib.h>

typedef struct task
{
  char *name;
  int startMonth, endMonth;
  int *dependencies, dependenciesCount;
} Task;

Task SetupTask(int numTasks);
void PrintGantt(Task tasksArray[], int numTasks);


int main(void) {
    int numTasks;
    printf("How many tasks would you like to add?");
    scanf("%d",&numTasks);

    Task tasksArray[numTasks];

    for (int i = 0; i < numTasks; i++)
    {
      tasksArray[i] = SetupTask(numTasks);
      printf("New task added: %s\n", tasksArray[i].name);
    }

    PrintGantt(tasksArray, numTasks);

    return 0;
}
void PrintGantt(Task tasksArray[], int numTasks)
{
    printf("          |January   |February  |March     |April     |May       |June      |July      |August    |September |October   |November  |December  |Dep       |\n");

    for(int i = 0;i<numTasks;i++){
        for(int k = 0;k<14;k++){
            printf("----------|");
        }
        printf("\n");

        printf("%-10s|", tasksArray[i].name);

        for(int j = 1;j<=12;j++){
            if (j >= tasksArray[i].startMonth && j <= tasksArray[i].endMonth) {
                printf("   XXX    |");
            } else{
                printf("          |");
            }
        }
        for(int n = 0;n<tasksArray[i].dependenciesCount;n++){
          printf("%d ",tasksArray[i].dependencies[n]);
        }

        printf("\n");
    }

    for(int i = 0;i<14;i++){
        printf("----------|");
    }
    printf("\n");
}

Task SetupTask(int numTasks)
{

  Task newTask;

  newTask.name = (char*)malloc(sizeof(char));

  printf("Please enter the task name:\n");
  scanf("%s", newTask.name);

  printf("Start month (1-12):\n");
  scanf("%d", &newTask.startMonth);

  while (newTask.startMonth < 1 || newTask.startMonth > 12)
  {
    printf("Invalid month entered. Please enter a number between 1 - 12:\n");
    scanf("%d", &newTask.startMonth);
  }

  printf("End month (%d-12):\n", newTask.startMonth);
  scanf("%d", &newTask.endMonth);

  while (newTask.endMonth < newTask.startMonth || newTask.endMonth > 12)
  {
    printf("Invalid month entered. Please enter a number between %d - 12:\n", newTask.startMonth);
    scanf("%d", &newTask.endMonth);
  }

  printf("Enter how many dependencies this task has:\n");
  scanf("%d", &newTask.dependenciesCount);


  if (newTask.dependenciesCount > 0)
  {
    newTask.dependencies = (int*) malloc(sizeof(int));

    for (int i = 0; i < newTask.dependenciesCount; i++)
    {
      printf("Enter dependent task (0 - %d):\n", numTasks - 1);
      scanf("%d", &newTask.dependencies[i]);

      while (newTask.dependencies[i] < 0 || newTask.dependencies[i] >= numTasks)
      {
        printf("Invalid number entered. Please enter a number between 0 - %d:\n", numTasks - 1);
        scanf("%d", &newTask.dependencies[i]);
      }
    }
  }

  return newTask;

}
