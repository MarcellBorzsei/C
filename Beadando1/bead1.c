#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int add_poem();
int list_poems();
int delete_poem();
int change_poem();

int main()
{
	while(1)
	{

	

	
		printf("%s", "Nyuszi Mama Verseskötete\n");
		printf("%s", "1. Új vers hozzáadása\n");
		printf("%s", "2. Versek listázása\n");
		printf("%s", "3. Vers törlése\n");
		printf("%s", "4. Vers módosítása\n");
		printf("%s", "5. Kilépés\n");

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
				exit(0);

		default:
				printf("%s", "Érvénytelen választás!\n");
				printf("%s", "Válassz újra!\n");


		}	

	}




	return 0; 
}

int add_poem()
{
	FILE* file = fopen("poems.dat", "ab");
	char* new_poem;

	// Opening file
	if(file == NULL)
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
	
	fwrite(&new_poem_length, sizeof(size_t), 1, file);
	fwrite(new_poem, sizeof(char), new_poem_length, file);

	free(new_poem);
	fclose(file);
	printf("Sikeresen hozzáadtad a verset!\n");
	printf("\n");

	return 1; 
	

}

int list_poems()
{
	FILE* file = fopen("poems.dat", "rb");
	size_t length_counter = 0; 
	
	if(file == NULL)
	{
		printf("Couldn't locate the file\n");
		return 0;
	}

	while(fread(&length_counter, sizeof(size_t), 1, file) == 1)
	{
		char* poems = malloc((length_counter + 1) * sizeof(char));
		if(poems == NULL)
		{
			printf("Memory allocation failed\n");
			return 0;
		}
		fread(poems, sizeof(char), length_counter, file);
		poems[length_counter] = '\0';
		printf("\n");
		printf("%s\n", poems);
	       	printf("\n");
		free(poems);	
	}

	fclose(file);

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


	FILE* file = fopen("poems.dat", "rb");
	
	if(file == NULL)
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

	while(fread(&length_counter, sizeof(size_t), 1, file) == 1)
	{
		if((counter + 1) == requested_number)
		{
			deleted = 1;
			fseek(file, length_counter, SEEK_CUR);
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
					return 0;
				}
				poems = poems_temp;
			}

			poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
			if(poems[list_iterator] == NULL)
			{
				printf("Memory allocation failed\n");
				free(poems);
				return 0;
			}
			fread(poems[list_iterator], sizeof(char), length_counter, file);
			poems[list_iterator][length_counter] = '\0';
			counter++;
			list_iterator++;
		}
		

	}

	fclose(file);

	if(!deleted)
	{
		printf("A kért vers nem található a fájlban.\n");
		for(int i = 0; i < list_iterator; i++)
		{
			free(poems[i]);
		}
		free(poems);
		return 0;
	}


	file = fopen("poems.dat", "wb");
	if(file == NULL)
	{
		printf("Couldn't locate the file\n");
		for(int i = 0; i < list_iterator; i++)
		{
			free(poems[i]);	
		}
		free(poems);
		return 0;
	}


	for(int i = 0; i < (list_iterator); i++)
	{
		size_t curr_poem_length = strlen(poems[i]);
		fwrite(&curr_poem_length, sizeof(size_t), 1, file);
	      	fwrite(poems[i], sizeof(char), curr_poem_length, file);	
	}

		

	for(int i = 0; i < (list_iterator); i++)
	{
		free(poems[i]);
	}

	free(poems);
	
	fclose(file);

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

	
	FILE* file = fopen("poems.dat", "rb");
	
	if(file == NULL)
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

	while(fread(&length_counter, sizeof(size_t), 1, file) == 1)
	{
		if((counter + 1) == requested_number)
		{
			deleted = 1;
			fseek(file, length_counter, SEEK_CUR);
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
					return 0;
				}
				poems = poems_temp;
			}

			poems[list_iterator] = malloc((length_counter + 1) * sizeof(char));
			if(poems[list_iterator] == NULL)
			{
				printf("Memory allocation failed\n");
				free(poems);
				return 0;
			}
			fread(poems[list_iterator], sizeof(char), length_counter, file);
			poems[list_iterator][length_counter] = '\0';
			counter++;
			list_iterator++;
		}
		

	}

	fclose(file);

	if(!deleted)
	{
		printf("A kért vers nem található a fájlban.\n");
		for(int i = 0; i < list_iterator; i++)
		{
			free(poems[i]);
		}
		free(poems);
		free(new_poem);
		return 0;
	}


	file = fopen("poems.dat", "wb");
	if(file == NULL)
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
			fwrite(&changed_poem_length, sizeof(size_t), 1, file);
			fwrite(new_poem, sizeof(char), changed_poem_length, file);
			is_changed_in = 1;
		}
		
		size_t curr_poem_length = strlen(poems[i]);
		fwrite(&curr_poem_length, sizeof(size_t), 1, file);
	      	fwrite(poems[i], sizeof(char), curr_poem_length, file);	
			
	}
	

	//Ha az utolsót választja módosításra
	if(!is_changed_in)
	{
		size_t changed_poem_length = strlen(new_poem);
		fwrite(&changed_poem_length, sizeof(size_t), 1, file);
		fwrite(new_poem, sizeof(char), changed_poem_length, file);
	}
	
	fclose(file);	

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

