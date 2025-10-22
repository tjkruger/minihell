
# minishell TODO (Checklist with Boxes)

## Core Execution
- [ ] Tokenizer
- [ ] Quote handling
- [ ] Escapes
- [ ] Pipes
- [ ] Redirections
- [ ] Variable expansion
- [ ] Command separators
- [ ] Builtin execution
- [ ] External command execution
- [ ] PATH lookup
- [ ] Process handling

## Builtins

### echo
- [ ] Plain echo
- [ ] Handle -n flag
- [ ] Handle multiple arguments
- [ ] Handle variable expansion

### cd
- [ ] cd <path>
- [ ] cd with no args → go to $HOME
- [ ] cd - (previous dir)
- [ ] Handle errors
- [ ] Update PWD and OLDPWD

### pwd
- [ ] Print current working directory
- [ ] Handle PWD variable consistency

### export
- [ ] Add/update environment variables
- [ ] Display exported vars (no args)
- [ ] Validate variable names

### unset
- [ ] Remove environment variables
- [ ] Handle invalid identifiers

### env
- [ ] Print all environment variables
- [ ] Handle extra arguments (error behavior)

### exit
- [ ] Exit minishell with correct exit code
- [ ] Handle numeric arguments
- [ ] Handle too many args
- [ ] Free all resources before exit

## Environment Management
- [ ] Copy environment from parent process
- [ ] Implement internal environment list
- [ ] Sync between list and envp
- [ ] Handle unset/export interactions

## Redirections
- [ ] Output redirection >
- [ ] Append output >>
- [ ] Input redirection <
- [ ] Heredoc <<
- [ ] Handle errors

## Pipes
- [ ] Multiple pipes
- [ ] Manage stdin/stdout properly
- [ ] File descriptor cleanup

## Signals
- [ ] Handle SIGINT (Ctrl+C)
- [ ] Handle SIGQUIT (Ctrl+\)
- [ ] Handle EOF (Ctrl+D)

## Error Handling
- [ ] Proper error messages
- [ ] Exit codes consistent with bash
- [ ] Syntax errors

## History
- [ ] In-memory history
- [ ] Persistent history (optional)
- [ ] Navigation (optional)

## Memory Management
- [ ] Free all allocated memory on exit
- [ ] Avoid leaks when commands fail
- [ ] Handle forked processes cleanly

## External Commands
- [ ] Execute /bin/ls
- [ ] Execute /bin/cat
- [ ] Execute /usr/bin/env
- [ ] PATH resolution
- [ ] Permission denied / not found errors

## Bonus (Optional)
- [ ] History navigation with arrows
- [ ] Autocompletion
- [ ] Wildcards (*, ?)
- [ ] Colored/custom prompt
- [ ] Persistent environment/history
