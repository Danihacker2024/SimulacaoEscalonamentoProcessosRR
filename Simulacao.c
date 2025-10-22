#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>
//#include "Interface.h"
#include "FilaCircularProcessos.h"
#include "tadInterface.h"

void InsereTabelaEX(TabelaP_EX **ptr, Processo proc, int tempo);

void gerarProcessos(Desc *desc, TabelaP_EX **ptr, int tempo){
	flag recursos;
	initFlag0(&recursos);
	int pid;
	int ppid = 1;
	int uid;
	uid = 1000;
	int CPU_Burst;
	int i, prioridade;
	Processo proc;
	for(i = 0; i<2;i++){
		pid = (rand() % 999)+1;
		ppid = rand() % pid;
		CPU_Burst = (rand() % 30) + 1;
		prioridade = (rand() % 5) + 1;
		if(CPU_Burst<=30){
			proc = criarProcesso(pid,ppid,uid,uid,CPU_Burst,0,prioridade,0, 0,recursos, 0, 0);
			enqueue(&*desc, proc);
			InsereTabelaEX(&*ptr, proc, tempo);
		}	
	}
}

void incluirNovoProcesso(Desc *desc, TabelaP_EX **ptr, int tempo){
	int pid = (rand() % 99)+1;
	int	ppid = rand() % pid;
	flag recursos;
	initFlag0(&recursos);
	int CPU_Burst = (rand() % 30) + 1;
	int prioridade = (rand() % 5) + 1;
	Processo proc = criarProcesso(pid,ppid,1000,1000,CPU_Burst,0,prioridade,0,0,recursos, 0, 0);
	if(CPU_Burst<=30){
		enqueue(&*desc, proc);
		InsereTabelaEX(&*ptr, proc, tempo);
	}	
}

void ExibirProcesso(Processo proc,int x, int y){
	gotoxy(x,y);
	textcolor(15);
	printf("Pid: %d",proc.pid);
	y++;
	gotoxy(x,y);
	printf("Ppid: %d",proc.ppid);
	y++;
	gotoxy(x,y);
	printf("Prioridade: %d",proc.prioridade);
	y++;
	gotoxy(x,y);
	printf("Filhos: %d",proc.filhos);
	y++;
	gotoxy(x,y);
	printf("Tempo: (%d/%d)",proc.tempo_exec,proc.CPU_Burst);
}

void ExibirProcessoBloqueado(Processo proc,int x, int y){
	gotoxy(x,y);
	textcolor(15);
	printf("Pid: %d",proc.pid);
	y++;
	gotoxy(x,y);
	printf("Ppid: %d",proc.ppid);
	y++;
	gotoxy(x,y);
	printf("Prioridade: %d",proc.prioridade);
	y++;
	gotoxy(x,y);
	printf("Filhos: %d",proc.filhos);
	if(proc.total>0){	
		y++;
		gotoxy(x,y);
		printf("Tempo: (%d/%d)",proc.timeblock,proc.total);
	}
	
}


void Fork(Processo proc, Desc *descritor, int filhos, TabelaP_EX *ptr, int tempo){
	proc.ppid=proc.pid;
	proc.pid+=filhos;
	proc.filhos=0;
	proc.FlagFork=1;
	enqueue(&*descritor,proc);
	InsereTabelaEX(&ptr, proc, tempo);
}

TabelaP *InserePCB(Processo processo){
	TabelaP *ptr;
	ptr = (TabelaP*)malloc(sizeof(TabelaP));
	ptr -> processo = processo;
	ptr -> prox = NULL;
	return ptr;
}

void InsereTabelaEX(TabelaP_EX **ptr, Processo processo, int tempo){
	TabelaP_EX *aux, *novo;
	novo = (TabelaP_EX*)malloc(sizeof(TabelaP_EX));
	novo -> processo = processo;
	novo -> tempoEX[0] = tempo;
	novo -> tempoEX[1] = 0;
	novo -> prox = NULL;
	if(*ptr == NULL){
		*ptr = novo;
	}
	else{
		aux = *ptr;
		while(aux->prox != NULL){
			aux = aux -> prox;
		}
		aux->prox = novo;
	}
}

