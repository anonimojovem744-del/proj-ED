#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Vereador {
    int id_vereador;
    char nome[60];
    char partido[15];
    char email[50];
    struct Vereador *prox;
} Vereador;

typedef struct Reuniao {
    int id_reuniao;
    char data_reuniao[11];
    char hora[6];
    char pauta[100];
    struct Reuniao *prox;
} Reuniao;

typedef struct Projeto {
    int id_proj;
    int id_autor;
    char titulo[100];
    char data_mostra[11];
    char categoria[30];
    char status[20];
    struct Projeto *prox;
} Projeto;

typedef struct Presenca {
    int id_presenca;
    int id_reuniao;
    int id_vereador;
    char status_presenca[15];
    struct Presenca *prox;
} Presenca;

typedef struct Votacao {
    int id_votacao;
    int id_projeto;
    int id_reuniao;
    int id_vereador;
    char voto[15];
    struct Votacao *prox;
} Votacao;

void copiar_string(char *pra_ca, const char *daqui, size_t tamanho_max) {
    if (!pra_ca || !daqui || tamanho_max == 0) return;
    strncpy(pra_ca, daqui, tamanho_max - 1);
    pra_ca[tamanho_max - 1] = '\0';
}

Vereador* carregar_vereadores(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return NULL;

    char linha[256];
    Vereador *head = NULL, *tail = NULL;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        Vereador *novo = (Vereador*) malloc(sizeof(Vereador));
        if (!novo) continue;
        novo->prox = NULL;

        char *token = strtok(linha, ";");
        if (token) novo->id_vereador = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->nome, token, sizeof(novo->nome));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->partido, token, sizeof(novo->partido));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->email, token, sizeof(novo->email));

        if (!head) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    fclose(f);
    return head;
}

Reuniao* carregar_reunioes(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return NULL;

    char linha[256];
    Reuniao *head = NULL, *tail = NULL;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        Reuniao *novo = (Reuniao*) malloc(sizeof(Reuniao));
        if (!novo) continue;
        novo->prox = NULL;

        char *token = strtok(linha, ";");
        if (token) novo->id_reuniao = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->data_reuniao, token, sizeof(novo->data_reuniao));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->hora, token, sizeof(novo->hora));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->pauta, token, sizeof(novo->pauta));

        if (!head) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    fclose(f);
    return head;
}

Projeto* carregar_projetos(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return NULL;

    char linha[256];
    Projeto *head = NULL, *tail = NULL;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        Projeto *novo = (Projeto*) malloc(sizeof(Projeto));
        if (!novo) continue;
        novo->prox = NULL;

        char *token = strtok(linha, ";");
        if (token) novo->id_proj = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->titulo, token, sizeof(novo->titulo));

        token = strtok(NULL, ";");
        if (token) novo->id_autor = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->data_mostra, token, sizeof(novo->data_mostra));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->categoria, token, sizeof(novo->categoria));

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->status, token, sizeof(novo->status));

        if (!head) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    fclose(f);
    return head;
}

Presenca* carregar_presencas(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return NULL;

    char linha[256];
    Presenca *head = NULL, *tail = NULL;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        Presenca *novo = (Presenca*) malloc(sizeof(Presenca));
        if (!novo) continue;
        novo->prox = NULL;

        char *token = strtok(linha, ";");
        if (token) novo->id_presenca = atoi(token);

        token = strtok(NULL, ";");
        if (token) novo->id_reuniao = atoi(token);

        token = strtok(NULL, ";");
        if (token) novo->id_vereador = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->status_presenca, token, sizeof(novo->status_presenca));

        if (!head) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    fclose(f);
    return head;
}

Votacao* carregar_votacoes(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return NULL;

    char linha[256];
    Votacao *head = NULL, *tail = NULL;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        Votacao *novo = (Votacao*) malloc(sizeof(Votacao));
        if (!novo) continue;
        novo->prox = NULL;

        char *token = strtok(linha, ";");
        if (token) novo->id_votacao = atoi(token);

        token = strtok(NULL, ";");
        if (token) novo->id_projeto = atoi(token);

        token = strtok(NULL, ";");
        if (token) novo->id_reuniao = atoi(token);

        token = strtok(NULL, ";");
        if (token) novo->id_vereador = atoi(token);

        token = strtok(NULL, ";");
        if (token) copiar_string(novo->voto, token, sizeof(novo->voto));

        if (!head) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    fclose(f);
    return head;
}

