void InterfaceInit(){
	int i, ci = 3, li = 1, cf = 111, lf = 30;
	gotoxy(ci,li);
	textcolor(15);
	printf("%c",201);
	gotoxy(ci,lf);
	printf("%c",200);
	gotoxy(cf,li);
	printf("%c",187);
	gotoxy(cf,lf);
	printf("%c",188);
	for(i=ci+1; i<cf; i++)
	{
		gotoxy(i,li);
		printf("%c",205);
		gotoxy(i,lf);
		printf("%c",205);		
	}
	for(i=li+1; i<lf; i++)
	{
		gotoxy(ci,i);
		printf("%c",186);
		gotoxy(cf,i);
		printf("%c",186);
	}
	gotoxy(ci + 36, li + 5);
	textcolor(11);
	printf("SIMULADOR CICLO DE VIDA DE UM PROJETO");
	gotoxy(ci + 47, li + 11);
	textcolor(2);
	printf("DESENVOLVEDORES");
	gotoxy(ci + 40 , li + 14);
	textcolor(14);
	printf("Daniel Martins de Almeida Neves");
	gotoxy(ci + 40, li + 16);
	textcolor(12);
	printf("Gabriel Lucas Moreira Mariano");
	gotoxy(ci + 40, li + 18);
	textcolor(13);
	printf("Mariana Fernandes Rezende");
	gotoxy(ci + 36, li + 24);
	textcolor(1);
	printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR");
}

