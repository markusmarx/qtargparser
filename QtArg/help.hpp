
/*!
	\file

	\brief Help printer.

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

#ifndef QTARG__HELP_HPP__INCLUDED
#define QTARG__HELP_HPP__INCLUDED

// Qt include.
#include <QTextStream>
#include <QMap>

// QtArg include.
#include "cmdline.hpp"
#include "arg.hpp"
#include "helpiface.hpp"
#include "exceptions.hpp"
#include "xorarg.hpp"
#include "multiarg.hpp"


//
// QtArgDefaultHelpPrinter
//

//! Default implementation of the QtArgHelpPrinterIface.
class QtArgDefaultHelpPrinter
	:	public QtArgHelpPrinterIface
{
	friend class QtArgHelp;

	private:
		QtArgDefaultHelpPrinter( const QtArgDefaultHelpPrinter & );
		QtArgDefaultHelpPrinter & operator = ( const QtArgDefaultHelpPrinter & );

	protected:
		QtArgDefaultHelpPrinter();

		virtual ~QtArgDefaultHelpPrinter();

	public:
		//! \return Static instance of this help printer.
		static QtArgDefaultHelpPrinter * instance()
		{
			static QtArgDefaultHelpPrinter printer;

			return &printer;
		}

		//! Print help into string.
		virtual QString printInString();

		//! Print help for the given argument into string.
		virtual QString printForArgumentInString( const QString & name );

		//! Print help for the given argument into string.
		virtual QString printForArgumentInString( const QChar & name );

		//! Print help.
		virtual void print();

		//! Print help for the given argument.
		virtual void printForArgument( const QString & name );

		//! Print help for the given argument.
		virtual void printForArgument( const QChar & name );

		/*!
			Set program description that will be used
			as first line in the help.
		*/
		virtual void setProgramDescription( const QString & desc );

		/*!
			Set executable name that defined in argv[0]
			or something else.
		*/
		virtual void setExecutableName( const QString & exec );

		//! Set command line.
		virtual void setCmdLine( QtArgCmdLine * cmdLine );

		//! Set length of the line in help.
		virtual void setLineLength( int length );

	private:
		//! Print help for the given argument.
		QString printForArgument( QtArgIface * arg );
		//! Set "HELP" string for the given argument.
		void setHelpString( QtArgIface * arg, const QString & help );
		//! Set delimiter character.
		void setDelimiterChar( const QChar & delim );
		//! Mark usage string if arhument is unrequired.
		QString markUnrequiredArgumentInUsageString( const QString & usage );
		//! Replace markers in "USAGE" string.
		void replaceMarkersInUsage( QString & usage );
		//! Format usage string.
		void formatUsageString( QString & usage, int offset, int width );
		//! Format string.
		void formatString( const QStringList & words,
			QString & str, int offset, int width );
		//! Replace markers in "HELP" strings.
		void replaceMarkersInHelp();
		//! Replace QtArgHelpPrinterIface::beforeNames markers.
		void replaceBeforeNames( QMutableMapIterator< QtArgIface*, QString > & it,
			int beforeNamesLength );
		/*!
			Replace QtArgHelpPrinterIface::beforeDescription markers
			and set description.
		*/
		void replaceBeforeDescriptionAndSetDescription(
			QMutableMapIterator< QtArgIface*, QString > & it,
			int beforeDescriptionLength );
		//! \return Max length of the name in the help.
		int calcNameLength( const QString & help );
		//! \return Length of the flags in the help.
		int calcFlagsLength( const QString & help );
		//! Create "USAGE" string.
		void createUsageString();
		//! Create "HELP" string.
		void createHelpString( const QtArgCmdLineIface::QtArgumentsList & list );
		//! Init names list.
		void initNames( const QtArgCmdLineIface::QtArgumentsList & list );
		//! \return Has required args?
		bool hasRequiredArgs() const;
		//! \return Has optional args?
		bool hasOptionalArgs() const;

	private:
		//! Command line.
		QtArgCmdLine * m_cmdLine;
		//! Names of all available arguments.
		QtArgIface::NamesList m_names;
		//! "HELP" strings.
		QMap< QtArgIface*, QString > m_help;
		//! "USAGE" string.
		QString m_usage;
		//! Max length of the name in the help.
		int m_maxNameLength;
		//! Max length of the flags in the help.
		int m_maxFlagsLength;
		//! Line length.
		int m_lineLength;

		//! Program description printed before help.
		QString m_programDescription;
		//! Executable name.
		QString m_executableName;

		//! Flags marker string.
		QString m_flagsMarker;
		//! Names marker string.
		QString m_namesMarker;

		//! Value of the QtArgHelpPrinterIface::namesSeparator.
		static const QString m_namesSeparator;
}; // class QtArgDefaultHelpPrinter