void exibir_vereadores(Vereador *head) {
    printf("\n=== VEREADORES ===\n");
    while (head) {
        printf("[%d] %s | Partido: %s | Email: %s\n", head->id_vereador, head->nome, head->partido, head->email);
        head = head->prox;
    }
}

void exibir_reunioes(Reuniao *head) {
    printf("\n=== REUNIÕES ===\n");
    while (head) {
        printf("[%d] Data: %s | Hora: %s | Pauta: %s\n", head->id_reuniao, head->data_reuniao, head->hora, head->pauta);
        head = head->prox;
    }
}

void exibir_projetos(Projeto *head) {
    printf("\n=== PROJETOS DE LEI ===\n");
    while (head) {
        printf("[%03d] %s | Autor ID: %d | Categoria: %s | Status: %s\n", head->id_proj, head->titulo, head->id_autor, head->categoria, head->status);
        head = head->prox;
    }
}

void exibir_presencas(Presenca *head) {
    printf("\n=== REGISTROS DE PRESENÇA ===\n");
    while (head) {
        printf("[%d] Reunião: %d | Vereador: %d | Status: %s\n", head->id_presenca, head->id_reuniao, head->id_vereador, head->status_presenca);
        head = head->prox;
    }
}

void exibir_votacoes(Votacao *head) {
    printf("\n=== REGISTROS DE VOTAÇÕES ===\n");
    while (head) {
        printf("[%d] Projeto: %d | Reunião: %d | Vereador: %d | Voto: %s\n", head->id_votacao, head->id_projeto, head->id_reuniao, head->id_vereador, head->voto);
        head = head->prox;
    }
}

void liberar_vereadores(Vereador *head) {
    while (head) { 
        Vereador *t = head; head = head->prox; free(t); 
    }
}

void liberar_reunioes(Reuniao *head) {
    while (head) { 
        Reuniao *t = head; head = head->prox; free(t); 
    }
}

void liberar_projetos(Projeto *head) {
    while (head) { 
        Projeto *t = head; head = head->prox; free(t);
    }
}

void liberar_presencas(Presenca *head) {
    while (head) { 
        Presenca *t = head; head = head->prox; free(t); 
    }
}

void liberar_votacoes(Votacao *head) {
    while (head) { 
        Votacao *t = head; head = head->prox; free(t); 
    }
}

