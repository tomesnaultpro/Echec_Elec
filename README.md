# ♟ ChessPro v4 — Guide Firebase

## 🚀 Démarrage en 5 minutes

### Étape 1 — Ouvrir le site
Sur GitHub Pages : `https://PSEUDO.github.io/chesspro`
Login : **admin / admin** → fonctionne immédiatement sans rien configurer (stockage local)

### Étape 2 — Configurer Firebase (optionnel mais recommandé)
Pour avoir une vraie base de données partagée entre tous les joueurs.

1. Allez sur **console.firebase.google.com** → Créer un projet
2. Dans le projet :
   - **Firestore Database** → Créer une base de données → Mode production
   - **Realtime Database** → Créer une base (pour le matchmaking temps réel)
   - **Authentication** → Sign-in method → Email/Password → Activer
3. **Project Settings** (⚙️) → Your apps → Web (</>) → Enregistrer
4. Copiez la config ressemblant à :
```json
{
  "apiKey": "AIza...",
  "authDomain": "monprojet.firebaseapp.com",
  "databaseURL": "https://monprojet-default-rtdb.firebaseio.com",
  "projectId": "monprojet",
  "storageBucket": "monprojet.appspot.com",
  "messagingSenderId": "123456789",
  "appId": "1:123:web:abc"
}
```
5. Connectez-vous en **admin** → **Panneau Admin** → **Configurer Firebase**
6. Collez la config JSON → **Connecter Firebase** ✅

### Étape 3 — Règles Firestore (copiez dans Firebase Console)
```
rules_version = '2';
service cloud.firestore {
  match /databases/{database}/documents {
    match /users/{userId} {
      allow read: if true;
      allow write: if true;
    }
    match /games/{gameId} {
      allow read, write: if true;
    }
    match /matchmaking/{userId} {
      allow read, write: if true;
    }
    match /live_games/{gameId} {
      allow read, write: if true;
    }
    match /_ping/{doc} {
      allow read, write: if true;
    }
    match /_test/{doc} {
      allow read, write: if true;
    }
    match /invitations/{doc} {
      allow read, write: if true;
    }
  }
}
```

### Règles Realtime Database
```json
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```

---

## 📊 Structure de la base de données

### Collection `users`
```json
{
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
```

### Collection `games`
```json
{
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
  "boardSnapshots": [...],
  "eloChanges": {"w": 12, "b": -12},
  "mode": "online"
}
```

### Collection `matchmaking` (joueurs disponibles)
```json
{
  "uid": "alice_xyz",
  "pseudo": "Alice",
  "elo": 1250,
  "avatar": "♟",
  "ts": 1700000000000,
  "status": "waiting"
}
```

---

## 🌐 Mode en ligne

### Matchmaking temps réel
1. Les deux joueurs vont dans **En ligne → Matchmaking**
2. Cliquez **Chercher une partie** → vous apparaissez dans la liste
3. Voyez les autres joueurs disponibles → cliquez **Inviter**
4. L'adversaire reçoit votre code → vous connecte automatiquement

### Code privé
1. **Créer** → partagez le code à 6 lettres
2. L'adversaire → **Rejoindre** → entre le code

---

## ⚠️ Important

- Le mode en ligne (PeerJS WebRTC) nécessite **HTTPS** → GitHub Pages ✅
- Sans Firebase → données dans le navigateur uniquement (1 seul PC)
- Avec Firebase → tous les joueurs partagent la même DB ✅

ChessPro v4 — Firebase + Firestore + PeerJS