//
// QtArgDefaultHelpPrinter implementation.
//

const QString QtArgDefaultHelpPrinter::m_namesSeparator =
	QLatin1String( "," );

inline
QtArgDefaultHelpPrinter::QtArgDefaultHelpPrinter()
	:	m_maxNameLength( 0 )
	,	m_maxFlagsLength( 0 )
	,	m_cmdLine( 0 )
	,	m_lineLength( 79 )
{
}

inline
QtArgDefaultHelpPrinter::~QtArgDefaultHelpPrinter()
{
}

inline void
QtArgDefaultHelpPrinter::initNames( const QtArgCmdLineIface::QtArgumentsList & list )
{
	m_names.clear();

	foreach( QtArgIface * arg, list )
	{
		// It's a XOR argument.
		if( arg->arguments().size() > 1 )
			initNames( arg->arguments() );
		else
			m_names.append( arg->names() );
	}
}

inline bool
QtArgDefaultHelpPrinter::hasRequiredArgs() const
{
	QMapIterator< QtArgIface*, QString > it( m_help );

	while( it.hasNext() )
	{
		it.next();

		if( it.key()->isRequired() )
			return true;
	}

	return false;
}

bool
QtArgDefaultHelpPrinter::hasOptionalArgs() const
{
	QMapIterator< QtArgIface*, QString > it( m_help );

	while( it.hasNext() )
	{
		it.next();

		if( !it.key()->isRequired() )
			return true;
	}

	return false;
}

inline QString
QtArgDefaultHelpPrinter::printInString()
{
	initNames( m_cmdLine->arguments() );

	createUsageString();

	createHelpString( m_cmdLine->arguments() );

	replaceMarkersInHelp();

	QString result = m_programDescription;
	result.append( QLatin1String( "\n\nUsage: " ) );
	result.append( m_executableName );
	result.append( QLatin1Char( ' ' ) );
	result.append( m_usage );
	result.append( QLatin1String( "\n\n" ) );

	QMapIterator< QtArgIface*, QString > it( m_help );

	if( hasRequiredArgs() )
	{
		result.append( QLatin1String( "Required arguments:\n" ) );

		while( it.hasNext() )
		{
			it.next();

			if( it.key()->isRequired() )
			{
				result.append( it.value() );
				result.append( QLatin1Char( '\n' ) );
			}
		}
	}

	if( hasOptionalArgs() )
	{
		result.append( QLatin1String( "Optional arguments:\n" ) );

		it.toFront();

		while( it.hasNext() )
		{
			it.next();

			if( !it.key()->isRequired() )
			{
				result.append( it.value() );
				result.append( QLatin1Char( '\n' ) );
			}
		}
	}

	return result;
}

inline QString
QtArgDefaultHelpPrinter::printForArgumentInString( const QString & name )
{
	QtArgIface * arg = m_cmdLine->findArgument( name );

	return printForArgument( arg );
}

inline QString
QtArgDefaultHelpPrinter::printForArgumentInString( const QChar & name )
{
	QtArgIface * arg = m_cmdLine->findArgument( name );

	return printForArgument( arg );
}

