#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>


//interface
void Moldura(int ci, int li, int cf, int lf, int corT, int corF) {
    int i;
    textcolor(corT);
    textbackground(corF);
    gotoxy(ci, li);
    printf("%c", 201);
    gotoxy(ci, lf);
    printf("%c", 200);
    gotoxy(cf, li);
    printf("%c", 187);
    gotoxy(cf, lf);
    printf("%c", 188);
    for (i = ci + 1; i < cf; i++) {
        gotoxy(i, li);
        printf("%c", 205);
        gotoxy(i, lf);
        printf("%c", 205);
        //Sleep(0.1);
    }
    for (i = li + 1; i < lf; i++) {
        gotoxy(ci, i);
        printf("%c", 186);
        gotoxy(cf, i);
        printf("%c", 186);
        //Sleep(0.1);
    }
}

void FormPrincipal(void) {
    Moldura(1, 1, 120, 30, 6, 0);
    Moldura(2, 2, 119, 4, 7, 0);
    gotoxy((120 - strlen("=== Simulacao Escalonamento Round Robin ===")) / 2, 3);
    printf("=== Simulacao Escalonamento Round Robin ===");
    Moldura(2, 5, 25, 29, 9, 0);
    Moldura(26, 5, 119, 29, 3, 0);
}

void Menu1() {
    system("cls");
	FormPrincipal();
    textcolor(15);
    textbackground(0);
    textcolor(10);
    textbackground(0);
    gotoxy(3,21);
    printf("[ENTER] Iniciar Programa");
    gotoxy(3,22);
    printf("[ESC] - Sair");
}

void Menu2(){
	system("cls");
	FormPrincipal();
    textcolor(15);
    textbackground(0);
    textcolor(10);
    textbackground(0);
    gotoxy(3,10);
    printf("[F1] Incluir novo processo");
    gotoxy(3,11);
    printf("[F2] Executar Processo");
    gotoxy(3,12);
    printf("na Fila de Prontos");
    gotoxy(3,13);
    printf("[F3] Colocar processo em");
    gotoxy(3,14);
    printf("espera");
    printf("Retirar da Fila de");
    printf("Espera");
    printf("Criar processo Filho");
    
    
    
    
    gotoxy(3,22);
    printf("[ESC] - Voltar");
}


void exibirParticipantes(void){
	Moldura(1, 1, 120, 30, 6, 0);
    Moldura(2, 2, 119, 4, 7, 0);
    Moldura(2, 5, 119, 29, 3, 0);
    textcolor(15);
    textbackground(0);
	gotoxy(44,3);printf("### PARTICIPANTES DO GRUPO ###");
	textcolor(2);
    textbackground(0);
    gotoxy(45,11);printf("Daniel Martins de Almeida Neves");
    gotoxy(45,13);printf("Gabriel");
    gotoxy(45,15);printf("Marina Rezende");
    textcolor(0);
    textbackground(0);
    Sleep(2000);
}

//fim da interface
