#bash script 
# Run the program
valgrind --suppressions=read.supp --show-leak-kinds=all --leak-check=full --track-fds=yes ./minishell 


