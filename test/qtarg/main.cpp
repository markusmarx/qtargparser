
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

// Qt include.
#include <QtCore/QString>
#include <QtCore/QStringList>

// unit test helper.
#include <test/helper/helper.hpp>

// QtArg include.
#include <QtArg/Arg>


UNIT_TEST_START

	//
	// test_qtarg_operators
	//

	UNIT_START( test_qtarg_operators )

		const QLatin1Char arg1Flag = QLatin1Char( 'a' );
		const QLatin1String arg1Name = QLatin1String( "one" );

		QtArg arg1( arg1Flag, arg1Name );
		QtArg arg2( arg1 );
		QtArg arg3 = arg1;

		CHECK_CONDITION( arg1 == arg2 )
		CHECK_CONDITION( arg1 == arg3 )
		CHECK_CONDITION( arg2 == arg3 )

		const QLatin1Char arg4Flag = QLatin1Char( 'b' );
		const QLatin1String arg4Name = QLatin1String( "two" );

		QtArg arg4( arg4Flag, arg4Name );

		CHECK_CONDITION( arg1 != arg4 )

		CHECK_CONDITION( arg1 == arg1Flag )
		CHECK_CONDITION( arg1 != arg4Flag )
		CHECK_CONDITION( arg1 == arg1Name )
		CHECK_CONDITION( arg1 != arg4Name )

	UNIT_FINISH( test_qtarg_operators )


	//
	// test_set_and_get
	//

	namespace /* anonymous */ {

		class Visitor
			:	public QtArgVisitorIface
		{
			public:
				void visit( QtArgCmdLineContext & )
				{
				}
		};

		class Constraint
			:	public QtArgConstraintIface
		{
			public:
				bool check( const QVariant & value ) const
				{
					return true;
				}
		};

	} /* namespace anonymous */

	UNIT_START( test_set_and_get )

		const QLatin1Char argFlag1 = QLatin1Char( 'a' );

		QtArg arg( argFlag1 );

		CHECK_CONDITION( arg.flag() == argFlag1 )

		const QLatin1Char argFlag2 = QLatin1Char( 'b' );

		arg.setFlag( argFlag2 );

		CHECK_CONDITION( arg.flag() == argFlag2 )

		const QtArgIface::FlagsList argFlags =
			QtArgIface::FlagsList() << argFlag1 << argFlag2;

		arg.setFlags( argFlags );

		CHECK_CONDITION( arg.flags() == argFlags )

		const QLatin1String argName1 = QLatin1String( "one" );

		arg.setName( argName1 );

		CHECK_CONDITION( arg.name() == argName1 )

		const QLatin1String argName2 = QLatin1String( "two" );

		arg.setName( argName2 );

		CHECK_CONDITION( arg.name() == argName2 )

		const QtArgIface::NamesList argNames =
			QtArgIface::NamesList() << argName1 << argName2;

		arg.setNames( argNames );

		CHECK_CONDITION( arg.names() == argNames )

		const QLatin1String argDescription =
			QLatin1String( "description" );

		arg.setDescription( argDescription );

		CHECK_CONDITION( arg.description() == argDescription )

		const QLatin1String argLongDescription =
			QLatin1String( "long description" );

		arg.setLongDescription( argLongDescription );

		CHECK_CONDITION( arg.longDescription() == argLongDescription )

		CHECK_CONDITION( arg.isRequired() == false )

		arg.setRequired( true );

		CHECK_CONDITION( arg.isRequired() == true )

		CHECK_CONDITION( arg.isWithValue() == false )

		arg.setWithValue( true );

		CHECK_CONDITION( arg.isWithValue() == true )

		Visitor visitor;

		arg.setVisitor( &visitor );

		CHECK_CONDITION( arg.visitor() == &visitor )

		Constraint constraint;

		arg.setConstraint( &constraint );

		CHECK_CONDITION( arg.constraint() == &constraint )

		CHECK_CONDITION( arg.isPresent() == false )

		arg.setPresent( true );

		CHECK_CONDITION( arg.isPresent() == true )

		CHECK_CONDITION( arg.isDefined() == false )

		arg.setDefined( true );

		CHECK_CONDITION( arg.isDefined() == true )

		const QVariant argValue = QVariant( true );

		arg.setValue( argValue );

		CHECK_CONDITION( arg.value() == argValue )

		QtArgCmdLineIface::QtArgumentsList argumentsList =
			QtArgCmdLineIface::QtArgumentsList() << &arg;

		CHECK_CONDITION( arg.arguments() == argumentsList )

	UNIT_FINISH( test_set_and_get )

UNIT_TEST_FINISH