int escrever(const char *caminho, const char *texto) {
    if (caminho == NULL || texto == NULL){ 
        return 1;
    }
    
    FILE *f = fopen(caminho, "a");
    if (f == NULL) return 1;

    if (fputs(texto, f) == EOF) {
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}

int id_existe(const char *caminho, int id) {
    FILE *f = fopen(caminho, "r");
    if (!f) return 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        int id_atual = atoi(linha);
        if (id_atual == id) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

// --- LISTAS MUAHAHAHAHA ---
const char *NOMES_BASE[] = {
    "Arthur", "Oliveira", "Patriota",
    "Lemos", "Conceicao", "Emidio", 
    "Araujo", "Andrey", "Assis", 
    "Correia", "Cayo", "Lins",
    "Mathaus", "Mickael", "D'Silva",
    "Chaves", "Santiago", "Ferreira", 
    "Santos", "Silver", "Prata",
    "Contes", "Mike", "Azevedo", 
    "Junior", "Descassa", "Sentiu",
    "Lenicia","Joao", "Mario", 
    "Carlos", "Silva", "Santos", 
    "Souza", "Pereira", "Lima", 
    "Ana", "Beatriz", "Lucas",
    "Leticia", "Mandraque", "Jonas",
    "INSIRA_NOME_BRABO"
};
const int TOTAL_NOMES = sizeof(NOMES_BASE) / sizeof(NOMES_BASE[0]);

const char *PARTIDOS[] = {
    "PIC", "PICHICA", "PIQB", 
    "PIF", "TPM", "PF", 
    "PSCRR", "NOVO", "ANTIGO", 
    "PSC", "PNET", "PP",
    "FON"
};
const int TOTAL_PARTIDOS = sizeof(PARTIDOS) / sizeof(PARTIDOS[0]);

const char *DOMINIOS[] = {
    "camara.leg.br", 
    "gmail.com", 
    "outlook.com", 
    "ic.ufal.br", 
    "lves.com.br", 
    "camara.gov.br",
    "fbi.gov.us",
    "hacker.tor.br",
    "empty.none.go"
};
const int TOTAL_DOMINIOS = sizeof(DOMINIOS) / sizeof(DOMINIOS[0]);

const char *ACOES_BASE[] = {
    "Institucionalizacao", "Regulamentacao", 
    "Memificacao", "Fomento", 
    "Proibicao", "Padronizacao", 
    "Valorizacao", "Nacionalizacao", 
    "Precarizacao", "Clusteriacao",
    "Oficializacao", "Consideracao",
    "Perdao", "Informe",
    "Ementa", "Documentalizacao"
};
const int TOTAL_ACOES = sizeof(ACOES_BASE) / sizeof(ACOES_BASE[0]);

const char *TEMAS_BASE[] = {
    "Saude", "Violencia", "Representacao", 
    "Patriotismo", "Panificacao", "Cambio", 
    "Educacao", "Cultura", "Criptomoedas", 
    "Gastronomia", "Seguranca", "CyberSeguranca",
    "Residuos", "Polica"
};
const int TOTAL_TEMAS = sizeof(TEMAS_BASE) / sizeof(TEMAS_BASE[0]);

const char *CATEGORIAS[] = {
    "Saude", "Educacao", "Infraestrutura", 
    "Meio Ambiente", "Seguranca", "Financas",
    "Migueh", "Inutil", "Trapaceio", "Manobra Legal"
    "Greve"
};

const int TOTAL_CATEGORIAS = sizeof(CATEGORIAS) / sizeof(CATEGORIAS[0]);

const char *STATUS_PROJ[] = {
    "Em Tramitacao", 
    "Aprovado", 
    "Rejeitado", 
    "Arquivado"
};
const int TOTAL_STATUS_PROJ = sizeof(STATUS_PROJ) / sizeof(STATUS_PROJ[0]);

const char *STATUS_PRESENCA[] = {
    "presente", 
    "ausente", 
    "justificado"
};
const int TOTAL_PRESENCA = sizeof(STATUS_PRESENCA) / sizeof(STATUS_PRESENCA[0]);

const char *VOTOS[] = {
    "Favoravel", 
    "Contrario", 
    "Abstencao"
};
const int TOTAL_VOTOS = sizeof(VOTOS) / sizeof(VOTOS[0]);
//---------------------------------------------------------------------------------------|

void sortear_tema_complexo(char *destino, size_t tam_max, const char *prefixo) {
    int acao = rand() % TOTAL_ACOES;
    int tema1 = rand() % TOTAL_TEMAS;
    int tema2 = rand() % TOTAL_TEMAS;

    if (prefixo && strlen(prefixo) > 0) {
        snprintf(destino, tam_max, "%s %s de %s de %s", prefixo, ACOES_BASE[acao], TEMAS_BASE[tema1], TEMAS_BASE[tema2]);
    } else {
        snprintf(destino, tam_max, "%s de %s de %s", ACOES_BASE[acao], TEMAS_BASE[tema1], TEMAS_BASE[tema2]);
    }
}

int sortear_id_existente(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return (rand() % 5) + 1; 

    int ids[100];
    int qtd = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), f) && qtd < 100) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        int id = atoi(linha);
        if (id > 0) ids[qtd++] = id;
    }
    fclose(f);

    if (qtd == 0) return (rand() % 5) + 1;
    return ids[rand() % qtd];
}

int estava_ausente(int id_reuniao, int id_vereador) {
    FILE *f = fopen("presenca.txt", "r");
    if (!f) return 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        
        int id_p, r_id, v_id;
        char status[20];
        if (sscanf(linha, "%d;%d;%d;%19s", &id_p, &r_id, &v_id, status) >= 4) {
            if (r_id == id_reuniao && v_id == id_vereador) {
                if (strstr(status, "ausente") != NULL) {
                    fclose(f);
                    return 1; 
                }
            }
        }
    }
    fclose(f);
    return 0; // Não ausente
}

int carregar_todos_ids(const char *caminho, int ids[], int max_ids) {
    FILE *f = fopen(caminho, "r");
    if (!f) return 0;

    int qtd = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), f) && qtd < max_ids) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        int id = atoi(linha);
        if (id > 0) ids[qtd++] = id;
    }
    fclose(f);
    return qtd;
}

int estava_presente(int id_reuniao, int id_vereador) {
    FILE *f = fopen("presenca.txt", "r");
    if (!f) return 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') continue;
        
        int id_p, r_id, v_id;
        char status[20];
        if (sscanf(linha, "%d;%d;%d;%19s", &id_p, &r_id, &v_id, status) >= 4) {
            if (r_id == id_reuniao && v_id == id_vereador) {
                if (strcmp(status, "presente") == 0) {
                    fclose(f);
                    return 1;
                }
            }
        }
    }
    fclose(f);
    return 0;
}

