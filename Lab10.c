#include <stdio.h>
void FIFO()
{
      int referenceString[10], pageFaults = 0, m, n, s, pages, frames;
      printf("\nEnter the number of Pages: ");
      scanf("%d", &pages);
      printf("\nEnter reference string values: ");
      for(m = 0; m < pages; m++)
      {
            scanf("%d", &referenceString[m]);
      }
      printf("\nEnter total number of frames: ");
      {
            scanf("%d", &frames);
      }
      int temp[frames];
      for(m = 0; m < frames; m++)
      {
            temp[m] = -1;
      }
      for(m = 0; m < pages; m++)
      {
            s = 0;
            for(n = 0; n < frames; n++)
            {
                  if(referenceString[m] == temp[n])
                  {
                        s++;
                        pageFaults--;
                  }
            }     
            pageFaults++;
            if((pageFaults <= frames) && (s == 0))
            {
                  temp[m] = referenceString[m];
            }   
            else if(s == 0)
            {
                  temp[(pageFaults - 1) % frames] = referenceString[m];
            }
            printf("\n");
            for(n = 0; n < frames; n++)
            {     
                  printf("%d\t", temp[n]);
            }
      } 
      printf("\nTotal Page Faults:\t%d\n", pageFaults);
}


void Optimal()
{
     int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < no_of_pages; ++i){
        scanf("%d", &pages[i]);
    }
    
    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0){
         flag3 =0;
        
            for(j = 0; j < no_of_frames; ++j){
             temp[j] = -1;
            
             for(k = i + 1; k < no_of_pages; ++k){
             if(frames[j] == pages[k]){
             temp[j] = k;
             break;
             }
             }
            }
            
            for(j = 0; j < no_of_frames; ++j){
             if(temp[j] == -1){
             pos = j;
             flag3 = 1;
             break;
             }
            }
            
            if(flag3 ==0){
             max = temp[0];
             pos = 0;
            
             for(j = 1; j < no_of_frames; ++j){
             if(temp[j] > max){
             max = temp[j];
             pos = j;
             }
             }            
            }
frames[pos] = pages[i];
faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d", faults);
}

int findLRU(int time[], int n){
int i, minimum = time[0], pos = 0;
 
for(i = 1; i < n; ++i){
if(time[i] < minimum){
minimum = time[i];
pos = i;
}
}
return pos;
}
 
int LRU()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
printf("Enter number of pages: ");
scanf("%d", &no_of_pages);
printf("Enter reference string: ");
    for(i = 0; i < no_of_pages; ++i){
     scanf("%d", &pages[i]);
    }
printf("Enter number of frames: ");
scanf("%d", &no_of_frames);
for(i = 0; i < no_of_frames; ++i){
     frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
     flag1 = flag2 = 0;
    
     for(j = 0; j < no_of_frames; ++j){
     if(frames[j] == pages[i]){
     counter++;
     time[j] = counter;
   flag1 = flag2 = 1;
   break;
   }
     }
    
     if(flag1 == 0){
for(j = 0; j < no_of_frames; ++j){
     if(frames[j] == -1){
     counter++;
     faults++;
     frames[j] = pages[i];
     time[j] = counter;
     flag2 = 1;
     break;
     }
     }
     }
    
     if(flag2 == 0){
     pos = findLRU(time, no_of_frames);
     counter++;
     faults++;
     frames[pos] = pages[i];
     time[pos] = counter;
     }
    
     printf("\n");
    
     for(j = 0; j < no_of_frames; ++j){
     printf("%d\t", frames[j]);
     }
}
printf("\n\nTotal Page Faults = %d", faults);
}

int main(){

int choice,tocontinue;
do{
printf("\nEnter the option to carry out Page referencing in: \n1.FIFO\n2.Optimal\n3.LRU\n4.To exit\nYour choice: ");
scanf("%d",&choice);
tocontinue=choice;
switch(choice){
case 1:FIFO();
       break;
case 2: Optimal();
        break;
case 3:LRU();
       break;
}}while(tocontinue<4);
return 0; 
}
