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

		tags += LogTag("Name", "Signal");
		tags += LogTag("Instance", name);
		Logger::Stream(LEVEL_INFO, tags) << "Initialized";
	}

	/*!
	 * \breif Put data into the signal.
	 *
	 * \param data the data to be inserted
	 */
	void setData(typebase data){
		Logger::Stream(LEVEL_DEBUG, tags) << "Putting " << data << "on signal";
		this->data = data;
	}

	/*!
	 * \brief Get the data in the signal.
	 *
	 * \return the current data in the signal
	 */
	typebase getData(typebase data){
		Logger::Stream(LEVEL_DEBUG, tags) << "Reading " << data << "from signal";
		return data;
	}

private:
	//! The data on the signal line
	typebase data;

	//! Tags for Logging
	LogTags tags;
};




#endif /* INCLUDE_CPUCORE_SIGNALS_H_ */
