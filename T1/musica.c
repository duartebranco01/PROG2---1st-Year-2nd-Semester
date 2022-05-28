/*****************************************************************/
/*Biblioteca musica | PROG2 | MIEEC | 2019/20     */
/*****************************************************************/

#include "musica.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

instante* instante_novo(int duracao, char *notas, int bateria[],  char* instrumentoExtra)
{   
    instante *insta = (instante *)malloc(sizeof(instante));
    int i=0, cont=0;
    if(insta==NULL)
    {
        free(insta);
        return NULL;
    }
    if(duracao>16||duracao<1) return NULL; //caso algum dos parametros estejam errados, retorna NULL
    else
    {
        for(i=0; i<8; i++)
        {
            if (bateria[i]<0 ||bateria[i]>1) return NULL;
        }

        for(i=0; i<strlen(notas); i++)
        {
            if(notas[i]>=65 && notas[i]<=71) cont++;
            else if(notas[i]>=50 && notas[i]<=53) cont++;
        }
        if(cont!=strlen(notas)) return NULL;
    }
    
    insta->duracao=duracao;
    
    insta->notasGuitarra[0]='-';
    insta->notasGuitarra[1]='-';
    
    insta->notasPiano[0]='-';
    insta->notasPiano[1]='-';
         
    for(i=0; i<strlen(notas); i++) 
        {     
            if(notas[i]=='2') //guitarra 2 e 3
            {
                insta->notasGuitarra[0]=notas[i-1];
            }
            else if(notas[i]=='3')
            {
                insta->notasGuitarra[1]=notas[i-1];   
            } 
            else if(notas[i]=='4') //piano 4 e 5
            {
                insta->notasPiano[0]=notas[i-1];
            }
            else if(notas[i]=='5')
            {
                insta->notasPiano[1]=notas[i-1];
            }                             
        }
        
    for(i=0; i<8; i++)
    {
        insta->bateria[i]=bateria[i]; 
    }
    if(instrumentoExtra==NULL)
    {
        insta->instrumentoExtra= NULL;
    }
    else
    {
    insta->instrumentoExtra=(char *) calloc(1, (strlen(instrumentoExtra)+1) * sizeof(char));
    strcpy(insta->instrumentoExtra, instrumentoExtra);
    }
  
    return insta;
    	
}

musica* musica_nova()
{
    musica *music= (musica *)malloc(sizeof(musica)); //cria nova musica
    if(music == NULL)
    {
        free(music);
        return NULL;
    }
	music->inicio = NULL; //apontador criado mas que nao aponta para nada
	music->cursor = NULL;
    return music;
}


int  instante_insere(musica *m , instante *t, int pos )
{
    instante *atual;
    int tamanho=0, i=0; 
    
    atual=m->inicio;

    if(m==NULL || t==NULL) return -1;
    else if(m->inicio==NULL)
    {
        m->inicio=t;
        t->proximo=m->inicio;
        return 0;
    }
    else
    {
        while(atual->proximo!=m->inicio) // 1 2 3 4 1
        {
            tamanho++;
            atual=atual->proximo; //atual esta no ultimo
        }
        tamanho++; //soma o ultimo elemento
        
        if(pos>tamanho || pos<-1) return -1;
    }
    
    if(pos==-1)
    {
            atual->proximo=t;
            t->proximo=m->inicio;
            return 0;
    }
    
    atual=m->inicio;

    for(i=0; i<pos-1; i++)  // 1 2 3 t 4
    {
        atual=atual->proximo; //atual =pos-1 
    }
    t->proximo=atual->proximo;
    atual->proximo=t;

        return 0; 
}

int musica_tamanho(musica *m)
{
    int tamanho=0;
    instante *atual=m->inicio;

    if(m==NULL) return -1;
    
    else if(m->inicio==NULL) return 0; //tamanho=0 se nao existir musica
    
    while(atual->proximo!=m->inicio) //conta tamanho  
    {   
        tamanho++;
        atual=atual->proximo;
    }
    tamanho++; //soma ultimo elemento
	    return tamanho;
}

