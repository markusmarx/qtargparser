
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

// QtArg include.
#include <QtArg/CmdLine>
#include <QtArg/CmdLineContext>
#include <QtArg/Exceptions>
#include <QtArg/XorArg>
#include <QtArg/Help>

// Qt include.
#include <QtCore/QTextStream>

// Visitor example include.
#include <samples/visitor/h/main.hpp>


//
// MyArgException
//

MyArgException::MyArgException( const QString & desc )
	:	QtArgBaseException( desc )
{
}


//
// MyArg
//

MyArg::MyArg()
	:	QtArg( QLatin1Char( 'a' ), QLatin1String( "arg" ),
			QLatin1String( "This is our argument with two required values" ),
			true, true )
{
	m_visitor.setArg( this );
	setVisitor( &m_visitor );
}

void
MyArg::setSecondValue( const QVariant & val )
{
	m_secondValue = val;
}

const QVariant &
MyArg::secondValue() const
{
	return m_secondValue;
}


//
// MyVisitor
//

MyVisitor::MyVisitor()
	:	m_arg( 0 )
{
}

void
MyVisitor::setArg( MyArg * arg )
{
	m_arg = arg;
}

void
MyVisitor::visit( QtArgCmdLineContext & context )
{
	if( !m_arg )
		throw MyArgException( QLatin1String( "Argument wasn't defined." ) );

	if( !context.atEnd() )
		m_arg->setSecondValue( context.next() );
	else
		throw MyArgException( QLatin1String( "There is no second value "
			"for the MyArg argument." ) );
}


void
main( int argc, char ** argv )
{
	try {
		MyArg arg;

		QtArgCmdLine cmdLine( argc, argv );

		QtArgHelp help( &cmdLine );
		help.printer()->setProgramDescription( QLatin1String(
			"This program shows how to use QtArgVisitorIface." ) );

		cmdLine.addArg( arg );
		cmdLine.addArg( help );

		cmdLine.parse();

		QTextStream out( stdout );

		out << QLatin1String( "Here is values of our argument : " )
			<< arg.value().toString()
			<< QLatin1String( "; " ) << arg.secondValue().toString()
			<< endl;
	}
	catch( const QtArgHelpHasPrintedEx & x )
	{
	}
	catch( const QtArgBaseException & x )
	{
		QTextStream out( stdout );
		out << QLatin1String( "Error : " ) << x.whatAsQString() << endl;
	}
}
