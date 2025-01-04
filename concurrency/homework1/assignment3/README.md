Fork and Exec with Arguments
- Objective: Understand how to pass arguments to programs executed with execl.
- Write a program that:
  * Uses fork to create a child process.
  * The child process should use execl to run the echo command with an argument (e.g., "Hello from the child process").
  * The parent process should print "Parent process done" after the child process is created.
- Expected Output: The message from the echo command followed by the parent's message.
