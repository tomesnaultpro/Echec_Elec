# ♟ ChessPro v5 — Guide GitHub Database

## 🚀 Démarrage en 5 minutes

### Étape 1 — Ouvrir le site
Ouvrez `index.html` directement dans Chrome/Edge, **ou** déployez sur GitHub Pages.

Login par défaut : **admin / admin** → fonctionne immédiatement sans configuration (stockage local du navigateur)

---

### Étape 2 — Créer la base de données GitHub (ADMIN uniquement)

La base de données est un **dépôt GitHub privé** qui stocke des fichiers JSON.
C'est gratuit, persistant, et partagé entre tous les joueurs.

#### 2a — Créer un Token GitHub
1. Allez sur **github.com → Settings → Developer settings**
2. **Personal access tokens → Tokens (classic) → Generate new token (classic)**
3. Donnez-lui un nom (ex : `chesspro-db`)
4. Cochez uniquement la permission **`repo`** (accès complet aux dépôts)
5. Cliquez **Generate token** → copiez le token (commence par `ghp_...`)

#### 2b — Créer un dépôt privé
1. Sur GitHub, créez un **nouveau dépôt privé** (ex : `chesspro-db`)
2. Notez : `votre-pseudo/chesspro-db`

#### 2c — Configurer dans l'application
1. Connectez-vous avec **admin / admin**
2. Allez dans **Panneau Admin → Configurer GitHub**
3. Renseignez :
   - **Token** : `ghp_xxxxxxxxxxxxxx`
   - **Dépôt** : `votre-pseudo/chesspro-db`
4. Cliquez **Connecter GitHub** ✅

👉 La base de données est initialisée automatiquement avec les fichiers :
- `db/users.json` — tous les comptes utilisateurs
- `db/games.json` — toutes les parties jouées
- `db/matchmaking.json` — joueurs en attente d'adversaire

---

## 🗄️ Structure de la base de données

### `db/users.json`
```json
{
  "alice_xyz": {
    "id": "alice_xyz",
    "pseudo": "Alice",
    "pseudoLower": "alice",
    "password": "hash_sha256",
    "avatar": "♟",
    "role": "user",
    "elo": 1250,
    "games": 12,
    "wins": 7,
    "losses": 4,
    "draws": 1,
    "joined": "01/01/2025"
  }
}
```

### `db/games.json`
```json
{
  "game_abc123": {
    "id": "game_abc123",
    "date": "01/01/2025",
    "timestamp": 1700000000000,
    "players": {"w": "alice_xyz", "b": "bob_abc"},
    "playerIds": ["alice_xyz", "bob_abc"],
    "wPseudo": "Alice",
    "bPseudo": "Bob",
    "reason": "checkmate",
    "winner": "w",
    "moves": ["e4", "e5", "Nf3"],
    "eloChanges": {"w": 12, "b": -12},
    "mode": "online"
  }
}
```

### `db/matchmaking.json`
```json
{
  "alice_xyz": {
    "uid": "alice_xyz",
    "pseudo": "Alice",
    "elo": 1250,
    "avatar": "♟",
    "ts": 1700000000000,
    "status": "waiting",
    "peerCode": "AB12CD"
  }
}
```

---

## 🌐 Mode en ligne

### Comment ça fonctionne

Le mode en ligne utilise **deux technologies** :
- **GitHub** → liste des joueurs disponibles (matchmaking, actualisée toutes les 5s)
- **PeerJS WebRTC** → connexion directe entre les deux joueurs pour les coups (temps réel)

### Matchmaking automatique
1. Les deux joueurs vont dans **En ligne → Matchmaking**
2. Cliquez **Chercher une partie** → vous apparaissez dans la liste (avec votre code PeerJS)
3. Voyez les autres joueurs → cliquez **⚔️ Inviter**
4. La connexion WebRTC s'établit automatiquement

### Code privé (sans matchmaking)
1. **Créer** → partagez le code à 6 lettres affiché
2. L'adversaire → **Rejoindre** → entre le code

---

## 🔐 Sécurité

- Les mots de passe sont **hashés avec SHA-256** avant stockage
- Le dépôt GitHub doit être **privé** pour protéger les données
- Le token GitHub est stocké en **localStorage** du navigateur admin uniquement
- Les joueurs normaux n'ont pas accès au token

---

## ⚠️ Important

- Le mode en ligne (PeerJS WebRTC) nécessite **HTTPS** → GitHub Pages ✅
- Sans GitHub configuré → données dans le navigateur uniquement (1 seul PC)
- Avec GitHub → tous les joueurs partagent la même DB ✅
- Le matchmaking se synchronise toutes les **5 secondes** (limitation de l'API GitHub)

---

## 🚀 Déploiement GitHub Pages (recommandé)

1. Créez un dépôt **public** (ex : `chesspro`)
2. Uploadez `index.html` à la racine
3. Settings → Pages → Source : `main` branch → `/root`
4. Votre site sera sur : `https://PSEUDO.github.io/chesspro`
5. Connectez-vous admin → configurez la DB GitHub (dépôt **privé** séparé)

---

ChessPro v5 — GitHub API + PeerJS WebRTC