void gerar_presencas_completas() {
    int v_ids[100], r_ids[100];
    int total_v = carregar_todos_ids("OsCapaPreta.txt", v_ids, 100);
    int total_r = carregar_todos_ids("reunioes.txt", r_ids, 100);

    for (int r = 0; r < total_r; r++) {
        for (int v = 0; v < total_v; v++) {
            int id;
            do {
                id = (rand() % 90000) + 10000;
            } while (id_existe("presenca.txt", id));

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%05d;%d;%d;%s\n", 
                     id, r_ids[r], v_ids[v], STATUS_PRESENCA[rand() % TOTAL_PRESENCA]);
            escrever("presenca.txt", buffer);
        }
    }
}

void gerar_votacoes_completas() {
    int v_ids[100], r_ids[100], p_ids[100];
    int total_v = carregar_todos_ids("OsCapaPreta.txt", v_ids, 100);
    int total_r = carregar_todos_ids("reunioes.txt", r_ids, 100);
    int total_p = carregar_todos_ids("projetos.txt", p_ids, 100);

    if (total_p == 0) return;

    for (int r = 0; r < total_r; r++) {
        // Vincula um projeto a cada reunião
        int id_projeto = p_ids[r % total_p];

        for (int v = 0; v < total_v; v++) {
            // Apenas quem estava 'presente' vota
            if (estava_presente(r_ids[r], v_ids[v])) {
                int id;
                do {
                    id = (rand() % 90000) + 10000;
                } while (id_existe("votacao.txt", id));

                char buffer[256];
                snprintf(buffer, sizeof(buffer), "%05d;%03d;%d;%d;%s\n", 
                         id, id_projeto, r_ids[r], v_ids[v], VOTOS[rand() % TOTAL_VOTOS]);
                escrever("votacao.txt", buffer);
            }
        }
    }
}

void limpar_arquivo(const char *caminho) {
    FILE *f = fopen(caminho, "w");
    if (f) fclose(f);
}

