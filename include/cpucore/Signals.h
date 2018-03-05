/*
 * signals.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_SIGNALS_H_
#define INCLUDE_CPUCORE_SIGNALS_H_
#include <cstdlib>
#include "util/Logger.h"

/*!
 * \brief class to implement signals inbetween sections of the cpu
 * \tparam typebase the datatype to be used in this signal
 */
template <typename typebase>
class Signal{
public:
	//! Initialize the signal. Must be able to assign 0 to typebase
	Signal(std::string name = "Unamed"){
		data = 0;
	}

	/*!
	 * \breif Put data into the signal.
	 *
	 * \param data the data to be inserted
	 */
	void setData(typebase data){
		this->data = data;
	}

	/*!
	 * \brief Get the data in the signal.
	 *
	 * \return the current data in the signal
	 */
	typebase getData(typebase data){
		return data;
	}

private:
	//! The data on the signal line
	typebase data;
};




#endif /* INCLUDE_CPUCORE_SIGNALS_H_ */
