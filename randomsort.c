/*
// ----------------------------------------------------------- 
// NAME : Prakhar Keshari                      User ID: pkeshari 
// DUE DATE : 02/03/2017                                       
// PROGRAM ASSIGNMENT #1                                        
// FILE NAME : prog1.c            
// PROGRAM PURPOSE :                                           
//      This program creates 4 child processes that run from main and have specific functions
// 		The first process creates m random integers and sorts them using heap sort
// 		The second process gives us the fibonacci number upto nth term
//		The third process solves Buffon prblem and gives us the probability of a needle crossing the floor
//		The forth process gives us the area under sin graph         
// ----------------------------------------------------------- 
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

//Method signatures
char* print(int* p, int m);
void heapify(int m, int *p, int i);
void heapSort(int m);
long int fibo(int n);
void fibonacci(int n);
void buffon(int r);
void areaSim(int s);

/* ----------------------------------------------------------- */
/* FUNCTION  print 										       */
/*     Takes an array of integers and puts it in a string      */
/* PARAMETER USAGE :                                           */
/*    *p - pointer to the array |   m - size of array   	   */
/* FUNCTION CALLED :                                           */
/*    none          										   */
/* ----------------------------------------------------------- */
char* print(int* p, int m){

	int i;
    int count = 0;
    char* str;    
    char* retStr;
    retStr  = malloc(sizeof(char)*(24576));
    str = malloc(sizeof(char)*(24576));
    retStr[0] = '\t';
    for(i = 0; i < m; i++ ){
        sprintf(str, "%4d ", p[i]);
        strcat(retStr, str);
        if(count == 19){
            strcat(retStr,"\n\t");
            count = -1;
        }
        count++;
    }
    count = 0;
    strcat(retStr, "\n");
    return retStr;
}

