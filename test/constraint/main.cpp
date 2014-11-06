
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
#include <QtArg/ArgConstraint>
#include <QtArg/CmdLine>

// Qt include.
#include <QtCore/QString>
#include <QtCore/QStringList>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START

	namespace /* anonymous */ {

		//
		// TestConstraint
		//

		class TestConstraint
			:	public QtArgConstraintIface
		{
			public:
				bool check( const QVariant & value ) const
				{
					return ( value.toBool() == false );
				}
		}; // class TestConstraint

	} /* namespace anonymous */


	//
	// test_constraint
	//

	UNIT_START( test_constraint )

		const QString argName = QLatin1String( "one" );

		QStringList arguments;
		arguments << QLatin1String( "program" )
			<< QLatin1String( "--" ) + argName;

		QtArgCmdLine cmd( arguments );

		QtArg one( argName );
		TestConstraint constraint;
		one.setConstraint( &constraint );

		cmd.addArg( one );

		CHECK_CONDITION( one.value().toBool() == false )

		CHECK_THROW( QtArgContraintNotObservedEx, cmd.parse(); )

		CHECK_CONDITION( one.value().toBool() == true )

	UNIT_FINISH( test_constraint )

UNIT_TEST_FINISH
