# ray-tr-hetic
# Comment Contribuer à ce Projet

Ce document guide tous les contributeurs pour assurer un processus de développement cohérent, propre et efficace. Suivre ces règles permet de lier notre travail sur GitHub à notre gestion de projet sur Jira.

## La Règle d'Or

**Ne jamais pousser de code directement sur la branche `main`.**

Toute modification de code, aussi petite soit-elle, doit passer par une Pull Request qui sera validée par au moins un autre membre de l'équipe.

## Notre Workflow Étape par Étape

Chaque nouvelle fonctionnalité, correction de bug ou tâche suit ce cycle de vie. La clé de notre projet Jira est **`RAY`**.

### 1. Démarrer une Tâche

1.  **Allez sur Jira :** Trouvez un ticket qui vous intéresse dans la colonne "À Faire" (To Do).
2.  **Assignez-vous le ticket.**
3.  **Déplacez le ticket** dans la colonne "En Cours" (In Progress). C'est le signal pour toute l'équipe que vous commencez le travail.

### 2. Préparer l'Environnement Local

Avant de commencer à coder, assurez-vous que votre branche `main` locale est parfaitement à jour avec le dépôt distant.

```bash
git switch main
git pull origin main
```

### 3. Créer une Branche de Travail

Créez une nouvelle branche à partir de `main`. Le nom de votre branche est **très important** car il fait le lien avec Jira.

**Convention de nommage :** `RAY-XX-description-courte`
- `RAY` : La clé de notre projet Jira.
- `XX` : Le numéro du ticket sur lequel vous travaillez.
- `description-courte` : Quelques mots en minuscules, séparés par des tirets, décrivant la tâche.

**Exemple pour le ticket `RAY-42` :**
```bash
git switch -c RAY-42-optimisation-calcul-vecteur
```

### 4. Coder et Faire un Commit Propre

Faites vos modifications. Lorsque vous êtes prêt à sauvegarder votre travail, créez un commit. Le message de commit est aussi **très important**.

**Convention pour le message de commit :** `RAY-XX: Description claire de la modification`

**Exemple :**
```bash
git add .
git commit -m "RAY-42: Optimisation du produit scalaire dans la classe Vector"
```

### 5. Pousser la Branche sur GitHub

Envoyez votre branche et vos commits sur le dépôt distant.

```bash
git push origin RAY-42-optimisation-calcul-vecteur
```

### 6. Créer une Pull Request (PR)

1.  Allez sur la page de votre dépôt GitHub.
2.  Un bandeau jaune vous proposera de créer une Pull Request pour la branche que vous venez de pousser. Cliquez sur **"Compare & pull request"**.
3.  **Titre :** Le titre doit être clair et commencer par la clé du ticket (ex: `RAY-42: Optimisation du calcul de vecteur`).
4.  **Description :** Ajoutez un lien vers le ticket Jira et décrivez brièvement les changements.
5.  **Reviewers :** Dans le menu de droite, assignez au moins un autre membre de l'équipe pour relire votre code.
6.  Cliquez sur **"Create pull request"**.

### 7. Revue de Code et Fusion

- **L'auteur de la PR** attend les retours. Il ne fusionne JAMAIS sa propre PR.
- **Le reviewer** relit le code. S'il a des commentaires, il les ajoute. Si tout est bon, il approuve la PR en cliquant sur "Review changes" > "Approve".

Une fois la PR approuvée, le reviewer (ou le gardien du dépôt) peut cliquer sur **"Merge pull request"**.

Et voilà ! Le ticket `RAY-42` passera automatiquement dans la colonne "Terminé".
## Contributeur
- Adrien Quimbre
- Joseph BAEGNE
