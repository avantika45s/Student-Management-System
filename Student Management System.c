/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>

struct studentDetails{
int student_id;
char first_name[50];
char last_name[50];
char hostel[10];
char course[10];
char dob[15];
char course_duration[15];
int roomNo;
};
typedef struct studentDetails studet;
struct list{
studet data;
struct list* next;
};
typedef struct list node;
typedef node* ptd;

//fetching the required data from disk 
ptd fetchfromDisk(FILE *disk ,int student_id){
ptd new = (ptd)malloc(sizeof(node)); 
int stringsize = 500;
new->data.student_id = student_id;
char student[stringsize]; //stringsize = 500
char studentDetail[500];
int current_line_number = 1;
while((fgets(student, 500 , disk)) != NULL){
strcpy(studentDetail, student);
char *token = strtok(student, "\t");                                     //splitting of a line of disk  
if(student_id == atoi(token)){                                           //char to int using atoi
//required student id has been found 
break;
}
else if(current_line_number < atoi(token)){
//data has been deleted and not found in disk
return NULL;
}
current_line_number ++;
}

char *token1 = strtok(studentDetail, "\t");                            //splitting the string using the delimiter : "\t";

char details[6][50]; 
//only strings info are being stored in this char array
int i = 0; 
while(token1 != NULL && i<6){
token1 = strtok(NULL, "\t");
strcpy(details[i], token1);
i++;
}
                                 
strcpy(new->data.first_name, details[0]);
strcpy(new->data.last_name, details[1]);
strcpy(new->data.hostel, details[2]);
strcpy(new->data.course, details[3]);
strcpy(new->data.dob, details[4]);
strcpy(new->data.course_duration, details[5]);

//for fetching room no.
token1 = strtok(NULL, "\t");    
new->data.roomNo = atoi(token1); 
new->next = NULL;
return new;
}

ptd mainmemory(ptd head, int op_id, int student_id, FILE *disk, FILE *outputFile){
disk = fopen("disk.txt", "r");
outputFile = fopen("outputFile.txt" , "a");

//when linked list is empty
if(head == NULL){
head = fetchfromDisk(disk, student_id);
//data not found in disk
if(head == NULL){
char msg[] = "data not found";
fputs(msg, outputFile);
return head;
}

return head;
}


//when linked list is having atleast one node
ptd ptr = (ptd)malloc(sizeof(node));
ptr = head;
int count = 0;
while(ptr != NULL){
if(ptr->data.student_id != student_id){
ptr = ptr->next;
count++;
}
else if(ptr->data.student_id == student_id){
count++;
break;
}
}


//addition of new node when no. of nodes < 5
if(count<5 && ptr == NULL){
ptd new = (ptd)malloc(sizeof(node)); 
new = fetchfromDisk(disk, student_id);
if(new == NULL){
char msg[] = "data not found";
fputs(msg, outputFile);
return head;
}
new->next = head;
head = new;
free(new);
return head;
}


if(count<=5 && ptr != NULL){
//node of same student id has been found in linked list(main memory)
return head;
}


//linked list is having 5 nodes
if(count == 5 && ptr == NULL){
ptd new = (ptd)malloc(sizeof(node));
//check whether the data is present in database or not
new = fetchfromDisk(disk, student_id);
if(new == NULL){
    //data not found in disk
   char msg[] = "data not found";
   fputs(msg, outputFile);
   return head;
}


//data found in disk
//delete one node and add another with different student id

//deleting from the end
ptr = head;
while(ptr->next->next != NULL){
ptr = ptr->next;
}
free(ptr->next);
ptr->next = NULL;

//adding at the beginning
new->next = head;
head = new;
return head;
}
}

void registration(FILE *firstnames, FILE *lastnames, FILE *hostel, FILE *courses, int student_id){
FILE *disk;
firstnames = fopen("firstnames.txt", "r");
lastnames = fopen("lastnames.txt", "r");
hostel = fopen("hostel.txt", "r");
courses = fopen("courses.txt", "r");
disk = fopen("disk.txt", "a");
int stringsize = 50;
int arraysize = 4;
char student[arraysize][stringsize]; 
//for(int i = 0; i<arraysize; i++){
int current_line_number = 0;

//choosing random line for random selection of details
int line_firstnames = (rand()%20), line_lastnames = (rand()%20), line_hostel = (rand()%5), line_courses = (rand()%5);

while((fscanf(firstnames, "%s", student[0])) != EOF){
    if (current_line_number == line_firstnames){
        //pointer is reached randomly chosen line
        break;
    }
current_line_number ++;
} 

current_line_number = 0;


while((fscanf(lastnames, "%s", student[1])) != EOF){
    if (current_line_number == line_lastnames){
        //pointer is reached randomly chosen line
        break;
    }
current_line_number ++;
} 

current_line_number = 0;


while((fscanf(hostel, "%s", student[2])) != EOF){
    if (current_line_number == line_hostel){
        //pointer is reached randomly chosen line
        break;
    }
current_line_number ++;
} 

current_line_number = 0;

while((fscanf(courses, "%s", student[3])) != EOF){
    if (current_line_number == line_courses){
        //pointer is reached randomly chosen line
        break;
    }
current_line_number ++;
} 

//write student id in disk
fprintf(disk, "%d\t" , student_id); 

//write string type details taken from different files
for(int i = 0 ; i<arraysize ; i++){
fprintf(disk, "%s\t" , student[i]);
}

//now generate and writing random dob(dd.mm.yyyy), duration of course, room no.
if((strcmp(student[3], "BTech.")) == 0){
    fprintf(disk, "%d", ((rand()%30)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%12)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%6)+2001));
    fputc('\t' , disk);
    fputs("4years", disk);             
    fputc('\t', disk);
    //room no.
    fprintf(disk, "%d", ((rand()%200)+101));
}

 if(strcmp(student[3] , "MTech.") == 0 || strcmp(student[3] , "MBA") == 0 || strcmp(student[3] , "MS") == 0 ){
    fprintf(disk, "%d", ((rand()%30)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%12)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%6)+1997));
    fputc('\t' , disk);
    fputs("2years", disk);
    fputc('\t', disk);
    fprintf(disk, "%d", ((rand()%100)+301));
   }