inline void
QtArgDefaultHelpPrinter::print()
{
	const QString help = printInString();

	QTextStream stream( stdout );
	stream << help;
}

inline void
QtArgDefaultHelpPrinter::printForArgument( const QString & name )
{
	QtArgIface * arg = m_cmdLine->findArgument( name );

	const QString help = printForArgument( arg );

	QTextStream out( stdout );
	out << help;
}

inline void
QtArgDefaultHelpPrinter::printForArgument( const QChar & name )
{
	QtArgIface * arg = m_cmdLine->findArgument( name );

	const QString help = printForArgument( arg );

	QTextStream out( stdout );
	out << help;
}

inline QString
QtArgDefaultHelpPrinter::printForArgument( QtArgIface * arg )
{
	if( arg )
	{
		initNames( m_cmdLine->arguments() );

		int flagsLength = 0;
		int maxNameLength = 0;

		QString usage = arg->getUsageString( m_names, flagsLength,
			maxNameLength );

		replaceMarkersInUsage( usage );

		formatUsageString( usage, 7, m_lineLength - 7 * 2 );

		QString description;

		if( !arg->longDescription().isEmpty() )
			description = arg->longDescription();
		else
			description = arg->description();

		QStringList words = description.split( QLatin1Char( ' ' ),
			QString::SkipEmptyParts );

		formatString( words, description, 13, m_lineLength - 13 * 2 );

		QString result( QLatin1String( "Usage: " ) );
		result.append( usage );
		result.append( QLatin1String( "\n\nDescription: " ) );
		result.append( description );

		return result;
	}
	else
		return QString();
}

inline void
QtArgDefaultHelpPrinter::createUsageString()
{
	m_usage.clear();

	int flagsLength = 0;
	int maxNameLength = 0;

	foreach( QtArgIface * arg, m_cmdLine->arguments() )
	{
		if( !arg->isRequired() && arg->arguments().size() == 1 )
			m_usage.append( markUnrequiredArgumentInUsageString(
				arg->getUsageString( m_names, flagsLength, maxNameLength ) ) );
		else
			m_usage.append( arg->getUsageString( m_names, flagsLength,
				maxNameLength ) );

		m_usage.append( QLatin1Char( '\n' ) );
	}

	replaceMarkersInUsage( m_usage );

	const int offset = 7 + m_executableName.length() + 1;
	const int width = m_lineLength - offset - 10;

	formatUsageString( m_usage, offset, width );
}

inline void
QtArgDefaultHelpPrinter::createHelpString(
	const QtArgCmdLineIface::QtArgumentsList & list )
{
	m_help.clear();

	foreach( QtArgIface * arg, list )
	{
		// It's a XOR argument.
		if( arg->arguments().size() > 1 )
			createHelpString( arg->arguments() );
		else
		{
			int flagsLength = 0;
			int maxNameLength = 0;

			const QString help = arg->getUsageString( m_names,
				flagsLength, maxNameLength );

			if( maxNameLength > m_maxNameLength )
				m_maxNameLength = maxNameLength;

			if( flagsLength > m_maxFlagsLength )
				m_maxFlagsLength = flagsLength;

			setHelpString( arg, help );
		}
	}
}

inline void
QtArgDefaultHelpPrinter::replaceMarkersInUsage( QString & usage )
{
	usage.remove( QtArgHelpPrinterIface::beforeFlags );
	usage.remove( QtArgHelpPrinterIface::beforeNames );
	usage.remove( QtArgHelpPrinterIface::newLine );

	usage.replace( QtArgHelpPrinterIface::beforeDescription,
		QLatin1String( "\n" ) );

	usage.replace( QtArgHelpPrinterIface::afterFlags,
		QLatin1String( "," ) );
	usage.replace( QtArgHelpPrinterIface::namesSeparator,
		QLatin1String( "," ) );
	usage.replace( QtArgHelpPrinterIface::flagMarker,
		m_flagsMarker );
	usage.replace( QtArgHelpPrinterIface::nameMarker,
		m_namesMarker );
}

