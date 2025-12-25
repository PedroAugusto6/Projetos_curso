#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ====================== ESTRUTURAS DE DADOS (STRUCTS) ====================== */

/* Representa o jogador e o seu inventário */
typedef struct {
    char nome[100];
    int pm;     /* Pontos Máximos de vida (Health Points Max) */
    int pr;     /* Pontos Restantes (Vida atual) */
    int chaves; /* Quantidade de chaves para abrir portas ($) */
    int pocoes; /* Quantidade de poções de cura */
    int bombas; /* Quantidade de bombas (armadilhas que explodiram) */
} mochila;

/* Representa o conteúdo de um Baú ('B') no mapa */
typedef struct {
    int pocao;  /* Valor de cura da poção (se for 0, não tem poção) */
    int chave;  /* 1 se tiver chave, 0 se não tiver */
    int bomba;  /* Valor do dano da bomba (se for 0, não é armadilha) */
} bau;

/* Guarda as coordenadas fixas importantes do mapa */
typedef struct {
    int inicio_l, inicio_c; /* Posição inicial ('#') */
    int saida_l, saida_c;   /* Posição de saída ('@') */
} posicao;

/* SNAPSHOT: Guarda o estado completo do jogo num determinado momento.
   Essencial para a funcionalidade de "Voltar" (Undo). */
typedef struct {
    int linha;
    int coluna;
    int pr;       /* Vida do jogador neste momento */
    int pocao;    /* Itens na mochila neste momento */
    int bomba;
    int chave;
    int dano;     /* Registo do que aconteceu neste turno (para logs) */
    int cura;

    /* Cópia visual do mapa neste momento (para desfazer portas abertas ou baús abertos) */
    char **mapa_copy;
} estado;

/* Nó da Pilha (Linked List) para o histórico de movimentos */
typedef struct NodeSt {
    estado e;            /* O dado guardado é um 'estado' completo */
    struct NodeSt* next; /* Ponteiro para o estado anterior (embaixo na pilha) */
} NodeSt;

/* A Pilha em si, que controla o topo do histórico */
typedef struct {
    NodeSt* top;
} Pilha;

/* Nó da Fila (apenas coordenadas) para o algoritmo BFS (Busca em Largura) */
typedef struct {
    int l, c;
} QNode;

/* A Fila Circular (Vetor Dinâmico) para gerenciar a ordem de exploração */
typedef struct {
    QNode *v;               /* Vetor de nós */
    int ini, fim, size, cap; /* Controle de início, fim, tamanho atual e capacidade total */
} Fila;

/* ====================== FUNÇÕES DA PILHA (Histórico/Undo) ====================== */

/* Inicializa a pilha como vazia */
void pilha_init(Pilha* p) { p->top = NULL; }

/* Verifica se a pilha está vazia (1 = sim, 0 = não) */
int pilha_vazia(Pilha* p) { return p->top == NULL; }

/* Adiciona um novo estado no topo da pilha (Salvar jogo) */
void pilha_push(Pilha* p, estado x) {
    NodeSt* n = (NodeSt*)malloc(sizeof(NodeSt));
    n->e = x;
    n->next = p->top; /* O novo nó aponta para o antigo topo */
    p->top = n;       /* O topo passa a ser o novo nó */
}

/* Remove e retorna o estado do topo (Carregar jogo/Undo) */
estado pilha_pop(Pilha* p) {
    // Cria um estado vazio para retornar em caso de erro
    estado none;
    none.linha = -1; none.coluna = -1;
    none.pr = 0;
    none.pocao = none.bomba = none.chave = none.dano = none.cura = 0;
    none.mapa_copy = NULL;

    if (p->top == NULL) return none;

    NodeSt* t = p->top;
    estado x = t->e;     /* Salva o dado antes de apagar o nó */
    p->top = t->next;    /* Avança o topo para o próximo */
    free(t);             /* Libera a memória do nó removido */
    return x;
}

/* ====================== FUNÇÕES DA FILA (BFS/Exploração) ====================== */

/* Inicializa a fila circular com capacidade definida */
void fila_init(Fila *f, int cap) {
    f->v = malloc(cap * sizeof(QNode));
    f->ini = f->fim = f->size = 0;
    f->cap = cap;
}

/* Verifica se a fila está vazia */
int fila_vazia(Fila *f) { return f->size == 0; }

/* Adiciona um nó no FIM da fila (Comportamento normal de fila) */
void fila_push(Fila *f, int l, int c) {
    f->v[f->fim].l = l;
    f->v[f->fim].c = c;
    f->fim = (f->fim + 1) % f->cap; /* Matemática circular: se chegar ao fim do vetor, volta ao 0 */
    f->size++;
}

/* Adiciona um nó no INÍCIO da fila (Fura-fila).
   Usado no UNDO para colocar o jogador de volta na vez de jogar imediatamente. */
