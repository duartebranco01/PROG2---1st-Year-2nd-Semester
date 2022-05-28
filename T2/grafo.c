/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafo.h"


grafo* grafo_novo()
{
    grafo *g= (grafo*)malloc(sizeof(grafo));
    if(g==NULL) return NULL;

    g->tamanho=0;
    g->nos=NULL;
    
    if(g->tamanho!=0) 
    {
        free(g);
        return NULL;
    }
    return g; 
}

void grafo_apaga(grafo* g)
{
    if(g==NULL) return; 

    int i=0, k=0;
        
    for (i=0;i<g->tamanho;i++)
    {
        for(k=0;k<g->nos[i]->tamanho;k++) 
        {   
            free(g->nos[i]->ligacoes[k]);
        }
        if(g->nos[i]->ligacoes!=NULL) free(g->nos[i]->ligacoes);
        free(g->nos[i]);
    }
    if(g->nos!=NULL) free(g->nos);
    free(g);

}

no_grafo * no_insere(grafo *g, char *user) 
{
    if(g==NULL || user==NULL || strlen(user)<=0 || strlen(user)>TAMANHO_CHAVE) return NULL;
    
    int i=0;

    for(i=0; i<g->tamanho;i++) // ve se repetido
    {
        if(strcmp(g->nos[i]->nome_user, user)==0) return NULL;
    }
    
    if(g->nos==NULL) g->nos=(no_grafo**)malloc((g->tamanho)*sizeof(no_grafo*));                                
    else if(g->nos!=NULL)  g->nos=(no_grafo**)realloc(g->nos, (g->tamanho)*sizeof(no_grafo*));                  

    no_grafo *no_novo=(no_grafo*)malloc(sizeof(no_grafo)); 
    if(no_novo==NULL) return NULL;
    
    no_novo->tamanho=0;
    no_novo->ligacoes=NULL;
    no_novo->nome_user=user;   

    g->tamanho++; 
    g->nos=(no_grafo**)realloc(g->nos, (g->tamanho)*sizeof(no_grafo)); 
    g->nos[g->tamanho-1]=no_novo; 
    return g->nos[g->tamanho-1];    
}

int  cria_ligacao(no_grafo *origem, no_grafo *destino, int peso) 
{
    
    if(origem==NULL || origem->tamanho<0 || destino==NULL || destino->tamanho<0 || peso<=0 || origem==destino) return -1; 
    
    if(origem->ligacoes==NULL || origem->tamanho==0) 
    {
        origem->ligacoes=(ligacao**)malloc(sizeof(ligacao*));
        if(origem->ligacoes==NULL) return -1;                 
    }
    else if(origem->ligacoes!=NULL) origem->ligacoes=(ligacao**)realloc(origem->ligacoes, (origem->tamanho)*sizeof(ligacao*));         
    
    int i=0;
    
    while(i<origem->tamanho)
    {
        if(origem->ligacoes[i]->destino==destino) return -1; // se o destino ja exite return -1
        i++;
    }
    
    origem->tamanho++;
    origem->ligacoes=(ligacao**)realloc(origem->ligacoes, (origem->tamanho)*sizeof(ligacao*)); 
    origem->ligacoes[origem->tamanho-1]=(ligacao*)malloc(sizeof(ligacao));
    
    if(origem->ligacoes[origem->tamanho-1]==NULL) return -1;

    origem->ligacoes[origem->tamanho-1]->peso_ligacao=peso;
    
    origem->ligacoes[origem->tamanho-1]->destino=destino;

    if(origem->ligacoes[origem->tamanho-1]->destino!=NULL) return 0;
    else return -1;
}

no_grafo * encontra_no(grafo *g, char *nomeU) 
{
    if(g==NULL || g->tamanho<=0 || g->nos==NULL || strlen(nomeU)<=0 || strlen(nomeU)>TAMANHO_CHAVE || nomeU==NULL) return NULL;

    int i;

    for(i=0;i<g->tamanho;i++)
    {
        if(strcmp(g->nos[i]->nome_user, nomeU)==0) return g->nos[i]; 
    }

    return NULL;
}

