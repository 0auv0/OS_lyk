#include<unistd.h>
#include<stdio.h>
#include<sys/syscall.h>
#include<stdlib.h>
#define MAX 100
int main(){
    int i,j,k,count=0,flag;
    int pid1[MAX];
    int pid2[MAX];
    char name[MAX][16] ;
    int status[MAX];
    unsigned long long time1[MAX];
    unsigned long long time2[MAX];
    int index[MAX] = {0};
    double time[MAX] = {-1};
    syscall(333,pid1,name,status,time1);
    while(1){
        count = flag =0;
        sleep(1);
        system("clear");
        syscall(333,pid2,name,status,time2);
        printf("PID\tCOMM\tISRUNNING\t%%CPU\tTIME\n");
        for(i=0; i<MAX; i++){
            for(j=0; j<MAX; j++){
                if(pid1[i] == pid2[j] && pid2[j] != 0){
                    time[j] = (time2[j] - time1[i])*1e-9;
                    index[count++] = j;
                }
            }
        }
        for(i=0;i<count-1;i++){
            for(j=i;j<count;j++){
                if(time[index[i]] - time[index[j]] < 1e-6){
                    int temp2 = index[i];
                    index[i] = index[j];
                    index[j] = temp2;
                }
            }
        }
        for(i=0;i<19;i++){
            printf("%d\t%s  \t%d\t%lf\t%lf\n",pid2[index[i]],
                                            name[index[i]],
                                            (status[index[i]]==0),
                                            time[index[i]]*100,
                                            time2[index[i]]*1e-9);
        }
        for(i=0;i<MAX;i++){
            pid1[i] = pid2[i];
            time1[i] = time2[i];
        }
    }
    return 0;
}