void fila_push_front(Fila *f, int l, int c) {
    f->ini = (f->ini - 1 + f->cap) % f->cap; /* Anda para trás no círculo */
    f->v[f->ini].l = l;
    f->v[f->ini].c = c;
    f->size++;
}

/* Remove e retorna o nó do INÍCIO da fila (Próximo passo a processar) */
QNode fila_pop(Fila *f) {
    QNode r = f->v[f->ini];
    f->ini = (f->ini + 1) % f->cap; /* Avança o início no círculo */
    f->size--;
    return r;
}

/* ====================== FUNÇÕES UTILITÁRIAS ====================== */

/* Mostra o status atual do jogador */
void mostrar_mochila(mochila *bag) {
    printf("Vida: %d/%d\nChaves: %d\nPocoes: %d\nBombas: %d\n",
           bag->pr, bag->pm, bag->chaves, bag->pocoes, bag->bombas);
}

/* Cria uma cópia exata do mapa atual (aloca nova memória) */
char **copiar_mapa(char **mapa, int linhas, int colunas) {
    char **m = malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        m[i] = malloc((colunas + 2) * sizeof(char)); /* +2 para \n e \0 */
        strcpy(m[i], mapa[i]);
    }
    return m;
}

/* Libera a memória de um mapa copiado */
void free_mapa_copy(char **m, int linhas) {
    if (!m) return;
    for (int i = 0; i < linhas; i++) free(m[i]);
    free(m);
}

/* Recalcula a matriz de visitados 'vis' baseada no mapa restaurado.
   Se for espaço vazio, Baú ou Porta, considera como NÃO visitado (0). */
void recompute_vis_from_map(int **vis, char **mapa, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == ' ' || mapa[i][j] == 'B' || mapa[i][j] == '$')
                vis[i][j] = 0;
            else
                vis[i][j] = 1; /* Paredes e caminhos já trilhados ('-') contam como visitados */
        }
    }
}

/* ====================== ALGORITMO PRINCIPAL (BFS Interativo) ====================== */

