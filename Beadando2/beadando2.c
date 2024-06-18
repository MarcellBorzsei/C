#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<time.h>
#include<signal.h>



struct mesg_buffer
{
	long mesg_type;
	char mesg_text[1024];
        int mesg_placement;
} message;

struct sent_poems
{
        int placements[2];
        char** poems;
};
typedef struct sent_poems SentPoems;

void handler(int signum)
{
	
}

int add_poem();
int list_poems();
int delete_poem();
int change_poem();
int delete_specific_poem(int which);
int number_of_poems();
SentPoems two_random_poems();
SentPoems read_in_from_pipe(char* my_fifo);
int isInArray(int array[], int size, int number);




int main()
{
	//Maszk létrehozása
	sigset_t mask;
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	
        signal(SIGUSR2, handler);
        
	//Pipe előkészítése
	char* my_fifo = "/tmp/22";


        if(access(my_fifo, F_OK) == 0)
        {
                if(unlink(my_fifo) == -1)
                {
                        perror("Unlink failed");
                        return -1;
                }
        }


        if(mkfifo(my_fifo, 0666) == -1)
        {
                perror("mkfifo failed");
                return -1;
        }


	//Pidek deklarálása
        pid_t mainParent = getpid();

        pid_t child1;
        pid_t child2;
        pid_t child3;
        pid_t child4;

	//Random szám track-elése
        srand(time(NULL));
        int random_index = rand() % 4;
        
	int rand_array[4];
	int rand_array_length = 0;

	//Üzenetsor előkészítése
	int msgid;
	key_t myKey = ftok("/tmp/4242", 42);
	if(myKey == -1)
	{
		perror("Ftok error");
		return -1;
	}

	

        child1 = fork();
        if(child1 == 0)
        {
                //Gyerek folyamat
                signal(SIGUSR1, handler);
                sigdelset(&mask, SIGUSR1);
		sigsuspend(&mask);
                printf("\nAz 1. fiú a kiválasztott\n");

                //Odaér, signalt kuld
                sleep(2);
                printf("\nMár félúton vagyok Barátfalvára\n");
                sleep(2);
                printf("\n(1) ideértem Barátfalvára\n");
                
                kill(mainParent, SIGUSR2);
		sleep(2);
                //sigsuspend(&mask);
		//printf("Second signal got\n");

                //Beolvasas a csobol
                //printf("Olvasok a csobol\n");
            
                SentPoems got_poems = read_in_from_pipe(my_fifo);

               
                printf("\nEzeket a verseket kaptam:\n");
                printf("\n%s\n", got_poems.poems[0]);
                printf("\n%s\n", got_poems.poems[1]);

		//printf("Beolvastam a csobol\n");
		
	
                int chosen_poem = rand() % 2;
  
		msgid = msgget(myKey, 0666 | IPC_CREAT);
		message.mesg_type = 1;
                message.mesg_placement = got_poems.placements[chosen_poem];
		strcpy(message.mesg_text, got_poems.poems[chosen_poem]);

                //printf("\nSent poems's placement: %d\n", got_poems.placements[chosen_poem]);


		msgsnd(msgid, &message, sizeof(message), 0);

		//printf("Message sent to parent\n");
		kill(mainParent, SIGUSR2);

		//sigsuspend(&mask);
                printf("\n********************Locsolás********************\n");
		printf("\n%s\n", got_poems.poems[chosen_poem]);
		printf("Szabad-e locsolni?\n");

		sleep(3);
		printf("\nMeglocsoltam a lányokat\n");


                
                

        }
        else if(child1 > 0)
        {
                //Szulo folyamat
                child2 = fork();

                if(child2 == 0)
                {
                        //Gyerek folyamat
                        signal(SIGUSR1, handler);
                        sigdelset(&mask, SIGUSR1);
                        sigsuspend(&mask);
                        printf("\nA 2. fiú a kiválasztott\n");

                        //Odaér, signalt kuld
                        sleep(2);
                        printf("\nMár félúton vagyok Barátfalvára\n");
                        sleep(2);
                        printf("\n(2) ideértem Barátfalvára\n");
                        
                        kill(mainParent, SIGUSR2);
                        sleep(2);
                        //sigsuspend(&mask);
                        //printf("Second signal got\n");

                        //Beolvasas a csobol
                        //printf("Olvasok a csobol\n");
                
                        SentPoems got_poems = read_in_from_pipe(my_fifo);

                
                        printf("\nEzeket a verseket kaptam:\n");
                        printf("\n%s\n", got_poems.poems[0]);
                        printf("\n%s\n", got_poems.poems[1]);

                        //printf("Beolvastam a csobol\n");
                        
                
                        int chosen_poem = rand() % 2;
        
                        msgid = msgget(myKey, 0666 | IPC_CREAT);
                        message.mesg_type = 1;
                        message.mesg_placement = got_poems.placements[chosen_poem];
                        strcpy(message.mesg_text, got_poems.poems[chosen_poem]);
                        
                        //printf("\nSent poems's placement: %d\n", got_poems.placements[chosen_poem]);

                        msgsnd(msgid, &message, sizeof(message), 0);

                        //printf("Message sent to parent\n");
                        kill(mainParent, SIGUSR2);

                        //sigsuspend(&mask);
                        printf("\n********************Locsolás********************\n");
                        printf("\n%s\n", got_poems.poems[chosen_poem]);
                        printf("Szabad-e locsolni?\n");

                        sleep(3);
                        printf("\nMeglocsoltam a lányokat\n");


                
		}
                else if(child2 > 0)
                {
                        //Szulo
                        child3 = fork();

                        if(child3 == 0)
                        {

                                //Gyerek folyamat
                                signal(SIGUSR1, handler);
                                sigdelset(&mask, SIGUSR1);
                                sigsuspend(&mask);
                                printf("\nA 3. fiú a kiválasztott\n");

                                //Odaér, signalt kuld
                                sleep(2);
                                printf("\nMár félúton vagyok Barátfalvára\n");
                                sleep(2);
                                printf("\n(3) ideértem Barátfalvára\n");
                                
                                kill(mainParent, SIGUSR2);
                                sleep(2);
                                //sigsuspend(&mask);
                                //printf("Second signal got\n");

                                //Beolvasas a csobol
                                //printf("Olvasok a csobol\n");
                        
                                SentPoems got_poems = read_in_from_pipe(my_fifo);

                        
                                printf("\nEzeket a verseket kaptam:\n");
                                printf("\n%s\n", got_poems.poems[0]);
                                printf("\n%s\n", got_poems.poems[1]);

                                //printf("Beolvastam a csobol\n");
                                
                        
                                int chosen_poem = rand() % 2;
                
                                msgid = msgget(myKey, 0666 | IPC_CREAT);
                                message.mesg_type = 1;
                                message.mesg_placement = got_poems.placements[chosen_poem];
                                strcpy(message.mesg_text, got_poems.poems[chosen_poem]);
                                
                                //printf("\nSent poems's placement: %d\n", got_poems.placements[chosen_poem]);

                                msgsnd(msgid, &message, sizeof(message), 0);

                                //printf("Message sent to parent\n");
                                kill(mainParent, SIGUSR2);

                                //sigsuspend(&mask);
                                printf("\n********************Locsolás********************\n");
                                printf("\n%s\n", got_poems.poems[chosen_poem]);
                                printf("Szabad-e locsolni?\n");

                                sleep(3);
                                printf("\nMeglocsoltam a lányokat\n");



                        }

                        else if(child3 > 0)
                        {
                                //Szulo
                                child4 = fork();

                                if(child4 == 0)
                                {
                                        //Gyerek folyamat
                                        signal(SIGUSR1, handler);
                                        sigdelset(&mask, SIGUSR1);
                                        sigsuspend(&mask);
                                        printf("\nA 4. fiú a kiválasztott\n");

                                        //Odaér, signalt kuld
                                        sleep(2);
                                        printf("\nMár félúton vagyok Barátfalvára\n");
                                        sleep(2);
                                        printf("\n(4) ideértem Barátfalvára\n");
                                        
                                        kill(mainParent, SIGUSR2);
                                        sleep(2);
                                        //sigsuspend(&mask);
                                        //printf("Second signal got\n");

                                        //Beolvasas a csobol
                                        //printf("Olvasok a csobol\n");
                                
                                        SentPoems got_poems = read_in_from_pipe(my_fifo);

                                
                                        printf("\nEzeket a verseket kaptam:\n");
                                        printf("\n%s\n", got_poems.poems[0]);
                                        printf("\n%s\n", got_poems.poems[1]);

                                        //printf("Beolvastam a csobol\n");
                                        
                                
                                        int chosen_poem = rand() % 2;
                        
                                        msgid = msgget(myKey, 0666 | IPC_CREAT);
                                        message.mesg_type = 1;
                                        message.mesg_placement = got_poems.placements[chosen_poem];
                                        strcpy(message.mesg_text, got_poems.poems[chosen_poem]);
                                        
                                        //printf("\nSent poems's placement: %d\n", got_poems.placements[chosen_poem]);

                                        msgsnd(msgid, &message, sizeof(message), 0);

                                        //printf("Message sent to parent\n");
                                        kill(mainParent, SIGUSR2);

                                        //sigsuspend(&mask);
                                        printf("\n********************Locsolás********************\n");
                                        printf("\n%s\n", got_poems.poems[chosen_poem]);
                                        printf("Szabad-e locsolni?\n");

                                        sleep(3);
                                        printf("\nMeglocsoltam a lányokat\n");
                                        



                                        

                                }
                                else if(child4 > 0)
                                {
                                        while(1)
                                        {
                                                printf("%s", "Nyuszi Mama Verseskötete\n");
                                                printf("%s", "1. Új vers hozzáadása\n");
                                                printf("%s", "2. Versek listázása\n");
                                                printf("%s", "3. Vers törlése\n");
                                                printf("%s", "4. Vers módosítása\n");
                                                printf("%s", "5. Locsolás\n");
                                                printf("%s", "6. Kilépés\n");

                                                printf("%s", "Válasszon egy lehetőséget: ");

                                                int choice;
                                                scanf("%d", &choice);

                                            

                                                while(getchar() != '\n');

                                                printf("\n");
                                                

                                                switch(choice)
                                                {
                                                        case 1:
                                                                add_poem();
                                                                break;
                                                        case 2:
                                                                list_poems();
                                                                break;
                                                        case 3:
                                                                delete_poem();
                                                                break;
                                                        case 4:
                                                                change_poem();
                                                                break;
                                                        case 5:
                                                                //locsolas
                                                                sleep(1);
                                                                //Szulo
								
								if(rand_array_length >= 4)
								{
									printf("Már minden nyuszi locsolkodott!\n");
								}
                                                                else if(number_of_poems() <= 1)
                                                                {
                                                                        printf("Kettőnél kevesebb versed van csak!\n");
                                                                }
								else
								{

									do
									{
										random_index = rand() % 4; 
									}while(isInArray(rand_array, rand_array_length, random_index));

									rand_array[rand_array_length] = random_index;
									rand_array_length++;

									//printf("Ki lett sorsolva melyik gyerek: %d\n", random_index);
									
							

        	                                                	switch(random_index)
               	                                                	{
                        	                                                case 0:
                                	                                                kill(child1, SIGUSR1);
                                        	                                        break;
                                                	                        case 1:
                                                        	                        kill(child2, SIGUSR1);
                                                                	                break;
                                	                                        case 2:
                                        	                                        kill(child3, SIGUSR1);
                                                	                                break;
                                                        	                case 3:
                                                                	                kill(child4, SIGUSR1);
                                                                        	        break;
                        	                                                default:
                                	                                                printf("Érvénytelen azonosítói\n");
                                        	                                        break;
                                                	                }
	
   	                                                                //Amíg a nyuszi odaér barátfalvára
        	                                                      	sigdelset(&mask, SIGUSR2);
									sigsuspend(&mask);

                        	                                        //printf("Megkaptam az üzenetet fiacskám\n");
                                                                

                                	                                //printf("\nKüldöm a két verset neked!\n");
                                        	                        SentPoems mama_poems = two_random_poems();
                                                                        
                                                	                size_t length1 = strlen(mama_poems.poems[0]);
                                                        	        size_t length2 = strlen(mama_poems.poems[1]);
                                                                        

       		                                                       	//printf("%s\n", mama_poems[0]);
                	                                                //printf("%s\n", mama_poems[1]);
									

                        	                                        int cso = open(my_fifo, O_WRONLY);

                                	                                if(cso == -1)
                                        	                        {
                                                	                        perror("Opening pipe failed");
                                                        	                return -1;
                                                                	}
	                                                                write(cso, &length1, sizeof(size_t));
        	                                                        write(cso, mama_poems.poems[0], length1);
                                                                        write(cso, &(mama_poems.placements[0]), sizeof(int));
                                                                        

                	                                                write(cso, &length2, sizeof(size_t));
                        	                                        write(cso, mama_poems.poems[1], length2);
                                                                        write(cso, &(mama_poems.placements[1]), sizeof(int));
                                                                        

                                	                                close(cso);
                                        	                        //printf("Csobe iras kesz\n");
                                                                


									sigsuspend(&mask);
									//printf("Visszatért a második üzeneted, olvashatom az üzenetsort.\n");
									msgid = msgget(myKey, 0666 | IPC_CREAT);

									msgrcv(msgid, &message, sizeof(message), 1, 0);
                                                                        //A kapott vers kitörlése, hogy többször ne kaphassa locsoló már
                                                                        delete_specific_poem(message.mesg_placement);
                                                                        
									//printf("\nA kapott vers sorszáma: %d\n", message.mesg_placement);

									msgctl(msgid, IPC_RMID, NULL);
									/*switch(random_index)
                                        	                        {
                                                	                        case 0:
                                                        	                        kill(child1, SIGUSR1);
                                                                	                break;
                                        	  	                	case 1:
                                                	                                kill(child2, SIGUSR1);
                                                        	                        break;
                                                                	        case 2:
                                                                        	        kill(child3, SIGUSR1);
                                                                                	break;
                              	                                        	case 3:
                                	                                                kill(child4, SIGUSR1);
                                                                                	break;
                                                            		        default:
                                                                        	        printf("Érvénytelen azonosítói\n");
                                                                               		break;
                                               	                	}*/
									wait(NULL);
									printf("\n********************Locsolás-vége********************\n\n\n\n");
                                                                
								}	
								break;

                                                        case 6:
                                                                kill(child1, SIGKILL);
                                                                kill(child2, SIGKILL);
                                                                kill(child3, SIGKILL);
                                                                kill(child4, SIGKILL);
                                                                wait(NULL);
                                                                wait(NULL);
                                                                wait(NULL);
                                                                wait(NULL);
                                                                unlink(my_fifo);
                                                                exit(0);

                                                        default:
                                                                printf("%s", "Érvénytelen választás!\n");
                                                                printf("%s", "Válassz újra!\n");

                                                }
                                        }
                                        
                                                
                                        

                                }
                                else
                                {
                                        perror("Fork error");
                                        return -1;
                                }
                        }
                        else
                        {
                                perror("Fork error");
                                return -1;
                        }

                }
                else
                {
                        perror("Fork error");
                        return -1;
                }

        }
        else
        {
                perror("Fork error");
                return -1;
        }


        return 0;
}

