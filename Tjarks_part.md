# Minishell Aufgabenaufteilung

## 🔵 Person A: Parsing & Input Processing

### Phase 1: Basis-Parsing
- [x] Tokenizer
- [ ] Quote handling (single and double quotes)
- [ ] Detect and reject unclosed quotes (syntax error)
- [ ] Variable expansion (`$VAR`, including special `$?`)
- [ ] Escapes (note: backslash `\` is **not required** — skip if not implementing bonus)

### Phase 2: Command-Struktur
- [ ] Parser: Command-Struktur aus Tokens erstellen
- [ ] Syntax-Validierung (malformed commands erkennen)
- [ ] Pipes (`|`) - Parsing-Teil (Token erkennen, Command-Chain aufbauen)

### Phase 3: Redirections (Parsing)
- [ ] Redirections (`<`, `>`, `>>`, `<<`) - Token erkennen und Files identifizieren
- [ ] Heredoc (`<<`) - Delimiter erkennen und Input sammeln
- [ ] Redirection-Fehler erkennen (fehlende Files, mehrfache Redirections)

### Phase 4: Integration & Error Handling
- [ ] Error Handling für Parsing-Fehler
- [ ] Syntax errors (unclosed quotes, malformed redirections)
- [ ] Memory Management für Parser (Tokens, Command-Structs freigeben)

### Zusätzlich (falls Zeit)
- [ ] History (bereits erledigt mit readline)
- [ ] Bonus: Wildcards (`*`, `?`) Parsing

---

## 🤝 Gemeinsame Aufgaben (zusammen besprechen/coden)

### Sprint 0 (Vor Start, ~1-2 Stunden zusammen)
- [ ] Command-Struktur definieren (`t_command`, `t_token`, etc.)
- [ ] Schnittstelle zwischen Parser und Executor festlegen
- [ ] Error-Handling-Strategie (wie werden Fehler weitergegeben?)
- [ ] Global variable definieren (für Exit-Status oder Signal-Flag)
- [ ] Makefile-Struktur

### Regelmäßige Integration (alle 2-3 Tage)
- [ ] Code-Review Sessions
- [ ] Integration Testing
- [ ] Merge-Konflikte lösen

### Final Phase (zusammen)
- [ ] End-to-End Testing mit komplexen Kommandos
- [ ] Memory-Leak-Checking (valgrind)
- [ ] Edge-Cases testen
- [ ] Norminette überprüfen
- [ ] Bonus-Features (falls Zeit)

---

## 📋 Zeitplan-Vorschlag

**Woche 1:**
- Person A: Tokenizer fertigstellen, Quote-Handling beginnen
- Person B: Alle Builtins implementieren (mit Test-Arrays)
- Gemeinsam: Command-Struktur definieren (Meeting)

**Woche 2:**
- Person A: Quote-Handling + Variable Expansion
- Person B: Environment Management + PATH lookup
- Gemeinsam: Erste Integration (einfache Commands ausführen)

**Woche 3:**
- Person A: Pipe-Parsing + Redirection-Parsing
- Person B: Pipe-Execution + Redirection-Execution
- Gemeinsam: Testing von Pipes & Redirections

**Woche 4:**
- Person A: Syntax-Error-Handling + Memory Cleanup
- Person B: Signal-Handling + Exit-Status-Management
- Gemeinsam: Final Integration & Testing

**Woche 5:**
- Gemeinsam: Bug-Fixing, Edge-Cases, Memory-Leaks
- Optional: Bonus-Features

---

## 💡 Tipps für unabhängiges Arbeiten

### Person A (Parser):
- Teste mit `printf` oder schreibe eine Debug-Funktion, die deine Command-Struktur ausgibt
- Erstelle Test-Inputs in separater Datei
- Beispiel: `char *test = "echo 'hello world' | grep hello > out.txt";`

### Person B (Executor):
- Erstelle Test-Arrays direkt im Code:
  ```c
  char *args[] = {"cd", "/tmp", NULL};
  builtin_cd(args, &env);
  ```
- Teste jeden Builtin einzeln bevor Integration
- Schreibe Helper-Funktionen für Environment früh

### Beide:
- Macht Feature-Branches: `git checkout -b feature/quote-handling`
- Commited oft, pusht täglich
- Dokumentiert eure Funktionen (kurze Kommentare)
- Bei Unsicherheit: kurz absprechen bevor viel Code geschrieben wird

---

## ⚠️ Kritische Synchronisationspunkte

Diese Dinge **müssen** zusammen besprochen werden:
1. Command-Struktur (Tag 1!)
2. Wie werden Errors zurückgegeben? (int return codes? struct mit error flag?)
3. Wer managed die globale Variable?
4. Wer schreibt die Main-Loop?
5. Format der Environment (array of strings? linked list?)

---

## 📦 Dateistruktur-Vorschlag

```
minishell/
├── srcs/
│   ├── main.c                    [Gemeinsam/Person B]
│   ├── parser/                   [Person A]
│   │   ├── tokenizer.c
│   │   ├── quotes.c
│   │   ├── expander.c
│   │   └── parser.c
│   ├── executor/                 [Person B]
│   │   ├── executor.c
│   │   ├── path.c
│   │   ├── pipes.c
│   │   └── redirections.c
│   ├── builtins/                 [Person B]
│   │   ├── echo.c
│   │   ├── cd.c
│   │   ├── pwd.c
│   │   ├── export.c
│   │   ├── unset.c
│   │   ├── env.c
│   │   └── exit.c
│   ├── env/                      [Person B]
│   │   └── env_manager.c
│   ├── signals/                  [Person B]
│   │   └── signals.c
│   └── utils/                    [Beide]
│       ├── error.c
│       ├── cleanup.c
│       └── utils.c
├── includes/
│   └── minishell.h               [Gemeinsam definieren]
└── Makefile
```