
union processo{
	int pid,ppid,uid,gid;
};typedef union processo Processo;

struct tpfilac{
	union processo Processo;
	struct tpfilac *prox;
};typedef struct tpfilac TpFilaC;

struct desc{
	struct tpfilac *inicio, *fim;
	int qtde;
};typedef struct desc Desc; 


void Init(Desc *desc);
Processo criarProcesso(int pid,int ppid, int uid, int gid);
void Enqueue(Desc *desc, Processo proc);
Processo Dequeue(Desc *desc);
char QisEmpty(int qtde);
void Exibir(Desc desc);

void Init(Desc *desc){
	desc.inicio=NULL;
	desc.fim=NULL;
	desc.qtde=0;
}

Processo criarProcesso(int pid,int ppid, int uid, int gid){
	Processo processo;
	processo.pid=pid;
	processo.ppid=ppid;
	processo.uid=uid;
	processo.gid=gid;	
}

void Enqueue(Desc *desc, Processo proc){
	TpFilaC *aux = (*desc)->inicio;
	TpFilaC *Nova = (TpFilaC*)malloc(sizeof(TpFilaC));
	Nova->Processo=proc;
	Nova->prox=NULL;
	if(aux==NULL)
		(*desc)->inicio=(*desc)->fim=Nova;
	else{
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=Nova;
		(*desc)->fim=Nova;
		(*desc)->qtde++;
	}		
}

Processo Dequeue(Desc *desc){
	Processo proc=(*desc)->inicio->Processo;
	TpFilaC *aux=(*desc)->inicio;
	(*desc)->inicio=aux->prox;
	free(aux);
	(*desc)->qtde--;
	return proc;
}

char QisEmpty(int qtde){
	return qtde==0;
}

void Exibir(Desc desc){
	Processo proc;
	while(!QisEmpty(desc.qtde)){
		proc = Dequeue(desc);
		printf("Pid: %d\n",proc.pid);
		printf("Ppid: %d\n",proc.ppid);
		printf("Gid: %d\n",proc.gid);
		printf("Uid: %d\n",proc.uid);
	}
		
}