inline QString
QtArgDefaultHelpPrinter::markUnrequiredArgumentInUsageString(
	const QString & usage )
{
	QString result = usage;

	const int beforeFlags =
		result.indexOf( QtArgHelpPrinterIface::beforeFlags );

	if( beforeFlags != -1 )
	{
		result.replace( beforeFlags, QtArgHelpPrinterIface::beforeFlags.length(),
			QLatin1String( "[ " ) );
	}
	else
	{
		const int beforeNames =
			result.indexOf( QtArgHelpPrinterIface::beforeNames );

		if( beforeNames != -1 )
			result.replace( beforeNames,
				QtArgHelpPrinterIface::beforeNames.length(),
				QLatin1String( "[ " ) );
	}

	const int beforeDescription = result.lastIndexOf(
		QtArgHelpPrinterIface::beforeDescription );

	if( beforeDescription != -1 )
		result.replace( beforeDescription,
			QtArgHelpPrinterIface::beforeDescription.length(),
			QLatin1String( " ]\n" ) );

	return result;
}

inline void
QtArgDefaultHelpPrinter::formatUsageString( QString & usage,
	int offset, int width )
{
	QStringList list = usage.split( QLatin1Char( '\n' ),
		QString::SkipEmptyParts );

	formatString( list, usage, offset, width );
}

inline void
QtArgDefaultHelpPrinter::formatString( const QStringList & words,
	QString & str, int offset, int width )
{
	str.clear();

	QStringListIterator it( words );

	int length = 0;

	while( it.hasNext() )
	{
		const QString value = it.next();

		length += value.length();

		if( length <= width )
		{
			str.append( value );
			str.append( QLatin1Char( ' ' ) );
		}
		else
		{
			length = value.length();
			str.append( QLatin1Char( '\n' ) );
			str.append( QString( offset, QLatin1Char( ' ' ) ) );
			str.append( value );
		}
	}
}

inline void
QtArgDefaultHelpPrinter::replaceMarkersInHelp()
{
	const int beforeFlagsLength = 2;
	const int afterNamesLength = 3;

	const int beforeNamesLength = beforeFlagsLength +
		m_maxFlagsLength + 2;
	const int beforeDescLength = beforeNamesLength +
		m_maxNameLength + afterNamesLength;

	QMutableMapIterator< QtArgIface*, QString > it( m_help );

	while( it.hasNext() )
	{
		it.next();

		it.value().replace( QtArgHelpPrinterIface::flagMarker,
			m_flagsMarker );
		it.value().replace( QtArgHelpPrinterIface::nameMarker,
			m_namesMarker );
		it.value().replace( QtArgHelpPrinterIface::namesSeparator,
			m_namesSeparator );

		const int beforeFlagsIdx =
			it.value().indexOf( QtArgHelpPrinterIface::beforeFlags );

		if( beforeFlagsIdx != -1 )
			it.value().replace( beforeFlagsIdx,
				QtArgHelpPrinterIface::beforeFlags.length(),
				QString( beforeFlagsLength, QLatin1Char( ' ' ) ) );

		int afterFlagsIdx =
			it.value().indexOf( QtArgHelpPrinterIface::afterFlags );

		if( afterFlagsIdx != -1 )
		{
			QString afterFlagsString( beforeNamesLength - afterFlagsIdx,
				QLatin1Char( ' ' ) );
			afterFlagsString.replace( 0, 1, QLatin1Char( ',' ) );

			it.value().replace( afterFlagsIdx,
				QtArgHelpPrinterIface::afterFlags.length(),
				afterFlagsString );
		}

		replaceBeforeNames( it, beforeNamesLength );

		replaceBeforeDescriptionAndSetDescription( it, beforeDescLength );
	}
}

