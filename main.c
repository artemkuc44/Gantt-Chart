#include <stdio.h>

int main(void) {
    int numTasks;
    printf("Enter how many tasks you would like to enter");
    scanf("%d",&numTasks);

    printf("          |January   |February  |March     |April     |May       |June      |July      |August    |September |October   |November  |December  |\n");


    for(int i = 0;i<numTasks;i++){
      for(int k = 0;k<13;k++){
          printf("----------|");
      }
      printf("\n");
      for(int j = 0;j<13;j++){
          printf("xxxxxxxxxx|");
      }
      printf("\n");
    }
    for(int i = 0;i<13;i++){
      printf("----------|");
    }
    return 0;
}
