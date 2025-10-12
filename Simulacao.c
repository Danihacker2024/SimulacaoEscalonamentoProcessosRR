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
	flag recursos;
	initFlag0(&recursos);
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
		enqueue(&*desc, criarProcesso(pid,ppid,uid,uid,CPU_Burst,0,prioridade,0,recursos));
	}
}

void incluirNovoProcesso(Desc *desc){
	flag recursos;
	initFlag0(&recursos);
	int CPU_Burst = (rand() % 30) + 1;
	int prioridade = (rand() % 5) + 1;
	enqueue(&*desc, criarProcesso(rand(),rand(),1000,1000,CPU_Burst,0,prioridade,0,recursos));
}

void ExibirProcesso(Processo proc,int x, int y){
	gotoxy(x,y);
	printf("Pid: %d",proc.pid);
	y++;
	gotoxy(x,y);
	printf("Ppid: %d",proc.ppid);
	y++;
	gotoxy(x,y);
	printf("Prioridade: %d",proc.prioridade);
	y++;
	gotoxy(x,y);
	printf("Gid/Uid: %d",proc.uid);
	y++;
	gotoxy(x,y);
	printf("Tempo: (%d/%d)",proc.tempo_exec,proc.CPU_Burst);
}

void ExibirProcessoSemTempoRecursos(Processo proc,int x, int y){
	gotoxy(x,y);
	printf("Pid: %d",proc.pid);
	y++;
	gotoxy(x,y);
	printf("Ppid: %d",proc.ppid);
	y++;
	gotoxy(x,y);
	printf("Prioridade: %d",proc.prioridade);
}


void Fork(Processo proc, Desc *descritor){
	proc.ppid=proc.pid;
	proc.pid++;
	proc.FlagFork=1;
	enqueue(&*descritor,proc);
}

