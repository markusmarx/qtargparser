
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
	// test_two_flags_in_composition
	//

	UNIT_START( test_two_flags_in_composition )

		QStringList arguments;
		arguments << QLatin1String( "program" ) << QLatin1String( "-ab" );

		QtArgCmdLine cmd( arguments );

		QtArg a( QLatin1Char( 'a' ) );
		QtArg b( QLatin1Char( 'b' ) );

		cmd.addArg( a );
		cmd.addArg( b );

		CHECK_CONDITION( a.value().toBool() == false )
		CHECK_CONDITION( b.value().toBool() == false )

		cmd.parse();

		CHECK_CONDITION( a.value().toBool() == true )
		CHECK_CONDITION( b.value().toBool() == true )

	UNIT_FINISH( test_two_flags_in_composition )


	//
	// test_flag_with_correct_defined_option_in_composition
	//

	UNIT_START( test_flag_with_correct_defined_option_in_composition )

		const QString value = QLatin1String( "value" );
		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "-ab" ) << value;

		QtArgCmdLine cmd( arguments );

		QtArg a( QLatin1Char( 'a' ) );
		QtArg b( QLatin1Char( 'b' ), QString(), QString(), false, true );

		cmd.addArg( a );
		cmd.addArg( b );

		CHECK_CONDITION( a.value().toBool() == false )
		CHECK_CONDITION( b.value().toString().isEmpty() )

		cmd.parse();

		CHECK_CONDITION( a.value().toBool() == true )
		CHECK_CONDITION( b.value().toString() == value )

	UNIT_FINISH( test_flag_with_correct_defined_option_in_composition )


	//
	// test_flag_composition_with_unexpected_option_after_it
	//

	UNIT_START( test_flag_composition_with_unexpected_option_after_it )

		const QString value = QLatin1String( "value" );
		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "-ab" ) << value;

		QtArgCmdLine cmd( arguments );

		QtArg a( QLatin1Char( 'a' ), QString(), QString(), false, true );
		QtArg b( QLatin1Char( 'b' ) );

		cmd.addArg( a );
		cmd.addArg( b );

		CHECK_CONDITION( a.value().toString().isEmpty() )
		CHECK_CONDITION( b.value().toBool() == false )

		CHECK_THROW( QtArgUnexpectedOptionEx, cmd.parse(); )

	UNIT_FINISH( test_flag_composition_with_unexpected_option_after_it )

UNIT_TEST_FINISH
