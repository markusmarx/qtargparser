
/*!
	\file

	\brief Visitor usage example.

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2010-2012 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef QTARG__SAMPLES__VISITOR__MAIN_HPP__INCLUDED
#define QTARG__SAMPLES__VISITOR__MAIN_HPP__INCLUDED

// QtArg include.
#include <QtArg/Arg>
#include <QtArg/Visitor>
#include <QtArg/Exceptions>

// Qt include.
#include <QtCore/QVariant>


class MyArg;


//
// MyArgException
//

//! Exception during processing of the argument with the two values??.
class MyArgException
	:	public QtArgBaseException
{
public:
	explicit MyArgException( const QString & desc );
}; // class MyArgException


//
// MyVisitor
//

//! Visitor for argument with the two values.
class MyVisitor
	:	public QtArgVisitorIface
{
public:
	MyVisitor();

	//! Set the argument, which belongs to a visitor.
	void setArg( MyArg * arg );

	void visit( QtArgCmdLineContext & context );

private:
	//! The argument, which belongs to a visitor.
	MyArg * m_arg;
}; // class MyVisitor


//
// MyArg
//

//! An argument with the two values.
class MyArg
	:	public QtArg
{
public:
	MyArg();

	//! Set second value.
	void setSecondValue( const QVariant & val );

	//! \return Second value.
	const QVariant & secondValue() const;

private:
	//! Visitor.
	MyVisitor m_visitor;
	//! Second value for this argument.
	QVariant m_secondValue;
}; // class MyArg

#endif // QTARG__SAMPLES__VISITOR__MAIN_HPP__INCLUDED