void InterfaceMain(){
	int i, ci = 3, li = 1, cf = 208, lf = 51;
	gotoxy(ci, li);
	textcolor(0);
	printf("%c",201);
	gotoxy(ci, lf);
	printf("%c",200);
	gotoxy(cf, li);
	printf("%c",187);
	gotoxy(cf, lf);
	printf("%c",188);
	for(i= ci+1; i<cf; i++)
	{
		gotoxy(i, li);
		printf("%c",205);
		gotoxy(i, lf);
		printf("%c",205);		
	}
	for(i= li+1; i<lf; i++)
	{
		gotoxy(ci, i);
		printf("%c",186);
		gotoxy(cf, i);
		printf("%c",186);
	}
	//Fila de Prontos
	gotoxy(ci + 2, li + 1);
	textcolor(2);
	printf("FILA DE PRONTOS");
	gotoxy(ci + 1, li + 2);
	printf("%c",201);
	gotoxy(ci + 1, li + 8);
	printf("%c",200);
	gotoxy(cf - 22, li + 2);
	printf("%c",187);
	gotoxy(cf - 22, li + 8);
	printf("%c",188);
	for(i= ci+2; i<cf - 22; i++)
	{
		gotoxy(i, li + 2);
		printf("%c",205);
		gotoxy(i, li + 8);
		printf("%c",205);		
	}
	for(i= li+3; i<li + 8; i++)
	{
		gotoxy(ci + 1, i);
		printf("%c",186);
		gotoxy(cf - 22, i);
		printf("%c",186);
	}
	//Fila de espera - HD
	gotoxy(ci + 2, li + 10);
	textcolor(1);
	printf("FILA DE ESPERA - HD");
	gotoxy(ci + 1, li + 11);
	printf("%c",201);
	gotoxy(ci + 1, li + 17);
	printf("%c",200);
	gotoxy(cf - 22, li + 11);
	printf("%c",187);
	gotoxy(cf - 22, li + 17);
	printf("%c",188);
	for(i= ci+2; i<cf - 22; i++)
	{
		gotoxy(i, li + 11);
		printf("%c",205);
		gotoxy(i, li + 17);
		printf("%c",205);		
	}
	for(i= li+12; i<li + 17; i++)
	{
		gotoxy(ci + 1, i);
		printf("%c",186);
		gotoxy(cf - 22, i);
		printf("%c",186);
	}
	//Fila de espera - Teclado
	gotoxy(ci + 2, li + 19);
	textcolor(4);
	printf("FILA DE ESPERA - TECLADO");
	gotoxy(ci + 1, li + 20);
	printf("%c",201);
	gotoxy(ci + 1, li + 26);
	printf("%c",200);
	gotoxy(cf - 22, li + 20);
	printf("%c",187);
	gotoxy(cf - 22, li + 26);
	printf("%c",188);
	for(i= ci+2; i<cf - 22; i++)
	{
		gotoxy(i, li + 20);
		printf("%c",205);
		gotoxy(i, li + 26);
		printf("%c",205);		
	}
	for(i= li+21; i<li + 26; i++)
	{
		gotoxy(ci + 1, i);
		printf("%c",186);
		gotoxy(cf - 22, i);
		printf("%c",186);
	}
	//Fila de espera - Mouse
	gotoxy(ci + 2, li + 28);
	textcolor(14);
	printf("FILA DE ESPERA - MOUSE");
	gotoxy(ci + 1, li + 29);
	printf("%c",201);
	gotoxy(ci + 1, li + 35);
	printf("%c",200);
	gotoxy(cf - 22, li + 29);
	printf("%c",187);
	gotoxy(cf - 22, li + 35);
	printf("%c",188);
	for(i= ci+2; i<cf - 22; i++)
	{
		gotoxy(i, li + 29);
		printf("%c",205);
		gotoxy(i, li + 35);
		printf("%c",205);		
	}
	for(i= li+30; i<li + 35; i++)
	{
		gotoxy(ci + 1, i);
		printf("%c",186);
		gotoxy(cf - 22, i);
		printf("%c",186);
	}
	//Fila de fork
	gotoxy(ci + 2, li + 37);
	textcolor(5);
	printf("FILA DE FORK");
	gotoxy(ci + 1, li + 38);
	printf("%c",201);
	gotoxy(ci + 1, li + 44);
	printf("%c",200);
	gotoxy(cf - 22, li + 38);
	printf("%c",187);
	gotoxy(cf - 22, li + 44);
	printf("%c",188);
	for(i= ci+2; i<cf - 22; i++)
	{
		gotoxy(i, li + 38);
		printf("%c",205);
		gotoxy(i, li + 44);
		printf("%c",205);		
	}
	for(i= li+39; i<li + 44; i++)
	{
		gotoxy(ci + 1, i);
		printf("%c",186);
		gotoxy(cf - 22, i);
		printf("%c",186);
	}
	//Opções
	textcolor(0);
	for(i = ci + 1; i < cf; i++){
		gotoxy(i, li + 46);
		printf("%c", 205);
	}
	textcolor(15);
	gotoxy(ci + 3, li + 48);
	printf("ESC - INTERROMPER A CRIACAO DE NOVOS PROCESSOS");
	gotoxy(ci + 70, li + 48);
	printf("ENTER - CRIAR UM NOVO PROCESSO");
	//CPU
	gotoxy(cf - 12, li + 1);
	textcolor(3);
	printf("CPU");
	gotoxy(cf - 21, li + 2);
	printf("%c",201);
	gotoxy(cf - 21, li + 8);
	printf("%c",200);
	gotoxy(cf - 1, li + 2);
	printf("%c",187);
	gotoxy(cf - 1, li + 8);
	printf("%c",188);
	for(i= cf - 20; i <cf - 1; i++)
	{
		gotoxy(i, li + 2);
		printf("%c",205);
		gotoxy(i, li + 8);
		printf("%c",205);		
	}
	for(i= li+3; i<li + 8; i++)
	{
		gotoxy(cf - 21, i);
		printf("%c",186);
		gotoxy(cf - 1, i);
		printf("%c",186);
	}
	//HD
	gotoxy(cf - 12, li + 10);
	textcolor(3);
	printf("HD");
	gotoxy(cf - 21, li + 11);
	printf("%c",201);
	gotoxy(cf - 21, li + 17);
	printf("%c",200);
	gotoxy(cf - 1, li + 11);
	printf("%c",187);
	gotoxy(cf - 1, li + 17);
	printf("%c",188);
	for(i= cf - 20; i <cf - 1; i++)
	{
		gotoxy(i, li + 11);
		printf("%c",205);
		gotoxy(i, li + 17);
		printf("%c",205);		
	}
	for(i= li+12; i<li + 17; i++)
	{
		gotoxy(cf - 21, i);
		printf("%c",186);
		gotoxy(cf - 1, i);
		printf("%c",186);
	}
	//Teclado
	gotoxy(cf - 14, li + 19);
	textcolor(3);
	printf("TECLADO");
	gotoxy(cf - 21, li + 20);
	printf("%c",201);
	gotoxy(cf - 21, li + 26);
	printf("%c",200);
	gotoxy(cf - 1, li + 20);
	printf("%c",187);
	gotoxy(cf - 1, li + 26);
	printf("%c",188);
	for(i= cf - 20; i < cf - 1; i++)
	{
		gotoxy(i, li + 20);
		printf("%c",205);
		gotoxy(i, li + 26);
		printf("%c",205);		
	}
	for(i= li+21; i<li + 26; i++)
	{
		gotoxy(cf - 21, i);
		printf("%c",186);
		gotoxy(cf - 1, i);
		printf("%c",186);
	}
	//Mouse
	gotoxy(cf - 13, li + 28);
	textcolor(3);
	printf("MOUSE");
	gotoxy(cf - 21, li + 29);
	printf("%c",201);
	gotoxy(cf - 21, li + 35);
	printf("%c",200);
	gotoxy(cf - 1, li + 29);
	printf("%c",187);
	gotoxy(cf - 1, li + 35);
	printf("%c",188);
	for(i= cf - 20; i < cf - 1; i++)
	{
		gotoxy(i, li + 29);
		printf("%c",205);
		gotoxy(i, li + 35);
		printf("%c",205);		
	}
	for(i= li+30; i<li + 35; i++)
	{
		gotoxy(cf - 21, i);
		printf("%c",186);
		gotoxy(cf - 1, i);
		printf("%c",186);
	}
}
