//Copyright Andrei Sugubete 315CAb 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vect {
	int x, y;
	short **v;
	struct vect *next;
} vect;

short s_siz = sizeof(short);
short p_siz = sizeof(short *);
short v_siz = sizeof(vect);
short i_siz = sizeof(int);

//Copiaza continutul structurii a in structura tinta

void copiere_vect(vect *a, vect *tinta)
{
	tinta->x = a->x;
	tinta->y = a->y;
	tinta->v = malloc(tinta->x * p_siz);
	for (int i = 0; i < tinta->x; i++) {
		tinta->v[i] = malloc(tinta->y * s_siz);
		for (int j = 0; j < tinta->y; j++)
			tinta->v[i][j] = a->v[i][j];
	}
}

//Dezaloca matricea bidimensionala de la adresa v, care are x linii

void dezalocare_matrice(short **v, int x)
{
	for (int i = 0; i < x; i++)
		free(v[i]);
	free(v);
}

//Intoarce adresa celui de al i-lea vector alocat dinamic
// de la innot spre dreapta

vect *go_to(vect *innot, int i)
{
	while (i > 0) {
		innot = (*innot).next;
		i--;
	}
	return innot;
}

//Citeste si atribuie toate elementele unei structuri v de tip vect

void citire(vect *v)
{
	scanf("%d%d", &v->x, &v->y);
	v->v = malloc(v->x  * p_siz);
	for (int i = 0; i < v->x; i++) {
		v->v[i] = malloc(v->y  * s_siz);
		for (int j = 0; j < v->y; j++)
			scanf("%hd", &v->v[i][j]);
	}
}

//Afiseaza toate elementele matricii aferente unei
// variabile v de tip struct vect

void afisare(vect *v)
{
	for (int i = 0; i < v->x; i++) {
		for (int j = 0; j < v->y; j++)
			printf("%hd ", v->v[i][j]);
		printf("\n");
	}
}

//Redimensioneaza conform cerintelor
// matricea bidimensionala din variabila v

void redimensionare(vect *v)
{
	//Citiri si declarari
	int l, c, *il, *ic;
	short **rez;
	scanf("%d", &l);
	il = malloc(l  * i_siz);
	for (int i = 0; i < l; i++)
		scanf("%d", &il[i]);
	scanf("%d", &c);
	ic = malloc(i_siz * c);
	for (int i = 0; i < c; i++)
		scanf("%d", &ic[i]);
	//Redimensionare
	rez = malloc(l * p_siz);
	for (int i = 0; i < l; i++) {
		rez[i] = malloc(c * s_siz);
		for (int j = 0; j < c; j++)
			rez[i][j] = v->v[il[i]][ic[j]];
	}
	dezalocare_matrice(v->v, v->x);
	v->x = l;
	v->y = c;
	v->v = rez;
	free(il);
	free(ic);
}

//Inmulteste doua matrici bidimensionale si pune rezultatul in rez

void inmultire(vect *x, vect *y, vect *rez)
{
	rez->x = x->x;
	rez->y = y->y;
	rez->v = malloc(p_siz  * x->x);
	for (int i = 0; i < rez->x; i++) {
		rez->v[i] = calloc(y->y, s_siz);
		for (int j = 0; j < rez->y; j++) {
			for (int k = 0; k < x->y; k++)
				rez->v[i][j] = (x->v[i][k] * y->v[k][j] + rez->v[i][j]) % 10007;
			while (rez->v[i][j] < 0)
				rez->v[i][j] += 10007;
		}
	}
}

//Intoarce suma tututor elementelor din
// matricea bidimensionala aferenta lui v, modulo 10007

long suma(vect *v)
{
	long rez = 0;
	for (int i = 0; i < v->x; i++) {
		for (int j = 0; j < v->y; j++)
			rez += v->v[i][j];
	}
	while (rez < 0)
		rez += 10007;
	return (short)(rez % 10007);
}

//Interschimba continutul a doua variabile tip struct vect

