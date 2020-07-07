/** @file main.c
 * 
 * @author Abderraouf Adjal
 * @brief ATMega328P Project.
 * @bug No known bugs.
 */

#include "global.h"
#include "main.h"

/* Global flag in ".noinit" memory section. */
NO_INIT_ATTR volatile uint8_t g_error_flag;

/**
 * @brief Main function.
 * @param void.
 * @return Should not return.
 * 
 */
int main(void)
{
    g_error_flag = G_ERROR_NONE;
    
    for(;;)
    {
    }
    
    /* Freestanding environment, no return required. */
}

/* =================================== EOF ================================== */
