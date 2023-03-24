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
void asciiArt();
int CheckCircle(Task tasks[], Node *visitedTasks, int newTask);

int main(void) {
    system("cls");
    asciiArt();
    int numTasks;
    char ans[4],ans2[4];
    printf("Welcome to the Gantt Generator\nWould you like to use the test example? (yes or no)");
    do {//creates infinite loop which breaks when the correct input is entered
        scanf("%3s", ans);
        if(strcmp(ans,"yes") == 0 || strcmp(ans,"no") == 0){
            break;
        } else {
            printf("Invalid input. Please enter either yes or no: ");
        }
    } while (1);

    if(strcmp(ans,"yes") == 0){
        SampleChart();
        printf("Would you like to continue to create your own?(yes or no)");
        do {
            scanf("%3s", ans2);
            if(strcmp(ans2,"yes") == 0 || strcmp(ans2,"no") == 0) {
                break;
            } else {
                printf("Invalid input. Please enter either yes or no: ");
            }
        } while (1);
    }

    if(strcmp(ans2,"yes") == 0 || strcmp(ans,"no") == 0){
        do {

            printf("How many tasks would you like to add?");
            if(scanf("%d", &numTasks) != 1){
                printf("Invalid input. You can have a maximum of 10 tasks, please enter a number between 0 and 10:\n");
                while(getchar() != '\n');
            }

        }while (numTasks < 0 || numTasks > 10);

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
                scanf("%10s",userInput);

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
                asciiArt();
            }
            else
            {
                printf("Invalid input entered. Please be careful with capitalization.\n");
            }

        }


        return 0;
    }
    else
    {
        asciiArt();
    }
}
void PrintGantt(Task tasksArray[], int numTasks)
{
    system("cls");
    int n = 0;
    for(int i = 0;i<14;i++){
        printf("|----------");
    }
    printf("|\n");
    printf("|Task Name |January   |February  |March     |April     |May       |June      |July      |August    |September |October   |November  |December  |Dependency|\n");

    for(int i = 0;i<numTasks;i++){
        for(int k = 0;k<14;k++){
            printf("|----------");
        }
        printf("|\n");

        printf("|%-10s|", tasksArray[i].name);

        for(int j = 1;j<=12;j++){
            if (j >= tasksArray[i].startMonth && j <= tasksArray[i].endMonth) {
                printf("   XXXX   |");
            } else {
                printf("          |");
            }
        }
        for(n = 0;n<tasksArray[i].dependenciesCount;n++){
            printf("%-2d",tasksArray[i].dependencies[n]);
        }
        for(int i = 0;i<10-(n*2);i++){
            printf(" ");
        }
        printf("|\n");

    }

    for(int k = 0;k<14;k++){
        printf("|----------");
    }
    printf("|\n");
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
    tasksArray[1].dependenciesCount = 2;
    tasksArray[1].dependencies = (int*) malloc(sizeof(int));
    tasksArray[1].dependencies[0] = 0;
    tasksArray[1].dependencies[1] = 1;


    tasksArray[2].name = "Task 3";
    tasksArray[2].startMonth = 2;
    tasksArray[2].endMonth = 6;
    tasksArray[2].dependenciesCount = 1;
    tasksArray[2].dependencies = (int*) malloc(sizeof(int));
    tasksArray[2].dependencies[0] = 1;

    tasksArray[3].name = "Task 4";
    tasksArray[3].startMonth = 5;
    tasksArray[3].endMonth = 12;
    tasksArray[3].dependenciesCount = 1;
    tasksArray[3].dependencies = (int*) malloc(2 * sizeof(int));
    tasksArray[3].dependencies[0] = 2;

    PrintGantt(tasksArray, numTasks);
}


