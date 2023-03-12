#include <stdio.h>
#include <stdlib.h>

typedef struct task
{
  char *name;
  int startMonth, endMonth;
  int *dependencies, dependenciesCount;
} Task;

Task SetupTask(int numTasks);

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

    printf("          |January   |February  |March     |April     |May       |June      |July      |August    |September |October   |November  |December  |\n");

    for(int i = 0;i<numTasks;i++){
        for(int k = 0;k<13;k++){
            printf("----------|");
        }
        printf("\n");
        for(int j = 0;j<13;j++){+
            printf("xxxxxxxxxx|");
        }
        printf("\n");
    }
    for(int i = 0;i<13;i++){
        printf("----------|");
    }
    return 0;
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

  int dependencies[newTask.dependenciesCount];
  for (int i = 0; i < newTask.dependenciesCount; i++)
  {
    printf("Enter dependent task (0 - %d):\n", numTasks - 1);
    scanf("%d", &dependencies[i]);

    while (dependencies[i] < 0 || dependencies[i] >= numTasks)
    {
      printf("Invalid number entered. Please enter a number between 0 - %d:\n", numTasks - 1);
      scanf("%d", &dependencies[i]);
    }
  }

  newTask.dependencies = dependencies;

  return newTask;

}
