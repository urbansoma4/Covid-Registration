#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

struct ugyfel_adatai {
	char nev[30];
	int evszam;
	char telefonszam[15];
	char felar;
	int oltva;
	struct ugyfel_adatai *next;
};

struct ugyfel_adatai *ugyfelek = 0; 



void listazas() {
	
	struct ugyfel_adatai *seged = ugyfelek;
		
	if (seged != 0) {
	int i = 1;
	printf("\nUgyfeleink:\n\n");
			do {
				printf("\n%d. ", i);
				printf("nev: %s", seged->nev);
				printf(" evszam: %d", seged->evszam);
				printf(" telefonszam: %s", seged->telefonszam);
				 if (seged->felar == 'i' )
				 {
				 	printf ( " felar: IGEN ");
				 }
				 else
				 {
				 	printf(" felar: NEM ");
				 }
				if (seged->oltva == 0 )
				 {
				 	printf ( "Nincs oltva");

				 }
				 else
				 {
				 	printf("OLTVA ");	
				 }

				 
				i++;
				seged = seged->next;
			} while (seged != 0);
	}
	else printf("Ures lista \n");
	
}

void addelem(char nev[30], int evszam, char telefonszam[15], char felar, int oltva) {
	int i;
	struct ugyfel_adatai *elem;
	elem = malloc( sizeof(struct ugyfel_adatai) );
	elem->next = ugyfelek;
	strcpy(elem->nev, nev);
	elem->evszam = evszam;
	strcpy(elem->telefonszam, telefonszam);
	elem->felar = felar;
	elem->oltva = oltva;
	
	ugyfelek = elem;
}


void beszuras() {
	char nev[30];
	int evszam;
	char telefonszam[15];
	char felar; 
	
	printf("\nUgyfel felvetele:\n");
	printf("Addja meg a nevet:");
	
	scanf("%[^\n]s", &nev);
	getchar();
	printf("\nAddja meg a szuletesi evszamat:\n");
	scanf("%d", &evszam);
	getchar();
	printf("\nAddja meg a telefonszamat:\n");
	scanf("%[^\n]s", &telefonszam);
	getchar();
	printf("\nKéri a fizetos felarat? (i/n):\n");
	scanf("%c", &felar);
	getchar();
	
	
	addelem(nev, evszam, telefonszam, felar, 0);
	
	printf("\nUgyfel regisztralva!\n");
}




void modositas() {
	char nev[30];
	int evszam;
	char telefonszam[15];
	char felar;
	int melyik;
	listazas();
	printf("\nAdd meg hanyadik ugyfel adatait szeretned modositani! ");
	scanf("%d", &melyik);
	getchar();
	printf("\nMost pedig addja meg az uj parametereket:\n");
	printf("Addja meg a nevet: ");
	scanf("%[^\n]s", &nev);
	getchar();
	printf("\nAddja meg a szuletesi evszamat: ");
	scanf("%d", &evszam);
	getchar();
	printf("\nAddja meg a telefonszamat: ");
	scanf("%[^\n]s", &telefonszam);
	getchar();
	printf("\nKéri a fizetos felarat? (i/n): ");
	scanf("%c", &felar);
	getchar();
	
	struct ugyfel_adatai *seged = ugyfelek;
		
	int i = 1;
			while (seged != 0 && i != melyik) {
				seged = seged->next;
				i++;
			}
			if (seged == 0) printf("Nincs ilyen sorszamu ugyfel a listaban!\n");
			else {
				strcpy(seged->nev, nev);
				seged->evszam = evszam;
				strcpy(seged->telefonszam, telefonszam);
				seged->felar = felar;
				
			}
	
	printf("\nA bejegyzes modositva!\n");
}
void modositas2(int melyik, struct ugyfel_adatai adatok) {
		if(adatok.oltva == 0){
			return;
		}
		struct ugyfel_adatai *seged = ugyfelek;
		int i = 1;
			while (seged != 0 && i != melyik) {
				seged = seged->next;
				i++;
			}
			if (seged == 0) printf("Nincs ilyen sorszamu ugyfel a listaban!\n");
			else {
				seged->oltva = adatok.oltva;
				printf("\nA bejegyzes modositva!\n");	
			}
	
}
void torles() {
	int melyik;
	listazas();
	printf("\nAdd meg a torolni kivant ugyfel sorszamat! ");
	scanf("%d", &melyik);
	getchar();
	
	struct ugyfel_adatai *seged = ugyfelek;
	struct ugyfel_adatai *elozo = 0;
		
	int i = 1;
			while (seged != 0 && i != melyik) {
				elozo = seged;
				seged = seged->next;
				i++;
			}
			if (seged == 0) printf("Nincs ilyen sorszamu ugyfel a listaban!\n");
			else {
				if (elozo == 0) ugyfelek = seged->next;
				else elozo->next = seged->next;
				free(seged);
			}
	
	printf("\nA bejegyzes torolve!\n");
}