void gera_random(const char *caminho, int qtd) {
    if (!caminho) return;

    for (int i = 0; i < qtd; i++) {
        // ID TA FUNCIONANDO NAO MEXE PORFAVOR <---------------
        int id;
        do {
            id = (rand() % 9000) + 1000;
        } while (id_existe(caminho, id));

        char buffer[256];

        if (strcmp(caminho, "OsCapaPreta.txt") == 0) {
            // ESQUEMA: id_vereador;nome;partido;email
            int n1 = rand() % TOTAL_NOMES, n2 = rand() % TOTAL_NOMES, n3 = rand() % TOTAL_NOMES;
            char nome[60], email[50];
            
            snprintf(nome, sizeof(nome), "%s %s %s", NOMES_BASE[n1], NOMES_BASE[n2], NOMES_BASE[n3]);
            snprintf(email, sizeof(email), "%c%c%c%d@%s", 
                     tolower(NOMES_BASE[n1][0]), tolower(NOMES_BASE[n2][0]), tolower(NOMES_BASE[n3][0]), 
                     id % 100, DOMINIOS[rand() % TOTAL_DOMINIOS]);

            snprintf(buffer, sizeof(buffer), "%d;%s;%s;%s\n", 
                     id, nome, PARTIDOS[rand() % TOTAL_PARTIDOS], email);

        } else if (strcmp(caminho, "reunioes.txt") == 0) {
            // ESQUEMA: id_reuniao;data_reuniao;hora;pauta
            char pauta[100];
            sortear_tema_complexo(pauta, sizeof(pauta), "Debate sobre");

            int dia = (rand() % 28) + 1;
            int mes = (rand() % 12) + 1;
            int hora = (rand() % 8) + 9;

            snprintf(buffer, sizeof(buffer), "%d;%02d/%02d/2026;%02d:00;%s\n", 
                     id % 100, dia, mes, hora, pauta);

        } else if (strcmp(caminho, "projetos.txt") == 0) {
            // ESQUEMA: id_proj;titulo;id_autor;data_mostra;categoria;status
            char titulo[100];
            sortear_tema_complexo(titulo, sizeof(titulo), "PL");

            // Pega um ID real de um vereador cadastrado
            int id_autor = sortear_id_existente("OsCapaPreta.txt"); 
            int dia = (rand() % 28) + 1;
            int mes = (rand() % 12) + 1;

            snprintf(buffer, sizeof(buffer), "%03d;%s;%d;%02d/%02d/2026;%s;%s\n", 
                     id % 1000, titulo, id_autor, dia, mes, 
                     CATEGORIAS[rand() % TOTAL_CATEGORIAS], STATUS_PROJ[rand() % TOTAL_STATUS_PROJ]);

        } else if (strcmp(caminho, "presenca.txt") == 0) {
            // ESQUEMA: id_presenca;id_reuniao;id_vereador;status_presenca
            int id_reuniao = sortear_id_existente("reunioes.txt");
            int id_vereador = sortear_id_existente("OsCapaPreta.txt");

            snprintf(buffer, sizeof(buffer), "%05d;%d;%d;%s\n", 
                     id, id_reuniao, id_vereador, STATUS_PRESENCA[rand() % TOTAL_PRESENCA]);

        } else if (strcmp(caminho, "votacao.txt") == 0) {
            // ESQUEMA: id_votacao;id_projeto;id_reuniao;id_vereador;voto
            int id_projeto = sortear_id_existente("projetos.txt");
            int id_reuniao = sortear_id_existente("reunioes.txt");
            int id_vereador;
            int tentativas = 0;

            // Sorteia vereadores até achar um que NÃO esteve ausente na reunião
            do {
                id_vereador = sortear_id_existente("OsCapaPreta.txt");
                tentativas++;
            } while (estava_ausente(id_reuniao, id_vereador) && tentativas < 30);

            snprintf(buffer, sizeof(buffer), "%05d;%03d;%d;%d;%s\n", 
                     id, id_projeto, id_reuniao, id_vereador, VOTOS[rand() % TOTAL_VOTOS]);

        } else {
            printf("Arquivo desconhecido: %s\n", caminho);
            return;
        }

        escrever(caminho, buffer);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    //limpar_arquivo("OsCapaPreta.txt"); 
    //limpar_arquivo("reunioes.txt");
    //limpar_arquivo("projetos.txt");
    //limpar_arquivo("presenca.txt");
    //limpar_arquivo("votacao.txt");

    printf("Gerando registros aleatorios abubulé de teste...\n");
    int qtd = 5;
    gera_random("OsCapaPreta.txt", qtd);
    gera_random("reunioes.txt", qtd);
    gera_random("projetos.txt", qtd);

    gerar_presencas_completas();
    gerar_votacoes_completas();

    printf("Carregando arquivos...\n");

    Vereador *lista_vereadores = carregar_vereadores("OsCapaPreta.txt");
    Reuniao  *lista_reunioes   = carregar_reunioes("reunioes.txt");
    Projeto  *lista_projetos   = carregar_projetos("projetos.txt");
    Presenca *lista_presencas  = carregar_presencas("presenca.txt");
    Votacao  *lista_votacoes   = carregar_votacoes("votacao.txt");

    if (lista_vereadores){
        exibir_vereadores(lista_vereadores);
    }else printf("\n[OPA OPA OPA] Nao foi possivel carregar 'OsCapaPreta.txt'\n");

    if (lista_reunioes){
        exibir_reunioes(lista_reunioes);
    }else printf("\n[OPA OPA OPA] Nao foi possivel carregar 'reunioes.txt'\n");

    if (lista_projetos) {
        exibir_projetos(lista_projetos);
    }else printf("\n[OPA OPA OPA] Nao foi possivel carregar 'projetos.txt'\n");

    if (lista_presencas) {
        exibir_presencas(lista_presencas);
    }else printf("\n[OPA OPA OPA] Nao foi possivel carregar 'presenca.txt'\n");

    if (lista_votacoes) {
        exibir_votacoes(lista_votacoes);
    }else printf("\n[OPA OPA OPA] Nao foi possivel carregar 'votacao.txt'\n");

    //NÃO APAGAR EM HIPOTESE ALGUMA, LIBERE TUDO E TODOS OU FICARÁ SEM RAM ETERNAMENTE ATÉ O FIM DOS TEMPOS
    liberar_vereadores(lista_vereadores);
    liberar_reunioes(lista_reunioes);
    liberar_projetos(lista_projetos);
    liberar_presencas(lista_presencas);
    liberar_votacoes(lista_votacoes);

    printf("\nMemoria liberada com sucesso. Voce não vai ficar sem ram\n");
    return 0;
}