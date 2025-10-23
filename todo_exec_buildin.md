## 🟢 Person B: Execution & Builtins

### Phase 1: Builtins (können sofort mit Test-Arrays implementiert werden)

#### echo
- [x] Plain echo
- [ ] Handle `-n` flag
- [ ] Handle multiple arguments
- [ ] Handle variable expansion in arguments

#### cd
- [ ] `cd <path>` (relative or absolute)
- [ ] `cd` with no args → go to `$HOME`
- [ ] Handle errors (e.g., no such file, permission denied)
- [ ] Update `PWD` and `OLDPWD` correctly

#### pwd
- [ ] Print current working directory
- [ ] Ensure output matches actual `PWD` (use `getcwd`)

#### export
- [ ] Add/update environment variables (`export KEY=VALUE`)
- [ ] Display all exported vars when called with no args
- [ ] Validate variable names (must match `[a-zA-Z_][a-zA-Z0-9_]*`)

#### unset
- [ ] Remove environment variables
- [ ] Validate identifiers (same rules as `export`)

#### env
- [ ] Print all environment variables (one per line, `KEY=VALUE`)
- [ ] Print error and return exit status 1 if extra args given

#### exit
- [ ] Exit minishell with correct exit code
- [ ] Handle numeric argument (e.g., `exit 42`)
- [ ] Handle too many arguments (error, don't exit)
- [ ] Free all resources before exit

### Phase 2: Environment Management
- [ ] Copy environment from `main`'s `envp`
- [ ] Maintain internal environment list (array of `char *`)
- [ ] Keep environment consistent across builtins (`export`, `unset`, `cd`)
- [ ] Helper-Funktionen: `getenv_custom`, `setenv_custom`, `unsetenv_custom`

### Phase 3: Command Execution
- [ ] Builtin execution (without forking) - Dispatcher-Funktion
- [ ] External command execution (`execve`)
- [ ] PATH lookup (for commands without `/`)
- [ ] Process handling (`fork`, `waitpid`, etc.)
- [ ] Execute absolute paths (e.g., `/bin/ls`)
- [ ] Execute relative paths (e.g., `./minishell`)
- [ ] Handle "command not found" and "permission denied" correctly

### Phase 4: Pipes & Redirections (Execution)
- [ ] Pipes (`|`) - Execution-Teil (`pipe()`, `dup2()`, FD-Management)
- [ ] Support multiple pipes (`cmd1 | cmd2 | cmd3`)
- [ ] Correctly chain stdin/stdout
- [ ] Close all unused file descriptors in parent and children
- [ ] Redirections - Execution (`open()`, `dup2()` für Files)
- [ ] Handle redirection errors (file not found, permission denied)

### Phase 5: Signals & Exit Status
- [ ] Handle `SIGINT` (Ctrl+C): show new prompt on new line
- [ ] Ignore `SIGQUIT` (Ctrl+\\)
- [ ] Handle EOF (Ctrl+D): exit cleanly
- [ ] Reset signal handlers to default in child processes before `execve`
- [ ] Set correct exit status for all commands (0 on success, 1+ on error)
- [ ] Track and update `$?` correctly

### Phase 6: Memory Management (Execution)
- [ ] Free all allocated memory on normal exit
- [ ] Clean up env copies, FDs, child processes
- [ ] Avoid leaks when commands fail

---

# 💡 Tipps für unabhängiges Arbeiten

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