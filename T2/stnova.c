/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"


estrutura* st_nova()
{   
    estrutura* st=(estrutura *)malloc(sizeof(estrutura));
    if(st==NULL) return NULL;

    st->st_tamanho=0;
    st->st_elementos=NULL;
    
    return st;

}

int st_insere(estrutura *st, elemento *elem) // insere e ordena apenas para o dataset pequeno, tem algum erro que faz abort no dataset grande
{   
    /*int i=0, prioridade=0, flag=0, k=0; 
    
    if(st==NULL || elem==NULL || st->st_tamanho<0 || strlen(elem->msg->remetente)<=0 || strlen(elem->msg->remetente)>TAMANHO_CHAVE 
    || strlen(elem->msg->destinatario)<=0 || strlen(elem->msg->destinatario)>TAMANHO_CHAVE) return -1;
    
    if(st->st_elementos==NULL || st->st_tamanho==0) st->st_elementos=(st_elemento**)malloc(sizeof(st_elemento*));

    for(i=0;i<st->st_tamanho;i++) //ver se repetido
    {   
        //printf("----------------------------------prioridade[i=%d]: %d\n", i, st->st_elementos[i]->prioridade);            //da para ver que ordena se tirar de comentario
        
        if(st->st_elementos[i]==NULL) return -1;
        if(st->st_elementos[i]!=NULL && strcmp(st->st_elementos[i]->msg->user, elem->msg->remetente)==0 && strcmp(st->st_elementos[i]->msg->alvo, elem->msg->destinatario)==0) // a->b
        {   
            st_elemento* aux=(st_elemento*)malloc(sizeof(st_elemento));
            aux->msg=(st_mensagem*)malloc(sizeof(st_mensagem));
            aux->proximo=(st_elemento*)malloc(sizeof(st_elemento));    
            aux->msg->texto=malloc(strlen(elem->msg->texto)*sizeof(char));
            strcpy(aux->msg->user, elem->msg->remetente);
            strcpy(aux->msg->alvo, elem->msg->destinatario); 
            strcpy(aux->msg->texto,elem->msg->texto);
            aux->prioridade=st->st_elementos[i]->prioridade+1; 
            aux->proximo=st->st_elementos[i];
            st->st_elementos[i]=aux;
            flag=1;

            k=i;
            st_elemento* aux2=(st_elemento*)malloc(sizeof(st_elemento));
            while(k>0 && (st->st_elementos[k]->prioridade>st->st_elementos[k-1]->prioridade)) // reorderna com prioridade incrementada
            {
		        aux2=st->st_elementos[k-1];
		        st->st_elementos[k-1]=st->st_elementos[k];
		        st->st_elementos[k]=aux2;
		        k--;
            }
        }
        if (st->st_elementos[i]!=NULL && strcmp(st->st_elementos[i]->msg->alvo, elem->msg->remetente)==0 && strcmp(st->st_elementos[i]->msg->user, elem->msg->destinatario)==0)
        {
            st->st_elementos[i]->prioridade=st->st_elementos[i]->prioridade+1; //incrementa prioridade no a se a->b ou b->a
            k=i;
            st_elemento* aux2=(st_elemento*)malloc(sizeof(st_elemento));
            while(k>0 && (st->st_elementos[k]->prioridade>st->st_elementos[k-1]->prioridade)) // reorderna com prioridade incrementada
            {
		        aux2=st->st_elementos[k-1];
		        st->st_elementos[k-1]=st->st_elementos[k];
		        st->st_elementos[k]=aux2;
		        k--;
            }
        }
    }
    
    if(flag==0) // se nao é repetido, cria-se - esta bem
    {
        st->st_tamanho++;
        
        st->st_elementos=(st_elemento**)realloc(st->st_elementos, (st->st_tamanho)*sizeof(st_elemento*));
        st->st_elementos[st->st_tamanho-1]=(st_elemento*)malloc(sizeof(st_elemento));  
        
        st->st_elementos[st->st_tamanho-1]->msg=(st_mensagem*)malloc(sizeof(st_mensagem));
        st->st_elementos[st->st_tamanho-1]->msg->texto=malloc(strlen(elem->msg->texto+1)*sizeof(char));

        strcpy(st->st_elementos[st->st_tamanho-1]->msg->user, elem->msg->remetente);  
        strcpy(st->st_elementos[st->st_tamanho-1]->msg->alvo, elem->msg->destinatario);
        strcpy(st->st_elementos[st->st_tamanho-1]->msg->texto, elem->msg->texto);
        
        st->st_elementos[st->st_tamanho-1]->prioridade=1;
       
    }

    return 0;*/
    return -1;
}


int st_importa_tabela(estrutura *st, tabela_dispersao *td)
{  
   if(st==NULL || td==NULL || td->tamanho<=0 ) return -1;
    elemento* elem=malloc(sizeof(elemento));
    
    int i=0, check=0;
    
    for(i=0;i<td->tamanho;i++)
    {
        elem=td->elementos[i];
        while(elem!=NULL)
        {
            check=st_insere(st, elem);
            if(check==-1) return -1;
            
            elem=elem->proximo;    
        }
    }
    return 0;
}

elemento *st_remove(estrutura *st, char *remetente)
{
    if(st==NULL || st->st_tamanho==0 || strlen(remetente)<=0) return NULL;
    // fizemos uma estrutura má, nao conseguimos reconverter para elemento da tabdispersao
    
    return NULL;
}


int st_apaga(estrutura *st)
{
    /*if(st==NULL || st->st_tamanho==0)
    {   
        free(st->st_elementos);
        free(st);
        return 0;
    }
    
    st_elemento* aux;
    for(int i=0;i<st->st_tamanho;i++)
    {
        while(aux!=NULL)
        {    
            aux=st->st_elementos[i]; 
            st->st_elementos[i]=st->st_elementos[i]->proximo; 
            free(aux->msg->user);
            free(aux->msg->alvo);
            free(aux->msg->texto);
            free(aux->proximo);
            free(aux->msg);
            free(aux);
        }
    }
    free(st->st_elementos);
    free(st);
    return 0;*/
    return -1;
}