int add_poem()
{
        int file = open("poems.dat", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        char* new_poem;

        // Opening file
        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }

        //Allocating memory (maximum 150 characters)
        new_poem =(char*)malloc(150 * sizeof(char));

        if(new_poem == NULL)
        {
                printf("Memory allocation failed\n");
                return 0;
        }


        //Requesting the poem
        printf("%s", "Kérlek írd le a verset: ");
        fgets(new_poem, 150, stdin);
        printf("\n");

        //Removing newline character if necessary
        size_t new_poem_length = strlen(new_poem);
        if(new_poem[new_poem_length - 1] == '\n')
        {
                new_poem[new_poem_length - 1] = '\0';
                new_poem_length--;
        }

        write(file, &new_poem_length, sizeof(size_t));
        write(file, new_poem, new_poem_length);

        //fwrite(&new_poem_length, sizeof(size_t), 1, file);
        //fwrite(new_poem, sizeof(char), new_poem_length, file);

        free(new_poem);
        close(file);
        printf("Sikeresen hozzáadtad a verset!\n");
        printf("\n");

        return 1;


}

int list_poems()
{
        int file = open("poems.dat", O_RDONLY );
        size_t length_counter = 0;

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }

        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {
                char* poems = malloc((length_counter + 1) * sizeof(char));
                if(poems == NULL)
                {
                        printf("Memory allocation failed\n");
                        return 0;
                }
                //fread(poems, sizeof(char), length_counter, file);
                if(read(file, poems, length_counter) == length_counter)
                {
                        poems[length_counter] = '\0';
                        printf("\n");
                        printf("%s\n", poems);
                        printf("\n");
                }
                free(poems);


        }

        close(file);

        return 1;

}



