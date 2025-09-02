


# Les threads ?

Les threads se **partage la mémoire virtuelle** d'un même processus.
Il permet d'effectuer plusieurs tâches en même temps. 
*Par exemple faire une correction orthographique pendant que l'utiliseur continu de taper.*
*C'est pour ca que la plupart des logiciels de traitement de texte utilise un thread spécifique pour les input de l'utilisateur.*

Comme il n'y pas de changement de mémoire virtuelle la **communication de contexte** est moins coûteuse en temps, que la commutation de contexte entre deux processus.

Pour **créer un threads** on doit définir un endroit ou on va **stocker certaines informations** à propos du thread. On va donc utilisé une variable de type `pthread_t`.

Pour initialiser un thread on va utilisé la fonction `pthread_create` qui a pour prototype :

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg);
```

# Le Mutex (*Mutual exclusion*)

Un Mutex est utilisé en informatique pour que **les ressources partagées** d'un système ne soit **pas utilisé en même temps**.

Cela permet dans le cas d'utilisation de **plusieurs threads** de réguler l'accés a certaines données en parallèles.

# Sémaphore

Un **sémaphore** est une variable partagée par différent "acteur" (*en l'occurence des **threads** dans le cas de <u>Philosophers</u>*)

# Différence entre Mutex & Sémaphore :

<img src="https://d8it4huxumps7.cloudfront.net/bites/wp-content/banners/2024/8/66d1a49234ad3_difference_between_mutex_and_semaphore.jpg?d=1200x800" alt="Logo" width="500">

# Programmation concurrente

C'est le fait de partager **differentes tâches** au processus donnant une impression de parallèlisme. 
En fait ce que va faire le processeur c'est qu'il va **travailler independament** sur chaques taches petit à petit pour que tout avance en même temps.

# Race condition

