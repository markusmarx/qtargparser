
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

// Qt include.
#include <QtCore/QString>
#include <QtCore/QStringList>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START


	//
	// test_xor_correctly_used
	//

	UNIT_START( test_xor_correctly_used )

		QStringList arguments;
		arguments << QLatin1String( "program" ) << QLatin1String( "--one" );

		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1String( "one" ) );
		QtArg two( QLatin1String( "two" ) );
		QtXorArg xored( one, two, QLatin1String( "xored" ) );

		cmd.addArg( xored );

		CHECK_CONDITION( one.value().toBool() == false )
		CHECK_CONDITION( two.value().toBool() == false )

		cmd.parse();

		CHECK_CONDITION( xored.isDefined() == true )
		CHECK_CONDITION( one.value().toBool() == true )
		CHECK_CONDITION( two.value().toBool() == false )

	UNIT_FINISH( test_xor_correctly_used )


	//
	// test_two_args_defined_under_xor
	//

	UNIT_START( test_two_args_defined_under_xor )

		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "--one" ) << QLatin1String( "--two" );

		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1String( "one" ) );
		QtArg two( QLatin1String( "two" ) );
		QtXorArg xored( one, two, QLatin1String( "xored" ) );

		cmd.addArg( xored );

		CHECK_THROW( QtArgXORMaskNotObservedEx, cmd.parse(); )

	UNIT_FINISH( test_two_args_defined_under_xor )


	//
	// test_adding_required_arg_under_xor_must_fail
	//

	UNIT_START( test_adding_required_arg_under_xor_must_fail )

		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "--one" ) << QLatin1String( "--two" );

		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1String( "one" ), QString(), true );
		QtArg two( QLatin1String( "two" ) );

		CHECK_THROW( QtArgRequiredArgumentUnderXORMaskEx,
			QtXorArg xored( one, two, QLatin1String( "xored" ) ); )

	UNIT_FINISH( test_adding_required_arg_under_xor_must_fail )


	//
	// test_mandatory_xor_arg_not_defined
	//

	UNIT_START( test_mandatory_xor_arg_not_defined )

		QStringList arguments;
		arguments << QLatin1String( "program" );

		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1String( "one" ) );
		QtArg two( QLatin1String( "two" ) );
		QtXorArg xored( one, two, QLatin1String( "xored" ), true );

		cmd.addArg( xored );

		CHECK_THROW( QtArgNotDefinedMandatoryArgumentEx, cmd.parse(); )

	UNIT_FINISH( test_mandatory_xor_arg_not_defined )

UNIT_TEST_FINISH