void betoltes() {

if( access("ugyfellista.bin", 0 ) != -1 ) {
	FILE *ugyfellistafile;
	ugyfellistafile = fopen("ugyfellista.bin", "rb");
	if (ugyfellistafile != NULL) {
		struct ugyfel_adatai seged2;
		while (fread(&seged2, sizeof(seged2), 1, ugyfellistafile)) {
			addelem(seged2.nev, seged2.evszam, seged2.telefonszam, seged2.felar, seged2.oltva);
		}
	}
	fclose(ugyfellistafile);
}
}

void mentes() {
	
	FILE *ugyfellistafile;
	ugyfellistafile = fopen("ugyfellista.bin", "w");
	struct ugyfel_adatai *seged2 = ugyfelek;
	while (seged2 != 0) {
		fwrite(seged2, sizeof(*seged2), 1, ugyfellistafile);
		seged2 = seged2->next;
	}
	fclose(ugyfellistafile);
}
//2 rész
 pid_t szulo_id = 0;
 int jelek = 0;
 int mento1_pipes_in[2];
 int mento1_pipes_out[2];
 int mento2_pipes_in[2];
 int mento2_pipes_out[2];


 void varakozas(int sig)
 {
 	if (sig == SIGUSR1)
 	{
 		jelek++;
 	}
 }

 void varakozas2(int sig)
 {
 	if (sig == SIGUSR2)
 	{
 		jelek++;
 	}
 }

 pid_t mento_1(int pipe_id_rec, int pipe_id_send){

 	char adatok[50];
 	pid_t szal = fork();
 	if (szal == -1)
 	{
 		exit(-1);
 	}
 	if (szal > 0)
 	{
 		return szal;
 	}
 	kill(szulo_id, SIGUSR1);
 	write(pipe_id_send,"hello", 12 );
     exit(0);
 }
 //gyerek2
 pid_t mento_2(int pipe_id_rec, int pipe_id_send){

	
 	char adatok[50];
 	pid_t szal = fork();
 	if (szal == -1)
 	{
 		exit(-1);
 	}
 	if (szal > 0)
 	{
 		return szal;
 	}
 	kill(szulo_id, SIGUSR2);
 	int test = 0;
 	read(pipe_id_rec, &test, sizeof(int));
 	printf("Amit kaptam %i\n ", test);
 	exit(0);
 }

//

void handler(int signalumber){
  printf("Harcra Fel!!!\n");
}

void busz(int i, int busz1_pipe[2], int busz2_pipe[2]){
	
	pid_t szulo = getppid();
	kill(szulo, SIGUSR1);
	
	struct ugyfel_adatai buszadat[5];
	
	if(i == 1){
		read(busz1_pipe[0],&buszadat,5*sizeof(struct ugyfel_adatai));
	}
	
	else{
		read(busz2_pipe[0],&buszadat,5*sizeof(struct ugyfel_adatai));
	}
	
	for (int j = 0; j < 5; j++)
	{	
		 int r = rand()%10;
		 if (r<9){
			buszadat[j].oltva = 1;
		 }
		printf("NEV: %s\n", buszadat[j].nev);
	}
	if(i == 1){
		write(busz1_pipe[1], buszadat, 5*sizeof(struct ugyfel_adatai));
		close(busz1_pipe[1]);
	}
	else{
		write(busz2_pipe[1], buszadat, 5*sizeof(struct ugyfel_adatai));
		close(busz2_pipe[1]);
	}
	
}
void torzs(int i, int busz1_pipe[2], int busz2_pipe[2]){
	pause();
	struct ugyfel_adatai busz1adat[5];
	int index1[5];
	struct ugyfel_adatai busz2adat[5];
	int index2[5];
	struct ugyfel_adatai *seged = ugyfelek;
	int num = 0;
	int j=1;
	while (num<5)
	{
		if(seged->oltva == 0){
			busz1adat[num] = *seged;
			index1[num]=j;
			num++;
			printf("%s varja az egyes busz\n", seged->nev);
		}
		seged = seged->next;
		j++;
	}
	write(busz1_pipe[1],busz1adat,5*sizeof(struct ugyfel_adatai));
	if (i>9){
		
		int num2 =0;
		while (num2<5)
		{
			if(seged->oltva == 0){
				busz2adat[num2] = *seged;
				index2[num2] = j;
				num2++;
				printf("%s varja az kettes busz\n", seged->nev);
			}
			seged = seged->next;
			j++;
		}
		write(busz2_pipe[1],busz2adat,5*sizeof(struct ugyfel_adatai));
	}
	
		wait(NULL);
		read(busz1_pipe[0], &busz1adat, 5*sizeof(struct ugyfel_adatai));
		close(busz1_pipe[0]);
		for (int x = 0; x < 5; x++)
		{
			modositas2(index1[x], busz1adat[x]);
		}
		
		if(i>9){
			read(busz2_pipe[0], &busz2adat, 5*sizeof(struct ugyfel_adatai));
			close(busz2_pipe[0]);
			for (int x = 0; x< 5; x++)
			{
				modositas2(index2[x], busz2adat[x]);
			}

		}
		
	
}


