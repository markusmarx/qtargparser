
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
	// test_complex_1
	//

	UNIT_START( test_complex_1 )

		QStringList arguments;
		arguments << QLatin1String( "test" )
			<< QLatin1String( "-a" ) << QLatin1String( "1" )
			<< QLatin1String( "--bb" ) << QLatin1String( "2" )
			<< QLatin1String( "--cc" ) << QLatin1String( "3" )
			<< QLatin1String( "-d" ) << QLatin1String( "4" )
			<< QLatin1String( "-e" ) << QLatin1String( "-f" )
			<< QLatin1String( "-g" )
			<< QLatin1String( "-i" ) << QLatin1String( "5" );

		QtArgCmdLine cmd( arguments );

		QtArg a( QLatin1Char( 'a' ), QString(), QString(), false, true );
		QtArg b( QLatin1String( "bb" ), QString(), false, true );
		QtArg c( QLatin1String( "cc" ), QString(), false, true );
		QtArg d( QLatin1Char( 'd' ), QString(), QString(), false, true );
		QtArg e( QLatin1Char( 'e' ), QString(), QString(), false, false );
		QtArg f( QLatin1Char( 'f' ), QString(), QString(), false, false );
		QtArg g( QLatin1Char( 'g' ), QString(), QString(), false, false );
		QtArg i( QLatin1Char( 'i' ), QString(), QString(), false, true );

		cmd.addArg( a );
		cmd.addArg( b );
		cmd.addArg( c );
		cmd.addArg( d );
		cmd.addArg( e );
		cmd.addArg( f );
		cmd.addArg( g );
		cmd.addArg( i );

		cmd.parse();

		CHECK_CONDITION( a.value().toString() == QLatin1String( "1" ) )
		CHECK_CONDITION( b.value().toString() == QLatin1String( "2" ) )
		CHECK_CONDITION( c.value().toString() == QLatin1String( "3" ) )
		CHECK_CONDITION( d.value().toString() == QLatin1String( "4" ) )
		CHECK_CONDITION( e.value().toBool() == true )
		CHECK_CONDITION( f.value().toBool() == true )
		CHECK_CONDITION( g.value().toBool() == true )
		CHECK_CONDITION( i.value().toString() == QLatin1String( "5" ) )

	UNIT_FINISH( test_complex_1 )


	//
	// test_complex_2
	//

	UNIT_START( test_complex_2 )

	QStringList arguments;
	arguments << QLatin1String( "test" )
		<< QLatin1String( "-a" ) << QLatin1String( "1" )
		<< QLatin1String( "--bb" ) << QLatin1String( "2" )
		<< QLatin1String( "--cc=3" )
		<< QLatin1String( "-d4" )
		<< QLatin1String( "-ef" )
		<< QLatin1String( "-gi5" );

	QtArgCmdLine cmd( arguments );

	QtArg a( QLatin1Char( 'a' ), QString(), QString(), false, true );
	QtArg b( QLatin1String( "bb" ), QString(), false, true );
	QtArg c( QLatin1String( "cc" ), QString(), false, true );
	QtArg d( QLatin1Char( 'd' ), QString(), QString(), false, true );
	QtArg e( QLatin1Char( 'e' ), QString(), QString(), false, false );
	QtArg f( QLatin1Char( 'f' ), QString(), QString(), false, false );
	QtArg g( QLatin1Char( 'g' ), QString(), QString(), false, false );
	QtArg i( QLatin1Char( 'i' ), QString(), QString(), false, true );

	cmd.addArg( a );
	cmd.addArg( b );
	cmd.addArg( c );
	cmd.addArg( d );
	cmd.addArg( e );
	cmd.addArg( f );
	cmd.addArg( g );
	cmd.addArg( i );

	cmd.parse();

	CHECK_CONDITION( a.value().toString() == QLatin1String( "1" ) )
	CHECK_CONDITION( b.value().toString() == QLatin1String( "2" ) )
	CHECK_CONDITION( c.value().toString() == QLatin1String( "3" ) )
	CHECK_CONDITION( d.value().toString() == QLatin1String( "4" ) )
	CHECK_CONDITION( e.value().toBool() == true )
	CHECK_CONDITION( f.value().toBool() == true )
	CHECK_CONDITION( g.value().toBool() == true )
	CHECK_CONDITION( i.value().toString() == QLatin1String( "5" ) )

	UNIT_FINISH( test_complex_2 )

	//
	// test_complex_3
	//

	UNIT_START( test_complex_3 )

	QStringList arguments;
	arguments << QLatin1String( "test" )
		<< QLatin1String( "-a" ) << QLatin1String( "1" )
		<< QLatin1String( "--bb" ) << QLatin1String( "2" )
		<< QLatin1String( "--cc=3" ) << QLatin1String( "-d4" )
		<< QLatin1String( "-efgi" ) << QLatin1String( "5" );

	QtArgCmdLine cmd( arguments );

	QtArg a( QLatin1Char( 'a' ), QString(), QString(), false, true );
	QtArg b( QLatin1String( "bb" ), QString(), false, true );
	QtArg c( QLatin1String( "cc" ), QString(), false, true );
	QtArg d( QLatin1Char( 'd' ), QString(), QString(), false, true );
	QtArg e( QLatin1Char( 'e' ), QString(), QString(), false, false );
	QtArg f( QLatin1Char( 'f' ), QString(), QString(), false, false );
	QtArg g( QLatin1Char( 'g' ), QString(), QString(), false, false );
	QtArg i( QLatin1Char( 'i' ), QString(), QString(), false, true );

	cmd.addArg( a );
	cmd.addArg( b );
	cmd.addArg( c );
	cmd.addArg( d );
	cmd.addArg( e );
	cmd.addArg( f );
	cmd.addArg( g );
	cmd.addArg( i );

	cmd.parse();

	CHECK_CONDITION( a.value().toString() == QLatin1String( "1" ) )
	CHECK_CONDITION( b.value().toString() == QLatin1String( "2" ) )
	CHECK_CONDITION( c.value().toString() == QLatin1String( "3" ) )
	CHECK_CONDITION( d.value().toString() == QLatin1String( "4" ) )
	CHECK_CONDITION( e.value().toBool() == true )
	CHECK_CONDITION( f.value().toBool() == true )
	CHECK_CONDITION( g.value().toBool() == true )
	CHECK_CONDITION( i.value().toString() == QLatin1String( "5" ) )

	UNIT_FINISH( test_complex_3 )


	//
	// test_complex_4
	//

	UNIT_START( test_complex_4 )

	QStringList arguments;
	arguments << QLatin1String( "test" )
		<< QLatin1String( "-a" ) << QLatin1String( "1" )
		<< QLatin1String( "-b=2" )
		<< QLatin1String( "-c3" )
		<< QLatin1String( "-d" ) << QLatin1String( "4" );

	QtArgCmdLine cmd( arguments );

	QtArg a( QLatin1Char( 'a' ), QString(), QString(), false, true );
	QtArg b( QLatin1Char( 'b' ), QString(), QString(), false, true );
	QtArg c( QLatin1Char( 'c' ), QString(), QString(), false, true );
	QtArg d( QLatin1Char( 'd' ), QString(), QString(), false, true );

	cmd.addArg( a );
	cmd.addArg( b );
	cmd.addArg( c );
	cmd.addArg( d );

	cmd.parse();

	CHECK_CONDITION( a.value().toString() == QLatin1String( "1" ) )
	CHECK_CONDITION( b.value().toString() == QLatin1String( "2" ) )
	CHECK_CONDITION( c.value().toString() == QLatin1String( "3" ) )
	CHECK_CONDITION( d.value().toString() == QLatin1String( "4" ) )

	UNIT_FINISH( test_complex_4 )


	//
	// test_complex_5
	//

	UNIT_START( test_complex_5 )

	QStringList arguments;
	arguments << QLatin1String( "test" )
		<< QLatin1String( "--a1" ) << QLatin1String( "1" )
		<< QLatin1String( "--b2=2" )
		<< QLatin1String( "--c3=3" )
		<< QLatin1String( "--d4" ) << QLatin1String( "4" );

	QtArgCmdLine cmd( arguments );

	QtArg a( QLatin1String( "a1" ), QString(), false, true );
	QtArg b( QLatin1String( "b2" ), QString(), false, true );
	QtArg c( QLatin1String( "c3" ), QString(), false, true );
	QtArg d( QLatin1String( "d4" ), QString(), false, true );

	cmd.addArg( a );
	cmd.addArg( b );
	cmd.addArg( c );
	cmd.addArg( d );

	cmd.parse();

	CHECK_CONDITION( a.value().toString() == QLatin1String( "1" ) )
	CHECK_CONDITION( b.value().toString() == QLatin1String( "2" ) )
	CHECK_CONDITION( c.value().toString() == QLatin1String( "3" ) )
	CHECK_CONDITION( d.value().toString() == QLatin1String( "4" ) )

	UNIT_FINISH( test_complex_5 )

UNIT_TEST_FINISH
