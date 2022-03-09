Test APD Practic 1

Subiect 1
Student: Hodoboc-Velescu Tudor
Grupa: 335CC

Am pornit de la un schelet de cod facut inainte, format din crearea si apelarea
thread-urilor, oprirea acestora, citirea input-urilor si functia thread_function.

Se preaiau numerele date ca argument folosind functia get_args. Pentru parsarea
argumentelor am creat o structura arguments. Se initializeaza vectorul initial
dupa regula data in enunt. Apoi se creaza si apeleaza thread-urile. Pentru fiecare
thread pun argumentele(id-ul, bariera etc) si apelez functia cu structura de
argumente data ca parametru. Pentru a ma asigura ca valorile thread-urilor vor
fi diferite, argumentele sunt stocate  intr-un vector. Iar apoi in main dau join
pentru a termina procesul. In functia thread_function, preiau argumentele, apoi
creez start-ul si end-ul pentru a delimita intervalul de lucru. Fiecare thread
isi parcurge intervalul cu un for si verifica daca valoarea curenta este cea
cautata. Daca da, se incrementeaza un contor de aparitii pe acest interval si o
suma partiala a indicilor pe acest interval. Se pune o bariera pentru a astepta
toate input-urile thread-urilor. Dupa thread-ul 0 ia toate rezultatele partiale
pentru fiecare thread(acestea sunt stocate intr-un vector partajat prin argumentele
date) si creaza rezultatele finale(numar final de aparitii si suma indicilor),
apoi le afiseaza.
