# Minishell Aufgabenaufteilung

## 🔵 Person A: Parsing & Input Processing

### Phase 1: Tokenization
- [x] Tokenizer ✅ (your debug output shows proper tokens)
- [ ] Quote handling (single and double quotes)
- [ ] Detect and reject unclosed quotes → syntax error
- [ ] Variable expansion (`$VAR`, including special `$?`)
- [ ] Escapes (backslash `\` not required)

### Phase 2: Command Structure
- [x] Build command structures from tokens ✅ (commands and arguments are correctly stored)
- [ ] Syntax validation (malformed commands, e.g., consecutive pipes, empty commands)
- [x] Pipes `|` → linked command chain ✅ (output shows 4 commands correctly linked)
- [x] Assign executable flag (identify builtins vs external/`./executable`)

### Phase 3: Redirections
- [x] Parse redirections `<`, `>`, `>>`, `<<` ✅ (all redirects appear in command struct)
- [ ] Heredoc (`<<`) → delimiter handling and input collection
- [ ] Redirection errors → missing filenames, multiple conflicting redirects

### Phase 4: Integration & Error Handling
- [ ] Parsing error handling (syntax errors in general)
- [ ] Syntax errors (unclosed quotes, malformed redirections, invalid pipe placement)
- [x] Memory management → free tokens, commands, and file lists
- [ ] Free allocated memory on errors/interruption (ensure no leaks during parsing or execution failures)

### Additionally
- [x] History ✅ (already works with readline)

