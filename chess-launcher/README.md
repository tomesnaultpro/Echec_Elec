# ♟ ChessLauncher

Un launcher d'échecs complet, moderne et prêt à l'emploi.

---

## 🚀 Lancement rapide

**Option 1 — Ouvrir directement**
Double-clique sur `index.html` dans ton navigateur.

**Option 2 — GitHub Pages (recommandé pour le mode en ligne)**
1. Crée un repo GitHub (ex: `chess-launcher`)
2. Upload `index.html`
3. Settings → Pages → Branch: main → Save
4. Accès : `https://TON_PSEUDO.github.io/chess-launcher`

> ⚠️ Le mode **En ligne** nécessite **HTTPS** → utilise GitHub Pages ou localhost.

---

## 🧩 Fonctionnalités

| Fonctionnalité | Statut |
|---|---|
| 1v1 Local | ✅ |
| Contre IA (3 niveaux) | ✅ |
| 1v1 En ligne (P2P) | ✅ |
| Matchmaking automatique | ✅ |
| Profil joueur | ✅ |
| Historique des parties | ✅ |
| Relecture coup par coup | ✅ |
| 3 thèmes de plateau | ✅ |
| Minuterie (1/3/5/10 min) | ✅ |
| Promotion automatique (Dame) | ✅ |
| Détection échec/mat/pat | ✅ |
| Notation algébrique | ✅ |

---

## 🌐 Mode en ligne

Le mode en ligne utilise **PeerJS** (WebRTC peer-to-peer, gratuit, sans serveur).

### Créer une partie
1. Va dans **Nouvelle partie → En ligne → Créer**
2. Copie le **code de 6 lettres**
3. Partage-le à ton adversaire

### Rejoindre une partie
1. Va dans **En ligne → Rejoindre**
2. Entre le code reçu
3. Clique **Rejoindre**

### Matchmaking
1. Va dans **En ligne → Matchmaking**
2. Clique **Rechercher**
3. Le système te met en relation automatiquement

---

## 🤖 Intelligence Artificielle

| Niveau | Description |
|---|---|
| 😊 Facile | Coups aléatoires |
| 🧠 Moyen | Minimax profondeur 2 |
| 😈 Difficile | Minimax + alpha-beta profondeur 3 |

L'IA peut être remplacée par **Stockfish** via API (hook prévu dans le code).

---

## ⚙️ Technologies utilisées

- **HTML5 / CSS3 / JavaScript** — Aucun framework
- **PeerJS** — Communication P2P temps réel (via CDN)
- **LocalStorage** — Persistance des données locales
- **Google Fonts** — Cinzel + Inter

---

## 📁 Structure

```
chess-launcher/
├── index.html    ← Application complète (tout-en-un)
└── README.md
```

---

## 🔧 Ajouter Stockfish (IA avancée)

Dans `index.html`, remplace la fonction `doAIMove()` :

```javascript
async function doAIMove() {
  const fen = boardToFEN(G.board, G.cur); // à implémenter
  const response = await fetch('https://TON_API_STOCKFISH?fen=' + fen);
  const data = await response.json();
  const move = data.bestmove; // ex: "e2e4"
  // convertir en [fr,fc,tr,tc] et appeler executeMove(...)
}
```

---

Fait avec ♟ par ChessLauncher v1.0.0