instante* musica_pesquisa_nota(musica *m, char nota, int instrumento)
{   
    int i=0;
    instante *find;
    
    if(m==NULL) return NULL;
    else if(nota<65 || nota>71) return NULL;
    else if(instrumento!=1 && instrumento!=0) return NULL; 
    
    else
    {   
        find=m->inicio;
        while(find->proximo!=m->inicio)
        {   
            for(i=0;i<2;i++)
            {
                if(instrumento==0) //guitarra 
                {
                    if(find->notasGuitarra[i]==nota)
                    {
                        return find;
                    }
                }
                else if(instrumento==1) //piano
                {
                    if(find->notasPiano[i]==nota)
                    {
                        return find;
                    }
                }
            }
            find=find->proximo;    
        }  
    }

    return NULL; //se nao encontrou
}


instante* instante_remove(musica *m, int pos)
{
    instante *atual, *remove;
    int i=0, tamanho;

    atual=m->inicio;

    tamanho=musica_tamanho(m);

    if(m==NULL || pos>tamanho || pos<0 ||tamanho<=0) return NULL;
    else if(m->inicio==NULL) return NULL;
    else
    {       
        if(tamanho==1)
        {
            remove=m->inicio;
            m->inicio=NULL;
            m->inicio->proximo=NULL;
                return remove;
        }
        else if(pos==0)
        {   
            while(atual->proximo!=m->inicio)
            {
                atual=atual->proximo; //atual =ultimo elemento
            }
            remove=m->inicio;
            atual->proximo=remove->proximo;
            m->inicio=m->inicio->proximo;
            return remove;
        }
        else
        {
            for(i=0; i<pos-1; i++)  // 1 2 3 4      pos=3
            {
                atual=atual->proximo; //atual =pos 1 a remove
            }
            remove=atual->proximo;
            atual->proximo=remove->proximo;
                return remove;
        }                                                                   
    }

	return NULL;
}


int instante_apaga( instante *t )
{
    if(t==NULL) return -1;
    else 
    {   
        if(t->instrumentoExtra!=NULL)
        {
            free(t->instrumentoExtra);
        }
        free(t);
        return 0;
    }
    return -1;
}


int musica_apaga(musica *m) 
{   
    instante *atual;
    atual=m->inicio;
    int tamanho=0, i=0, flag=0;           

    tamanho=musica_tamanho(m);

    if(m==NULL || tamanho==-1) return -1;
    else if(atual!=NULL)
    {
        for(i=0;i<tamanho;i++)
        {   
            flag=instante_apaga(atual);
            if(flag==-1) return -1;
            else if(flag==0) atual=atual->proximo;
        }           
        free(m);                  
        return 0;
    }
    return -1;
}