inline void
QtArgDefaultHelpPrinter::replaceBeforeNames(
	QMutableMapIterator< QtArgIface*, QString > & it, int beforeNamesLength )
{
	int beforeNamesIdx =
		it.value().indexOf( QtArgHelpPrinterIface::beforeNames );

	while( beforeNamesIdx != -1 )
	{
		it.value().replace( beforeNamesIdx,
			QtArgHelpPrinterIface::beforeNames.length(),
			QString( beforeNamesLength, QLatin1Char( ' ' ) ) );

		beforeNamesIdx =
			it.value().indexOf( QtArgHelpPrinterIface::beforeNames );
	}
}

static inline void
insertDescription( QStringList & words, int availableSpace,
	int pos, QString & result, int minSpace,
	int & newLineIdx )
{
	if( availableSpace > minSpace )
	{
		int wordsLength = words.first().length();

		while( wordsLength <= availableSpace && !words.isEmpty() )
		{
			result.insert( pos, words.first() );

			pos += words.first().length();

			if( wordsLength < availableSpace )
			{
				result.insert( pos, QLatin1Char( ' ' ) );

				++pos;
				++wordsLength;
			}

			words.removeFirst();

			if( !words.isEmpty() )
				wordsLength += words.first().length();
		}
	}

	result.insert( pos, QLatin1Char( '\n' ) );

	newLineIdx = pos + 1;
}

inline void
QtArgDefaultHelpPrinter::replaceBeforeDescriptionAndSetDescription(
	QMutableMapIterator< QtArgIface*, QString > & it,
	int beforeDescriptionLength )
{
	int beforeDescIdx =
		it.value().indexOf( QtArgHelpPrinterIface::beforeDescription );

	int availableSpace = m_lineLength - beforeDescriptionLength;
	const int minSpaceForDesc = 20;

	QStringList words = it.key()->description().split( QLatin1Char( ' ' ),
		QString::SkipEmptyParts );

	int newLineIdx = 0;

	while( beforeDescIdx != -1 )
	{
		const int toReplaceWithSpaces = beforeDescriptionLength -
			( beforeDescIdx - newLineIdx );

		it.value().replace( beforeDescIdx,
			QtArgHelpPrinterIface::beforeDescription.length(),
			QString( toReplaceWithSpaces, QLatin1Char( ' ' ) ) );

		beforeDescIdx += toReplaceWithSpaces;

		if( !words.isEmpty() )
			insertDescription( words, availableSpace,
				beforeDescIdx, it.value(), minSpaceForDesc,
				newLineIdx );
		else
			it.value().insert( beforeDescIdx, QLatin1Char( '\n' ) );

		beforeDescIdx =
			it.value().indexOf( QtArgHelpPrinterIface::beforeDescription );
	}

	if( availableSpace < minSpaceForDesc )
	{
		beforeDescriptionLength = 10;
		availableSpace = m_lineLength - beforeDescriptionLength;
	}

	while( !words.isEmpty() )
	{
		it.value().insert( it.value().length(),
			QString( beforeDescriptionLength, QLatin1Char( ' ' ) ) );

		insertDescription( words, availableSpace,
			it.value().length(), it.value(), minSpaceForDesc,
			newLineIdx );
	}
}

inline void
QtArgDefaultHelpPrinter::setProgramDescription( const QString & desc )
{
	m_programDescription = desc;
}

inline void
QtArgDefaultHelpPrinter::setExecutableName( const QString & exec )
{
	m_executableName = exec;
}

inline void
QtArgDefaultHelpPrinter::setCmdLine( QtArgCmdLine * cmdLine )
{
	m_cmdLine = cmdLine;

	setDelimiterChar( m_cmdLine->delimiter() );
}

inline void
QtArgDefaultHelpPrinter::setLineLength( int length )
{
	m_lineLength = length;
}