int delete_poem()
{
        int requested_number;

        do
        {
                printf("Írd be a vers sorszámát, amit törölni szeretnél: ");
                if(scanf("%d", &requested_number) != 1 || requested_number <= 0)
                {
                        printf("Helyetelen sorszámot adtál meg. Adj meg egy pozitív egész számot!\n");
                        while(getchar() != '\n');
                }

        }while(requested_number <= 0);
        printf("\n");


        int file = open("poems.dat", O_RDONLY);

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }


        int capacity = 10;
        char** poems = malloc(capacity * sizeof(char*));
        if(poems == NULL)
        {
                printf("Memory allocation failed\n");
        }


        int list_iterator = 0;
        int deleted = 0;
        int counter = 0;
        size_t length_counter;

        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {
                if((counter + 1) == requested_number)
                {
                        deleted = 1;
                        lseek(file, length_counter, SEEK_CUR);
                        counter++;
                }
                else
                {
                        if(list_iterator >= capacity)
                        {
                                capacity *= 2;
                                char** poems_temp = realloc(poems, capacity * sizeof(char*));
                                if(poems_temp == NULL)
                                {
                                        printf("Memory allocation failed\n");
                                        close(file);
                                        free(poems);
                                        return 0;
                                }
                                poems = poems_temp;
                        }

                        poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
                        if(poems[list_iterator] == NULL)
                        {
                                printf("Memory allocation failed\n");
                                close(file);
                                free(poems);
                                return 0;
                        }
                        //fread(poems[list_iterator], sizeof(char), length_counter, file);
                        read(file, poems[list_iterator], length_counter);
                        poems[list_iterator][length_counter] = '\0';
                        counter++;
                        list_iterator++;
                }


        }



        if(!deleted)
        {
                printf("A kért vers nem található a fájlban.\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                close(file);
                return 0;
        }
        close(file);


        file = open("poems.dat", O_WRONLY | O_TRUNC);
        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                close(file);
                return 0;
        }


        for(int i = 0; i < (list_iterator); i++)
        {
                size_t curr_poem_length = strlen(poems[i]);
                write(file, &curr_poem_length, sizeof(size_t));
                write(file, poems[i], curr_poem_length);

                //fwrite(&curr_poem_length, sizeof(size_t), 1, file);
                //fwrite(poems[i], sizeof(char), curr_poem_length, file);
        }



        for(int i = 0; i < (list_iterator); i++)
        {
                free(poems[i]);
        }

        free(poems);

        close(file);

        printf("A vers törölve lett.\n");
        printf("\n");
        return 1;

}