musica *musica_importa(const char *nomef){
   FILE *f = fopen(nomef, "r");
    if(f == NULL) return NULL;
    
    musica *m = musica_nova();
    if(m == NULL){
        return NULL;
        fclose(f);
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
    if(m->cursor==NULL) m->cursor=m->inicio;
    
    if(m==NULL || duracao<0 || m->inicio==NULL || m->cursor==NULL) return -1;
    else
    {
            while(1)
            {
                duracao-=m->cursor->duracao; 
                m->cursor=m->cursor->proximo;
                if(duracao<=0) break;
            }
            return 0;
    }

    return -1;
}

int musica_corrige(musica *m, char *ficheiro)
{  
    instante *alterar;
    int tamanho=0, modifica=0, instrumento, i=0, pi=0, pf=0, toca=0, bateria_pos=0, cont_bem=0, duracao_nova=0, x;
    char nota_alterar, nota_nova, absorve[20];

    tamanho=musica_tamanho(m);

    FILE *fpointer;
    fpointer=fopen(ficheiro, "r");
                                                                                                                                  
    if(fpointer==NULL || m==NULL || tamanho==-1) 
    {
        fclose(fpointer);
        return -1;
    }

    else 
    {
        while(fscanf(fpointer,"%d", &modifica)!=EOF) 
        {   
            alterar=m->inicio;
            switch (modifica)
            {
                case 1:
                    fscanf(fpointer, " %d %d", &pi, &pf);
                    if(pi<0 || pi>tamanho || pf<0 || pf>tamanho || pi>pf)
                    {   
                        break;
                    }

                    else
                    {
                        while(pi<=pf)
                        {
                            alterar=instante_remove(m, pi);
                            if(alterar==NULL) return -1;
                            x=instante_apaga(alterar);
                            if(x==-1) return -1;
                            pi++;
                        }
                        cont_bem++;
                        break;
                    }
                    
                case 2: //0=guitarra 1=piano
                    fscanf(fpointer," %d %c %c", &instrumento, &nota_alterar, &nota_nova);
                    
                    if(nota_alterar<'A' || nota_alterar>'G' || nota_nova<'A' || nota_nova>'G')
                    {   
                        break;
                    } 
                    else if(instrumento!= 1 && instrumento!=0)
                    {   
                        break;
                    }
                    else if(instrumento==0)
                    {   
                        alterar=musica_pesquisa_nota(m, nota_alterar, instrumento);
                        while(alterar!=NULL)
                        {
                            for(i=0;i<2;i++)
                            {
                                if(alterar->notasGuitarra[i]==nota_alterar) alterar->notasGuitarra[i]=nota_nova;
                            }
                            alterar=musica_pesquisa_nota(m, nota_alterar, instrumento);
                        }
                        cont_bem++;
                        break;
                    }

                    else if(instrumento==1)
                    {
                        alterar=musica_pesquisa_nota(m, nota_alterar, instrumento);
                        while(alterar!=NULL)
                        {
                            for(i=0;i<2;i++)
                            {
                                if(alterar->notasPiano[i]==nota_alterar) alterar->notasPiano[i]=nota_nova;
                            }
                            alterar=musica_pesquisa_nota(m, nota_alterar, instrumento);
                        }
                        cont_bem++;
                        break;
                    }

                case 3:
                    fscanf(fpointer, " %d %d %d %d", &bateria_pos, &toca, &pi, &pf);
                    if( bateria_pos<0 || bateria_pos>7 || (toca!=1 && toca!=0) || pi>pf || pi<0 || pf<0 || pf>tamanho || pi>tamanho)
                    {
                        break;
                    }
                    else 
                    {
                        for(i=0;i<pi;i++)
                        {
                        alterar=alterar->proximo; //poe alterar em pi
                        }   

                        while(pi<=pf)
                        {   
                            alterar->bateria[bateria_pos]=toca;
                            alterar=alterar->proximo;
                            pi++; 
                        }
                        cont_bem++;
                        break; 
                    }

                case 4:
                    fscanf(fpointer, " %d %d %d", &duracao_nova, &pi, &pf);
                    if( duracao_nova<1 || duracao_nova>16 || pi>pf || pi<0 || pf<0 || pf>tamanho)
                    {
                        break;
                    } 
                    
                    else
                    {
                        for(i=0;i<pi;i++)
                        {
                            alterar=alterar->proximo; //poe alterar em pi
                        }     
                        
                        while(pi<=pf)
                        {   
                            alterar->duracao=duracao_nova;
                            alterar=alterar->proximo;
                            pi++; 
                        }
                        cont_bem++;
                        break; 
                    }

                default: // se case nao estiver entre 1 a 4
                fgets(absorve, 20, fpointer);
                break;
            }   
        }
        fclose(fpointer);
        return cont_bem;
    }
    fclose(fpointer);
    return -1;
}    

    