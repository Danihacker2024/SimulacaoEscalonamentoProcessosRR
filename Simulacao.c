#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>
#include "Interface.h"
#include "FilaCircularProcessos.h"

int gerarProcessos(Desc *desc){
	int pid;
	pid = rand();
	int ppid = 1;
	int uid;
	uid = 1000;
	int CPU_Burst;
	int i;
	for(i = 0; i<2;i++){
		CPU_Burst = (rand() % 30) + 1;
		enqueue(&*desc, criarProcesso(pid,ppid,uid,uid,CPU_Burst,0));
		ppid = pid;
		pid++;	
	}
	return pid;
}

void incluirNovoProcesso(Desc *desc, int ppid){
	int pid = ppid+1;
	int uid = 1000;
	int CPU_Burst;
	CPU_Burst = (rand() % 30) + 1;
	enqueue(&*desc, criarProcesso(pid,ppid,uid,uid,CPU_Burst,0));
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
	Processo CPU;
	FormPrincipal();
	textcolor(15);
    textbackground(0);
	int tempo,y;
	Desc descritor,descEspera;
	init(&descritor);init(&descEspera);
	ultimoPid = gerarProcessos(&descritor);
	//Exibir(descritor);
	gotoxy(30, 7);
	printf("Tempo da simulacao em segundos: ");
	scanf("%d",&tempo);
	CPU = dequeue(&descritor);
    while(CPU.pid!=0 || tempo>0 || !QisEmpty(descEspera.qtde)){
	    if(kbhit()){
			opcao = Menu2();
			if(opcao==1)
				incluirNovoProcesso(&descritor,ultimoPid);
			else if(opcao==2){
				if(!QisEmpty(descritor.qtde)){
					enqueue(&descritor,CPU);
					CPU = dequeue(&descritor);
					quantum=1;	
				}
			}
			else if(opcao==3){
				enqueue(&descEspera,CPU);
				if(!QisEmpty(descritor.qtde))
						CPU = dequeue(&descritor);	
			}
			else if(opcao==4)
				enqueue(&descritor,dequeue(&descEspera));
		}else{
			clrscr();
			FormPrincipal();
			textcolor(15);
    		textbackground(0);
    		gotoxy(3,21);
    		printf("[ENTER] Opcoes");
			gotoxy(30, 7);
			if(tempo>=0)
				printf("Tempo Total: %d segundos",tempo);
			else 
				printf("Tempo Total: 0 segundos");
			if(CPU.tempo_exec<CPU.CPU_Burst){
				gotoxy(30,9);
				printf("Processo em Execucao na CPU");
				ExibirProcesso(CPU,30,10);
				sorteioEsp=(rand() % 10) + 1;
				if(sorteioEsp==5){
					gotoxy(70,9);
					printf("Processo foi bloqueado");
					enqueue(&descEspera,CPU);
					if(!QisEmpty(descritor.qtde))
						CPU = dequeue(&descritor);
					quantum=1;
				}
				if(quantum!=10)
					quantum++;
				if(quantum==10 && !QisEmpty(descritor.qtde)){
					gotoxy(70,9);
					printf("Acabou o quantum");
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
	    	tempo--;
		}
	}
}




int main(void){
	srand(time(NULL));
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

}

