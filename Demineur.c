#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int N = 0;
int K = 0; //declaration de variables globales qui seront par la suite modifiées par l'utilisateur a l'aide d'un scanf

void Init_Grille (char **tab_jeu,int **tab_reponse) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++){
            tab_jeu[i][j] = '-';      //Chaque case du tableau de jeu, celui affiche dans le terminal, est remplace par un tiret indiquant qu'elle n'a pas ete ouverte
            tab_reponse[i][j] = 0;    //Chaque case du tableau de reponse est remplacer par un 0, indiquant qu'il n'y a pas de mines autour
        }
    }
    int k = K;
    srand(time(NULL));  //permet de rendre la fonction rand vraiment aleatoire
    for (int mines_placees=0 ; mines_placees <= k; mines_placees++) {      //Boucle fort qui place les mines de maniere aleatoire sur le tableau de reponse
            i = rand()%N;
            j = rand()%N;
            if (tab_reponse[i][j] == 0)
                tab_reponse[i][j] = 9;
            else
                k++;
    }
// On modifie ensuite les valeurs des cases autour des mines, on prend les coins au cas par cas, les lignes et colonnes sur les marges du tableaub aussi, et on verifie ensuite pour toute valeur
// qui n'est ni a la marge ni dans un coin
        int mines = 0;
    if (tab_reponse[0][0] != 9){
        if (tab_reponse[0][1] == 9)
            mines++;
        if (tab_reponse[1][0] == 9)
            mines++;
        if (tab_reponse[1][1] == 9)
        tab_reponse[0][0] = mines;
    }
    tab_reponse[0][N-1]   = (tab_reponse[0][N-2] == 9) + (tab_reponse[1][N-1] == 9) + (tab_reponse[1][N-2] == 9);
    tab_reponse[N-1][0]   = (tab_reponse[N-1][1] == 9) + (tab_reponse[N-2][0] == 9) + (tab_reponse[N-2][1] == 9);
    tab_reponse[N-1][N-1] = (tab_reponse[N-1][N-2]==9) + (tab_reponse[N-2][N-1]==9) + (tab_reponse[N-2][N-2]==9);
    for (int a = 1; a < N-1; a++) {
        if (tab_reponse[a][0]!=9)
            tab_reponse[a][0] = (tab_reponse[a-1][0]==9) + (tab_reponse[a-1][1]==9) + (tab_reponse[a][1]==9) +
                                (tab_reponse[a+1][0]==9) + (tab_reponse[a+1][1]==9);
    }
    for (int a=1; a<N-1; a++) {
        if (tab_reponse[a][N-1]!=9)
            tab_reponse[a][N-1] = (tab_reponse[a-1][N-2]==9) + (tab_reponse[a-1][N-1]==9) + (tab_reponse[a][N-2]==9) +
                                    (tab_reponse[a+1][N-1]==9) + (tab_reponse[a+1][N-2]==9);
    }
    for (int b=1; b<N-1; b++) {
        if (tab_reponse[0][b]!=9)
            tab_reponse[0][b] = (tab_reponse[0][b-1]==9) + (tab_reponse[0][b+1]==9) + (tab_reponse[1][b-1]==9) +
                                (tab_reponse[1][b]==9) + (tab_reponse[1][b+1]==9);
    }
    for (int b=1; b<N-1; b++) {
        if (tab_reponse[N-1][b]!=9)
            tab_reponse[N-1][b] = (tab_reponse[N-1][b-1]==9) + (tab_reponse[N-1][b+1]==9) + (tab_reponse[N-2][b-1]==9) +
                                    (tab_reponse[N-2][b]==9) + (tab_reponse[N-2][b+1]==9);
    }
    for (int a=1; a<N-1; a++)
        for (int b=1; b<N-1; b++) {
            if (tab_reponse[a][b]!=9)
            tab_reponse[a][b] = (tab_reponse[a-1][b-1]==9) + (tab_reponse[a-1][b]== 9)+ (tab_reponse[a-1][b+1]== 9)+
                                (tab_reponse[a][b-1]==9) + (tab_reponse[a][b+1]==9) +
                                (tab_reponse[a+1][b-1]==9) + (tab_reponse[a+1][b]==9) + (tab_reponse[a+1][b+1]==9);
        }
}

//L'affichage se fait en fonction de la taille que l'utilisateur a definit. On utilise un operateur ternaire pour que le tableau ne soit pas decale lorsque la taille de N est > 10

void Aff_Grille(char **tab_jeu){
    int i,j;
    printf("   |");
    for(i=0;i<N;i++)
        printf(" %d%s",i,i>9?"":" ");
    printf("\n");
    printf("___|");
    for(i=0;i<N;i++)
        printf("___",i>9?"":"_");
    printf("\n");
    for(i=0;i<N;i++){
        printf(" %d%s| ",i,i>9?"":" ");
    for(j=0;j<N;j++)
        printf("%c  ",tab_jeu[i][j]);
    printf("\n");
    }
}