int bfs_step(char **mapa, bau **matrizBau, int linhas, int colunas,
             posicao local, mochila *bag) {

    // --- 1. PREPARAÇÃO (SETUP) ---

    // Aloca e zera a matriz 'vis' (visitados)
    int **vis = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) vis[i] = calloc(colunas, sizeof(int));

    // Inicia a Fila e coloca o ponto de partida do jogador
    Fila fila;
    fila_init(&fila, linhas * colunas);
    fila_push(&fila, local.inicio_l, local.inicio_c);
    vis[local.inicio_l][local.inicio_c] = 1; // Marca início como visitado

    // Aloca matriz 'pai' para reconstruir o caminho final (Backtracking visual)
    posicao **pai = malloc(linhas * sizeof(posicao*));
    for (int i = 0; i < linhas; i++) {
        pai[i] = malloc(colunas * sizeof(posicao));
        for (int j = 0; j < colunas; j++) pai[i][j].inicio_l = pai[i][j].inicio_c = -1;
    }

    // Inicia a Pilha de Histórico para o voltar
    Pilha hist;
    pilha_init(&hist);

    getchar(); /* limpar buffer inicial do teclado */

    // Vetores de direção: Cima, Baixo, Esquerda, Direita
    int dl[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // --- 2. LOOP PRINCIPAL DO JOGO ---

    while (1) {
        // Se a fila acabar, não há mais caminhos possíveis
        if (fila_vazia(&fila)) {
            printf("Caminho inexistente ou sem saida.\n");
            return 0; // Derrota por falta de caminho
        }

        // "Espreita" o próximo passo (quem é o próximo da fila?) sem remover ainda
        QNode next = fila.v[fila.ini];
        int nl = next.l;
        int nc = next.c;

        // --- INTERFACE VISUAL ---
        printf("\nProximo no a processar: (%d,%d)\n", nl, nc);
        printf("\nEstado atual do mapa:\n");
        for (int i = 0; i < linhas; i++) printf("%s", mapa[i]);
        printf("\n");
        mostrar_mochila(bag);

        // --- MENU DE ESCOLHA ---
        printf("\nEscolha: 1 - Avancar, 2 - Voltar, 3 - Sair\n");
        int op = 0;
        // Loop de validação para garantir que o usuário digita números
        while (1) {
            if (scanf("%d", &op) != 1) {
                int ch; while ((ch = getchar()) != EOF && ch != '\n'); // Limpa input sujo
                printf("Entrada invalida. Digite 1, 2 ou 3: ");
                continue;
            }
            int ch; while ((ch = getchar()) != EOF && ch != '\n'); // Limpa buffer do Enter
            if (op >= 1 && op <= 3) break;
            printf("Digite 1 (Avancar), 2 (Voltar) ou 3 (Sair): ");
        }

        // --- OPÇÃO 3: SAIR ---
        if (op == 3) {
            printf("\nExecucao interrompida pelo usuario.\n");
            return 0;
        }

        // --- OPÇÃO 2: VOLTAR ---
        if (op == 2) {
            if (pilha_vazia(&hist)) {
                printf("\nNao ha movimentos anteriores para voltar.\n");
                continue;
            }
            // Recupera o último estado salvo
            estado s = pilha_pop(&hist);

            if (s.mapa_copy != NULL) {
                // 1. Restaura o desenho do Mapa
                for (int i = 0; i < linhas; i++) strcpy(mapa[i], s.mapa_copy[i]);

                // 2. Recalcula onde o robô já "passou" para liberar caminhos de volta
                recompute_vis_from_map(vis, mapa, linhas, colunas);

                // 3. Restaura os status da Mochila
                bag->pocoes = s.pocao;
                bag->bombas = s.bomba;
                bag->chaves = s.chave;
                bag->pr = s.pr;

                // 4. "Fura a fila": Coloca o robô de volta no início da fila para jogar de novo
                fila_push_front(&fila, s.linha, s.coluna);

                // 5. Limpa a memória da cópia usada
                free_mapa_copy(s.mapa_copy, linhas);
                printf("\nEstado anterior restaurado. Voltando para (%d,%d)\n", s.linha, s.coluna);
                continue;
            } else {
                printf("\nErro: estado sem mapa_copy.\n");
                continue;
            }
        }

        // --- OPÇÃO 1: AVANÇAR ---
        if (op == 1) {
            // 1. Tira da fila e define onde estamos PISANDO AGORA
            QNode atual = fila_pop(&fila);
            int l = atual.l, c = atual.c;

            // 2. Salva o estado atual (Snapshot) ANTES de modificar qualquer coisa
            estado snap;
            snap.linha = l;
            snap.coluna = c;
            snap.pr = bag->pr;
            snap.pocao = bag->pocoes;
            snap.bomba = bag->bombas;
            snap.chave = bag->chaves;
            if (mapa[l][c] == 'B') {
                snap.dano = matrizBau[l][c].bomba; 
                snap.cura = matrizBau[l][c].pocao; 
            } else {
                snap.dano = 0;
                snap.cura = 0;
            }
            snap.mapa_copy = copiar_mapa(mapa, linhas, colunas);
            pilha_push(&hist, snap); // Guarda na pilha

            // ====================================================
            // FASE A: INTERAGIR COM O QUADRADO ONDE ESTOU (l, c)
            // ====================================================

            // Chegou na Saída? (@)
            if (mapa[l][c] == '@') {
                printf("\nCaminho encontrado!\n");
                // Reconstrói o caminho visualmente usando a matriz 'pai'
                int x = l, y = c;
                while (pai[x][y].inicio_l != -1) {
                    // Pinta o caminho de volta com '-'
                    if (mapa[x][y] != '#' && mapa[x][y] != '@' && mapa[x][y] != '*')
                        mapa[x][y] = '-';
                    int px = pai[x][y].inicio_l;
                    int py = pai[x][y].inicio_c;
                    x = px; y = py; // Volta um passo para trás
                }
                return 1; // Vitória!
            }

            // Tem Baú? ('B')
            if (mapa[l][c] == 'B') {
                printf("\nEncontrou um Bau em (%d,%d)!\n", l, c);

                // Se for Bomba (Armadilha)
                if (matrizBau[l][c].bomba > 0) {
                    int dano = matrizBau[l][c].bomba;
                    bag->pr -= dano;
                    bag->bombas++;
                    printf("ARMADILHA! Bomba explodiu. Dano: %d. Vida restante: %d\n", dano, bag->pr);

                    if (bag->pr <= 0) {
                        printf("\nO jogador morreu. Fim de jogo.\n");
                        return 0; // Derrota (Game Over)
                    }
                }

                // Se for Poção
                if (matrizBau[l][c].pocao > 0) {
                    int cura = matrizBau[l][c].pocao;
                    // Só usa a poção se a vida não estiver cheia
                    if (bag->pr < bag->pm) {
                        bag->pr += cura;
                        if (bag->pr > bag->pm) bag->pr = bag->pm; // Não ultrapassa o máximo
                        printf("Bebeu pocao. Vida recuperada para: %d\n", bag->pr);
                    } else {
                        bag->pocoes++; // Guarda na mochila
                        printf("Vida cheia. Guardou pocao na mochila. Total: %d\n", bag->pocoes);
                    }
                }

                // Se for Chave
                if (matrizBau[l][c].chave > 0) {
                    bag->chaves += matrizBau[l][c].chave;
                    printf("Pegou uma chave! Total: %d\n", bag->chaves);
                }

                printf("Pressione ENTER para continuar...");
                getchar();
            }

            // Marca visualmente onde já pisamos (Rastro '-'), exceto na saída ou início
            if (mapa[l][c] != '@' && mapa[l][c] != '#') {
                mapa[l][c] = '-';
            }

            // ====================================================
            // FASE B: PROCURAR VIZINHOS (Onde posso ir a seguir?)
            // ====================================================

            for (int k = 0; k < 4; k++) {
                int r = l + dl[k]; // Nova linha vizinha
                int s = c + dc[k]; // Nova coluna vizinha

                // 1. Verifica Limites do mapa
                if (r < 0 || r >= linhas || s < 0 || s >= colunas) continue;
                // 2. Verifica se já visitamos/agendamos
                if (vis[r][s]) continue;

                // 3. Se for Parede (*), ignora
                if (mapa[r][s] == '*') continue;

                // 4. Lógica da Porta Trancada ($)
                if (mapa[r][s] == '$') {
                    if (bag->chaves > 0) {
                        bag->chaves--; // Gasta a chave
                        mapa[r][s] = '-'; // Abre visualmente a porta
                        printf("\nPorta destrancada em (%d,%d) (gasto 1 chave).\n", r, s);
                    } else {
                        continue; // Sem chave, é como se fosse parede
                    }
                }

                // 5. Adicionar à Fila (Agendar visita futura)
                vis[r][s] = 1;
                pai[r][s].inicio_l = l;
                pai[r][s].inicio_c = c;

                // Nota: O item do baú só será pego quando sairmos da fila (Fase A)
                fila_push(&fila, r, s);
            }
        }
    }
    return 0;
}

