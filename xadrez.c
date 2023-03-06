#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define RES "\e[0m"

int ch2int(char ch) {
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    int retnum = (int) strtol(str, NULL, 10);
    return retnum;
}

void clrcon() {
	puts("\e[1;1H\e[2J");
}

void tabuleiro() {
	/* Criação do tabuleiro */

	char tabuleiro[8][8][3];
	char letra = 'a';

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			sprintf(&tabuleiro[x][y][0], "%c%d", letra, y + 1);
		}

		letra == 'h' ? letra = 'a' : letra++;
	}

	char cavalobranco1[3] = "b1";
	char cavalobranco2[3] = "g1";
	char bispobranco1[3] = "c1";
	char bispobranco2[3] = "f1";
	char torrebranco1[3] = "a1";
	char torrebranco2[3] = "h1";
	char rainhabranco[3] = "d1";
	char reibranco[3] = "e1";
	char peoesbranco[8][3] = {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"};

	char cavalopreto1[3] = "g8";
	char cavalopreto2[3] = "b8";
	char bispopreto1[3] = "f8";
	char bispopreto2[3] = "c8";
	char torrepreto1[3] = "h8";
	char torrepreto2[3] = "a8";
	char rainhapreto[3] = "d8";
	char reipreto[3] = "e8";
	char peoespreto[8][3] = {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"};

	char * pecasbrancas[] = {cavalobranco1, cavalobranco2, bispobranco1, bispobranco2, torrebranco1, torrebranco2, rainhabranco, reibranco};
	char * pecaspretas[] = {cavalopreto1, cavalopreto2, bispopreto1, bispopreto2, torrepreto1, torrepreto2, rainhapreto, reipreto};

	int ispawn;
	int vezbranco = 1;
	int quantbranco = 0;
	int vezpreto = 0;
	int quantpreto = 0;

	/* Jogo */

	// Mostrar tabuleiro e validar sintaxe do lance

	char lance[4];
	char iniciais[] = {'b', 'r', 'q', 'n', 'k'};
	int invalido = 1;
	int vazio = 1;
	char coord[3];
	char peca;
	int isblack;

	inputlance:
	while (1) {
		clrcon();

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				for (int z = 0; z < 8; z++) {
					if (pecasbrancas[z][0] == tabuleiro[x][y][0] && pecasbrancas[z][1] == tabuleiro[x][y][1]) {
						vazio = 0;
						if (pecasbrancas[z] == pecasbrancas[0] || pecasbrancas[z] == pecasbrancas[1]) {
							peca = 'N';
						}
						else if (pecasbrancas[z] == pecasbrancas[2] || pecasbrancas[z] == pecasbrancas[3]) {
							peca = 'B';
						}
						else if (pecasbrancas[z] == pecasbrancas[4] || pecasbrancas[z] == pecasbrancas[5]) {
							peca = 'R';
						}
						else if (pecasbrancas[z] == pecasbrancas[6]) {
							peca = 'Q';
						}
						else if (pecasbrancas[z] == pecasbrancas[7]) {
							peca = 'K';
						}
					}
					else if (pecaspretas[z][0] == tabuleiro[x][y][0] && pecaspretas[z][1] == tabuleiro[x][y][1]) {
						isblack = 1;
						vazio = 0;
						if (pecaspretas[z] == pecaspretas[0] || pecaspretas[z] == pecaspretas[1]) {
							peca = 'N';
						}
						else if (pecaspretas[z] == pecaspretas[2] || pecaspretas[z] == pecaspretas[3]) {
							peca = 'B';
						}
						else if (pecaspretas[z] == pecaspretas[4] || pecaspretas[z] == pecaspretas[5]) {
							peca = 'R';
						}
						else if (pecaspretas[z] == pecaspretas[6]) {
							peca = 'Q';
						}
						else if (pecaspretas[z] == pecaspretas[7]) {
							peca = 'K';
						}
					}
					else if (peoesbranco[z][0] == tabuleiro[x][y][0] && peoesbranco[z][1] == tabuleiro[x][y][1]) {
						vazio = 0;
						peca = 'p';
					}
					else if (peoespreto[z][0] == tabuleiro[x][y][0] && peoespreto[z][1] == tabuleiro[x][y][1]) {
						isblack = 1;
						vazio = 0;
						peca = 'p';
					}
				}
				if (vazio == 0) {
					isblack == 1 ? printf("%s%c%s   ", RED, peca, RES) : printf("%s%c%s   ", YEL, peca, RES);
					vazio = 1;
					isblack = 0;
				}
				else {
					printf("·   ");
				}
			}
			puts("\n");
		}

		vezbranco == 1 ? printf("\n:: %sBranco%s - Digite seu lance :: ", YEL, RES) : printf("\n::: %sPreto%s - Digite seu lance :: ", RED, RES);
		fgets(lance, 3, stdin);

		coord[0] = lance[1];
		coord[1] = lance[2];

		char placeholder[2];
		placeholder[0] = coord[1];
		placeholder[1] = '\0';

		int num = strtol(placeholder, NULL, 10);

		char placeholder2[2];
		placeholder2[0] = lance[1];
		placeholder2[1] = '\0';

		int num2 = strtol(placeholder2, NULL, 10);

		if (strlen(lance) == 2) {
			 if (tolower(lance[0]) >= 'a' && tolower(lance[0]) <= 'h') {
				if (num2 <= 9 && num2 >= 1) {
					invalido = 0;
					ispawn = 1;
					coord[0] = lance[0];
					coord[1] = lance[1];
					break;
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			if (tolower(lance[0]) == iniciais[i]) {
				invalido = 0;
				break;
			}
		}

		if (invalido == 1) {
			continue;
		}

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (tolower(coord[0]) == tabuleiro[x][y][0]) {
					invalido = 0;
					break;
				}
				else {
					invalido = 1;
				}
			}
			if (invalido == 0)
				break;
		}

		if (invalido == 1) {
			continue;
		}

		if (num > 9 || num < 1) {
			invalido = 1;
		}

		if (invalido == 1) {
			continue;
		}

		break;
	}
	/* Checar tabuleiro  */
	int ilegal = 1;

	if (ispawn == 1 && vezbranco == 1) {
		for (int i = 0; i < 8; i++) {
			if (coord[0] == peoesbranco[i][0] && ((ch2int(coord[1])-ch2int(peoesbranco[i][1])) == 1 || (ch2int(coord[1])-ch2int(peoesbranco[i][1])) == 2)) {
				ilegal = 0;
				if (ch2int(coord[1])-ch2int(peoesbranco[i][1]) == 2) {
					if (ch2int(peoesbranco[i][1]) == 2) {
						ilegal = 0;
					}
					else {
						ilegal = 1;
					}
				}
				if (ilegal == 0) {
					peoesbranco[i][0] = coord[0];
					peoesbranco[i][1] = coord[1];
					peoesbranco[i][2] = '\0';
					break;
				}
			}
		}
	}

	if (ispawn == 1 && vezpreto == 1) {
		for (int i = 0; i < 8; i++) {
			if (coord[0] == peoespreto[i][0] && ((ch2int(peoespreto[i][1])-ch2int(coord[1])) == 1 || (ch2int(peoespreto[i][1])-ch2int(coord[1])) == 2)) {
				ilegal = 0;
				peoespreto[i][0] = coord[0];
				peoespreto[i][1] = coord[1];
				peoespreto[i][2] = '\0';
				break;
			}
		}
	}

	if (vezbranco == 1 && ilegal == 0) {
		vezpreto = 1;
		vezbranco = 0;
		quantbranco++;
	}
	else if (vezpreto == 1 && ilegal == 0) {
		vezpreto = 0;
		vezbranco = 1;
		quantpreto++;
	}
	goto inputlance;
}


int main() {
	tabuleiro();
	return 0;
}

