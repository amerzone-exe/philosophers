# Explication des fonctions pthread

## 1. `pthread_create`
Cette fonction permet de créer un **nouveau thread** qui exécute une fonction donnée.

### **Prototype**
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg);
```

### **Exemple**
```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine(void *arg) {
    printf("Thread lancé !\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, routine, NULL);
    pthread_join(thread, NULL);  // Attend que le thread se termine
    return 0;
}
```

---

## 2. `pthread_detach`
Permet de **détacher** un thread, c'est-à-dire qu'il ne pourra plus être rejoint (`pthread_join`).

### **Prototype**
```c
int pthread_detach(pthread_t thread);
```

### **Exemple**
```c
pthread_t thread;
pthread_create(&thread, NULL, routine, NULL);
pthread_detach(thread);
```
🚨 **Attention** : Une fois détaché, on ne peut plus utiliser `pthread_join` sur ce thread !

---

## 3. `pthread_join`
Permet d'**attendre** la fin d'un thread.

### **Prototype**
```c
int pthread_join(pthread_t thread, void **retval);
```

### **Exemple**
```c
pthread_t thread;
pthread_create(&thread, NULL, routine, NULL);
pthread_join(thread, NULL);
```
🔥 **Cas d'usage** : Éviter que le programme ne se termine avant que les threads aient fini leur travail.

---

## 4. `pthread_mutex_init`
Crée un **mutex** (verrou) pour protéger une section critique dans un programme multithreadé.

### **Prototype**
```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```

### **Exemple**
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
```

---

## 5. `pthread_mutex_destroy`
Détruit un **mutex** pour libérer les ressources système associées.

### **Prototype**
```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

### **Exemple**
```c
pthread_mutex_destroy(&mutex);
```
⚠ **Important** : Détruire un mutex uniquement quand plus aucun thread ne l'utilise.

---

## 6. `pthread_mutex_lock`
Verrouille un **mutex** pour empêcher d'autres threads d'accéder à une section critique.

### **Prototype**
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

### **Exemple**
```c
pthread_mutex_lock(&mutex);
```

---

## 7. `pthread_mutex_unlock`
Déverrouille un **mutex** pour permettre aux autres threads d'y accéder.

### **Prototype**
```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

### **Exemple**
```c
pthread_mutex_unlock(&mutex);
```

---

# **Exemple Complet d'utilisation des Mutex et Threads**

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;  // Déclaration d'un mutex

void *routine(void *arg) {
    pthread_mutex_lock(&mutex);  // Verrouille la ressource
    printf("Thread %ld : Accès à la ressource protégée\n", (long)arg);
    sleep(1);  // Simulation d'un traitement long
    printf("Thread %ld : Libération de la ressource\n", (long)arg);
    pthread_mutex_unlock(&mutex);  // Libère la ressource
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);  // Initialisation du mutex

    pthread_create(&thread1, NULL, routine, (void *)1);
    pthread_create(&thread2, NULL, routine, (void *)2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);  // Destruction du mutex
    return 0;
}
```

---

# **Résumé des pthreads**

| Fonction | Description |
|----------|------------|
| `pthread_create` | Crée un thread |
| `pthread_detach` | Détache un thread (pas besoin de `pthread_join`) |
| `pthread_join` | Attend la fin d'un thread |
| `pthread_mutex_init` | Initialise un mutex |
| `pthread_mutex_destroy` | Détruit un mutex |
| `pthread_mutex_lock` | Verrouille un mutex |
| `pthread_mutex_unlock` | Déverrouille un mutex |

---

Si tu veux d'autres précisions ou un autre exemple, dis-moi ! 😊

