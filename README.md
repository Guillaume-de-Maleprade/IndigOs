Malloc() et free()

Conception
==========

Idées de conception
-------------------

Pour développer les fonction <code>malloc()</code> et <code>free()</code> nous avons implémenté une liste chaînée, stockant une liste de zones mémoire allouées ou libres.

Conception en liste chaînée
---------------------------

Nous avons créé une structure *node* contenant

-   <code>next</code> : Node suivante
-   <code>size</code> : Taille de l’élément contenu dans la node ou de la mémoire libre
-   <code>addr</code> : Adresse de l’élément à renvoyer
-   <code>allocated</code>: Booléen pour savoir si la *node* est allouée ou non.

N’ayant pas d’allocation dynamique puisque nous la développons, il nous faut un moyen de pouvoir allouer de la mémoire dans notre zone mémoire totale. L’adresse mémoire renvoyée par le malloc étant la case mémoire libre et non la case mémoire de la structure. Il nous fallait un moyen de stocker nos structures.

Nous avions deux choix :

-   Réserver tout une zone mémoire ou nous stockions seulement les données de la structure.
-   Ajouter la structure *node* juste avant la mémoire qu’il peut allouer / alloue.

Nous avons choisi la 2<sup>e</sup> option car en connaissant la taille que prend la structure, nous pouvons à l’aide d’une adresse de mémoire libre que l’on a renvoyée, retrouver l’adresse de la structure avec une simple soustraction !

Une fois ces problèmes de conception résolus, nous nous sommes attaqués au développement.

Développement
=============

### Nous avons utilisé plusieurs fonctions :

Initialisation de la liste
```c
void createList();
```

Retourne MY_NULL  s’il n’y a pas assez de mémoire disponible ou une node s’il trouve une case (la fonction va chercher la case la plus petite suffisante) :
```c
node * checkMemFree(size_m);
```

Crée une nouvelle node de la bonne taille et une node plus petite libre si l’espace est trop grand. Sinon renvoie directement la node de la bonne taille :
```c
node * allocate(void *, size_m);
```

Permet de parcourir et combiner des nodes libres consécutives en une seule grande : 
```c
node *combineFreeNodes();
```

Equivaut à la fonction free() à développer :
```c
void mem_free(void *); 
```

Equivaut à la fonction malloc() à développer :
```c
void * mem_alloc(size_m);
```

Affiche l’état actuel de la mémoire (aide pour dev) :
```c
void checkMemory();
```

Tests
=====

Nous avons une séquence de tests qui va fonctionner comme ceci

1.  Allocation d’une mémoire totale de 4096
2.  Création des 3 premières nodes de taille 512, 256 et 1024 (3 mem_alloc)
3.  Libération de la 3<sup>e</sup> node
4.  Combinaison des deux nodes consécutives libérées (lors de l'utilisation de <code>mem_free(void *)</code> )

1.  Allocation d’une mémoire supérieure à des cases de mémoire libre disponibles

Pour simplifier le développement, l’allocation se fait à la fin (« à droite ») de la zone mémoire libre trouvée.

Perspectives d’améliorations
============================

Supprimer la variable *addr* car nous connaissons la taille exacte de notre structure. Nous pouvons donc la calculer aisément (on passerait d’une taille de 16 octets à 12 octets par *node*).


Lancement
=========

Dans une invite de commande, lancer `go.cmd`
