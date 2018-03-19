/*
 * config.h
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <iostream>

#ifndef SILENT

#define INFORMATION(STUFF) \
	std::cout << STUFF << std::endl;

#else

#define INFORMATION(STUFF)

#endif


#endif /* INCLUDE_CONFIG_H_ */
