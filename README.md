# PCLP1_Tema2
PCLP1 Tema 2
Copyright Andrei Sugubete 315CAb 2022-2023
Autor: Sugubete Andrei

Mod de implementare si functionare:
- Matricile sunt stocate in mod dinamic in structuri de date care contin:
a. numarul de linii ale matricii
b. numarul de coloane ale liniilor matricii
c. adresa la care este stocata matricea
- De asemenea, retinem doar adresele la care sunt stocate matricile,
pentru a putea sa le dezalocam si alocam in mod integral
- Implementarea comenzilor este facuta sub forma de query uri, in care
citim doar prima litera si folosim un switch in functie de aceasta

Instructiuni de utilizare:
- Compilare cu comanda "make"
- Executare cu "./my_octave"
- Introduceti date conform instructiunilor:
* L -> citeste o matrice
* D -> afiseaza dimensiunile unei matrici
* P -> afiseaza continutul unei matrici
* C -> redimensioneaza o matrice
* M -> inmulteste 2 matrici si o adauga la lista de matrici la final
* O -> sorteaza in functie de suma toate matricile
* T -> transpune continutul unei matrici
* R -> ridica la o putere data o matrice
* F -> elibereaza memoria unei matrici
* Q -> elibereaza memoria tuturor matricilor si inchide programul
* S -> inmulteste 2 matrici cu algoritmul lui Strassen
* Orice altceva -> comanda nerecunoscuta, afiseaza o eroare
