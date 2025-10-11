struct Flag{
	char HD, teclado, mouse;
};typedef struct Flag flag;

void initFlag1(flag *flag){
	flag->HD=flag->mouse=flag->teclado=1;
}

void initFlag0(flag *flag){
	flag->HD=flag->mouse=flag->teclado=0;
}

struct processo{
	int pid,ppid,uid,gid;
	int CPU_Burst,tempo_exec;
	int prioridade;
	int filhos;
	flag Recursos;
};typedef struct processo Processo;

struct tpfilac{
	struct processo PCB;
	struct tpfilac *prox;
};typedef struct tpfilac TpFilaC;

struct desc{
	struct tpfilac *inicio, *fim;
	int qtde;
};typedef struct desc Desc; 


void init(Desc *desc);
Processo criarProcesso(int pid,int ppid, int uid, int gid, int CPU_Burst, int tempo_exec, int prioridade, int filhos, flag Recursos);
void NovaCaixa(Processo proc, Processo **Nova);
void enqueue(Desc *desc, Processo proc);
Processo dequeue(Desc *desc);
char QisEmpty(int qtde);
void Exibir(Desc desc);

void init(Desc *desc){
	desc->inicio=NULL;
	desc->fim=NULL;
	desc->qtde=0;
}

Processo criarProcesso(int pid,int ppid, int uid, int gid, int CPU_Burst, int tempo_exec, int prioridade, int filhos, flag Recursos){
	Processo processo;
	processo.pid=pid;
	processo.ppid=ppid;
	processo.uid=uid;
	processo.gid=gid;
	processo.CPU_Burst=CPU_Burst;
	processo.tempo_exec=tempo_exec;
	processo.prioridade=prioridade;
	processo.filhos=filhos;
	processo.Recursos=Recursos;
	return processo;	
}
/*
void NovaCaixa(Processo proc, Processo **Nova){
	*Nova = (Processo*)malloc(sizeof(Processo));
	(*Nova)->pid=proc.pid;
	(*Nova)->ppid=proc.ppid;
	(*Nova)->uid=proc.uid;
	(*Nova)->gid=proc.gid;
	(*Nova)->CPU_Burst=proc.CPU_Burst;
	(*Nova)->tempo_exec=proc.tempo_exec;
	(*Nova)->prioridade=proc.prioridade;
	(*Nova)->filhos=proc.filhos;
}*/

void enqueue(Desc *desc, Processo proc){
    TpFilaC *Nova = (TpFilaC*)malloc(sizeof(TpFilaC));
    TpFilaC *aux=desc->inicio;
    Nova->PCB=proc;
    Nova->prox = NULL;
    if(desc->inicio == NULL){      
        desc->inicio = desc->fim = Nova;
    } /*else if(Nova->PCB.prioridade==1){                       
		Nova->prox=desc->inicio;
        desc->inicio = Nova;
    } else if(Nova->PCB.prioridade==5){
    	desc->fim->prox = Nova;
        desc->fim = Nova;
	} */else {
		while(aux->prox!=NULL && aux->prox->PCB.prioridade<=Nova->PCB.prioridade)
			aux=aux->prox;
		Nova->prox=aux->prox;
		aux->prox=Nova;
		if(Nova->prox==NULL)
			desc->fim=Nova;	
	}
    desc->qtde++;   
}

//tem q mudar a logica do dequeue e enqueue -> problema com ponteiro e struct
Processo dequeue(Desc *desc){
	Processo proc=desc->inicio->PCB;
	TpFilaC *aux=desc->inicio;
	desc->inicio=aux->prox;
	free(aux);
	desc->qtde--;
	return proc;
}

char QisEmpty(int qtde){
	return qtde==0;
}





