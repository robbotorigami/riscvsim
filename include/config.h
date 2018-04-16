/*
 * config.h
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <iostream>

#ifdef SILENT

#define INFORMATION(STUFF)

#elif defined PRINT

#define INFORMATION(STUFF) \
	std::cout << STUFF << std::endl;

#else

#include <fstream>

extern std::ofstream fs;

#define INFORMATION(STUFF) \
	fs << STUFF << std::endl;

#endif


#endif /* INCLUDE_CONFIG_H_ */
