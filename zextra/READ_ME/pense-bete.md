Penser à rajouter la *link option* **-pthread** lors de la compilation. Car la lib de pthread nécessite une liason explicite.

`-lpthread` : Lie seulement la bibliothèque *(libpthread.so)*.

`-pthread` : Lie la bibliothèque et configure **les macros/paramètres** de compilation pour le multithreading.

Penser a protéger le pthread_create. 
Si ca renvoie quelque chose different de 0 c'est qu'il y a eu une erreur sinon c'st que c'est que ca a fonctionné.
Pareil pour pthread_join.