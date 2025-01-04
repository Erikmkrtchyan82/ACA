Multiple Forks and Execs
- Objective: Work with multiple child processes created using fork and run different commands using execl.
- Write a program that:
  * Creates two child processes using fork.
  * The first child process should use execl to run the ls command.
  * The second child process should use execl to run the date command.
  * The parent process should print "Parent process done" after creating both child processes.
- Expected Output: The output of the ls command followed by the output of the date command, and finally the parent's message.
