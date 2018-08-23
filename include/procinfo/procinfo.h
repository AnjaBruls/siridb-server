/*
 * procinfo.h - Process info for the current running process.
 *
 * Got most information from:
 *
 * http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-
 *      memory-consumption-from-inside-a-process
 *
 * author       : Jeroen van der Heijden
 * email        : jeroen@transceptor.technology
 * copyright    : 2016, Transceptor Technology
 *
 * changes
 *  - initial version, 18-03-2016
 *
 */

#ifndef PROCINFO_H_
#define PROCINFO_H_

/* Total_Physical_Memory returned in KB */
long int procinfo_total_physical_memory(void);

/* Total_Virtual_Memory returned in KB */
long int procinfo_total_virtual_memory(void);

/* Total Open Files */
long int procinfo_open_files(const char * path);


#endif  /* PROCINFO_H_ */
