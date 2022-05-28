/*****************************************************************/
/*Biblioteca musica | PROG2 | MIEEC | 2019/20     */
/*****************************************************************/

#include "musica.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

instante* instante_novo(int duracao, char *notas, int bateria[],  char* instrumentoExtra)
{
	return NULL;
}

musica* musica_nova()
{
	return NULL;
}


int  instante_insere(musica *m , instante *t, int pos )
{
	return -1;
}

int musica_tamanho(musica *m)
{
	return -1;
}

instante* musica_pesquisa_nota(musica *m, char nota, int instrumento)
{
	return NULL;
}


instante* instante_remove(musica *m, int pos)
{
	return NULL;
}


int instante_apaga( instante *t )
{
	return -1;
}




int musica_apaga(musica *m)
{
	return -1;
}

musica *musica_importa(const char *nomef){
    FILE *f = fopen(nomef, "r");
    if(f == NULL) return NULL;
    
    musica *m = musica_nova();
    if(m == NULL){
        fclose(f);
        return NULL;

    }

    int duracao = 0, i, j;
    char str_aux[100] = {};
    int bateria[8] = {0};
    char notas[9] = {0};
    char instrumentoExtra[100] = {0};
   
    instante *aux;

    while(fscanf(f, "%d", &duracao) != EOF){
        fgets(str_aux, 100*sizeof(char), f);
        str_aux[strlen(str_aux)-1] = '\0';

        /* lê os 8 carateres correspondentes à bateria */
        i = 0;
        j = 1;
        while(i < 8){
            
            bateria[i] = atoi(str_aux+j);
            i++;
            j+=2;
        }

        /* lê o resto da linha do ficheiro */
        if(strlen(str_aux+17) > 1){
            j = 0;
            for(i = 17; i < strlen(str_aux+17)+18; i++){
                if(str_aux[i] == ' ') continue;
                else if(str_aux[i] == '"'){
                    strcpy(instrumentoExtra, str_aux+i+1);
                    instrumentoExtra[strlen(instrumentoExtra) - 1] = '\0';
                    break;
                }
                else if(j < 8){
                    notas[j++] = str_aux[i];
                }
            }
           
        }
       
        /* cria novo instante (caso não exista instrumentoExtra coloca NULL */
        if(strlen(instrumentoExtra) <= 1){
            aux = instante_novo(duracao, notas, bateria, NULL);
        }
        else{
            aux = instante_novo(duracao, notas, bateria, instrumentoExtra);
        }
        
        if(aux == NULL){
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* insere instante na lista */
        if(instante_insere(m, aux, -1) == -1){
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* reinicia instrumentoExtra e notas */
        memset(instrumentoExtra, '\0', 100);
        memset(notas, '\0', 9);

    }
    fclose(f);
    return m;

}
int musica_toca(musica *m, int duracao)
{
    return -1;
}
int musica_corrige(musica *m, char *ficheiro){
   
   return -1;
}