/* ====================== FUNÇÃO MAIN ====================== */

int main() {
    srand((unsigned int)time(NULL)); // Semente para números aleatórios

    posicao local;
    char escolha;
    char nomeArquivo[200];
    int aux;

    // Carregamento do Mapa
    printf("Escolha o mapa (a, b ou c): ");
    scanf(" %c", &escolha);
    if(escolha=='a')aux=3;
    if(escolha=='b')aux=4;
    if(escolha=='c')aux=5;

    sprintf(nomeArquivo, "ed1-trabalho-jogo_exploracao-mapa_%c-ascii.txt", escolha);
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) { printf("Erro ao abrir arquivo.\n"); return 1; }

    int colunas, linhas;
    fscanf(arquivo, "%d", &colunas);
    fscanf(arquivo, "%d", &linhas);
    fgetc(arquivo); // Consome o \n após os números

    // Aloca a matriz do mapa dinamicamente
    char **matriz = malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc((colunas + 2) * sizeof(char));
        fgets(matriz[i], colunas + 2, arquivo);
    }
    fclose(arquivo);

    // Aloca e preenche a matriz de Baús (com itens aleatórios)
    bau **matrizBau = malloc(linhas * sizeof(bau*));
    for (int i = 0; i < linhas; i++) {
        matrizBau[i] = malloc(colunas * sizeof(bau));
        for (int j = 0; j < colunas; j++) {
            matrizBau[i][j].pocao = matrizBau[i][j].bomba = matrizBau[i][j].chave = 0;

            // Identifica posições especiais
            if (matriz[i][j] == '#') { local.inicio_l = i; local.inicio_c = j; }
            if (matriz[i][j] == '@') { local.saida_l = i; local.saida_c = j; }

            // Gera loot aleatório para os Baús
            if (matriz[i][j] == 'B') {
                if(aux>0){
                    matrizBau[i][j].chave=1;
                    aux--;
                }
                else{
                    int item = (rand() % 3) + 1; // 1=Poção, 2=Chave, 3=Bomba
                    if (item == 1) matrizBau[i][j].pocao = (rand() % 5) + 1;
                    else if (item == 2) matrizBau[i][j].chave = 1;
                    else matrizBau[i][j].bomba = (rand() % 4) + 1;
                }
            }
        }
    }

    mochila bag = {"Jogador", 10, 10, 0, 0, 0};

    // Estado inicial visual
    printf("\nMapa carregado:\n");
    for (int i = 0; i < linhas; i++) printf("%s", matriz[i]);

    printf("\nIniciando BFS passo-a-passo (1=Avancar, 2=Voltar, 3=Sair)...\n");
    mostrar_mochila(&bag);

    // Chama o loop principal do jogo
    bfs_step(matriz, matrizBau, linhas, colunas, local, &bag);

    // Mostra estado final
    printf("\nMapa final:\n");
    for (int i = 0; i < linhas; i++) printf("%s", matriz[i]);

    printf("\nStatus final da mochila:\n");
    mostrar_mochila(&bag);

    return 0;
}