void CriarProcesso(Desc *desc, TabelaP_EX **ptr, int tempo){
	int ppid;
	flag recursos;
	initFlag0(&recursos);
	int CPU_Burst, prioridade, pid, f = 1;
	clrscr();
	InterfaceInclude();
	gotoxy(43, 12);
	textcolor(9);
	printf("DIGITE O PID DO PROCESSO:");
	gotoxy(43, 13);
	textcolor(15);
	scanf("%d", &pid);
	if(pid <= 0)
		f = 0;
	gotoxy(43, 16);
	textcolor(9);
	printf("DIGITE A PRIORIDADE DO PROCESSO (ate 5):");
	gotoxy(43, 17);
	textcolor(15);
	scanf("%d", &prioridade);
	if(prioridade < 1 || prioridade > 5){
		f = 0;
	}
	gotoxy(43, 20);
	textcolor(9);
	printf("DIGITE O TEMPO DE EXECUCAO DO PROCESSO (ate 30):");
	gotoxy(43, 21);
	textcolor(15);
	scanf("%d", &CPU_Burst);
	if(CPU_Burst < 1 || CPU_Burst > 30){
		f = 0;
	}
	if(f == 1){
		ppid=rand();
		while(ppid>pid)
			ppid=rand();
		Processo proc = criarProcesso(pid, ppid,1000,1000,CPU_Burst,0,prioridade,0,0,recursos, 0, 0);
		enqueue(&*desc, proc);
		InsereTabelaEX(&*ptr, proc, tempo);
	}
}

void initRelatorio(Relatorio *relatorio){
	relatorio -> qtdeTerminated = 0; 
	relatorio -> tempoEspera[0] = 0;
	relatorio -> tempoEspera[1] = 0;
	relatorio -> tempoEspera[2] = 0;
	relatorio -> block = NULL;
	relatorio -> contexto = NULL;
	relatorio -> tabelaEX = NULL;
	relatorio -> tabelaPai = NULL;
}


char BuscaProcesso(TabelaP *ptr, int id){
	while(ptr != NULL && ptr -> processo.pid != id){
		ptr = ptr -> prox;
	}
	return ptr == NULL;
}

void InsereTabela(TabelaP **ptr, Processo processo){
	TabelaP *aux, *nova;
	nova = (TabelaP*)malloc(sizeof(TabelaP));
	nova -> processo = processo;
	nova -> prox = NULL;
	if(*ptr == NULL){
		*ptr = nova;
	} 
	else{
		aux = *ptr;
		while(aux->prox != NULL){
			aux = aux -> prox;
		}
		aux->prox = nova;
	}
}

void AlteraTabelaEX(TabelaP_EX *ptr, int id, int tempo){
	while(ptr != NULL && ptr -> processo.pid != id){
		ptr = ptr -> prox;
	}
	if(ptr!=NULL)
		ptr -> tempoEX[1] = tempo;
}

char BuscaTabelaPai(TabelaP_Pai *ptr, int id){
	while(ptr != NULL && ptr -> processo.pid != id){
		ptr = ptr -> prox;
	}
	return ptr == NULL;
}

void InsereTabelaPai(TabelaP_Pai **ptr, Processo processo){
	TabelaP_Pai *aux, *novo;
	novo = (TabelaP_Pai*)malloc(sizeof(TabelaP_Pai));
	novo -> processo = processo;
	novo -> contChildren = 1;
	novo -> tempoWait[0] = 0;
	novo -> tempoWait[1] = 0;
	novo -> prox = NULL;
	if(*ptr == NULL){
		*ptr = novo;
	}
	else{
		aux = *ptr;
		while(aux->prox != NULL){
			aux = aux -> prox;
		}
		aux->prox = novo;
	}
}

void AlterarTabelaPai(TabelaP_Pai *ptr, int id, char op, int tempo){
	while(ptr != NULL && ptr -> processo.pid != id){
		ptr = ptr -> prox;
	}
	if(ptr != NULL){
		if(op == 'F'){
		ptr -> contChildren++;
		}
		else{
			if(op == 'E'){
				ptr -> tempoWait[0] = tempo;
			}
			else{
				if(op == 'S'){
					ptr -> tempoWait[1] = tempo;
				}
			}
		}
	}
	
}

void ExibirRelatorio(Relatorio relatorio){
	clrscr();
	InterfaceRelatorio();
	textcolor(15);
	gotoxy(43, 9);
	printf("Qtde de Processo Finalizados: %d", relatorio.qtdeTerminated);
	getch();
}

