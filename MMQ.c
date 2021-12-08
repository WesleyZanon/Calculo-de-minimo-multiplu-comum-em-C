//wesley davi zanon novaes
//RA: 190545
//Data: 19/05/2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

//declaração das funções do programa
//funcao de alocação dos ponteiros

void aloca(int **p, int tam);
void recebeValores(int *p, int i);
void mostraValores(int *p, int i);
void calculaReta(int *X,int *x0, int *x1, int i);
void calculaParabola(int *X, int *x0, int *x1, int *x2,int i);
int calculaEscalar(int *y, int *x, int i);
void calculaMMC(int v1,int v2,int *resp);
float calculaPontos(float p1, float p2, float pv1, float pv2);


main()
{	    
	
	printf("---------- Metodos Numericos Computacionais - Minimos Quadrados ----------\n\n\n\n");
	
	//declaração de variaveis da funcao int
	int *x = NULL,*y = NULL,i,op;
	//op -> variavel de opcao
	
	//ponteiro para a matriz e pivo de gauss
	float *m, pivo1, pivo2;
	
	//ponteiros para calcular a potencia 
	int *u0 = NULL, *u1 = NULL, *u2 = NULL;
	
	//variavel de auxilio nos testes
	int aux,r;
	
	//Os pontos de aX^2+aX+b
	float a0,a1,a2;
	
	char pp;
	
	//variavel resposavel por realocar os espaços do ponteiro.
	printf("Digite o numero de pontos da tabela de x e f(x) x e F(X): ");
	scanf("%i", &i);
	
	//funcao para alocar os espaços dentro de x, y, U0, U1 2 U2
	aloca(&x,i);    
	aloca(&y,i);
	aloca(&u0,i);
	aloca(&u1,i);
	aloca(&u2,i);
	
	//x e F(x) vao ser alimentados pelos valores
	printf("\n\n\nDigite o valor para cada ponto de x:\n");
	recebeValores(x,i);
	printf("\n\n\n\nDigite o valor para cada ponto de y:\n");
	recebeValores(y,i);
	
	//funcao para mostrar os valores dentro do ponteiro
	mostraValores(x,i);
	mostraValores(y,i);
	
	

	
	
	
	//condições para as opcoes reta e parabola
	//sistema de repeticao para continuar calculando reta ou parabola
	do
	{
		//op vai ser usada nessas opcao	
		printf("\n\n\nDigite uma opção (1) reta (2) parabola: ");
		scanf("%i", &op);
		
	    printf("\n\n----------- Construindo P -----------\n\n\n");
	    
		if(op==1)
		{
			calculaReta(x,u0,u1,i);
			printf("Vetores:\n");
			printf("Y\tU0\tU1\n");
			
		//mostrar os novos valores de U0 e U1
		 for(aux=0;aux<i;aux++)
	{
		printf("%i\t%i\t%i\n",*(y+aux),*(u0+aux),*(u1+aux));
		}	
		
		printf("\n\n----------- Sistema Escalar -----------\n\n\n");
		
		//alocar 6 espaços para a matrix 3x2
		aloca(&m,6);
		
		//calcular os pontos da matriz
		*(m+(0*3+0))= calculaEscalar(u0,u0,i);
		//printf("\n*(m+(0*3+0)) = %.2f\n",*(m+(0*3+0)));
		*(m+(0*3+1))= calculaEscalar(u0,u1,i);
		//printf("\n*(m+(0*3+1)) = %.2f\n",*(m+(0*3+1)));		
		*(m+(0*3+2))= calculaEscalar(u0,y,i);
		//printf("\n*(m+(0*3+2)) = %.2f\n",*(m+(0*3+2)));
		
		*(m+(1*3+0)) = calculaEscalar(u0,u1,i);
		//printf("\n*(m+(1*3+0)) = %.2f\n",*(m+(1*3+0)));
		*(m+(1*3+1)) = calculaEscalar(u1,u1,i);
		//printf("\n*(m+(1*3+1)) = %.2f\n",*(m+(1*3+1)));
		*(m+(1*3+2))= calculaEscalar(u1,y,i);
		//printf("\n*(m+(1*3+2)) = %.2f\n",*(m+(1*3+2)));
		
		//exibir a matriz
		mostraMatriz6(m);
		
		//Resolver por Gauss
		//primeiro encontrar o mmc da l1 e l2
		//segundo encontrar o pivos da l1 e l2
		
		//calcular mmc do primeiro numero da linha 0 e 1 para determinar o pivo
		calculaMMC(*(m+(0*3+0)),*(m+(1*3+0)),&r);
		
		pivo1 = r/(*(m+(0*3+0)));
		//printf("\nTeste pivo1: %.2f", pivo1);
		pivo2 = r/(*(m+(1*3+0)));
		//printf("\nTeste pivo2: %.2f", pivo2);
		
		//printf("\nteste l1c0: %.2f\n", *(m+(1*3+0)));
		*(m+(1*3+0)) = calculaPontos(*(m+(0*3+0)), *(m+(1*3+0)), pivo1, pivo2);
		
		//printf("\n2 - teste l1c0: %.2f\n", *(m+(1*3+0)));
		//printf("\nteste l1c0: %.2f\n", *(m+(1*3+0)));
		
		*(m+(1*3+1)) = calculaPontos(*(m+(0*3+1)), *(m+(1*3+1)), pivo1, pivo2);
		*(m+(1*3+2)) = calculaPontos(*(m+(0*3+2)), *(m+(1*3+2)), pivo1, pivo2);
		
        printf("\n\n\n------- Eliminação de Gauss -------\n\n\n");
        mostraMatriz6(m);
        
        a0 = (*(m+(1*3+2)))/(*(m+(1*3+1)));
        //printf("teste a0: %.3f",a0);
        a1 = (((*(m+(0*3+2)))-(((*(m+(0*3+1)))*a0)))/(*(m+(0*3+0))));
        //printf("teste a1: %.3f",a1);
        
        printf("\n\nP(X) = (%.3f)x+(%.3f)",a0,a1);
				
		}
		//para parabola nao teve muitos comentarios, pois e o mesmo metodo da reta
		else if(op==2)
		{   
		    //calcular os u0, u1, u2 para a matriz final
			calculaParabola(x,u0,u1,u2,i);
			
			printf("Vetores:\n");
			printf("Y\tU0\tU1\tU2\n");
			//mostrar os novos valores de U0 e U1 e U2
			for(aux=0;aux<i;aux++)
			{
				printf("%i\t%i\t%i\t%i\n",*(y+aux),*(u0+aux),*(u1+aux),*(u2+aux));
			}
			
			printf("\n\n----------- Sistema Escalar -----------\n\n\n");
		
			//alocar 12 espaços para a matrix 4x3
			aloca(&m,12);
			
			*(m+(0*4+0))= calculaEscalar(u0,u0,i);
			*(m+(0*4+1))= calculaEscalar(u0,u1,i);
			*(m+(0*4+2))= calculaEscalar(u0,u2,i);
			*(m+(0*4+3))= calculaEscalar(u0,y,i);
			
			*(m+(1*4+0))= calculaEscalar(u1,u0,i);
			*(m+(1*4+1))= calculaEscalar(u1,u1,i);
			*(m+(1*4+2))= calculaEscalar(u1,u2,i);
			*(m+(1*4+3))= calculaEscalar(u1,y,i);
			
			*(m+(2*4+0))= calculaEscalar(u2,u0,i);
			*(m+(2*4+1))= calculaEscalar(u2,u1,i);
			*(m+(2*4+2))= calculaEscalar(u2,u2,i);
			*(m+(2*4+3))= calculaEscalar(u2,y,i);
			
			//exibir a matriz
			mostraMatriz12(m);
			
			//aplicar o mmc para a linha0 e linha1
			calculaMMC(*(m+(0*4+0)),*(m+(1*4+0)),&r);
			
			pivo1 = r/(*(m+(0*4+0)));
			pivo2 = r/(*(m+(1*4+0)));
			
            printf("\n\n\n------- Eliminação de Gauss -------\n\n\n");
            *(m+(1*4+0)) = calculaPontos(*(m+(0*4+0)), *(m+(1*4+0)), pivo1, pivo2);
            *(m+(1*4+1)) = calculaPontos(*(m+(0*4+1)), *(m+(1*4+1)), pivo1, pivo2);
            *(m+(1*4+2)) = calculaPontos(*(m+(0*4+2)), *(m+(1*4+2)), pivo1, pivo2);
            *(m+(1*4+3)) = calculaPontos(*(m+(0*4+3)), *(m+(1*4+3)), pivo1, pivo2);
            mostraMatriz12(m);
            
            //aplicar o mmc para a linha0 e linha2
            calculaMMC(*(m+(0*4+0)),*(m+(2*4+0)),&r);
            
			pivo1 = r/(*(m+(0*4+0)));
			pivo2 = r/(*(m+(2*4+0)));
			
			printf("\n\n\n------- Eliminação de Gauss -------\n\n\n");
			*(m+(2*4+0)) = calculaPontos(*(m+(0*4+0)), *(m+(2*4+0)), pivo1, pivo2);
            *(m+(2*4+1)) = calculaPontos(*(m+(0*4+1)), *(m+(2*4+1)), pivo1, pivo2);
            *(m+(2*4+2)) = calculaPontos(*(m+(0*4+2)), *(m+(2*4+2)), pivo1, pivo2);
            *(m+(2*4+3)) = calculaPontos(*(m+(0*4+3)), *(m+(2*4+3)), pivo1, pivo2);
			mostraMatriz12(m);
			
			//aplicar o mmc para a linha0 e linha1
			calculaMMC(*(m+(1*4+1)),*(m+(2*4+1)),&r);
			
			pivo1 = r/(*(m+(1*4+1)));
			pivo2 = r/(*(m+(2*4+1)));
			
            printf("\n\n\n------- Eliminação de Gauss -------\n\n\n");
            //Esse ponto ja esta zerado
            *(m+(2*4+0)) = calculaPontos(*(m+(1*4+0)), *(m+(2*4+0)), pivo1, pivo2);
            *(m+(2*4+1)) = calculaPontos(*(m+(1*4+1)), *(m+(2*4+1)), pivo1, pivo2);
            *(m+(2*4+2)) = calculaPontos(*(m+(1*4+2)), *(m+(2*4+2)), pivo1, pivo2);
            *(m+(2*4+3)) = calculaPontos(*(m+(1*4+3)), *(m+(2*4+3)), pivo1, pivo2);
            mostraMatriz12(m);
            
            //calcular o p(x) de a0, a1 e a2 = P(X) = a2X^2+a1X+a0
            
            a2 = (*(m+(2*4+3)))/(*(m+(2*4+2)));
            a1 = ((*(m+(1*4+3)))-((*(m+(1*4+2)))*a1))/(*(m+(1*4+1)));
            a0 = ((*(m+(0*4+3)))-((*(m+(0*4+2)))*a2)-((*(m+(0*4+1)))*a1))/(*(m+(0*4+0)));
            
            printf("\n\nP(x) = (%.3f)x^2+(%.3f)X+(%.3f)",a0,a1,a2);
		}
		printf("\n\nDigija fazer o mesmo calculo? s/n: ");
		scanf("%s",&pp);
		printf("\n");
		
		
	}while(pp=='s');
	
	getch();
	return 0;
}

