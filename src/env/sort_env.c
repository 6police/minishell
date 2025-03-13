#include "ft_env.h"

void swap_env_var(t_env_var *a, t_env_var *b, t_env *env)
{
    if (!a || !b || !env || a->next != b)
        return;

    // Handle the case where 'a' is the head of the list
    if (a->prev)
        a->prev->next = b;
    else
        env->head = b;  // Update head if 'a' was the head

    // Update the next of 'b' to point to the correct node after swap
    if (b->next)
        b->next->prev = a;

    // Swap the nodes by adjusting their 'prev' and 'next' pointers
    a->next = b->next;
    b->prev = a->prev;

    b->next = a;
    a->prev = b;

    // Handle the case where 'a' was the last node
    if (!a->next)
        env->last = a;
}

void sort_env_list(t_env *env)
{
    int swapped;
    t_env_var *tmp;

    if (!env || !env->head)
        return;

    do
    {
        swapped = 0;
        tmp = env->head;

        while (tmp->next)
        {
            // Compare keys of adjacent nodes
            if (ft_strcmp(tmp->key, tmp->next->key) > 0)
            {
                // Swap if they are out of order
                swap_env_var(tmp, tmp->next, env);
                swapped = 1;
            }
            else
            {
                // Only move forward if no swap occurred
                tmp = tmp->next;
            }
        }
    } while (swapped);  // Continue until no more swaps are made
}