void Simulacao(){
	flag flag;
	initFlag1(&flag);
	char opcao;
	int ultimoPid;
	int quantum=0;
	char achou;
	char flagExec=1;
	int sorteioRec,sorteioNecRec, sorteioFork,sorteioInclusao;
	Processo HD, Teclado, Mouse;
	TpFilaC *aux;
	TpFilaC *CPU = (TpFilaC*)malloc(sizeof(TpFilaC));
	CPU->prox=NULL;
	clrscr();
	InterfaceMain();
	int tempo=0,y,x;
	Desc descProntos,descHD, descMouse, descTeclado, descWait;
	init(&descProntos);init(&descHD);init(&descMouse);init(&descTeclado);init(&descWait);
	gerarProcessos(&descProntos);
	//Exibir(descritor);
	CPU->PCB = dequeue(&descProntos);
    while(CPU != NULL || !QisEmpty(descProntos.qtde)){
	    if(kbhit()){
	    	opcao = getch();
	    	if(opcao==27){
	    		flagExec=0;
			}else if(opcao==13){
				if(flagExec)
					incluirNovoProcesso(&descProntos);
			}
		}
		else{
			clrscr();
			InterfaceMain();
			gotoxy(130, 49);
			printf("TEMPO TOTAL: %d SEGUNDOS",tempo);
			if(CPU!=NULL && CPU->PCB.tempo_exec<CPU->PCB.CPU_Burst){
				ExibirProcesso(CPU->PCB,190,4);
				if(CPU->PCB.tempo_exec==1){
					sorteioNecRec = rand() % 3;
					if(sorteioNecRec>0)
						sorteioRec=(rand() % 3) + 1;
					else
						sorteioRec=-1;
					//sorteio do fork 
					sorteioFork = rand() % 2;
					if(sorteioFork==1){
						Fork(CPU->PCB, &descProntos);
						enqueue(&descWait, CPU->PCB);
						CPU->PCB=dequeue(&descProntos);
						quantum=0;
					}
				}
				if(sorteioRec==1){
					if(flag.HD){
						CPU->PCB.Recursos.HD=1;
						CPU->PCB.Recursos.mouse=0;
						CPU->PCB.Recursos.teclado=0;
						flag.HD=0;
						HD=CPU->PCB;
					}else if(!flag.HD && !CPU->PCB.Recursos.HD){
						enqueue(&descHD,CPU->PCB);
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}
					}
				}else if(sorteioRec==2){
					if(flag.teclado){
						CPU->PCB.Recursos.teclado=1;
						CPU->PCB.Recursos.HD=0;
						CPU->PCB.Recursos.mouse=0;
						flag.teclado=0;
						Teclado=CPU->PCB;
					}else if(!flag.teclado && !CPU->PCB.Recursos.teclado){
						enqueue(&descTeclado,CPU->PCB);
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}
					}
				}else if(sorteioRec==3){
					if(flag.mouse){
							CPU->PCB.Recursos.mouse=1;
							CPU->PCB.Recursos.HD=0;
							CPU->PCB.Recursos.teclado=0;
							flag.mouse=0;
							Mouse=CPU->PCB;
						}else if(!flag.mouse && !CPU->PCB.Recursos.mouse){
							enqueue(&descMouse,CPU->PCB);
							if(!QisEmpty(descProntos.qtde)){
								CPU->PCB = dequeue(&descProntos);
								quantum=0;
							}
						}
				}
				if(quantum<10)
					quantum++;
				printf("quantum: %d", quantum);
				if(quantum==10 && !QisEmpty(descProntos.qtde)){
					enqueue(&descProntos,CPU->PCB);
					CPU->PCB = dequeue(&descProntos);
					quantum=0;
				}		
			}else{
				gotoxy(190,4);
				printf("FINALIZADO");
				if(CPU->PCB.Recursos.HD){
					CPU->PCB.Recursos.HD=0;
					flag.HD=1;
					while(!QisEmpty(descHD.qtde))
						enqueue(&descProntos,dequeue(&descHD));
				}
				if(CPU->PCB.Recursos.teclado){
					CPU->PCB.Recursos.teclado=0;
					flag.teclado=1;
					while(!QisEmpty(descTeclado.qtde))
						enqueue(&descProntos,dequeue(&descTeclado));
				}
				if(CPU->PCB.Recursos.mouse){
					CPU->PCB.Recursos.mouse=0;
					flag.mouse=1;
					while(!QisEmpty(descMouse.qtde))
						enqueue(&descProntos,dequeue(&descMouse));
				}
				if(CPU->PCB.FlagFork){
					aux=descWait.inicio;
					while(aux!=NULL && CPU->PCB.ppid!=aux->PCB.pid)
						aux=aux->prox;
					if(aux!=NULL)
						enqueue(&descProntos,dequeueProc(&descWait,&aux));
				}
				if(!QisEmpty(descProntos.qtde)){
					CPU->PCB = dequeue(&descProntos);
					quantum=1;
				}else{
					CPU=NULL;
					gotoxy(190,4);
					printf("SEM PROCESSO NA CPU");
				}
			}
			if(!QisEmpty(descProntos.qtde)){
				x=6;
				aux = descProntos.inicio;
				while(aux!=NULL){
					ExibirProcesso(aux->PCB,x,4);
					x+=15;
					aux=aux->prox;
				}
			}
			if (!QisEmpty(descHD.qtde)) {
				x=6;
				aux = descHD.inicio;
				while(aux!=NULL){
					ExibirProcesso(aux->PCB,x,13);
					x+=15;
					aux=aux->prox;
				}
			}
			if (!QisEmpty(descTeclado.qtde)) {
				x=6;
				aux = descTeclado.inicio;
				while(aux!=NULL){
					ExibirProcesso(aux->PCB,x,22);
					x+=15;
					aux=aux->prox;
				}
			}
			if (!QisEmpty(descMouse.qtde)) {
			    x=6;
				aux = descMouse.inicio;
				while(aux!=NULL){
					ExibirProcesso(aux->PCB,x,31);
					x+=15;
					aux=aux->prox;
				}
			}
			if(!QisEmpty(descWait.qtde)){
				x=6;
				aux = descWait.inicio;
				while(aux!=NULL){
					ExibirProcesso(aux->PCB,x,40);
					x+=15;
					aux=aux->prox;
				}
			}
			if(flag.HD){
				gotoxy(190,15);
				printf("DISPONIVEL");
			}else
				ExibirProcessoSemTempoRecursos(HD,190,13);
			if(flag.teclado){
				gotoxy(190,24);
				printf("DISPONIVEL");
			}else
				ExibirProcessoSemTempoRecursos(Teclado,190,22);
			if(flag.mouse){
				gotoxy(190,33);
				printf("DISPONIVEL");
			}else
				ExibirProcessoSemTempoRecursos(Mouse,190,31);
			//sorteio de inclusao de novos processos
			if(flagExec){
				sorteioInclusao=rand() % 3;
				if(sorteioInclusao==1)
					incluirNovoProcesso(&descProntos);
			}
			CPU->PCB.tempo_exec++;
			Sleep(1000);
	    	tempo++;
		}
	}
}




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

