#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>
//#include "Interface.h"
#include "FilaCircularProcessos.h"
#include "tadInterface.h"

void gerarProcessos(Desc *desc){
	int pid;
	int ppid = 1;
	int uid;
	uid = 1000;
	int CPU_Burst;
	int i, prioridade;
	for(i = 0; i<2;i++){
		pid = rand();
		ppid = rand();
		CPU_Burst = (rand() % 30) + 1;
		prioridade = (rand() % 5) + 1;
		enqueue(&*desc, criarProcesso(pid,ppid,uid,uid,CPU_Burst,0,prioridade,0));
	}
}

void incluirNovoProcesso(Desc *desc){
	int CPU_Burst = (rand() % 30) + 1;
	int prioridade = (rand() % 5) + 1;
	enqueue(&*desc, criarProcesso(rand(),rand(),1000,1000,CPU_Burst,0,prioridade,0));
}

void ExibirProcesso(Processo proc,int x, int y){
	gotoxy(x,y);
	printf("Pid: %d\n",proc.pid);
	y++;
	gotoxy(x,y);
	printf("Ppid: %d\n",proc.ppid);
	y++;
	gotoxy(x,y);
	printf("Gid: %d\n",proc.gid);
	y++;
	gotoxy(x,y);
	printf("Uid: %d\n",proc.uid);
	y++;
	gotoxy(x,y);
	printf("Tempo de execucao: (%d/%d)",proc.tempo_exec,proc.CPU_Burst);
}

void Simulacao(){
	char opcao;
	int ultimoPid;
	int quantum=1;
	int sorteioEsp;
	Processo *CPU;
	clrscr();
	InterfaceMain();
	int tempo=0,y;
	Desc descProntos,descHD, descMouse, descTeclado;
	init(&descProntos);init(&descHD);init(&descMouse);init(descTeclado);
	gerarProcessos(&descProntos);
	//Exibir(descritor);
	CPU = dequeue(&descritor);
    while(CPU != NULL || !QisEmpty(descProntos)){
	    if(kbhit())
			incluirNovoProcesso(&descritor,ultimoPid);
		else{
			clrscr();
			InterfaceMain();
			gotoxy(30, 7);
			printf("Tempo: %d segundos",tempo);
			if(CPU.tempo_exec<CPU.CPU_Burst){
				ExibirProcesso(CPU,30,10);
				sorteioEsp=(rand() % 10) + 1;
				if(quantum!=10)
					quantum++;
				if(quantum==10 && !QisEmpty(descProntos.qtde)){
					enqueue(&descritor,CPU);
					CPU = dequeue(&descritor);
					quantum=1;
				}
					
			} else if(!QisEmpty(descritor.qtde)){
				gotoxy(70,9);
				printf("Processo finalizado");
				CPU = dequeue(&descritor);
				quantum=1;
			}
			else{
				CPU.pid=0;
				gotoxy(30,9);
				printf("Nenhum processo na CPU");	
			}
			if(!QisEmpty(descritor.qtde)){
				gotoxy(30,16);
				printf("Primeiro da Fila de Prontos");
				ExibirProcesso(descritor.inicio->Processo,30,17);	
			}else{
				gotoxy(30,16);
				printf("Nenhum processo na Fila de Prontos");
			}
			if(!QisEmpty(descEspera.qtde)){
				gotoxy(30, 23);
				printf("Primeiro da Fila de Espera");
				ExibirProcesso(descEspera.inicio->Processo,30,24);
				sorteioEsp=(rand() % 10) + 1;
				if(sorteioEsp==5){
					enqueue(&descritor,dequeue(&descEspera));
					gotoxy(70, 23);
					printf("Saiu da Espera");
				}
			} else {
				gotoxy(30,23);
				printf("Nenhum processo na Fila de Espera");	
			}
			CPU.tempo_exec++;
			Sleep(1000);
	    	tempo++;
		}
	}
}

*/


int main(void){
	srand(time(NULL));
	InterfaceInit();
	getch();
	Simulacao();
	
	/*
	exibirParticipantes();
	char opcao;
	do{
		Menu1();
		opcao = getch();
		switch(opcao){
			case 13:
				system("cls");
				Simulacao();
				break;
			default:
				gotoxy(10,13);
				printf("Opcao invalida...");
				break;
		}	
	}while(opcao!=27);
	*/
}

