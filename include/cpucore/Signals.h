/*
 * signals.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_SIGNALS_H_
#define INCLUDE_CPUCORE_SIGNALS_H_
#include <cstdlib>
#include <vector>


/*!
 * \brief abstract class that implements the callback interface for a signal
 */
class DrivenObject{
public:
	virtual ~DrivenObject(){}
	virtual void computeSignals() = 0;
};

/*!
 * \brief class to implement signals inbetween sections of the cpu
 * \tparam typebase the datatype to be used in this signal
 */
template <typename typebase>
class Signal{
public:
	//! Initialize the signal. Must be able to assign 0 to typebase
	Signal(){
		data = 0;
	}

	/*!
	 * \brief Register a new object to be updated with this signal chagnes
	 *
	 * \param updatable the object to be updated
	 */
	void registerDriven(DrivenObject* driven){
		updatelist.push_back(driven);
	}

	/*!
	 * \breif Put data into the signal.
	 *
	 * \param data the data to be inserted
	 */
	void setData(typebase data){
		this->data = data;
		for(auto module : updatelist){
			module->computeSignals();
		}
	}

	/*!
	 * \brief Get the data in the signal.
	 *
	 * \return the current data in the signal
	 */
	typebase getData(){
		return data;
	}

	/*!
	 * \brief syntactic sugar for setData
	 */
	void operator=(const typebase &in){
		data = in;
	}

	/*!
	 * \brief syntactic sugar for getData
	 */

private:
	//! The driving node for this signal
	std::vector<DrivenObject*> updatelist;
	//! The data on the signal line
	typebase data;
};

/*!
 * \brief Class to implement a simple boolean mux
 */
template <typename datatype>
class Mux: public DrivenObject{
public:
	Mux(Signal<datatype>& input1,
			Signal<datatype>& input2,
			Signal<bool>& control,
			Signal<datatype>& output)
	:input1(input1),
	 input2(input2),
	 control(control),
	 output(output)
	{
		input1.registerDriven(this);
		input2.registerDriven(this);
		control.registerDriven(this);
	}

	void computeSignals(){
		datatype outputval;
		outputval = control.getData() ? input2.getData() : input1.getData();
		output.setData(outputval);
	}

private:
	//! First input to the mux (False value)
	Signal<datatype>& input1;
	//! Second input to the mux (True value)
	Signal<datatype>& input2;
	//! Control input to the mux
	Signal<bool>& control;
	//! Output of the mux
	Signal<datatype>& output;
};



#endif /* INCLUDE_CPUCORE_SIGNALS_H_ */
