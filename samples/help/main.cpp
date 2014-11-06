
/*!
	\file

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
#include <QtArg/Arg>
#include <QtArg/XorArg>
#include <QtArg/CmdLine>
#include <QtArg/Help>

// Qt include.
#include <QtCore/QDebug>


void main( int argc, char ** argv )
{
	try {
		QtArgCmdLine cmd( argc, argv );

		QtArg one( QtArgIface::NamesList() << QLatin1String( "one" )
				<< QLatin1String( "and-one" ),
			QLatin1String( "This is requred argument with value. "
				"And this is his description." ), true, true );
		one.setLongDescription( QLatin1String( "This argument is required and have value."
			"And this is a long description of the this argument. "
			"Note that you must set value for this argument" ) );

		QtArg timeout( QLatin1String( "timeout" ), QLatin1String( "Timeout for the application. "
			"Value is milliseconds." ), false, true );
		timeout.setValueSpecifier( QLatin1String( "ms" ) );

		QtArg a( QtArgIface::FlagsList() << QLatin1Char( 'a' )
				<< QLatin1Char( 'c' ) << QLatin1Char( 'd' ),
			QtArgIface::NamesList() << QLatin1String( "three-flags" ),
			QLatin1String( "This argument uses three flags and one name. "
				"And this argument will be under the XOR mask with -b argument." ) );

		QtArg b( QtArgIface::FlagsList() << QLatin1Char( 'b' )
				<< QLatin1Char( 'e' ) << QLatin1Char( 'f' ),
			QtArgIface::NamesList(), QLatin1String( "This argument uses three flags too. "
				"And he will be under the XOR mask with -a argument." ),
			false, true );

		QtXorArg xored( a, b, QLatin1String( "xored" ) );

		QtArgHelp help( &cmd );
		help.printer()->setProgramDescription(
			QLatin1String( "This application just show power of the QtArg help." ) );
		help.printer()->setExecutableName( QLatin1String( argv[0] ) );

		cmd.addArg( one );
		cmd.addArg( timeout );
		cmd.addArg( xored );
		cmd.addArg( help );

		cmd.parse();
	}
	catch( const QtArgHelpHasPrintedEx & x )
	{
	}
	catch( const QtArgBaseException & x )
	{
		qDebug() << x.what();
	}
}
