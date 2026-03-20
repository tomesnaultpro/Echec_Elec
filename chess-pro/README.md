# ♟ ChessPro — Launcher Complet

Plateforme d'échecs complète avec login, admin, Arduino LEDs, ELO, et bien plus.

---

## 🚀 Démarrage rapide

**Option 1 — Local (sans serveur)**
Ouvre `index.html` dans **Google Chrome ou Edge**.

**Option 2 — GitHub Pages (recommandé)**
1. Crée un repo GitHub
2. Upload `index.html`
3. Settings → Pages → Branch: main → Save
4. Accès : `https://TON_PSEUDO.github.io/NOM_REPO`

> ⚠️ Le mode **En ligne** et **Arduino** nécessitent **HTTPS** → utilise GitHub Pages.

---

## 🔐 Connexion par défaut

| Pseudo | Mot de passe | Rôle |
|--------|-------------|------|
| `admin` | `admin` | 👑 Administrateur |

---

## 🧩 Fonctionnalités complètes

### Authentification
- ✅ Login / Inscription
- ✅ Hachage SHA-256 des mots de passe
- ✅ Sessions avec token JWT simulé
- ✅ Auto-login (session persistante 7 jours)
- ✅ Rôles : user / admin

### Jeu
- ✅ 1v1 Local
- ✅ Contre IA (4 niveaux : Facile / Moyen / Difficile / Maître)
- ✅ 1v1 En ligne P2P (WebRTC / PeerJS)
- ✅ Matchmaking automatique
- ✅ Toutes les règles officielles (échec, mat, pat, promotion)
- ✅ Notation algébrique des coups
- ✅ Minuterie (∞ / 1 / 3 / 5 / 10 min)

### Arduino LEDs
- ✅ Connexion via Web Serial (Chrome/Edge)
- ✅ LED Vert = pièce sélectionnée
- ✅ LED Bleu = mouvements possibles
- ✅ LED Rouge = captures possibles
- ✅ Flash orange = coup joué
- ✅ Flash rouge = erreur (coup illégal)
- ✅ Page de configuration et test dédiée

### Profil & Classement
- ✅ ELO dynamique
- ✅ Statistiques (parties / victoires / défaites / win rate)
- ✅ Avatars personnalisables
- ✅ Classement ELO global

### Social
- ✅ Système d'amis (ajouter / supprimer)
- ✅ Invitations de partie
- ✅ Notifications en temps réel
- ✅ Chat en ligne pendant la partie

### Historique & Relecture
- ✅ Toutes les parties enregistrées
- ✅ Relecture coup par coup
- ✅ Navigation (début / précédent / suivant / fin)
- ✅ Gain/perte ELO affiché

### Admin
- ✅ Gestion des utilisateurs
- ✅ Configuration token API
- ✅ URL de base de données externe
- ✅ Logs système
- ✅ Statistiques globales
- ✅ Suppression d'utilisateurs

### Interface
- ✅ Thème sombre / clair
- ✅ 3 thèmes de plateau (Classique / Océan / Forêt)
- ✅ 3 tailles de plateau (S / M / L)
- ✅ Design responsive (mobile friendly)
- ✅ Animations des pièces

---

## 🔌 Code Arduino (inchangé)

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
    int r     = data.substring(i1 + 1, i2).toInt();
    int g     = data.substring(i2 + 1, i3).toInt();
    int b     = data.substring(i3 + 1).toInt();

    if (index >= 0 && index < NUMPIXELS) {
      pixels.setPixelColor(index, pixels.Color(r, g, b));
      pixels.show();
    }
  }
}
```

---

## 🌐 Mode en ligne

Utilise **PeerJS** (WebRTC peer-to-peer).
- **Gratuit** et **sans serveur**
- Nécessite **HTTPS** (GitHub Pages)
- Fonctionne via code de partie ou matchmaking

---

## 🔒 Sécurité

| Mesure | Implémentation |
|--------|---------------|
| Hachage MDP | SHA-256 + sel via SubtleCrypto |
| Sessions | Token JWT simulé (expiration 7 jours) |
| Namespacing | Préfixe `cp_` en localStorage |
| Rôles | user / admin avec vérification côté UI |

> Note: Pour une vraie production, utiliser un backend avec bcrypt + JWT serveur.

---

## 📁 Structure

```
chess-pro/
├── index.html    ← Application complète tout-en-un
└── README.md
```

---

ChessPro v2.0 — Fait avec ♟
