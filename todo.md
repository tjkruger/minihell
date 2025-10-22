# minishell TODO (Checklist with Boxes)

## Core Execution
- [x] Tokenizer
- [ ] Quote handling (single and double quotes)
- [ ] Escapes (note: backslash `\` is **not required** — skip if not implementing bonus)
- [ ] Pipes (`|`)
- [ ] Redirections (`<`, `>`, `>>`, `<<`)
- [ ] Variable expansion (`$VAR`, including special `$?`)
- [ ] Builtin execution (without forking)
- [ ] External command execution (`execve`)
- [ ] PATH lookup (for commands without `/`)
- [ ] Process handling (`fork`, `waitpid`, etc.)
- [ ] Detect and reject unclosed quotes (syntax error)

## Builtins

### echo
- [x] Plain echo
- [ ] Handle `-n` flag
- [ ] Handle multiple argumentsgit 
- [ ] Handle variable expansion in arguments

### cd
- [ ] `cd <path>` (relative or absolute)
- [ ] `cd` with no args → go to `$HOME`
- [ ] Handle errors (e.g., no such file, permission denied)
- [ ] Update `PWD` and `OLDPWD` correctly

### pwd
- [ ] Print current working directory
- [ ] Ensure output matches actual `PWD` (use `getcwd`)

### export
- [ ] Add/update environment variables (`export KEY=VALUE`)
- [ ] Display all exported vars when called with no args
- [ ] Validate variable names (must match `[a-zA-Z_][a-zA-Z0-9_]*`)

### unset
- [ ] Remove environment variables
- [ ] Validate identifiers (same rules as `export`)

### env
- [ ] Print all environment variables (one per line, `KEY=VALUE`)
- [ ] Print error and return exit status 1 if extra args given

### exit
- [ ] Exit minishell with correct exit code
- [ ] Handle numeric argument (e.g., `exit 42`)
- [ ] Handle too many arguments (error, don’t exit)
- [ ] Free all resources before exit

## Environment Management
- [ ] Copy environment from `main`’s `envp`
- [ ] Maintain internal environment list (array of `char *`)
- [ ] Keep environment consistent across builtins (`export`, `unset`, `cd`)
- [ ] Expand `$VAR` and `$?` at execution time (not parse time)

## Redirections
- [ ] Output redirection (`>`)
- [ ] Append output (`>>`)
- [ ] Input redirection (`<`)
- [ ] Heredoc (`<<`) — read until delimiter, feed as stdin
- [ ] Handle redirection errors (e.g., file not found, permission denied)

## Pipes
- [ ] Support multiple pipes (`cmd1 | cmd2 | cmd3`)
- [ ] Correctly chain stdin/stdout using `pipe()` and `dup2()`
- [ ] Close all unused file descriptors in parent and children

## Signals
- [ ] Handle `SIGINT` (Ctrl+C): show new prompt on new line (interactive mode only)
- [ ] Ignore `SIGQUIT` (Ctrl+\\): do nothing
- [ ] Handle EOF (Ctrl+D): exit cleanly
- [ ] Reset signal handlers to default in child processes before `execve`

## Error Handling
- [ ] Print clear error messages (like bash)
- [ ] Set correct exit status for all commands (0 on success, 1+ on error)
- [ ] Detect and report syntax errors (e.g., unclosed quotes, malformed redirections)

## History
- [x] In-memory history (via `readline` + `add_history`)
- [x] Navigation with arrow keys (handled by `readline`)

## Memory Management
- [ ] Free all allocated memory on normal exit
- [ ] Avoid leaks when commands fail or syntax is invalid
- [ ] Clean up tokens, command structs, env copies, etc.

## External Commands
- [ ] Execute absolute paths (e.g., `/bin/ls`)
- [ ] Execute relative paths (e.g., `./minishell`)
- [ ] Resolve commands via `PATH`
- [ ] Handle “command not found” and “permission denied” correctly

## Global Constraints
- [ ] Use **exactly one global variable** (e.g., for exit status or signal flag)
- [ ] Do **not** interpret `;`, `\`, or other unrequired metacharacters
- [ ] Do **not** leak memory (except known `readline` leaks)

## Bonus (Optional — only after mandatory is perfect)
- [ ] `&&` and `||` with parentheses
- [ ] Wildcards (`*`, `?`) for current directory
- [ ] Colored/custom prompt
- [ ] Persistent history or environment