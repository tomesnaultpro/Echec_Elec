# ♟ ChessPro — Guide d'installation complet

## Structure du projet

```
chesspro/
├── index.html        ← Application complète
├── db/
│   ├── users.json    ← Base de données des utilisateurs
│   └── games.json    ← Base de données des parties
└── README.md
```

---

## 🚀 Mise en ligne sur GitHub Pages (étape par étape)

### Étape 1 — Créer le repository GitHub

1. Connectez-vous sur [github.com](https://github.com)
2. Cliquez sur **"New repository"** (bouton vert)
3. Nommez-le : `chesspro` (ou ce que vous voulez)
4. Cochez **"Public"** (obligatoire pour GitHub Pages gratuit)
5. Cochez **"Add a README file"**
6. Cliquez **"Create repository"**

### Étape 2 — Uploader les fichiers

1. Sur la page du repo, cliquez **"Add file" → "Upload files"**
2. Uploadez **tous les fichiers** :
   - `index.html`
   - `db/users.json` (créez d'abord le dossier `db`)
   - `db/games.json`
3. Cliquez **"Commit changes"**

> Pour créer le dossier `db` : cliquez "Add file" → "Create new file" → tapez `db/users.json` → copiez le contenu du fichier users.json fourni.

### Étape 3 — Activer GitHub Pages

1. Allez dans **Settings** (onglet en haut du repo)
2. Dans le menu gauche : **Pages**
3. Source : **Deploy from a branch**
4. Branch : **main** → **/ (root)**
5. Cliquez **Save**
6. Attendez 2-3 minutes
7. Votre site est accessible à : `https://VOTRE_PSEUDO.github.io/chesspro`

---

## 🔑 Créer le Personal Access Token (nécessaire pour la DB)

Le token permet à l'application d'écrire dans les fichiers JSON.

1. Sur GitHub, cliquez votre **avatar** (en haut à droite) → **Settings**
2. Dans le menu gauche, tout en bas : **Developer settings**
3. **Personal access tokens** → **Tokens (classic)**
4. Cliquez **"Generate new token (classic)"**
5. Note (description) : `chesspro-db`
6. Expiration : **No expiration** (ou 1 an)
7. Cochez uniquement : ✅ **repo** (tout le groupe repo)
8. Cliquez **"Generate token"**
9. **⚠️ COPIEZ LE TOKEN MAINTENANT** — il ne sera plus visible ensuite

Le token ressemble à : `ghp_xxxxxxxxxxxxxxxxxxxx`

---

## ⚙️ Première connexion — Configuration

1. Ouvrez votre site GitHub Pages
2. Un formulaire de configuration s'affiche :
   - **Owner** : votre pseudo GitHub (ex: `monpseudo`)
   - **Repository** : nom du repo (ex: `chesspro`)
   - **Personal Access Token** : le token ghp_ copié ci-dessus
3. Cliquez **"Connecter GitHub →"**
4. Si tout est bon, le login s'affiche ✅

> La configuration est sauvegardée dans votre navigateur. Vous ne la saisirez qu'une seule fois par navigateur.

---

## 🔐 Compte Admin par défaut

| Pseudo | Mot de passe |
|--------|-------------|
| `admin` | `admin` |

**⚠️ Changez le mot de passe immédiatement** dans le Panneau Admin → "Modifier les identifiants Admin".

---

## 🌐 Mode en ligne (Multijoueur)

Le mode en ligne utilise **PeerJS (WebRTC)** — connexion directe entre navigateurs, sans serveur intermédiaire.

- ✅ Fonctionne sur GitHub Pages (HTTPS)
- ❌ Ne fonctionne **pas** en ouvrant index.html comme fichier local
- Gratuit et sans limite

### Comment jouer en ligne :
1. Les deux joueurs ouvrent le même site GitHub Pages
2. Joueur 1 : **En ligne → Créer** → partage le code à 6 lettres
3. Joueur 2 : **En ligne → Rejoindre** → entre le code → connecté !

---

## 🔌 Arduino LEDs

Compatible avec Chrome et Edge uniquement (Web Serial API).

**Code Arduino (à uploader sur votre carte) :**

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN 11
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    int i1 = data.indexOf(',');
    int i2 = data.indexOf(',', i1 + 1);
    int i3 = data.indexOf(',', i2 + 1);
    int index = data.substring(0, i1).toInt();
    int r = data.substring(i1 + 1, i2).toInt();
    int g = data.substring(i2 + 1, i3).toInt();
    int b = data.substring(i3 + 1).toInt();
    if (index >= 0 && index < NUMPIXELS) {
      pixels.setPixelColor(index, pixels.Color(r, g, b));
      pixels.show();
    }
  }
}
```

---

## 📁 Format des fichiers JSON

### db/users.json
```json
{
  "admin": {
    "id": "admin",
    "pseudo": "admin",
    "password": "hash_sha256_du_mot_de_passe",
    "avatar": "♚",
    "role": "admin",
    "elo": 1500,
    "games": 0,
    "wins": 0,
    "losses": 0,
    "draws": 0,
    "joined": "2025-01-01"
  }
}
```

### db/games.json
```json
[]
```

---

## ❓ Problèmes fréquents

**"Erreur de connexion à la base de données"**
→ Vérifiez que votre token a bien le scope `repo`
→ Vérifiez que le repo est public
→ Vérifiez les fichiers `db/users.json` et `db/games.json` existent dans le repo

**"Le mode en ligne ne fonctionne pas"**
→ Vous devez être sur GitHub Pages (HTTPS), pas en fichier local

**"Je ne vois pas mes parties sauvegardées"**
→ La DB GitHub est partagée. Si quelqu'un d'autre utilise le site sur un autre navigateur, leurs données sont dans le même fichier JSON.

---

ChessPro v3.0 — GitHub Pages + JSON DB