void interschimba(vect *a, vect *b)
{
	a = a->next; b = b->next;
	short **v;
	v = a->v;
	a->v = b->v;
	b->v = v;
	int tmp = a->x;
	a->x = b->x;
	b->x = tmp;
	tmp = a->y;
	a->y = b->y;
	b->y = tmp;
}

//Efectueaza sortarea a 'siruri' variabile de tip struct vect, incepand de la v

void sortare(vect *v, int siruri)
{
	short *sume = malloc(s_siz * siruri);
	vect *tmp, *tmp2 = v;
	int tmp3;
	//aflam toate sumele
	tmp = v->next;
	for (int i = siruri - 1; i >= 0; i--) {
		sume[siruri - i - 1] = suma(tmp);
		tmp = tmp->next;
	}
	//facem interschimbarile
	for (int i = 0 ; i < siruri - 1; i++) {
		tmp = tmp2->next;
		for (int j = i + 1; j < siruri; j++) {
			if (sume[i] > sume[j]) {
				interschimba(tmp2, tmp);
				tmp3 = sume[i];
				sume[i] = sume[j];
				sume[j] = tmp3;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	free(sume);
}

//Efectueaza traspunerea matricii aferente variabilei v

void transpunere(vect *v)
{
	short **rez = malloc(v->y * p_siz);
	for (int j = 0 ; j < v->y; j++) {
		rez[j] = malloc(v->x * s_siz);
		for (int i = 0; i < v->x; i++)
			rez[j][i] = v->v[i][j];
	}
	dezalocare_matrice(v->v, v->x);
	v->v = rez;
	int tmp = v->x;
	v->x = v->y;
	v->y = tmp;
}

//Ridica la o putere matricea aferenta variabilei v

void ridica_putere(vect *v, int putere)
{
	while (putere > 1) {
		vect *k1 = malloc(v_siz), *k2 = malloc(v_siz);
		//copiem valorile lui v in k1
		copiere_vect(v, k1);
		dezalocare_matrice(v->v, v->x);
		//efectuam inmultirile
		if (putere % 2 == 0) {
			inmultire(k1, k1, v);
			putere /= 2;
		} else {
			inmultire(k1, k1, k2);
			inmultire(k1, k2, v);
			putere = (putere - 1) / 2;
			dezalocare_matrice(k2->v, k2->x);
		}
		//dezalocare
		dezalocare_matrice(k1->v, k1->x);
		free(k1);
		free(k2);
	}
}

//In caz ca nu sunt indeplinite cerintele de redimensionare,
//aceasta functie este apelata pentru a sari peste
//datele ramase de citit, fara a le prelucra.

void redimensionare_else(void)
{
	printf("No matrix with the given index\n");
	int l, *il;
	scanf("%d", &l);
	il = malloc(l * i_siz);
	for (int i = 0; i < l; i++)
		scanf("%d", &il[i]);
	free(il);
	scanf("%d", &l);
	il = malloc(l * i_siz);
	for (int i = 0; i < l; i++)
		scanf("%d", &il[i]);
	free(il);
}

//Efectueaza actiunile necesarii query ului de inmultire

void f_inmultire(int *sirurinot, vect *innot, vect *teletmpt)
{
	int notnr, notnr2;
	scanf("%d%d", &notnr, &notnr2);
	int r1 = notnr < *sirurinot && notnr >= 0;
	int r2 = notnr2 < *sirurinot && notnr2 >= 0;
	if (r1 && r2) {
		vect *k1 = go_to(innot, notnr), *k2 = go_to(innot, notnr2);
		if (k1->y == k2->x) {
			teletmpt = go_to(innot, *sirurinot - 1);
			inmultire(k1, k2, teletmpt->next);
			*sirurinot += 1;
			teletmpt->next->next = malloc(v_siz);
		} else {
			printf("Cannot perform matrix multiplication\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

//Efectueaza actiunile necesarii query ului de transpunere

void f_transpunere(int *sirurinot, vect *innot, vect *teletmpt)
{
	int notnr;
	scanf("%d", &notnr);
	if (notnr < *sirurinot && notnr >= 0) {
		teletmpt = go_to(innot, notnr);
		transpunere(teletmpt);
	} else {
		printf("No matrix with the given index\n");
	}
}

//Efectueaza actiunile necesarii
// query ului de eliberare a unei matrici

void f_elib_mat(int *sirurinot, vect *innot, vect *teletmpt, vect *tmhax)
{
	int notnr;
	scanf("%d", &notnr);
	if (notnr < *sirurinot && notnr >= 0) {
		teletmpt = go_to(innot, notnr);
		dezalocare_matrice(teletmpt->v, teletmpt->x);
		teletmpt->v = teletmpt->next->v;
		teletmpt->x = teletmpt->next->x;
		teletmpt->y = teletmpt->next->y;
		tmhax = teletmpt->next->next;
		free(teletmpt->next);
		teletmpt->next = tmhax;
		*sirurinot -= 1;
		if (notnr == *sirurinot - 1 && !teletmpt->next)
			teletmpt->next = malloc(v_siz);
	} else {
		printf("No matrix with the given index\n");
	}
}

//Efectueaza actiunile necesarii query ului
// de afisare a dimensiunii unei matrici

void f_afisare_dimensiune(int *sirurinot, vect *innot, vect *teletmpt)
{
	int notnr;
	scanf("%d", &notnr);
	if (notnr < *sirurinot && notnr >= 0) {
		teletmpt = go_to(innot, notnr);
		printf("%d %d\n", teletmpt->x, teletmpt->y);
	} else {
		printf("No matrix with the given index\n");
	}
}

//Efectueaza actiunile necesarii query ului de ridicare la putere in timp
//logaritmic al matricii specificate

void putere_logaritmica(int *sirurinot, vect *innot, vect *teletmpt)
{
	int a, b;
	scanf("%d%d", &a, &b);
	if (a < *sirurinot && a >= 0) {
		if (b > 0) {
			teletmpt = go_to(innot, a);
			if (teletmpt->x == teletmpt->y)
				ridica_putere(teletmpt, b);
			else
				printf("Cannot perform matrix multiplication\n");
		} else {
			printf("Power should be positive\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

int main(void)
{
	char s[10];
	int continu = 1, siruri = 0, tmpnr;
	vect *init = malloc(v_siz), *tmp, *tmpx;
	while (continu) {
		scanf("%s", s);
		switch (s[0]) {
		case 'L': //citire vector
			tmp = go_to(init, siruri);
			siruri++;
			tmp->next = malloc(v_siz);
			citire(tmp);
			break;
		case 'D': //afisare dimensiuni
			f_afisare_dimensiune(&siruri, init, tmp);
			break;
		case 'P': //afisare vector
			scanf("%d", &tmpnr);
			if (tmpnr < siruri && tmpnr >= 0) {
				tmp = go_to(init, tmpnr);
				afisare(tmp);
				break;
			}
			printf("No matrix with the given index\n");
			break;
		case 'C': //redimensionare
			scanf("%d", &tmpnr);
			if (tmpnr < siruri && tmpnr >= 0) {
				tmp = go_to(init, tmpnr);
				redimensionare(tmp);
				break;
			}
			redimensionare_else();
			break;
		case 'M': //inmultire
			f_inmultire(&siruri, init, tmp);
			break;
		case 'O': //sortare
			tmpx = malloc(v_siz);
			tmpx->next = init;
			sortare(tmpx, siruri);
			init = tmpx->next;
			free(tmpx);
			break;
		case 'T': //transpunere
			f_transpunere(&siruri, init, tmp);
			break;
		case 'R': //Ridicare putere logaritmic
			putere_logaritmica(&siruri, init, tmp);
			break;
		case 'F': //eliberare memorie matrice
			f_elib_mat(&siruri, init, tmp, tmpx);
			break;
		case 'Q': //eliberarea tuturor matricilor + STOP
			continu = 0;
			while (siruri > 0) {
				tmp = init;
				dezalocare_matrice(init->v, init->x);
				init = init->next;
				free(tmp);
				siruri--;
			}
			free(init);
			break;
		case 'S': //Inmultire matrici Strassen
			scanf("%d%d", &tmpnr, &tmpnr);
			printf("Unrecognized command\n");
			break;
		default:  //Comanda nerecunoscuta
			printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
