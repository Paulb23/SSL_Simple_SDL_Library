/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Logger.h
   @author  P. Batty
   @brief   Implements a Logging function.

   This module implements a simple logging function that will
   write a message to a file.
*/
/*--------------------------------------------------------------------------*/

#ifndef LOGGER_H_
#define LOGGER_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Writes a message to a file
  @param    text		  Text to write.
  @param    ...          printf arguments
  @return 	 void

  Writes a message to a file, in the style of printf.


\-----------------------------------------------------------------------------*/
void SSL_Log_Write(const char *text, ...);

#endif