void oltas(){
	
int busz1_pipe[2];
int busz2_pipe[2];	
signal(SIGUSR1,handler);
signal(SIGUSR2,handler);
	
	
	pid_t busz1, busz2;
 	betoltes();
	listazas();
	struct ugyfel_adatai *seged = ugyfelek;
	int i = 0;
	if (seged != 0) {
			do {
				if(seged->oltva == 0){
					i++;
				}
				seged = seged->next;
			} while (seged != 0);
	}
	printf( "Nem oltottak szama: %i\n",i);
	
		if(i > 4)
		{
		if(pipe(busz1_pipe) == -1 || pipe(busz2_pipe) == -1)
    	{
        perror("Pipe open error\n"); return 1;
    	}
		fflush(stdout);
		busz1 = fork();


			if (busz1 == 0) //busz1
			{
				busz(1,busz1_pipe,busz2_pipe);
			} 
			else {
				if(i>9)
					{


					busz2 = fork();

						if (busz2 == 0) //busz2
						{
							busz(2,busz1_pipe,busz2_pipe);
						}
						else //szulo ha busz2 is van 
						{ 
							torzs(i,busz1_pipe,busz2_pipe);
						}
					}
					else //szulo ha busz1 van csak
					{
						torzs(i,busz1_pipe,busz2_pipe);
					}

				}
		}

	

	 signal(SIGUSR1, varakozas);
	 signal(SIGUSR2, varakozas2);
	 szulo_id = getpid();

	
	 int succ = pipe(mento1_pipes_in);
	 if (succ == -1)
	 {
	 	exit(-1);
	 }
	 int succ1 = pipe(mento1_pipes_out);
	 if (succ1 == -1)
	 {
	 	exit(-1);
	 }
	 int succ2 = pipe(mento2_pipes_out);
	 if (succ2 == -1)
	 {
	 	exit(-1);
	 }
	 int succ3 = pipe(mento2_pipes_in);
	 if (succ3 == -1)
	 {
	 	exit(-1);
	 }
	
	 wait(NULL);

	 mento_1(mento1_pipes_out[0],mento1_pipes_in[1]);
	 mento_2(mento2_pipes_out[0],mento2_pipes_in[1]);

	 while (jelek < 1);
	 puts("First Ambulance is ready.");
	 while (jelek < 2);
	 puts("Second Ambulance is ready.\n");
	 int number_of_test = 4;
	 write(mento2_pipes_out[1], &number_of_test, sizeof(int));
     char tesszt[12];
     read(mento1_pipes_in[0], &tesszt, 12);
     wait(NULL);
     printf("Üzenet: %s ", tesszt);

}
int main() {
	
	betoltes();
	srand(time(0));
	printf("\n\nUgyfelek regisztralasa\n");
	int vege;	
	do {
		printf("\n\n---------------\nMenu\n\n");
		printf("1. Listazas\n");
		printf("2. Beszuras\n");
		printf("3. Modositas\n");
		printf("4. Torles\n");
		printf("5. Kilepes");
		printf("\n\n---------------\n");
		scanf("%d", &vege);
		getchar();
		switch (vege) {
			case 1:
				listazas();
			break;
			case 2:
				beszuras();
			break;
			case 3:
				modositas();
			break;
			case 4:
				torles();
			break;
			case 5:
			break;
			default:
				printf("\n\nNem letezo menupont!\n");
			break;
		}
	} while (vege != 5);
	oltas();
	mentes();
	return 0;
}