void aloca(int **p, int tam)
{
	if((*p=(int*)calloc(tam,sizeof(int)))==NULL)
	{
		printf("Erro na alocao!");
		exit(1);
	
	}
	
}
void recebeValores(int *p, int i)
{
	int aux;
	for(aux=0;aux<i;aux++)
	{
		printf("Digite o valor de %i: ",aux);
		scanf("%i",p+aux);
		}
		}
void mostraValores(int *p, int i)
{
	int aux;
	
	for(aux=0;aux<i;aux++)
	{
		printf("%i\t",*(p+aux));
	}
	printf("\n");
}
//mostrar a matriz de reta
void mostraMatriz6(float *p)
{	
	int c,l;
	
	for(l=0;l<2;l++)
	{
		for(c=0;c<3;c++)
		{
			printf("%.2f\t",*(p+(l*3+c)));
				}		
				printf("\n");
	}
}

//mostrar a matriz de parabola
void mostraMatriz12(float *p)
{	
	int c,l;
	
	for(l=0;l<3;l++)
	{
		for(c=0;c<4;c++)
		{
			printf("%.2f\t",*(p+(l*4+c)));
				}		
				printf("\n");
	}
}

void calculaReta(int *X,int *x0, int *x1, int i)
{	
	//variavel de auxilio para acessar os ponteirs
	int aux;
	
	//acessar todos os valores da variavel para calcular
	for(aux=0;aux<i;aux++)
	{		
			//calcular os valores de u0 e u1 elevando-os a ^0 e ^1
			*(x0+aux) = pow(*(X+aux),0);
			*(x1+aux) = pow(*(X+aux),1);
	}

}