int change_poem()
{
        int requested_number;

        do
        {
                printf("Írd be a vers sorszámát, amit módosítani szeretnél: ");
                if(scanf("%d", &requested_number) != 1 || requested_number <= 0)
                {
                        printf("Helyetelen sorszámot adtál meg. Adj meg egy pozitív egész számot!\n");
                        while(getchar() != '\n');
                }

        }while(requested_number <= 0);
        while(getchar() != '\n');

        printf("\n");


        char* new_poem = malloc(150 * sizeof(char));

        if(new_poem == NULL)
        {
                printf("Memory allocation failed\n");
                return 0;
        }


        //Requesting the poem
        printf("%s", "Kérlek írd le a módosított verset: ");
        fgets(new_poem, 150, stdin);
        printf("\n");

        //Removing newline character if necessary
        size_t new_poem_length = strlen(new_poem);
        if(new_poem[new_poem_length - 1] == '\n')
        {
                new_poem[new_poem_length - 1] = '\0';
                new_poem_length--;
        }


        int file = open("poems.dat", O_RDONLY);

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }


        int capacity = 10;
        char** poems = malloc(capacity * sizeof(char*));
        if(poems == NULL)
        {
                printf("Memory allocation failed\n");
        }


        int list_iterator = 0;
        int deleted = 0;
        int counter = 0;
        size_t length_counter;

        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {
                if((counter + 1) == requested_number)
                {
                        deleted = 1;
                        lseek(file, length_counter, SEEK_CUR);
                        counter++;
                }
                else
                {
                        if(list_iterator >= capacity)
                        {
                                capacity *= 2;
                                char** poems_temp = realloc(poems, capacity * sizeof(char*));
                                if(poems_temp == NULL)
                                {
                                        printf("Memory allocation failed\n");
                                        free(poems);
                                        close(file);
                                        return 0;
                                }
                                poems = poems_temp;
                        }

                        poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
                        if(poems[list_iterator] == NULL)
                        {
                                printf("Memory allocation failed\n");
                                close(file);
                                free(poems);
                                return 0;
                        }
                        read(file, poems[list_iterator], length_counter);
                        poems[list_iterator][length_counter] = '\0';
                        counter++;
                        list_iterator++;
                }


        }

        close(file);

        if(!deleted)
        {
                printf("A kért vers nem található a fájlban.\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                free(new_poem);
                close(file);
                return 0;
        }


        file = open("poems.dat", O_WRONLY | O_TRUNC);
        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                free(poems);
                return 0;
        }



        int is_changed_in = 0;
        for(int i = 0; i < (list_iterator); i++)
        {
                if(i == (requested_number - 1))
                {
                        size_t changed_poem_length = strlen(new_poem);
                        write(file, &changed_poem_length, sizeof(size_t));
                        write(file, new_poem, changed_poem_length);
                        is_changed_in = 1;
                }

                size_t curr_poem_length = strlen(poems[i]);
                write(file, &curr_poem_length, sizeof(size_t));
                write(file, poems[i], curr_poem_length);

        }


        //Ha az utolsót választja módosításra
        if(!is_changed_in)
        {
                size_t changed_poem_length = strlen(new_poem);
                write(file, &changed_poem_length, sizeof(size_t));
                write(file, new_poem, changed_poem_length);
        }

        close(file);

        for(int i = 0; i < (list_iterator); i++)
        {
                free(poems[i]);
        }

        free(new_poem);
        free(poems);

        printf("A vers módosítva lett.\n");
        printf("\n");
        return 1;

}


