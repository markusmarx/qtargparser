
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
	// test_space_in_argument_name
	//

	UNIT_START( test_space_in_argument_name )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1String( " one" ),
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_space_in_argument_name )


	//
	// test_delimiter_is_a_flag
	//

	UNIT_START( test_delimiter_is_a_flag )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1Char( '-' ), QString(),
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_delimiter_is_a_flag )


	//
	// test_space_is_a_flag
	//

	UNIT_START( test_space_is_a_flag )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1Char( ' ' ), QString(),
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_space_is_a_flag )


	//
	// test_tab_is_a_flag
	//

	UNIT_START( test_tab_is_a_flag )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1Char( '\t' ), QString(),
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_tab_is_a_flag )


	//
	// test_empty_name
	//

	UNIT_START( test_empty_name )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QtArg one( QString(),
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_empty_name )


	//
	// test_empty_name_in_list_of_names
	//

	UNIT_START( test_empty_name_in_list_of_names )

		QStringList arguments;
		QtArgCmdLine cmd( arguments );

		QStringList names;
		names << QLatin1String( "one" ) << QLatin1String( "" )
			<< QLatin1String( "three" );

		QtArg one( names,
			QLatin1String( "It's our argument with dissallowed name or flag" ) );

		CHECK_THROW( QtArgDissallowedFlagOrNameEx, cmd.addArg( one ); )

	UNIT_FINISH( test_empty_name_in_list_of_names )


	//
	// test_correct_name
	//

	UNIT_START( test_correct_name )

		const QString value = QLatin1String( "value" );

		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "--correct-argument" ) << value;

		QtArgCmdLine cmd( arguments );

		QtArg one( QLatin1Char( 'a' ), QLatin1String( "correct-argument" ),
			QLatin1String( "It's our argument with correct name and flag" ),
			false, true );

		cmd.addArg( one );

		CHECK_CONDITION( one.value().toString().isEmpty() )

		cmd.parse();

		CHECK_CONDITION( one.value().toString() == value )

	UNIT_FINISH( test_correct_name )

UNIT_TEST_FINISH