void Simulacao(){
	flag flag;
	initFlag1(&flag);
	int i;
	char opcao;
	int ultimoPid;
	int quantum=0;
	char achou;
	char flagExec=1;
	int sorteioRec,sorteioNecRec, sorteioFork,sorteioInclusao;
	Processo HD, Teclado, Mouse;
	TpFilaC *aux;
	TpFilaC *CPU = (TpFilaC*)malloc(sizeof(TpFilaC));
	Relatorio relatorio;
	CPU->prox=NULL;
	clrscr();
	InterfaceMain();
	int tempo=0,y,x;
	Desc descProntos,descHD, descMouse, descTeclado, descWait;
	init(&descProntos);init(&descHD);init(&descMouse);init(&descTeclado);init(&descWait);
	initRelatorio(&relatorio);
	gerarProcessos(&descProntos, &relatorio.tabelaEX, tempo);
	//Exibir(descritor);
	CPU->PCB = dequeue(&descProntos);
    while((CPU != NULL) || !QisEmpty(descProntos.qtde) || !flag.HD || !flag.mouse || !flag.teclado){
	    if(kbhit()){
	    	opcao = getch();
	    	if(opcao==27){
	    		flagExec=0;
			}else if(opcao==13){
				if(flagExec)
					CriarProcesso(&descProntos, &relatorio.tabelaEX, tempo);
			}
		}
		else{
			clrscr();
			InterfaceMain();
			if(flagExec == 0){
				gotoxy(6, 49);
				textcolor(0);
				printf("ESC - INTERROMPER A CRIACAO DE NOVOS PROCESSOS");
				gotoxy(73, 49);
				textcolor(0);
				printf("ENTER - CRIAR UM NOVO PROCESSO");
				gotoxy(130, 49);
				textcolor(6);
				printf("TEMPO TOTAL: %d SEGUNDOS",tempo);
			}
			gotoxy(130, 49);
			printf("TEMPO TOTAL: %d SEGUNDOS",tempo);
			textcolor(15);
			if(CPU!=NULL && CPU->PCB.tempo_exec<CPU->PCB.CPU_Burst){
				ExibirProcesso(CPU->PCB,190,4);
				sorteioNecRec = rand() % 10;
				if(sorteioNecRec==1)
					sorteioRec=(rand() % 3) + 1;
				else
					sorteioRec=-1;
				
				if(sorteioRec==1){
					relatorio.tempoEspera[0] += tempo;
					if(BuscaProcesso(relatorio.block, CPU -> PCB.pid)){
						relatorio.tempoEspera[2]++;
						InsereTabela(&relatorio.block, CPU -> PCB);
					}
					if(flag.HD){
						HD=CPU->PCB;
						HD.Recursos.HD=1;
						HD.Recursos.mouse=0;
						HD.Recursos.teclado=0;
						flag.HD=0;
						HD.timeblock=0;
						HD.total = (rand()%30) + 1;
						while(HD.total<=0 && HD.total>30)
							HD.total = (rand()%30) + 1;
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						} else{
							CPU=NULL;
						}
					}else if(!flag.HD && !CPU->PCB.Recursos.HD){
						enqueue(&descHD,CPU->PCB);
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}else{
							CPU=NULL;
							gotoxy(190,4);
							printf("SEM PROCESSO NA CPU");
						}
						
					}
					
				}else if(sorteioRec==2){
					relatorio.tempoEspera[0] += tempo;
					if(BuscaProcesso(relatorio.block, CPU -> PCB.pid)){
						relatorio.tempoEspera[2]++;
						InsereTabela(&relatorio.block, CPU -> PCB);
					}
					if(flag.teclado){
						Teclado=CPU->PCB;
						Teclado.Recursos.mouse=1;
						Teclado.Recursos.HD=0;
						Teclado.Recursos.teclado=0;
						flag.teclado=0;
						Teclado.timeblock=0;
						Teclado.total = (rand()%30) + 1;
						while(Teclado.total<=0 && Teclado.total>30)
							Teclado.total = (rand()%30) + 1;
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}else{
							CPU=NULL;
							gotoxy(190,4);
							printf("SEM PROCESSO NA CPU");
						}
					}else if(!flag.teclado && !CPU->PCB.Recursos.teclado){
						enqueue(&descTeclado,CPU->PCB);
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}else{
							CPU=NULL;
							gotoxy(190,4);
							printf("SEM PROCESSO NA CPU");
						}
					}
					
				}else if(sorteioRec==3){
					relatorio.tempoEspera[0] += tempo;
					if(BuscaProcesso(relatorio.block, CPU->PCB.pid)){
						relatorio.tempoEspera[2]++;
						InsereTabela(&relatorio.block, CPU->PCB);
					}
					if(flag.mouse){
						Mouse=CPU->PCB;
						Mouse.Recursos.mouse=1;
						Mouse.Recursos.HD=0;
						Mouse.Recursos.teclado=0;
						Mouse.timeblock=0;
						flag.mouse=0;
						Mouse.total = (rand()%30) + 1;
						while(Mouse.total<=0 && Mouse.total>30)
							Mouse.total = (rand()%30) + 1;
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
							}else{
							CPU=NULL;
							gotoxy(190,4);
							printf("SEM PROCESSO NA CPU");
						}
					}else if(!flag.mouse && !CPU->PCB.Recursos.mouse){
						enqueue(&descMouse,CPU->PCB);
						if(!QisEmpty(descProntos.qtde)){
							CPU->PCB = dequeue(&descProntos);
							quantum=0;
						}else{
							CPU=NULL;
							gotoxy(190,4);
							printf("SEM PROCESSO NA CPU");
						}
					}	
				}
				if(flagExec){
					sorteioFork = rand() % 10;
					if(sorteioFork==1){
						if(BuscaTabelaPai(relatorio.tabelaPai, CPU -> PCB.pid)){
							InsereTabelaPai(&relatorio.tabelaPai, CPU -> PCB);
						}
						else{
							AlterarTabelaPai(relatorio.tabelaPai, CPU -> PCB.pid, 'F', tempo);
						}
						CPU->PCB.filhos++;
						Fork(CPU->PCB, &descProntos, CPU->PCB.filhos, relatorio.tabelaEX, tempo);
						quantum=0;
					}
				}
				
				if(quantum<10)
					quantum++;
				//printf("quantum: %d", quantum);
				if(quantum==10 && !QisEmpty(descProntos.qtde)){
					if(BuscaProcesso(relatorio.contexto, CPU -> PCB.pid)){
						InsereTabela(&relatorio.contexto, CPU -> PCB);
					}
					enqueue(&descProntos,CPU->PCB);
					CPU->PCB = dequeue(&descProntos);
					quantum=0;
				}		
			}else{
				gotoxy(190,4);
				printf("FINALIZADO");
				if(CPU!=NULL){
					relatorio.qtdeTerminated++;
					AlteraTabelaEX(relatorio.tabelaEX, CPU -> PCB.pid, tempo);
					if(CPU->PCB.filhos>0){
						AlterarTabelaPai(relatorio.tabelaPai, CPU -> PCB.pid, 'E', tempo);
						enqueue(&descWait, CPU->PCB);
					}
					if(CPU->PCB.FlagFork){
						aux=descWait.inicio;
						while(aux!=NULL && CPU->PCB.ppid!=aux->PCB.pid)
							aux=aux->prox;
						if(aux!=NULL){
							if(aux->PCB.filhos>0)
								aux->PCB.filhos--;
							if(aux->PCB.filhos==0){
								AlterarTabelaPai(relatorio.tabelaPai, aux -> PCB.pid, 'S', tempo);
								dequeueProc(&descWait,&aux);
							}
						} else{
							aux=descProntos.inicio;
							while(aux!=NULL && CPU->PCB.ppid!=aux->PCB.pid)
								aux=aux->prox;
							if(aux!=NULL)
								aux->PCB.filhos--;
						}
					}
				}
				if(!QisEmpty(descProntos.qtde)){
					if (CPU == NULL)
						CPU = (TpFilaC*)malloc(sizeof(TpFilaC));
					CPU->PCB = dequeue(&descProntos);
					quantum=1;
				}else{
					CPU=NULL;
					gotoxy(190,4);
					printf("SEM PROCESSO NA CPU");
				}
			}
			if(!QisEmpty(descProntos.qtde)){
				i=0;
				x=6;
				aux = descProntos.inicio;
				while(aux!=NULL && i<12){
					ExibirProcesso(aux->PCB,x,4);
					x+=15;
					aux=aux->prox;
					i++;
				}
			}
			if (!QisEmpty(descHD.qtde)) {
				x=6;
				aux = descHD.inicio;
				while(aux!=NULL){
					ExibirProcessoBloqueado(aux->PCB,x,13);
					x+=15;
					aux=aux->prox;
				}
			}
			if (!QisEmpty(descTeclado.qtde)) {
				x=6;
				aux = descTeclado.inicio;
				while(aux!=NULL){
					ExibirProcessoBloqueado(aux->PCB,x,22);
					x+=15;
					aux=aux->prox;
				}
			}
			if (!QisEmpty(descMouse.qtde)) {
			    x=6;
				aux = descMouse.inicio;
				while(aux!=NULL){
					ExibirProcessoBloqueado(aux->PCB,x,31);
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
			}else{
				HD.timeblock++;
				ExibirProcessoBloqueado(HD,190,13);
				if(HD.timeblock>=HD.total){
					relatorio.tempoEspera[1] += tempo;
					enqueue(&descProntos,HD);
					if(!QisEmpty(descHD.qtde))
						HD = dequeue(&descHD);
					else
						flag.HD=1;
				}
			}
			if(flag.teclado){
				gotoxy(190,24);
				printf("DISPONIVEL");
			}else{
				Teclado.timeblock++;
				ExibirProcessoBloqueado(Teclado,190,22);
				if(Teclado.timeblock>=Teclado.total){
					relatorio.tempoEspera[1] += tempo;
					enqueue(&descProntos,Teclado);
					if(!QisEmpty(descTeclado.qtde))
						Teclado = dequeue(&descTeclado);
					else
						flag.teclado=1;
				}
			}
			if(flag.mouse){
				gotoxy(190,33);
				printf("DISPONIVEL");
			}else{
				Mouse.timeblock++;
				ExibirProcessoBloqueado(Mouse,190,31);
				if(Mouse.timeblock>=Mouse.total){
					relatorio.tempoEspera[1] += tempo;
					enqueue(&descProntos,Mouse);
					if(!QisEmpty(descMouse.qtde))
						Mouse = dequeue(&descMouse);
					else
						flag.mouse=1;
				}
			}
			//sorteio de inclusao de novos processos
			if(flagExec){
				sorteioInclusao=rand() % 10;
				if(sorteioInclusao==1)
					incluirNovoProcesso(&descProntos, &relatorio.tabelaEX, tempo);
			}
			if(CPU!=NULL)
				CPU->PCB.tempo_exec++;
			Sleep(100);
	    	tempo++;
		}
	}
	system("cls");
	textcolor(15);
	printf("Finalizados: %d\n", relatorio.qtdeTerminated);
	printf("Bloqueado: %d\n", relatorio.tempoEspera[2]);
	float media; 
	if (relatorio.tempoEspera[2] != 0){
		media = (relatorio.tempoEspera[1] - relatorio.tempoEspera[0]) / relatorio.tempoEspera[2];
		if(media < 0){
			media = -media;
		}
	}
	else
    	media = 0;
	printf("Media: %.2f\n", media);
	TabelaP *ptr;
	ptr = relatorio.contexto;
	int contador = 0;
	while(ptr != NULL){
		contador++;
		ptr = ptr -> prox;
	}
	printf("Mudanca de Contexto: %d\n", contador);
	TabelaP_EX *ptr2 = relatorio.tabelaEX;
	while(ptr2 != NULL){
		printf("Processo: %d\nTempo de Execucao: %d\n", ptr2 -> processo.pid, (ptr2 -> tempoEX[1] - ptr2 -> tempoEX[0]));
		ptr2 = ptr2 -> prox;
	}
	TabelaP_Pai *ptr3 = relatorio.tabelaPai;
	int timeP;
	while(ptr3 != NULL){
		if(ptr3 -> tempoWait[1] == 0){
			ptr3 -> tempoWait[1] = tempo;
		}
		if(ptr3 -> tempoWait[0] == 0){
			timeP = 0;
		}
		else{
			timeP = ptr3 -> tempoWait[1] - ptr3 -> tempoWait[0];
		}
		printf("Processo: %d\nFilhos: %d\nWait: %d\n", ptr3 -> processo.pid, ptr3 -> contChildren, timeP);
		ptr3 = ptr3 -> prox;
		timeP = 0;
	}
	getch();
	//ExibirRelatorio(relatorio);
}


int main(void){
	srand(time(NULL));
	InterfaceInit();
	getch();
	Simulacao();
	return 0;
}
