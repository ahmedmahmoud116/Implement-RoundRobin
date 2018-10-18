#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct Node *next;
} Node;//struct that contains the elements in every node
typedef struct
{
    Node *front, *rear;
} Queue; //the elements in the queue
typedef struct
{
    int start_time;
    int execute_time;
    char name [10];
} process;//struct needed to read from file and store informations
//prototypes
void initialize(Queue *q);//it gives the initial values of the queue
int dequeue (Queue *q);//it returns the value of the first elements entered in the queue which the front point on it
int isEmpty(Queue *q);//it returns 0 or 1 which is the stack is empty or not
void enqueue(Queue *q,int data);//it enter a new node in the queue
Node* newnode(int data);//it initial a new node with and put the value you want into it
void schedule(Queue *q);

int main()
{
    Queue q;
    initialize(&q);
    schedule(&q);
    return 0;
}
Node* newnode(int data)
{
    Node *n = (Node*)malloc(sizeof(Node));//it allocate size in a memory with the size of the structure Node
    n->data = data;//and the Node consists of Data and next so we put the data you called with in the data in the node
    n->next = NULL;//and the pointer next in the node will point to NULL
    return n;//return the node so you can use it and save it in any variable you want
}
void initialize(Queue *q)
{
    q->front = q->rear = NULL;//the initialization of any empty queue is the front and rear will point to NULL
}
void enqueue(Queue *q,int data)
{
    Node *n = newnode(data);//initialize a new node and save it in Node n
    if(isEmpty(q))//check if the queue is empty?
        q->front = q->rear = n;//so the new node is the first node in the queue so rear and front will point on it
    else //else if the queue is not empty
    {
        q->rear->next = n;//the node which the rear point into it the next of it will point to n
        q->rear = n;//and the rear which point on the last node in the queue will point on the n
    }
}
int dequeue (Queue *q)
{
    if(!isEmpty(q))//check if the queue is not empty?
    {
        int data = q->front->data;//initialize a variable which will take the value of the firs node in the queue
        Node* temp = q->front;//create a temp and make it point to the front node
        q->front = temp->next;//and the front will point to the next node after the first
        free(temp);//free temp which will free the node after takes its value
        if(isEmpty(q))//and check if the queue became empty after that?
            q->rear = q->front = NULL;//so we have an empty queue so as initialize the rear and front point to NULL
        return data;
    }
    else
    {
        printf("can't dequeue the queue is empty!!!");//there is no elements in the queue to dequeue
        exit(0);//error
    }
}
int isEmpty(Queue *q)
{
    if(q->front && q->rear)//check front and rear point to NULL then the queue is empty as the condition in initialization and return 1
        return 0;
    else
        return 1;
}
void schedule(Queue *q)
{
    FILE*F;//pointer to open and read from the file
    process pro[10]; // create variables of process that will take values from file and deal with the processing
    int processing_time;//the process time at the start of the file
    int i=0,j=0,flag=0,str=0;//the counters
    char s[10];//its char that read the numbers as string before change them to int
    char c;//char that reads from the file
    int temp;//temporary variable to use
    char start[10];//a string to read the start time then cast it to int
    char execute[10];//a string to read the execute time then case it to int
    int enter=0;//counter to start string
    int out=0;//counter to execute string
    int noofitems=0;
    if(F = fopen("RoundRobin.txt","r") == NULL)//if open file to read return NULL then the file not found and it will exit
    {
        printf("FILE NOT FOUND!!!!!");
        exit(0);
    }
    else//it found the file and start to read from it
    {
        printf("THE FILE:\n");
        F = fopen("RoundRobin.txt","r");//it opens the file to read from it
        while(!feof(F))//loop until the end if the file
        {
            c = getc(F);//reads char char from the file
            printf("%c",c);//and print it on the screen
            if(c == '=')//if c equal the equal sign then the number after it is the processing time
            {
                flag++;//means the processing time is taken
                while(!feof(F))//loop until the end of the file to take the processing time
                {
                    c = getc(F);
                    printf("%c",c);
                    if(c == ' ')//means if c is space skip the loop and start from the second while again
                    {
                        continue;
                    }
                    else if(c != '\n')//means if he still does not finish reading the line
                    {
                        s[str] = c;//read the number of processing time and put it in the string
                        str++;//increase the counter of the string
                    }
                    else
                    {
                        processing_time =atoi(s);//its function in c that case the array of characters that contain numbers to an int
                        break;//when it take the number it skip the loop
                    }
                }
            }
            else if(flag>0) // flag >0 means that the  time is processing is taken
            {
                pro[0].name[0]=c;//c here is the first element of the processing item and we will save it in the array in the name
                j++;   // it loops inside the name array inside struct process
                flag=0;// flag here indicate which part of the word the pointer of file at
                i=0;  // counter which moves inside the array of struct process
                while(!feof(F))
                {
                    c=getc(F);
                    printf("%c",c);
                    if(c==' ') // if  c was space increase flag and continue to know that we complete the first word
                    {
                        flag++;
                        continue;
                    }
                    else if(c >= '0' && c <='9')//if c is a number go and check
                    {
                        if(flag == 1)//means that the first space happened and go to enter the start time
                        {
                            start[enter]=c;//put it in the array of character again to cast it to int
                            enter++;//increase counter of the start array
                              noofitems++;
                        }
                        else if(flag == 2)
                        {
                            execute[out] = c;//put it in the array of character again to cast it to int
                            out++;//increase counter of the execute array
                        }
                        else //no space happened?
                        {
                            pro[i].name[j] = c;//then the char or the number is still the name of the process
                            j++;//increase the counter of the name array
                        }
                    }
                    else if(c=='\n')//it finished reading the line
                    {
                        pro[i].start_time= atoi(start);//then cast the array of char start and put it in the int start time
                        pro[i].execute_time= atoi(execute);//then cast the array of char execute and put it in the int execute time
                        flag=0;//reset the counter of spaces
                        pro[i].name[j]='\0';//and end the string name with the null to be able to use without error
                        j=0;//reset the counter of the array name
                        i++;//reset the counter of the array process
                        start[0]='\0';//reset the string used
                        execute[0]='\0';//reset the string used
                        enter=0;//reset their counters
                        out=0;//reset their counters
                    }
                    else//no space or numbers or finishing the line its maybe char then put it in the name
                    {
                        pro[i].name[j] = c;
                        j++;
                    }
                }
                if (feof(F)) // if the file end the reading so we have to make step of ending line
                {
                    pro[i].name[j-1]='\0';//we put the end of the last string name
                    pro[i].start_time=atoi(start);//and the end of the last process items beacuse it didin't enter in the null
                    pro[i].execute_time=atoi(execute);
                    flag=0;
                }
                flag++;// to continue enter the else if
            }
        }
        fclose(F);//closing the file
        flag=0;//reset the counters to use them again
        i=0;//reset the counters to use them again
    }
    printf("\n%d",noofitems);
    printf("\n------------------------------------------\n\n");
    printf("PROCESSING:\n");
    while(i<processing_time)//loop till the time that we read at the head of file
    {
        if(i==0)//the time equal zero
        {
            for(j=0; j<noofitems; j++)//loops from zero to four number of items inside the file
            {
                if(pro[j].start_time == i && pro[j].name!=NULL)//if the name not equal null means there is element in the array
                {
                    enqueue(q,j);//put the index in the queue
                }
            }
        }

        if(!isEmpty(q)) // if the queue isn't empty
        {
            temp=dequeue(q); // remove the first element
            pro[temp].execute_time--; // and decrease the execute time
            if(pro[temp].execute_time==0) //if execute time equal zero
            {
                printf("%s (%d-->%d) aborted \n",pro[temp].name,i,i+1);//then this element is finished execution and abort it
                i++;
                for(j=0; j<noofitems; j++)
                {
                    if(pro[j].start_time == i&&pro[j].name!=NULL)
                    {
                        enqueue(q,j);
                    }
                }
            }
            else if (pro[temp].execute_time !=0) // if execute time not equal to zero
            {
                printf("%s (%d-->%d)\n",pro[temp].name,i,i+1);//its used to print the element that we take it from the queue
                i++;// when the time increase check if there is any element have entering time at this time  before queue last process
                for(j=0; j<noofitems; j++)//then check again
                {
                    if(pro[j].start_time == i&&pro[j].name!=NULL)
                    {
                        enqueue(q,j);
                    }
                }
                enqueue(q,temp); // then put the element again inside the queue
            }

        }
        else // if the queue was empty
        {
            printf("Idle (%d-->%d)\n",i,i+1);
            i++;// when the time increase check if there is any element have entering time at this time
            for(j=0; j<noofitems; j++)
            {
                if(pro[j].start_time == i&&pro[j].name!=NULL)
                {
                    enqueue(q,j);
                    flag++;
                }
            }
        }
    }
    printf("Stop"); //end

}



