
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
#include <QtArg/CmdLine>

// Qt include.
#include <QtCore/QString>
#include <QtCore/QStringList>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START

	//
	// test_very_similar_names
	//

	UNIT_START( test_very_similar_names )

		QStringList arguments;
		arguments << QLatin1String( "test" )
			<< QLatin1String( "--log" ) << QLatin1String( "log.txt" )
			<< QLatin1String( "--log1" ) << QLatin1String( "log1.txt" );

		QtArgCmdLine cmd( arguments );

		QtArg log( QtArgIface::NamesList() << QLatin1String( "log" ),
			QLatin1String( "description log file" ), false, true );
		QtArg log1( QtArgIface::NamesList() << QLatin1String( "log1" ),
			QLatin1String( "description log file2" ), false, true );

		cmd.addArg( log1 );
		cmd.addArg( log );

		cmd.parse();

		CHECK_CONDITION( log.value().toString() == QLatin1String( "log.txt" ) )
		CHECK_CONDITION( log1.value().toString() == QLatin1String( "log1.txt" ) )

	UNIT_FINISH( test_very_similar_names )

UNIT_TEST_FINISH
