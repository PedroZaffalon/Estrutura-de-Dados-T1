#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "lista.h"
#include "gerarSvg.h"
#include "geo.h"

int main(int argc, char *argv[])
{
    int i = 1;
    char *paramGeo = NULL;
    char *paramQry = NULL;
    char *path = NULL;
    char *outPath = NULL;
    char *geoArq = NULL;
    char *qryArq = NULL;
    char *nomeArq = NULL;
    char *nomeQry = NULL;
    char *saida = NULL;
    char *saidaQry = NULL;
    while(i<argc){
        if (strcmp("-f",argv[i])==0){
            i++;
            if (argv[i] == NULL){
                printf("Erro - Sem parametros em -f");
                exit(1);
            }
            paramGeo = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(paramGeo,argv[i]);
        }
        else if (strcmp("-e",argv[i])==0){
            i++;
            if (argv[i] == NULL){
                printf("Erro - Sem parametros em -e");
                exit(1);
            }
            path = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(path,argv[i]);
        }
        else if (strcmp("-q",argv[i])==0){
            i++;
            if (argv[i] == NULL){
                printf("Erro - Sem parametros em -q");
                exit(1);
            }
            paramQry = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(paramQry,argv[i]);
        }
        else if (strcmp("-o",argv[i])==0){
            i++;
            if (argv[i] == NULL){
                printf("Erro! - Sem parametros em -o");
                exit(1);
            }
            outPath = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(outPath,argv[i]);
        }
        i++;
    }
	if (path != NULL) {
		geoArq = (char *)malloc((strlen(paramGeo)+strlen(path)+2)*sizeof(char));
    	sprintf(geoArq,"%s/%s",path,paramGeo);
        if (paramQry != NULL){
            qryArq = (char *)malloc((strlen(paramQry)+strlen(path)+2)*sizeof(char));
            sprintf(qryArq,"%s/%s",path,paramQry);
        }
	} else {
		geoArq = (char *)malloc((strlen(paramGeo)+1)*sizeof(char));
    	strcpy(geoArq, paramGeo);
        if(paramQry != NULL){
            qryArq = (char *)malloc((strlen(paramQry)+1)*sizeof(char));
            strcpy(qryArq, paramQry);
        }
	}
    no* figuras = geo(geoArq);
    nomeArq = obterNomeArquivo(paramGeo);
    saida = (char*)malloc((strlen(nomeArq) + strlen(outPath) + 6)*sizeof(char));
    sprintf(saida,"%s/%s.svg",outPath,nomeArq);
    gerarSvg(saida,figuras);
    if (paramQry != NULL){
        nomeQry = obterNomeArquivo(paramQry);
        saidaQry = (char*)malloc((strlen(outPath) + strlen(nomeArq) + strlen(nomeQry) + 3)*sizeof(char));
        sprintf(saidaQry,"%s/%s-%s",outPath,nomeArq,nomeQry);
        qry(figuras,qryArq,saidaQry);
        free(saidaQry);
        free(qryArq); 
        free(paramQry);
    }
    free(paramGeo);
    free(path);
	free(outPath);
    free(geoArq);
    free(saida);
    deletarLista(figuras);
    printf("Mémoria desalocada\n");   
    return 0;
}