
struct processo{
	int pid,ppid,uid,gid;
	int CPU_Burst,tempo_exec;
};typedef struct processo Processo;

struct tpfilac{
	struct processo Processo;
	struct tpfilac *prox;
};typedef struct tpfilac TpFilaC;

struct desc{
	struct tpfilac *inicio, *fim;
	int qtde;
};typedef struct desc Desc; 


void init(Desc *desc);
Processo criarProcesso(int pid,int ppid, int uid, int gid, int CPU_Burst, int tempo_exec);
void enqueue(Desc *desc, Processo proc);
Processo dequeue(Desc *desc);
char QisEmpty(int qtde);
void Exibir(Desc desc);

void init(Desc *desc){
	desc->inicio=NULL;
	desc->fim=NULL;
	desc->qtde=0;
}

Processo criarProcesso(int pid,int ppid, int uid, int gid, int CPU_Burst, int tempo_exec){
	Processo processo;
	processo.pid=pid;
	processo.ppid=ppid;
	processo.uid=uid;
	processo.gid=gid;
	processo.CPU_Burst=CPU_Burst;
	processo.tempo_exec=tempo_exec;
	return processo;	
}

void enqueue(Desc *desc, Processo proc){
    TpFilaC *Nova = (TpFilaC*)malloc(sizeof(TpFilaC));
    Nova->Processo = proc;
    Nova->prox = NULL;

    if(desc->inicio == NULL){      
        desc->inicio = desc->fim = Nova;
    } else {                       
        desc->fim->prox = Nova;
        desc->fim = Nova;
    }

    desc->qtde++;   
}

Processo dequeue(Desc *desc){
	Processo proc=desc->inicio->Processo;
	TpFilaC *aux=desc->inicio;
	desc->inicio=aux->prox;
	free(aux);
	desc->qtde--;
	return proc;
}

char QisEmpty(int qtde){
	return qtde==0;
}