SentPoems read_in_from_pipe(char* my_fifo)
{
        //If error occurs
        SentPoems error_dummy;


        SentPoems got_poems;

        int cso = open(my_fifo, O_RDONLY);
        if(cso == -1)
        {
                perror("Opening file failed");
                return error_dummy;
	}
        got_poems.poems = malloc(2 * sizeof(char*));
        if(got_poems.poems == NULL)
        {
                printf("Memory allocation failed");
                return error_dummy;
        }

        size_t length1;
        int placement1;
        read(cso, &length1, sizeof(size_t));

        got_poems.poems[0] = malloc((length1 + 1) * sizeof(char));

        if(got_poems.poems[0] == NULL)
        {
                printf("Memory allocation failed");
		free(got_poems.poems);
                return error_dummy;
        }
	read(cso, got_poems.poems[0], length1);
	got_poems.poems[0][length1] = '\0';
        read(cso, &placement1, sizeof(int));



	size_t length2;
        int placement2;
        read(cso, &length2, sizeof(size_t));

        got_poems.poems[1] = malloc((length2 + 1) * sizeof(char));
        if(got_poems.poems[1] == NULL)
        {
                printf("Memory allocation failed");
                free(got_poems.poems[0]);
		free(got_poems.poems);
                return error_dummy;
        }
        
	read(cso, got_poems.poems[1], length2);
        got_poems.poems[1][length2] = '\0';
        read(cso, &placement2, sizeof(int));
        
        got_poems.placements[0] = placement1;
        got_poems.placements[1] = placement2;
	
	close(cso);
	
	
        return got_poems;
}