if(strcmp(student[3] , "PhD") == 0){
    fprintf(disk, "%d", ((rand()%30)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%12)+1));
    fputc('.' , disk);
    fprintf(disk, "%d", ((rand()%6)+1992));
    fputc('\t' , disk);
    fputs("5years", disk);
    fputc('\t', disk);
    fprintf(disk, "%d", ((rand()%100)+401));
}

fputc('\n', disk);
fclose(firstnames);
fclose(lastnames);
fclose(hostel);
fclose(courses);
fclose(disk);
}


bool search(ptd head, int student_id){
ptd ptr = (ptd)malloc(sizeof(node));
ptr = head;
while(ptr != NULL){
if(ptr->data.student_id == student_id){
return true;
}
else{
ptr = ptr->next;
}
}
return false;
}


void delete(ptd head, int student_id, FILE *disk){
char studentDetail[500];
char *filename = "disk.txt";
disk = fopen("disk.txt", "r");
// Temporary file to write modified content
FILE *output = fopen("temp.txt", "a"); 

if (disk == NULL || output == NULL) {
perror("File opening failed");
exit(EXIT_FAILURE);
}
char buffer[500]; 
int current_line = 0;
// while (fgets(buffer, sizeof(buffer), disk) != NULL) {
// current_line++;

while((fgets(buffer, 500 , disk))!= NULL){
    strcpy(studentDetail, buffer);
current_line ++;
//first word of line is student_id in disk file
char *token = strtok(buffer, "\t"); 
if(atoi(token) != student_id){
//copying data of other students in temp file
fputs(studentDetail, output);
}
}
fclose(disk);
fclose(output);

// Replace the original file with modified content
remove(filename);
rename("temp.txt", filename);
}




void server(const char *filename){
FILE *queuefile;
queuefile = fopen(filename, "r");
ptd head = (ptd)malloc(sizeof(node));
head = NULL;
FILE *outputFile = fopen("outputFile.txt" , "a");
FILE *disk ;
int stringsize = 100;
char request[stringsize]; 
clock_t start_time = clock();
double elapsed_time ;
while((fgets(request, 100 , queuefile)) != NULL){
//splitting the string using the delimiter : " ";
char *token = strtok(request, "  "); 
int stid = atoi(token); //storing student id
token = strtok(NULL, "  ");
int opid = atoi(token);
token = strtok(NULL, "  ");
double time;
//sscanf(token, "%lf" , &time);
time = atof(token);
token = strtok(NULL, "  ");
char request_type[20];
strcpy(request_type, token);

if(opid == 0){
//call registration function
FILE *firstnames; FILE *lastnames; FILE *hostel; FILE *courses;
registration(firstnames, lastnames, hostel, courses, stid);
//write in the output file
elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
fprintf(outputFile, "%d has been registered via %s request_generator at %.6f\n", stid, request_type, elapsed_time);
head = mainmemory(head, 0 , stid , disk, outputFile);
}

else if(opid == 1 ){ 
//call search function
//check in main memory, if present - ok
bool searching = search(head, stid);
// if not, open disk file and search for that then bring it to linked list
//write in output file
elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
fprintf(outputFile, "%d is searched via %s request_generator at %.6f\n", stid, request_type, elapsed_time);
head = mainmemory(head, 1 , stid , disk, outputFile);
}

else if(opid == 2){
//bring it in mainmemory
head = mainmemory(head, 2 , stid , disk, outputFile);
//write in output file
elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
fprintf(outputFile, "%d has been updated via %s request_generator at %.6f\n", stid, request_type, elapsed_time);
}

else if(opid == 3){
//call delete function
delete(head, stid, disk);
//write in output file
elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
fprintf(outputFile, "%d has been deleted via %s request_generator at %.6f\n", stid, request_type, elapsed_time);
}
}
}


