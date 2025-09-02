// Tant que le philosophe est vivant ET qu’aucun autre philosophe n’est mort :
//     - Essayer de prendre les deux fourchettes :
//         - Attendre que la fourchette gauche soit disponible
//         - Réserver la fourchette gauche (changer son état)
//         - Afficher : "<timestamp> <id> has taken a fork"

//         - Attendre que la fourchette droite soit disponible
//         - Réserver la fourchette droite
//         - Afficher : "<timestamp> <id> has taken a fork"

//     - Manger :
//         - Afficher : "<timestamp> <id> is eating"
//         - Enregistrer l’heure actuelle comme "dernier repas"
//         - Dormir pendant `time_to_eat` (usleep)

//     - Relâcher les deux fourchettes :
//         - Changer leur état à "disponible"

//     - Dormir :
//         - Afficher : "<timestamp> <id> is sleeping"
//         - Dormir pendant `time_to_sleep`

//     - Penser :
//         - Afficher : "<timestamp> <id> is thinking"

//     - (Optionnel) Petite pause ou yield pour éviter 100% CPU
