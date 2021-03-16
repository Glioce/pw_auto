#include <stdio.h>
#include <string.h>

#define ACTIVADO 1
#define DESACTIVADO 0
#define ON 1
#define OFF 0

#define	PRINTESTADO(x)	printf("\n\rEstado: %d\n\r",x);
#define ESPACIOSTERM	printf("\n\n\r");

int estado = 0;
int abortar = DESACTIVADO;

int dist0,dist1,dist2,dist3,dist4,dist5,distprom = 0;
int parking = DESACTIVADO;
int pwmA,pwmR = OFF;

int main()
{
	printf("Algoritmo AutoAparcamiento \n\r");
	estado = 0;
	while(1)
	{
		if (estado == 0 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto Parado antes de buscar un espacio\n\r");
				printf(" *Auto*=\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Distancia 1 >= 20 y Distancia 2 >=20 \n\r");
				printf("\rDist1 = ");
				scanf("%d",&dist1);
				printf("\rDist2 = ");
				scanf("%d",&dist2);
				
				if (dist2 >= 20 && dist1 >= 20)
				{
					estado = 1;	
				}
			}while(estado == 0 && abortar == DESACTIVADO);
		}
		
		if (estado == 1 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Avanza y busca un espacio\n\r");
				printf("  *Auto*=->\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Distancia 1 >= 90 y Distancia 2 >= 90\n\r");
				printf("Distancia 0 > 10  \n\r");
				printf("\rDist1 = ");
				scanf("%d",&dist1);
				printf("\rDist2 = ");
				scanf("%d",&dist2);
				
				printf("\rDist0 = ");
				scanf("%d",&dist0);
				
				if (dist0 >= 10)
				{
					pwmA = ON;
					printf("Motores Encendidos\r\n");
				}
				else
				{
					pwmA = OFF;
					printf("Motores Apagados\r\n");
				}
				
				if (dist2 >= 90 && dist1 >= 90)
				{
					pwmA = OFF;
					printf("Motores Apagados\r\n");
					estado = 2;	
				}
			}while(estado == 1 && abortar == DESACTIVADO);
		}
		
		if (estado == 2 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto encuentra un espacio\n\r");
				printf("                *Auto*=\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Motores Apagados\r\n");
				printf("Estacionarse??[Y/n]: ");
				scanf("%c",&parking);
				if (parking == 'Y'||parking == 'y')
				{
					parking = ACTIVADO;
					printf("Estacionandose\r\n");
					estado = 3;
				}
			}while(estado == 2 && abortar == DESACTIVADO);
		}

		if (estado == 3 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto Avanza para preparase\n\r");
				printf("               *Auto*=->\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Distancia 1 <= 20 y Distancia 2 <= 20\n\r");
				printf("Distancia 0 > 10  \n\r");
				printf("\rDist1 = ");
				scanf("%d",&dist1);
				printf("\rDist2 = ");
				scanf("%d",&dist2);
				
				printf("\rDist0 = ");
				scanf("%d",&dist0);
				
				if (dist0 >= 10)
				{
					pwmA = ON;
					printf("Motores Encendidos\r\n");
				}
				else
				{
					pwmA = OFF;
					printf("Motores Apagados\r\n");
				}
				
				if (dist2 <= 20 && dist1 <= 20)
				{
					pwmA = OFF;
					printf("Motores Apagados\r\n");
					estado = 4;	
				}
			}while(estado == 3 && abortar == DESACTIVADO);
		}

		if (estado == 4 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto preparado se detiene\n\r");
				printf("                               *Auto*=\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				
				pwmA = OFF;
				printf("Motores Apagados\r\n");
				estado = 5;
			}while(estado == 4 && abortar == DESACTIVADO);
		}
		
		if (estado == 5 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				printf("Auto preparado gira el volante\n\r");
				printf("                              *Auto*/\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				estado = 6;
			}while(estado == 5 && abortar == DESACTIVADO);
		}
		
		if (estado == 6 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				printf("Auto Preparado con voltante girado retrocede\n\r");
				printf("                            <-*Auto*/\n\r");
				printf("=============             =============\n\r");
				printf("=============             =============\n\r");
				printf("Distancia 3 <= 30 y Distancia 2 <= 20\n\r");
				printf("Distancia 3 > 10 Stop!\n\r");
				printf("\rDist3 = ");
				scanf("%d",&dist3);
				printf("\rDist2 = ");
				scanf("%d",&dist2);

				
				if (dist3 <= 10)
				{
					pwmR = ON;
					printf("Motores Reversa Encendidos\r\n");
				}
				else
				{
					pwmR = OFF;
					printf("Motores Reversa Apagados\r\n");
				}
				
				if (dist3 <= 30 && dist2 <= 20)
				{
					pwmR = OFF;
					printf("Motores Reversa Apagados\r\n");
					estado = 7;	
				}
			}while(estado == 6 && abortar == DESACTIVADO);
		}
		
		if (estado == 7 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto se detiene cuando llega a una posicion de reversa deseada\n\r");
				printf("                   to*/\n\r");
				printf("=============   *Au       =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Motores Reversa Apagados\r\n");
				estado = 8;
			}while(estado == 7 && abortar == DESACTIVADO);
		}
		
		if (estado == 8 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto en la posicion de reversa deseada giro contrario del volante\n\r");
				printf("                   to*|\n\r");
				printf("=============   *Au       =============\n\r");
				printf("=============             =============\n\r");
				
				estado = 9;
			}while(estado == 8 && abortar == DESACTIVADO);
		}
		
		if (estado == 9 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto con giro contrario al volante retrocede\n\r");
				printf("                   to*|\n\r");
				printf("============= <-*Au       =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Distancia 3 < 10\n\r");
				printf("\rDist3 = ");
				scanf("%d",&dist3);
				
				if (dist3 >= 10)
				{
					pwmR = ON;
					printf("Motores Reversa Encendidos\r\n");
				}
				else
				{
					pwmR = OFF;
					printf("Motores Reversa Apagados\r\n");
					estado = 10;
				}
			}while(estado == 9 && abortar == DESACTIVADO);
		}
		
		if (estado == 10 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
								
				printf("Auto parado dentro del cajon de estacionamiento\n\r");
				printf("============= *Auto*|     =============\n\r");
				printf("=============             =============\n\r");
				
				pwmR = OFF;
				printf("Motores Reversa Apagados\r\n");
				estado = 11;
			}while(estado == 10 && abortar == DESACTIVADO);
		}
		
		if (estado == 11 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
								
				printf("Auto parado dentro del cajon de estacionamiento, Volante derecho\n\r");
				printf("============= *Auto*=     =============\n\r");
				printf("=============             =============\n\r");
				
				pwmR = OFF;
				printf("Motores Reversa Apagados\r\n");
				printf("Volante derecho\r\n");
				estado = 12;
			}while(estado == 11 && abortar == DESACTIVADO);
		}
		
		if (estado == 12 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto parado dentro del cajon de estacionamiento, mide distancia promedio \n\r");
				printf("============= *Auto*=     =============\n\r");
				printf("=============             =============\n\r");
				
				pwmR = OFF;
				printf("Motores Reversa Apagados\r\n");
				printf("Medir Distancia Promedio de Dist 0 y 3\r\n");
				printf("\rDist0 (Delantera)= ");
				scanf("%d",&dist0);
				printf("\rDist3 (Trasera) = ");
				scanf("%d",&dist3);
				printf("Calcular Distancia promedio\r\n");
				distprom = (dist0+dist3)/2;
				printf("Promedio: %d\r\n",distprom);
				estado = 13;
			}while(estado == 12 && abortar == DESACTIVADO);
		}
		
		if (estado == 13 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto comienza a avanzar a una distancia promedio \n\r");
				printf("============= *Auto*=->   =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Motores Avance Encendidos\r\n");
				pwmA = ON;
				printf("Distancia 3 >= %d o Distancia 0 <= %d\n\r",distprom,distprom);
				printf("\rDist0 (Delantera)= ");
				scanf("%d",&dist0);
				if (dist0 <= distprom||dist3 >= distprom)
				{
					pwmA = ON;
					printf("Motores Avance Apagados\r\n");
					estado = 14;
				}
				else
				{
					pwmA = OFF;
					printf("Motores Avence Encendidos\r\n");
				}
			}while(estado == 13 && abortar == DESACTIVADO);
		}
		
		if (estado == 14 && abortar == DESACTIVADO)
		{
			do
			{
				ESPACIOSTERM;
				PRINTESTADO(estado);
				
				printf("Auto se detiene en el cajon de estacionamiento \n\r");
				printf("=============   *Auto*=   =============\n\r");
				printf("=============             =============\n\r");
				
				printf("Motores Avance Apagados\r\n");
				pwmA = OFF;
				pwmR = OFF;
				printf("AutoAparcamiento Finalizado\r\n");
				estado = 15;
			}while(estado == 14 && abortar == DESACTIVADO);
		}
	}
}