inline void
QtArgDefaultHelpPrinter::setHelpString( QtArgIface * arg, const QString & help )
{
	m_help.insert( arg, help );
}

inline void
QtArgDefaultHelpPrinter::setDelimiterChar( const QChar & delim )
{
	m_flagsMarker = QString( delim );
	m_namesMarker = QString( 2, delim );
}


//
// QtArgHelp
//

//! Argument for the help priniting.
/*!
	Defined as argument with "h" flag and
	"help" name.
*/
class QtArgHelp
	:	public QtArg
{
	public:
		explicit QtArgHelp( QtArgCmdLine * cmdLine,
			bool throwExceptionOnPrint = true );

		virtual ~QtArgHelp();

		//! \return Printer implementation.
		QtArgHelpPrinterIface * printer();

		//! Set printer implementation.
		void setPrinter( QtArgHelpPrinterIface * p );

		//! \name QtArgIface implementation.
		//! \{

			//! Process with visitor.
			virtual void visit( QtArgCmdLineContext & context );

		//! \}

	private:
		//! Printer implemenation.
		QtArgHelpPrinterIface * m_printer;
		//! Pointer to the QtArgCmdLine.
		QtArgCmdLine * m_cmdLine;
		//! Should argument throw exception on printing of help.
		bool m_throwExceptionOnPrint;
}; // class QtArgHelp


//
// QtArgHelp implementation.
//

inline
QtArgHelp::QtArgHelp( QtArgCmdLine * cmdLine,
	bool throwExceptionOnPrint )
	:	QtArg( QLatin1Char( 'h' ), QLatin1String( "help" ),
			QLatin1String( "Print this help." ) )
	,	m_printer( QtArgDefaultHelpPrinter::instance() )
	,	m_cmdLine( cmdLine )
	,	m_throwExceptionOnPrint( throwExceptionOnPrint )
{
	m_printer->setCmdLine( m_cmdLine );
}

inline
QtArgHelp::~QtArgHelp()
{
}

inline QtArgHelpPrinterIface *
QtArgHelp::printer()
{
	return m_printer;
}

inline void
QtArgHelp::setPrinter( QtArgHelpPrinterIface * p )
{
	m_printer = p;

	m_printer->setCmdLine( m_cmdLine );
}

inline void
QtArgHelp::visit( QtArgCmdLineContext & context )
{
	m_printer->setCmdLine( m_cmdLine );

	if( !context.atEnd() )
	{
		QString argName = context.next();

		if( m_cmdLine->isArgument( argName ) )
		{
			argName.replace( 0, 2, QLatin1String( "" ) );

			printer()->printForArgument( argName );
		}
		else if( m_cmdLine->isFlag( argName ) )
		{
			QTextStream out( stdout );
			argName.replace( 0, 1, QLatin1String( "" ) );

			if( argName.length() )
			{
				try {
					QtArgIface * arg = m_cmdLine->findArgument( argName[ 0 ] );

					foreach( QChar f, argName )
					{
						if( arg != m_cmdLine->findArgument( f ) )
							throw QtArgUnknownArgumentEx( QString() );
					}

					printer()->printForArgument( argName[ 0 ] );
				}
				catch( const QtArgUnknownArgumentEx & )
				{
					out << QString::fromLatin1( "Unknown argument: %1%2" )
						.arg( m_cmdLine->delimiter() )
						.arg( argName );

					if( m_throwExceptionOnPrint )
						throw QtArgHelpHasPrintedEx();
				}
			}
			else
			{
				out << QLatin1String( "Empty flag." );

				if( m_throwExceptionOnPrint )
					throw QtArgHelpHasPrintedEx();
			}
		}
		else
			printer()->printForArgument( argName );
	}
	else
		m_printer->print();

	if( m_throwExceptionOnPrint )
		throw QtArgHelpHasPrintedEx();
}

#endif // QTARG__HELP_HPP__INCLUDED
