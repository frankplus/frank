Un risolutore del sudoku scritto in ANSI C per console.
E' funzionante solo su windows perch� usa l'istruzione system("CLS"); e la funzione gotoxy per muoversi nella console.
per muoversi basta usare i tasti direzionali,
per inserire un valore si usano i tasti numerici,
per cancellare un valore premere zero, canc oppure backspace.
� possibile caricare una griglia gi� compilata presente nel file save_sudoku.txt, basta premere F2.
potete anche salvare una vostra griglia premendo F1 ma sovrascriver� quello precedente.
La Funzione calcola() usa un algoritmo che risolve il sudoku cercando la cella con meno valori possibili, inserisce un valore e fa una funzione ricorsiva.
la funzione ricorsiva va in fondo, fino a quando una cella non ha pi� nessun valore possibile oppure ha raggiunto la profondit� massima cio� quando il sudoku � completo.
By Pnb2Frank.