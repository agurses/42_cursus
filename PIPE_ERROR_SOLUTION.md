# Pipe Error Handling Solution

## Problem
Child processes in a pipeline were not properly handling their own redirects and error conditions. When a child process failed, other child processes in the pipeline would continue executing and potentially write duplicate error messages or unwanted output.

## Solution

### Key Changes Made:

1. **Individual Redirect Handling**: Each child process now only handles its own redirects, not the entire pipeline's redirects.

2. **Output Capture and Conditional Display**: All pipeline output is temporarily captured and only displayed if no errors occur.

3. **Immediate Error Detection**: The parent process detects errors as soon as any child process exits and immediately kills remaining processes.

4. **Proper Exit Status Propagation**: The first error encountered is saved and used as the final exit status.

### Files Modified:

#### `minikabuk/src/executor/pipe.c`
- Added `has_redirect_in_current_command()` function to check for redirects in the current command only
- Modified `execute_pipe_child()` to use individual redirect handling
- Enhanced `execute_pipe_line()` with output capture and immediate error detection
- Implemented temporary output redirection to prevent race conditions

#### `minikabuk/src/executor/redirection.c`
- Added `handle_redirect_for_current_command()` function for individual command redirect handling
- Modified error handling to exit immediately on redirect errors

#### `minikabuk/src/executor/executor.h`
- Added function declaration for `handle_redirect_for_current_command()`

### How It Works:

1. **Output Capture Setup**: Before creating child processes, stdout is redirected to a temporary pipe
2. **Child Process Creation**: Each child process is created with its own redirect setup
3. **Individual Redirect Processing**: Each child processes only its own redirects using `has_redirect_in_current_command()`
4. **Immediate Error Detection**: Parent process monitors child exit statuses using `waitpid(-1, &status, 0)`
5. **Chain Breaking**: On first error, remaining processes are killed using `SIGKILL`
6. **Conditional Output**: If no errors occurred, captured output is displayed; otherwise, only error messages are shown

### Technical Implementation:

```c
// Create temporary pipe to capture output
pipe(temp_pipe);
saved_stdout = dup(STDOUT_FILENO);
dup2(temp_pipe[1], STDOUT_FILENO);

// Process pipeline...

// Restore stdout and conditionally display output
dup2(saved_stdout, STDOUT_FILENO);
if (!child_failed) {
    // Display captured output
}
```

### Benefits:

- **No Duplicate Errors**: Only the first error is reported
- **No Unwanted Output**: Output from subsequent commands is suppressed when errors occur
- **Proper Resource Cleanup**: All pipes and processes are properly cleaned up
- **Consistent Behavior**: Matches bash behavior for pipe error handling
- **Individual Command Isolation**: Each command handles its own redirects independently
- **Race Condition Prevention**: Output capture prevents timing issues

### Testing:

Use the provided test scripts to verify the solution works correctly:

```bash
./test_pipe_errors.sh
./test_additional_scenarios.sh
```

These scripts test various error scenarios including:
- Command not found errors
- Permission denied errors
- Directory execution errors
- Redirect errors
- Multiple errors in pipeline
- Successful pipeline execution (control test)

### Example Behavior:

**Before (problematic):**
```bash
$ nonexistent_command | echo hello
minishell: nonexistent_command: command not found
hello
```

**After (fixed):**
```bash
$ nonexistent_command | echo hello
minishell: nonexistent_command: command not found
```

**Before (problematic):**
```bash
$ echo hello | nonexistent_command | echo world
minishell: nonexistent_command: command not found
world
```

**After (fixed):**
```bash
$ echo hello | nonexistent_command | echo world
minishell: nonexistent_command: command not found
```

The second command (`echo hello` or `echo world`) no longer executes when the first command fails.

### Performance Considerations:

- The solution uses minimal additional resources (one temporary pipe)
- Error detection is immediate and efficient
- Process cleanup is thorough and prevents zombie processes
- Output capture only occurs during pipeline execution