double throughput(const char *request_type, int total_request){
FILE *queuefile = fopen("request_queuefile.txt", "r");
int count = 0;
// char buffer[150];
char line[150];
//char *a = fgets(buffer, 150, queuefile);
char *token;
// double  start_time;                                                      
double last_time;
// token = strtok(a, "  ");
// int i = 0;
// while(i<3){
// //request_type = token;                                             
// if(i == 2){
// //sscanf(token, "%lf" , &start_time);           //no need of start_time
// start_time = atof(token);
// }
// token = strtok(NULL, "  ");
// i++;
// }
while(fgets(line, 150, queuefile) != NULL && count < total_request){ 
token = strtok(line, "  ");
i = 0;
while(i<3){
//request_type = token;
if(i == 2){
//sscanf(token, "%lf" , &lasttime);
last_time = atof(token);
}
token = strtok(NULL, "  ");
i++;
}
// request_type = token;
if(strcmp(token, request_type) == 0){
count++;
}

//bring out last time from file
double throughput = total_request / last_time;
return throughput;
}
}


double response_time(const char *request_type, int total_request){
    FILE *queuefile = fopen("request_queuefile.txt", "r");
    float time[total_request];
    char line[150];
    int count = 0;
    while(fgets(line, 150, queuefile) != NULL && count < total_request){
    char *token = strtok(line, "  ");
    int i = 0; int j = 0;
    while(i<3){
    //request_type = token;
    if(i == 2){
    // sscanf(token, "%.6f" , &time[j]);
    time[j] = atof(token);
    }
    token = strtok(NULL, "  ");
    i++;
    j++;
    }
    // request_type = token;
    if(strcmp(token, request_type) == 0){
    count++;
    }
    }
    double t = 0.0 ;
    for(int k =0; k<total_request; k++){
       t += time[k];
    }
    double meantime = t / total_request ;
return meantime;
}


void placeinQueue(int student_id, int op_id, double elapsed_time, char *request_type){
FILE *queuefile;
queuefile = fopen("request_queuefile.txt", "a");
fprintf(queuefile, "%d  %d  %.6f  %s\n", student_id, op_id, elapsed_time, request_type);
fclose(queuefile);
}


void *request_generator_regular(void *arg){
int count = 0;
int student_id, op_id;
clock_t start_time = *((clock_t *)arg);
while((++count)<=50){
student_id = ((rand()%100)+1) ;
op_id = (rand()% 4);
double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
placeinQueue(student_id , op_id , elapsed_time, "regular_request");
sleep(1);
}
pthread_exit(NULL);
}


void *request_generator_random(void *arg){
int count = 0;
int student_id, op_id;
clock_t start_time = *((clock_t *)arg);
while((++count)<=20){
student_id = ((rand()%100)+1) ;
op_id = (rand()% 4);
double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
placeinQueue(student_id , op_id , elapsed_time, "random_request");
sleep((rand()%3)+1);
}
pthread_exit(NULL);
}


int main(int argc , char *argv[]){
FILE *firstnames , *lastnames , *hostel , *courses , *disk;
//registering 100 students initially
int count = 1, student_id;
while(count<=100){
student_id = count;
registration(firstnames, lastnames, hostel, courses, student_id);
count++;
}
//for calling two request generator function simultaneously
clock_t start_time = clock();
pthread_t thread1, thread2;

if (argc > 1) {
        if (strcmp(argv[1], "first") == 0) {
            //firstFunction();
            pthread_create(&thread1, NULL, request_generator_regular, &start_time);
            pthread_create(&thread2, NULL, request_generator_random, &start_time);
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
        } else if (argc > 2) {
            const char *filename = argv[2];
            int intValue = atoi(argv[3]);
            processFile(filename);
            processInteger(intValue);
            const char *filename = argv[2];
            // FILE *queuefile;
            server(filename);
            const char *request1 = argv[3];
            int total_request1 = atoi(arg[4]);
            const char *request2 = argv[5];
            int total_request2 = atoi(arg[6]);
            printf("%.7f\n", throughput(request1, total_request1));
            printf("%.7f\n", throughput(request2 , total_request2));
            printf("%.7f\n", response_time(request1, total_request1));
            printf("%.7f\n", response_time(request2, total_request2));


        } else {
            printf("Insufficient arguments.\n");
        }
    } else {
        printf("No arguments provided.\n");
    }

// pthread_create(&thread1, NULL, request_generator_regular, &start_time);
// pthread_create(&thread2, NULL, request_generator_random, &start_time);
// pthread_join(thread1, NULL);
// pthread_join(thread2, NULL);

// const char *filename = argv[1];
// // FILE *queuefile;
// server(filename);
// const char *request1 = argv[2];
// int total_request1 = atoi(arg[3]);
// const char *request2 = argv[4];
// int total_request2 = atoi(arg[5]);

// printf("%.7f\n", throughput(request1, total_request1));
// printf("%.7f\n", throughput(request2 , total_request2));
// printf("%.7f\n", response_time(request1, total_request1));
// printf("%.7f\n", response_time(request2, total_request2));

return 0;
}*/