SentPoems two_random_poems()
{

        // If error occurs
        SentPoems error_dummy;


        int file = open("poems.dat", O_RDONLY);

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return error_dummy;
        }


        int capacity = 10;
        char** poems = malloc(capacity * sizeof(char*));
        if(poems == NULL)
        {
                printf("Memory allocation failed\n");
        }


        int list_iterator = 0;
        size_t length_counter;

        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {

                if(list_iterator >= capacity)
                {
                        capacity *= 2;
                        char** poems_temp = realloc(poems, capacity * sizeof(char*));
                        if(poems_temp == NULL)
                        {
                                printf("Memory allocation failed\n");
                                close(file);
                                free(poems);
                                return error_dummy;
                        }
                        poems = poems_temp;
                }

                poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
                if(poems[list_iterator] == NULL)
                {
                        printf("Memory allocation failed\n");
                        close(file);
                        free(poems);
                        return error_dummy;
                }
                //fread(poems[list_iterator], sizeof(char), length_counter, file);
                read(file, poems[list_iterator], length_counter);
                poems[list_iterator][length_counter] = '\0';
                list_iterator++;





        }

        close(file);

        int random_index1;
        int random_index2;
        do
        {
                random_index1 = rand() % (list_iterator);
                random_index2 = rand() % (list_iterator);
        }while(random_index1 == random_index2);

        SentPoems mySentPoems;
        mySentPoems.placements[0] = random_index1;
        mySentPoems.placements[1] = random_index2;

        mySentPoems.poems = malloc(2 * sizeof(char*));
        if(mySentPoems.poems == NULL)
        {
                printf("Memory allocation failed\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                return error_dummy;
        }
        mySentPoems.poems[0] = malloc(strlen(poems[random_index1]) * sizeof(char));
        mySentPoems.poems[1] = malloc(strlen(poems[random_index2]) * sizeof(char));

        if(mySentPoems.poems[0] == NULL || mySentPoems.poems[1] == NULL)
        {
                printf("Memory allocation failed\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                free(mySentPoems.poems[0]);
                free(mySentPoems.poems[1]);
                free(mySentPoems.poems);
                return error_dummy;
        }

        
        

        strcpy(mySentPoems.poems[0], poems[random_index1]);
        strcpy(mySentPoems.poems[1], poems[random_index2]);


        for(int i = 0; i < (list_iterator); i++)
        {
                free(poems[i]);
        }

        free(poems);

        return mySentPoems;

}

int delete_specific_poem(int which)
{
               

        int file = open("poems.dat", O_RDONLY);

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }


        int capacity = 10;
        char** poems = malloc(capacity * sizeof(char*));
        if(poems == NULL)
        {
                printf("Memory allocation failed\n");
        }


        int list_iterator = 0;
        int deleted = 0;
        int counter = 0;
        size_t length_counter;

        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {
                if((counter) == which)
                {
                        deleted = 1;
                        lseek(file, length_counter, SEEK_CUR);
                        counter++;
                }
                else
                {
                        if(list_iterator >= capacity)
                        {
                                capacity *= 2;
                                char** poems_temp = realloc(poems, capacity * sizeof(char*));
                                if(poems_temp == NULL)
                                {
                                        printf("Memory allocation failed\n");
                                        close(file);
                                        free(poems);
                                        return 0;
                                }
                                poems = poems_temp;
                        }

                        poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
                        if(poems[list_iterator] == NULL)
                        {
                                printf("Memory allocation failed\n");
                                close(file);
                                free(poems);
                                return 0;
                        }
                        //fread(poems[list_iterator], sizeof(char), length_counter, file);
                        read(file, poems[list_iterator], length_counter);
                        poems[list_iterator][length_counter] = '\0';
                        counter++;
                        list_iterator++;
                }


        }



        if(!deleted)
        {
                printf("A kért vers nem található a fájlban.\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                close(file);
                return 0;
        }
        close(file);


        file = open("poems.dat", O_WRONLY | O_TRUNC);
        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                for(int i = 0; i < list_iterator; i++)
                {
                        free(poems[i]);
                }
                free(poems);
                close(file);
                return 0;
        }


        for(int i = 0; i < (list_iterator); i++)
        {
                size_t curr_poem_length = strlen(poems[i]);
                write(file, &curr_poem_length, sizeof(size_t));
                write(file, poems[i], curr_poem_length);

                //fwrite(&curr_poem_length, sizeof(size_t), 1, file);
                //fwrite(poems[i], sizeof(char), curr_poem_length, file);
        }



        for(int i = 0; i < (list_iterator); i++)
        {
                free(poems[i]);
        }

        free(poems);

        close(file);

        printf("\n");
        return 1;

}

int number_of_poems()
{
        int file = open("poems.dat", O_RDONLY );
        size_t length_counter = 0;

        if(file == -1)
        {
                printf("Couldn't locate the file\n");
                return 0;
        }

        int list_iterator = 0;
        while(read(file, &length_counter, sizeof(size_t)) == sizeof(size_t))
        {
                char* poems = malloc((length_counter + 1) * sizeof(char));
                if(poems == NULL)
                {
                        printf("Memory allocation failed\n");
                        return 0;
                }
                //fread(poems, sizeof(char), length_counter, file);
                if(read(file, poems, length_counter) == length_counter)
                {
                        poems[length_counter] = '\0';
                }
                free(poems);
                list_iterator++;


        }

        close(file);

        return list_iterator;

}

int isInArray(int array[], int size, int number)
{
	for(int i = 0; i < size; i++)
	{
		if(array[i] == number)
		{
			return 1;
		}
	}
	return 0;
}