grafo * criaGrafo(tabela_dispersao *td)
{   
    if(td==NULL || td->tamanho<=0 || td->elementos==NULL) return NULL;
    int msg[2], i=0, ligacao; 
    
    grafo* g=grafo_novo();
    if(g==NULL) return NULL;
    
    elemento* elem;
    
    for(i=0;i<td->tamanho;i++)                                                                        
    {                                                                                           
        elem=td->elementos[i]; 
        
        while(elem!=NULL)
        {
            if(strlen(elem->msg->remetente)<=0) return NULL; 
            
            ligacao2(td, elem->msg->remetente, elem->msg->destinatario, msg);
            ligacao=cria_ligacao(no_insere(g, elem->msg->remetente), no_insere(g, elem->msg->destinatario), msg[0]); 
            cria_ligacao(encontra_no(g, elem->msg->destinatario), encontra_no(g, elem->msg->remetente), msg[1]); 
            if(ligacao==-1) //se nós ja estiverem criados, faz ligacao
            {
                cria_ligacao(encontra_no(g, elem->msg->remetente), encontra_no(g, elem->msg->destinatario), msg[0]);
            }
            elem=elem->proximo;
        }  
       
    }

    return g;
}

no_grafo **lista_amigos(grafo *g, char *nomeU, int *n) 
{
    if(g==NULL || g->tamanho<=0 || nomeU==NULL || strlen(nomeU)<=0 || strlen(nomeU)>TAMANHO_CHAVE || n==NULL) return NULL;
    
    int i=0, k=0, p=0, amigos=0; 
    no_grafo* no_nomeU;
    no_grafo* no;
  
    no_nomeU=encontra_no(g, nomeU);
    if(no_nomeU==NULL) return NULL;
    
    no_grafo** vec=(no_grafo**)malloc(sizeof(no_grafo*)); 
    if(vec==NULL) return NULL;
     
    for(i=0;i<g->tamanho;i++) //percorre grafo
    {
        no = g->nos[i];
        for(k=0; k<no->tamanho; k++)
        {
            if(no->ligacoes[k]->peso_ligacao>=4 && strcmp(no->ligacoes[k]->destino->nome_user, no_nomeU->nome_user)==0) // a->b
            {
                for(p=0;p<no_nomeU->tamanho;p++)
                {
                    if(no_nomeU->ligacoes[p]->peso_ligacao>=4 && strcmp(no_nomeU->ligacoes[p]->destino->nome_user, no->nome_user)==0) // b->a
                    {
                        vec=(no_grafo**)realloc(vec, (1+amigos)*sizeof(no_grafo*));
                        vec[amigos]=no;
                        amigos++;   
                    }
                }
            }
        }
    }
    *n = amigos;
    return vec;
}

int identifica(int M, int *n, int tamanho, no_grafo *no_percorre, char *nomeU, no_grafo **vec_percorre, no_grafo *no_nomeU) //da certo com a.out, tem mem leaks, segfault no valgrind? resto nao tem das funcoes nao têm leaks
{   
    int i=0;
    tamanho++;
    *n=tamanho;
    if(tamanho>M) return -1;
    
    if(strcmp(no_percorre->nome_user,nomeU)==0) //encontrou 
    {   
        if(tamanho<2) return -1;
        //e tamanho maior que 2
        vec_percorre=(no_grafo**)realloc(vec_percorre, tamanho*sizeof(no_grafo*));
        if(vec_percorre==NULL)
        {
            free(vec_percorre);
            return -1;
        }
        vec_percorre[0]=no_nomeU; 

        return 0;
    }

    for(i=0;i<no_percorre->tamanho;i++)
    {
        if(no_percorre->ligacoes[i]!=NULL)
        {
            if(identifica(M, n, tamanho, no_percorre->ligacoes[i]->destino, nomeU, vec_percorre, no_nomeU)==0) // repete com o no_percorre=destino
            {
                vec_percorre[tamanho]=no_percorre;
                return 0;
            }
        }
    }
    return -1;
}

no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n) //ate esta funcao nao há memory leaks
{
    if(g==NULL || nomeU==NULL || M<2 || n==NULL) return NULL;
    int i=0, tamanho=0;
    
    no_grafo** vec_percorre=(no_grafo**)malloc(sizeof(no_grafo*));
    
    if(*n!=0) *n=0;

    no_grafo* no_nomeU=encontra_no(g, nomeU);
    
    for(i=0;i<no_nomeU->tamanho;i++) 
    {
        if (no_nomeU->ligacoes[i]!=NULL) //percorre todas as ligacoes
        {
            if(identifica(M, n, tamanho, no_nomeU->ligacoes[i]->destino, nomeU, vec_percorre, no_nomeU)==0) return vec_percorre;
        }    
    }   
    free(vec_percorre);
    free(no_nomeU);
    return NULL;
}