Task SetupTask(int numTasks)
{
    Task newTask;
    newTask.name = (char*) malloc(11 * sizeof(char)); //allocate memory for up to 10 characters and \0

    printf("Please enter the new task name (up to 10 characters):\n");
    scanf("%10s",newTask.name);


    while(getchar() != '\n');//clear buffer
    do { //validate start month input

        printf("Start month (1-12):\n");
        if (scanf("%d", &newTask.startMonth) != 1){//if not an integer value scanf will evaluate to less than 1
            printf("Invalid input. Please enter a number between 1 - 12:\n");
            while(getchar() != '\n');//clear input buffer to make sure it is clear before next input operation. if this line was not here the non integer input would stay in the buffer
        }
    } while (newTask.startMonth < 1 || newTask.startMonth > 12);
    do {//validate end month input
        printf("End month (%d-12):\n", newTask.startMonth);
        if (scanf("%d", &newTask.endMonth) != 1) {//if not an integer value scanf will evaluate to less than 1
            printf("Invalid input. Please enter a number between %d - 12:\n", newTask.startMonth);
            while(getchar() != '\n');//clear buffer
        }
    } while (newTask.endMonth < newTask.startMonth || newTask.endMonth > 12);

    //validate dependencies count input
    int maxTasks;
    if (numTasks > 5) {
        maxTasks = 5;
    } else {
        maxTasks = numTasks;
    }
    do {
        printf("Enter how many dependencies this task has (0-%d):\n", maxTasks);
        if (scanf("%d", &newTask.dependenciesCount) != 1) {
            printf("Invalid input. Please enter a number between 0 - %d:\n", maxTasks);
            while(getchar() != '\n');
        }
    } while (newTask.dependenciesCount < 0 || newTask.dependenciesCount > maxTasks);

    // Validate dependencies inputs
    if (newTask.dependenciesCount > 0) {
        newTask.dependencies = (int*) malloc(newTask.dependenciesCount * sizeof(int));
        for (int i = 0; i < newTask.dependenciesCount; i++) {
            int alreadyContained = 0;
            do {
                printf("Enter dependent task (0 - %d):\n", numTasks - 1);
                if (scanf("%d", &newTask.dependencies[i]) != 1) {
                    printf("Invalid input. Please enter a number between 0 - %d:\n", numTasks - 1);
                    while(getchar() != '\n');
                    continue;
                }
                if (newTask.dependencies[i] < 0 || newTask.dependencies[i] >= numTasks) {
                    printf("Invalid number entered. Please enter a number between 0 - %d:\n", numTasks - 1);
                    continue;
                }
                for (int j = 0; j < i; j++) {
                    if (newTask.dependencies[i] == newTask.dependencies[j]) {
                        alreadyContained = 1;
                        break;
                    }
                }
                if (alreadyContained == 1) {
                    printf("Duplicate dependency entered. Please enter a new number between 0 - %d:\n", numTasks - 1);
                    continue;
                }
            } while (alreadyContained == 1 || newTask.dependencies[i] < 0 || newTask.dependencies[i] >= numTasks);
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
void asciiArt()
{
    printf("\n"
           "               ____      _      _   _     _____    _____         ____  U _____ u _   _   U _____ u   ____        _       _____   U  ___ u   ____     \n"
           "            U /\"___|uU  /\"\\  u | \\ |\"|   |_ \" _|  |_ \" _|     U /\"___|u\\| ___\"|/| \\ |\"|  \\| ___\"|/U |  _\"\\ u U  /\"\\  u  |_ \" _|   \\/\"_ \\/U |  _\"\\ u  \n"
           "            \\| |  _ / \\/ _ \\/ <|  \\| |>    | |      | |       \\| |  _ / |  _|\" <|  \\| |>  |  _|\"   \\| |_) |/  \\/ _ \\/     | |     | | | | \\| |_) |/  \n"
           "             | |_| |  / ___ \\ U| |\\  |u   /| |\\    /| |\\       | |_| |  | |___ U| |\\  |u  | |___    |  _ <    / ___ \\    /| |\\.-,_| |_| |  |  _ <    \n"
           "              \\____| /_/   \\_\\ |_| \\_|   u |_|U   u |_|U        \\____|  |_____| |_| \\_|   |_____|   |_| \\_\\  /_/   \\_\\  u |_|U \\_)-\\___/   |_| \\_\\   \n"
           "              _)(|_   \\\\    >> ||   \\\\,-._// \\\\_  _// \\\\_       _)(|_   <<   >> ||   \\\\,-.<<   >>   //   \\\\_  \\\\    >>  _// \\\\_     \\\\     //   \\\\_  \n"
           "             (__)__) (__)  (__)(_\")  (_/(__) (__)(__) (__)     (__)__) (__) (__)(_\")  (_/(__) (__) (__)  (__)(__)  (__)(__) (__)   (__)   (__)  (__) \n");
}