void calculaParabola(int *X, int *x0, int *x1, int *x2,int i)
{	
	//variavel de auxilio para acessar os ponteirs
	int aux;
	
	//acessar todos os valores da variavel para calcular
	for(aux=0;aux<i;aux++)
	{		
			//calcular os valores de u0 e u1 elevando-os a ^0 e ^1 e ^2
			*(x0+aux) = pow(*(X+aux),0);
			*(x1+aux) = pow(*(X+aux),1);
			*(x2+aux) = pow(*(X+aux),2);
	}
}

// entrando os valores que irao ser multiplicados
//ja que todos os valores passaram por potrncia entao ele sao inteiros
int calculaEscalar(int *y, int *x, int i)
{
	int aux,soma, total = 0;
	
	for(aux=0;aux<i;aux++)
	{
		soma = (*(y+aux))*(*(x+aux));
		total = total+soma;
	}
	//printf("\n<total> %i\n",total);
	return total;
}

//calcula o mmc para encontrar os pivos
void calculaMMC(int v1,int v2,int *resp)
{
   int cont=2,dividiu,resposta=1;
   while (v1!=1 || v2!=1){
         dividiu=0;
         if (v1%cont==0){
            dividiu=1;
            v1=v1/cont;
         }
         if (v2%cont==0){
            dividiu=1;
            v2=v2/cont;
         }
         if (dividiu==0){
           cont++;
         }else{
           resposta=resposta*cont;
         }
   } 
   *resp=resposta; 
}

//calcular os pontos da matriz para retornar um novo valor
float calculaPontos(float p1, float p2, float pv1, float pv2)
{
    float resultado;
    //printf("\nteste p1: %.2f", p1);
    //printf("\nteste p2: %.2f", p2);
    //printf("\nteste pv1: %.2f", pv1);
    //printf("\nteste pv2: %.2f", pv2);
    
    
    resultado = (p2*pv2)-(p1*pv1);
    //printf("\nteste resultado: %.2f\n",resultado);
    return resultado;
}