/* ----------------------------------------------------------- */
/* FUNCTION  heapify                         				   */
/*     This is                            */
/* PARAMETER USAGE :                                           */
/*    a list of all parameters and their meaning               */
/* FUNCTION CALLED :                                           */
/*    a list of functions that are called by this one          */
/* ----------------------------------------------------------- */
void heapify(int m, int *p, int i){

	int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
    int temp=0;
 
    // If left child is larger than root
    if (l < m && p[l] > p[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < m && p[r] > p[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {

    	temp = p[i];
    	p[i]=p[largest];
    	p[largest]=temp;
 
        // Recursively heapify the affected sub-tree
        heapify(m, p, largest);
    }
}

// main function to do heap sort
void heapSort(int m){

	char* str;
    char* tempStr;
    tempStr    = malloc(sizeof(char)*1028);
    str = malloc(sizeof(char)*32768);
    int *p = (int*) malloc(m*sizeof(int));
	srand( time( NULL ) );
	int i;


	sprintf(tempStr, "\n   Heap Sort Process Started\n   Random Numbers Generated:\n");
    strcat(str, tempStr);
	//initializing the array of random numbers
	for(i=0; i<m; i++){
		p[i]=rand()%100;
	}


	sprintf(tempStr, "%s", print(p, m));
    strcat(str, tempStr);
    // Build heap (rearrange array)
    for (int i = m/(2 - 1); i >= 0; i--)
        heapify(m, p, i);

    int temp = 0;
 
    // One by one extract an element from heap
    for (int i=m-1; i>=0; i--)
    {
        // Move current root to end

    	temp = p[i];
    	p[i]=p[0];
    	p[0]=temp;
 
        // call max heapify on the reduced heap
        heapify(i, p, 0);
    }
    sprintf(tempStr, "   Sorted Sequence:\n");    
    strcat(str, tempStr);

    sprintf(tempStr, "%s", print(p, m));
    strcat(str, tempStr);


    sprintf(tempStr, "   Heap Sort Process Exits\n");
    strcat(str, tempStr);

    write(1, str, strlen(str));
    free(p);
    free(str);
    free(tempStr);
    exit(1);
}

long int fibo(int n){

	if(n==1 || n==2){
		return 1;
	}
		return (fibo(n-1) + fibo(n-2));
}

void fibonacci(int n){
	char* str;
    char* output;

    str = malloc(sizeof(char)*1024);
    output  = malloc(sizeof(char)*2048);
    
   // write(1, "Fibonacci Process Started\n", 26);
    sprintf(str, "\n      Fibonacci Process Started\n");
    strcat(output, str);

    sprintf(str, "      Input Number %d\n", n);
    strcat(output, str);

    sprintf(str, "      Fibonacci Number f(%d) is %ld\n      Fibonacci Process Exits\n", n, fibo(n));
    strcat(output, str);
    
    write(1, output, strlen(output));
    free(str);
    free(output);
    exit(1);
}

void buffon(int r){

	srand( time( NULL ) );

	float d=0;
	float a=0;

	int i;
	float t=0;

	char* str;
    char* output;

    str = malloc(sizeof(char)*1024);
    output  = malloc(sizeof(char)*2048);

    sprintf(str, "\n         Buffon's Needle Process Started\n         Input Number %d\n", r);
    strcat(output, str);

	for(i=0; i<r; i++){
		d = ((float)rand())/(float)RAND_MAX;
		a = ((float)rand())/(float)RAND_MAX*(2.0*acos(-1));
		if( (d+sin(a)) <0  ||  (d+sin(a)) >1){
			t ++;
		}
	}

	sprintf(str, "         Estimated Probability is %.5f\n         Buffon's Needle Process Exits\n", t/(float)r);
    strcat(output, str);
    write(1, output, strlen(output));
    free(str);
    free(output);
    exit(1);
}

void areaSim(int s){

	float a = 0;
	float b= 0;
	int t = 0;
	char* str;
    char* output;
    str = malloc(sizeof(char)*1024);
    output  = malloc(sizeof(char)*2048);
	int i;
	for(i=0; i<s; i++){
		a = ((float)rand())/(float)RAND_MAX*(acos(-1));
		b = ((float)rand())/(float)RAND_MAX;

		if(b<=sin(a)){
			t++;
		}
	}
	sprintf(str, "         Input Number %d   		 Total Hit %d\n         Estimated Area is %f\n         Integration Process Exits\n", s, t, ((float)t/(float)s)*acos(-1));

 	strcat(output, str);    
    
 	write(1, output, strlen(output));

 	free(str);
 	free(output);
 	exit(1);
}

// void getRandom(int m, int *p){

// 	srand( time( NULL ) );


	

// 	int i;

// 	//initializing the array of random numbers
// 	for(i=0; i<m; i++){
// 		p[i]=rand()%100;
// 	}

// 	heapSort(m, p);

	

// }

int main(int argc, char *argv[]){

	int m, n, r, s , status, waiting;
	char * str; 
	char * output;
	pid_t pid, childpid;

	str = malloc(sizeof(char)*1024);
    output  = malloc(sizeof(char)*2048);
    waiting=0;

    if(argc != 5){
        write(2, "incorrect number of arguments\n", 36);
        return 1;
    }

	m = atoi(argv[1]);
	n = atoi(argv[2]);
	r = atoi(argv[3]);
	s = atoi(argv[4]);


	// printf("hbshsbhcbdchdbchdbchdbchdbchdbchdbch %d\n", n);

	//heapSort(m);

	
	int i;
	sprintf(str, "Main Process Started \n Number of Random Numbers   = %d\nFibonacci Input            = %d\nBuffon's Needle Iterations = %d\nIntegration Iterations     = %d\n", m, n, r, s);
    strcat(output, str);
    srand(time(NULL));


    for(i = 0; i<4; i++){
        pid = fork();
        if(pid == 0){
            if(i == 0){
                write(1, "Heap Sort Process Created\n", 26);
                strcat(output, str);
                heapSort(m);

            } else if(i == 1){
                write(1,"Fobonacci Process Created\n", 26);
                strcat(output, str);
                fibonacci(n);
            } else if(i == 2){
                write(1, "Buffon's Needle Process Created\n", 32);            
                strcat(output, str);
                buffon(r);
            } else if(i == 3){
                 write(1, "Integration Process Created\n", 28);
                 strcat(output, str);
                 areaSim(s);
            	}
        } else {
            if(waiting == 0){
                sprintf(str, "Main Process Waits\n");
                strcat(output, str);
                waiting = 1;
            }
            while(wait(&status) != pid);
        }
    }   
    sprintf(str, "Main Procss Exits\n");
    strcat(output, str);

    write(1, output, strlen(output));    

    free(str);
    free(output);

	

	// int fib=fibo(n);


	// float prob = buffon(r);

	// float area = areaSim(s);

	// printf("Input Number %d \n Fibonacci Number F(%d) is %d \n prob = %f\narea = %f\n", n, n, fib, prob, area);
	return 0;
}



