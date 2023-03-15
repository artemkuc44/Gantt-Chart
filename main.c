#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

typedef struct task
{
  char *name;
  int startMonth, endMonth;
  int *dependencies, dependenciesCount;
} Task;

Task SetupTask(int numTasks);
void SampleChart();
void PrintGantt(Task tasksArray[], int numTasks);
int CheckCircle(Task tasks[], Node *visitedTasks, int newTask);

int main(void) {
    int numTasks;
    char ans[4],ans2[4];
    printf("Welcome to the Gantt Generator\nWould you like to use the test example? (yes or no)");
    scanf("%s",ans);
    if(strcmp(ans,"yes") == 0){
          SampleChart();
          printf("Would you like to continue to create your own?(yes or no)");
          scanf("%s",ans2);
    }
    if(strcmp(ans2,"yes") == 0 || strcmp(ans,"no") == 0){
          printf("How many tasks would you like to add?");
          scanf("%d",&numTasks);

          while (numTasks < 0 || numTasks > 10)
          {
              printf("Invalid number of tasks. Please enter a number between 1 - 10:\n");
              scanf("%d", &numTasks);
          }

          Task tasksArray[numTasks];

          for (int i = 0; i < numTasks; i++)
          {
            tasksArray[i] = SetupTask(numTasks);
            printf("New task added: %s\n", tasksArray[i].name);
          }

          PrintGantt(tasksArray, numTasks);

          char *userInput = (char*) malloc(sizeof(char));
          while (strcmp(userInput, "quit") != 0)
          {
              //Takes the users input for what they want the action to be
              printf("If you wish to edit the Gantt please type \"edit\" / If you wish to run a test, type \"test\" or to \nexit, type \"quit\" and then press enter to execute your option. ");
              scanf("%s", userInput);

              if (strcmp(userInput, "edit") == 0)
              {
                  //Gets the name of the task that the user wants to edit
                  printf("Please enter the name of the task you want to edit: ");
                  scanf("%s", userInput);

                  //Once the name of the task is acquired, it checks for the location of that task
                  int foundTask = 0;
                  for (int i = 0; i < numTasks; i++)
                  {
                      if (strcmp(tasksArray[i].name, userInput) == 0)
                      {
                          //Reassigns task's values when found
                          foundTask = 1;
                          tasksArray[i] = SetupTask(numTasks);
                          break;
                      }
                  }
                  if (foundTask == 0)
                  {
                      printf("That task does not exist.\n");
                  }
                  else
                  {
                      //If task was found it remakes the Gantt chart and clears the terminal
                      printf("Task edited successfully.");
                      PrintGantt(tasksArray, numTasks);
                      //Notes for Artjom below
                      //Somewhere around here I think the clearing of the terminal should be done?
                      //Maybe it should just be done in the PrintGantt function.
                  }

              }
              else if (strcmp(userInput, "test") == 0)
              {
                  //Iterates through each task to check for circle dependencies down each tree
                  int returnValue = 0;
                  for (int i = 0; i < numTasks; i++)
                  {
                      for (int j = 0; j < tasksArray[i].dependenciesCount; j++)
                      {
                          //Creates a list to track what nodes have been passed through
                          Node *head = (Node*)malloc(sizeof(Node));
                          MakeList(head, i);
                          returnValue = CheckCircle(tasksArray, head, tasksArray[i].dependencies[j]);

                          //Return value will be equal to one if it found a circle dependency and wants to break
                          if (returnValue == 1)
                          {
                              break;
                          }
                      }
                      if (returnValue == 1)
                      {
                          break;
                      }
                  }
                  if (returnValue == 0)
                  {
                      printf("Your Gantt is free of circle dependencies.\n");
                  }
              }
              else if (strcmp(userInput, "quit") == 0)
              {
                  //Do nothing
              }
              else
              {
                  printf("Invalid input entered. Please be careful with capitalization.\n");
              }

          }


      return 0;
    }
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
                printf("...XXXX...|");
            } else {
                printf("..........|");
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
void SampleChart()
{
  int numTasks = 4;
  Task tasksArray[numTasks];

  tasksArray[0].name = "Task 1";
  tasksArray[0].startMonth = 1;
  tasksArray[0].endMonth = 2;
  tasksArray[0].dependenciesCount = 0;

  tasksArray[1].name = "Task 2";
  tasksArray[1].startMonth = 3;
  tasksArray[1].endMonth = 4;
  tasksArray[1].dependenciesCount = 1;
  tasksArray[1].dependencies = (int*) malloc(sizeof(int));
  tasksArray[1].dependencies[0] = 0;

  tasksArray[2].name = "Task 3";
  tasksArray[2].startMonth = 2;
  tasksArray[2].endMonth = 6;
  tasksArray[2].dependenciesCount = 1;
  tasksArray[2].dependencies = (int*) malloc(sizeof(int));
  tasksArray[2].dependencies[0] = 1;

  tasksArray[3].name = "Task 4";
  tasksArray[3].startMonth = 5;
  tasksArray[3].endMonth = 12;
  tasksArray[3].dependenciesCount = 2;
  tasksArray[3].dependencies = (int*) malloc(2 * sizeof(int));
  tasksArray[3].dependencies[0] = 0;
  tasksArray[3].dependencies[1] = 2;

  PrintGantt(tasksArray, numTasks);
}


Task SetupTask(int numTasks)
{
      //Reads in all the required user input for a task
      //Makes sure they enter valid info within given ranges, and no duplicate dependencies
      Task newTask;
      newTask.name = (char*)malloc(sizeof(char));

      printf("Please enter the new task name:\n");
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

      //Only allowed max of 5 dependencies per task
      int maxTasks = numTasks;
      if (numTasks > 5)
      {
          maxTasks = 5;
      }

      while (newTask.dependenciesCount < 0 || newTask.dependenciesCount > maxTasks)
      {
          printf("Invalid number of dependencies. Please enter a number between 0 - %d:\n", maxTasks);
          scanf("%d", &newTask.dependenciesCount);
      }

      if (newTask.dependenciesCount > 0)
      {
            newTask.dependencies = (int*) malloc(sizeof(int));

            for (int i = 0; i < newTask.dependenciesCount; i++)
            {
                  printf("Enter dependent task (0 - %d):\n", numTasks - 1);
                  scanf("%d", &newTask.dependencies[i]);

                  //Makes sure there aren't any duplicate dependencies
                  int alreadyContained = 0;
                  for (int j = 0; j < i; j++)
                  {
                      if (newTask.dependencies[i] == newTask.dependencies[j])
                      {
                          alreadyContained = 1;
                          break;
                      }
                  }

                  while (newTask.dependencies[i] < 0 || newTask.dependencies[i] >= numTasks || alreadyContained == 1)
                  {
                      alreadyContained = 0;
                      printf("Invalid number entered. Do not enter duplicates. Please enter a number between 0 - %d:\n", numTasks - 1);
                      scanf("%d", &newTask.dependencies[i]);
                      for (int j = 0; j < i; j++)
                      {
                          if (newTask.dependencies[i] == newTask.dependencies[j])
                          {
                              alreadyContained = 1;
                              break;
                          }
                      }
                  }
            }
      }

  return newTask;

}

int CheckCircle(Task tasks[], Node *visitedTasks, int newTask)
{
      //Checks circle dependencies recursively, tracking what tasks have been passed through with a linked list
      //Check linkedList.h for descriptions of the linked list functions
      if (Contains(visitedTasks, newTask) == 1)
      {
            //Circle dependency found
            printf("Circle dependency found concerning task %d.\n", newTask);
            printf("Consider changing up dependencies to fix this issue.\n\n");
            return 1;
      }

      //If there are multiple paths to go down it will copy the list and go down each path with a unique list
      if (tasks[newTask].dependenciesCount > 1)
      {
            int returnValue;
            for (int i = 0; i < tasks[newTask].dependenciesCount; i++)
            {
                  Node *newHead = (Node*)malloc(sizeof(Node));
                  Copy(newHead, visitedTasks);
                  Add(newHead, newTask);
                  if (CheckCircle(tasks, visitedTasks, tasks[newTask].dependencies[i]) == 1)
                  {
                      returnValue = 1;
                  }
            }
            if (returnValue == 1)
            {
              return 1;
            }
      }
      //Otherwise it will just continue down the singular path and check the next dependency
      else if (tasks[newTask].dependenciesCount == 1)
      {
          Add(visitedTasks, newTask);
          if (CheckCircle(tasks, visitedTasks, tasks[newTask].dependencies[0]) == 1)
          {
              return 1;
          }
      }
      return 0;
}