//On utilise la fonction demasque_case pour verifier si la case saisit par l'utilisateur est une mine ou pas. La fonction va chercher les valeurs de la case choisit dans le tab_reponse pour ensuite
//Les afficher dans le tab_jeu. On utilise le principe de recursivite pour verifier si, lorsque l'utilisateur saisit une case qui contient un 0, ouvre toutes les cases autour qui ne contiennent pas de mines

void Demasque_case(int i, int j, int **tab_reponse, char **tab_jeu){
    if(tab_reponse[i][j]==9){
        printf("\n-------------------\n|C'etait une mine!|\n-------------------\n\n");
        tab_jeu[i][j]='X';
        return;
    }
        tab_jeu[i][j] = tab_reponse[i][j]+48;
    if(tab_reponse[i][j]==0){
        if((i+1>=0) && (i+1<N) && (j>=0) && (j<N) && tab_jeu[i+1][j]!='0')
            Demasque_case(i+1, j, tab_reponse, tab_jeu);
        if((i-1>=0) && (i-1<N) && (j>=0) && (j<N) && tab_jeu[i-1][j]!='0')
            Demasque_case(i-1, j, tab_reponse, tab_jeu);
        if((i+1>=0) && (i+1<N) && (j+1>=0) && (j+1<N) && tab_jeu[i+1][j+1]!='0')
            Demasque_case(i+1, j+1, tab_reponse, tab_jeu);
        if((i>=0) && (i<N) && (j-1>=0) && (j-1<N) && tab_jeu[i][j-1]!='0')
            Demasque_case(i, j-1, tab_reponse, tab_jeu);
        if((i>=0) && (i<N) && (j+1>=0) && (j+1<N) && tab_jeu[i][j+1]!='0')
            Demasque_case(i, j+1, tab_reponse, tab_jeu);
        if((i-1>=0) && (i-1<N) && (j+1>=0) && (j+1<N) && tab_jeu[i-1][j+1]!='0')
            Demasque_case(i-1, j+1, tab_reponse, tab_jeu);
        if((i+1>=0) && (i+1<N) && (j-1>=0) && (j-1<N) && tab_jeu[i+1][j-1]!='0')
            Demasque_case(i+1, j-1, tab_reponse, tab_jeu);
        if((i-1>=0) && (i-1<N) && (j-1>=0) && (j-1<N) && tab_jeu[i-1][j-1]!='0')
            Demasque_case(i-1, j-1, tab_reponse, tab_jeu);
    }
}

int main(){
    //Utilisation de la fonction Time pour afficher le temps, On recuper le temps au debut, � la fin, et on fait la soustraction des deux pour avoir le temps total
    time_t begin = time( NULL );
    int **tab_reponse, i, j;
    printf("Bienvenue dans le jeu du demineur!\n\nCombien de lignes-colonnes voulez vous ? ");
    scanf("%d", &N);
    K = (N*N)/5;

    //Allocation dynamiques des tableaux
    tab_reponse=malloc(N*sizeof(int*));
    for(i=0;i<N;i++)
    tab_reponse[i]=malloc(sizeof(int)*N);
    char **tab_jeu;
    tab_jeu=malloc(N*sizeof(char*));
    for(i=0;i<N;i++)
    tab_jeu[i]=malloc(sizeof(char)*N);

    Init_Grille(tab_jeu,tab_reponse);
    int compteur;
    i=0, j=0;
    //Declaration de booleens pour la gestion de fin du jeu: victoire ou defaite, quand s'arrete t-on.
    //Utilisation d'une boucle do while qui demande a l'utilisateur de rentrer les coordonnees d'une nouvelle case a chaque tour
    //La boucle est imbriquee de nombreuses autre boucle permettant de verifier a chaque tour de boucle si, la valeur saisit par l'utilisateur est dans la grille de jeu; l'utilisateur n'est pas
    //tomber sur une mine (defaite), il reste des cases non-min�es a decouvrir (victoire)
    bool pas_fini = true, victoire = false;
    while(pas_fini==true){
        do{
            printf("Veuillez entrer la ligne de la case (entre 0 et %d)   : ",N-1);
            scanf("%d",&i);
        }while((i<0) || (i>=N));
        do{
            printf("Veuillez entrer la colonne de la case (entre 0 et %d) : ",N-1);
            scanf("%d",&j);
        }while((j<0) || (j>=N));
        Demasque_case(i, j, tab_reponse, tab_jeu);
        printf("\n");
        Aff_Grille(tab_jeu);
        printf("\n");
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                if(tab_jeu[i][j]=='X'){
                    i = N;
                    pas_fini = false;
                    break;
                }
        if(pas_fini==false)
            break;
        compteur = 0;
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                if(tab_jeu[i][j]=='-')
                    compteur++;
        if(compteur<=K){
            pas_fini=false;
            victoire = true;
        }
    }
    time_t end = time(NULL);
    unsigned long secondes = (unsigned long) difftime( end, begin );
    if(victoire==true)
        printf("\n-----------------------------------------\n|Bravo! Vous avez gagne en %ld secondes!|\n-----------------------------------------\n\n",secondes);
    else
        printf("\n---------------------------------------------------\n|Vous avez perdu. Votre partie a dure %ld secondes.|\n---------------------------------------------------\n\n",secondes);
    return 0;
}
