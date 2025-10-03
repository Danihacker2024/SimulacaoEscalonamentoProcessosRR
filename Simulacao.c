



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>
#include "Interface.h"
#include "FilaCircularProcessos.h"

void gerarProcessos(Desc *desc){
	int pid;
	pid = rand();
	int ppid = 1;
	int uid;
	uid = 1000;
	int CPU_Burst;
	int i;	
	for(i = 0; i<10;i++){
		CPU_Burst = (rand() % 20) + 1;
		enqueue(&*desc, criarProcesso(pid,ppid,uid,uid,CPU_Burst,0));
		ppid = pid;
		pid++;	
	}
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
	Processo CPU;
	FormPrincipal();
	textcolor(15);
    textbackground(0);
	int tempo,y;
	Desc descritor,descEspera;
	init(&descritor);init(&descEspera);
	gerarProcessos(&descritor);
	//Exibir(descritor);
	gotoxy(30, 7);
	printf("Tempo da simulacao em segundos: ");
	scanf("%d",&tempo);
	CPU = dequeue(&descritor);
    while(tempo>0){
	    if(kbhit()){
			opcao = Menu2();
		}else{
			clrscr();
			FormPrincipal();
			textcolor(15);
    		textbackground(0);
    		gotoxy(3,21);
    		printf("[ENTER] Opcoes");
			gotoxy(30, 7);
			printf("Tempo Total: %d segundos",tempo);
			if(CPU.tempo_exec<=CPU.CPU_Burst){
				gotoxy(30,9);
				printf("Processo em Execucao na CPU");
				ExibirProcesso(CPU,30,10);	
			} else if(!QisEmpty(descritor.qtde))
				CPU = dequeue(&descritor);
			else{
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

