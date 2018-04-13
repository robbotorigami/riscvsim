/*
 * signals.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_SIGNALS_H_
#define INCLUDE_CPUCORE_SIGNALS_H_
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>

#include "instruction/IInstructions.h"


/*!
 * \brief abstract class that implements the callback interface for a signal
 */
class DrivenObject{
public:
	virtual ~DrivenObject(){}
	virtual void computeSignals() = 0;
};

/*!
 * \brief abstract class to implement objects which should only update on a clock cycle
 */
enum ClockEdge{
	RISING,
	FALLING,
};
class ClockableObject{
public:
	virtual ~ClockableObject(){}
	virtual void clock(ClockEdge edge) = 0;
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
	 * \brief Remove an object from the update list
	 *
	 * \param updatable the object to be removed
	 */
	void unregisterDriven(DrivenObject* driven){
		auto i = std::find(updatelist.begin(), updatelist.end(), driven);
		assert(i != updatelist.end());
		updatelist.erase(i);
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
	typebase getData() const;

	Signal& operator=(typebase d){
		setData(d);
		return *this;
	}

	operator typebase() const{
		return getData();
	}

private:
	//! The driving node for this signal
	std::vector<DrivenObject*> updatelist;
	//! The data on the signal line
	typebase data;
};

template <typename typebase>
typebase Signal<typebase>::getData() const{
	return data;
}


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

	~Mux(){
		input1.unregisterDriven(this);
		input2.unregisterDriven(this);
		control.unregisterDriven(this);
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

/*!
 * \brief Simple class to represent a clockable register
 */
template <typename datatype>
class Register: public ClockableObject{
public:
	Register(Signal<datatype>& input,
			Signal<datatype>& output)
	:input(input),
	 stored(0),
	 output(output)
	{
	}

	void clock(ClockEdge edge){
		if(edge == RISING)
			stored = input;
		if(edge == FALLING)
			output = stored;
	}

private:
	//! Input to the register
	Signal<datatype>& input;
	datatype stored;
	//! Output of the register
	Signal<datatype>& output;
};

/*!
 * \brief Simple class to implement an adder
 */
template <typename datatype>
class Adder: public DrivenObject{
public:
	Adder(Signal<datatype>& input1, Signal<datatype>& input2, Signal<datatype>& output)
	:input1(input1), input2(input2), output(output)
	{
		input1.registerDriven(this);
		input2.registerDriven(this);
	}

	~Adder(){
		input1.unregisterDriven(this);
		input2.unregisterDriven(this);
	}

	void computeSignals(){
		output = static_cast<datatype>(input1) + static_cast<datatype>(input2);
	}

private:
	//! First input to the adder
	Signal<datatype>& input1;
	//! Second input to the adder
	Signal<datatype>& input2;
	//! Output of the adder
	Signal<datatype>& output;
};

/*!
 * \brief Simple class to connect two signals
 */
template <typename datatype>
class Coupler: DrivenObject{
public:
	Coupler(Signal<datatype>& input, Signal<datatype>& output)
	:input(input), output(output){
		input.registerDriven(this);
	}

	~Coupler(){
		input.unregisterDriven(this);
	}

	void computeSignals(){
		output = static_cast<datatype>(input);
	}
private:
	//! Input Signal
	Signal<datatype>& input;
	//! Output Signal
	Signal<datatype>& output;
};

/*!
 * \brief Simple class to implement a shifter
 */
template <typename datatype, size_t shiftbits>
class Shifter: DrivenObject{
public:
	Shifter(Signal<datatype>& input, Signal<datatype>& output)
	:input(input), output(output)
	{
		input.registerDriven(this);
	}

	~Shifter(){
		input.unregisterDriven(this);
	}

	void computeSignals(){
		output = static_cast<datatype>(input) << shiftbits;
	}
private:
	//! Input Signal
	Signal<datatype>& input;
	//! Output Signal
	Signal<datatype>& output;
};

template <typename from, typename to>
class Converter: DrivenObject{
public:
	Converter(Signal<from>& input, Signal<to>& output)
	:input(input), output(output)
	{
		input.registerDriven(this);
	}
	~Converter(){
		input.unregisterDriven(this);
	}

	void computeSignals(){
		output = static_cast<to>(static_cast<from>(input));
	}
private:
	Signal<from>& input;
	Signal<to>& output;
};

#endif /* INCLUDE_CPUCORE_SIGNALS_H_ */
