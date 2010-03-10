/*
   Copyright (C) 2008, 2010, Oracle and/or its affiliates. All rights reserved.

   The MySQL Connector/C++ is licensed under the terms of the GPL
   <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
   MySQL Connectors. There are special exceptions to the terms and
   conditions of the GPL as it is applied to this software, see the
   FLOSS License Exception
   <http://www.mysql.com/about/legal/licensing/foss-exception.html>.
*/

#ifndef _SQL_WARNING_H_
#define _SQL_WARNING_H_


#include <stdexcept>
#include <string>
#include <memory>
#include "sqlstring.h"

namespace sql
{

#ifdef _WIN32
#pragma warning (disable : 4290)
//warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#endif

class SQLWarning
{
protected:

	const sql::SQLString	sql_state;
	const int				errNo;
	SQLWarning *			next;
	const sql::SQLString	descr;

public:

	SQLWarning(const sql::SQLString& reason, const sql::SQLString& SQLState, int vendorCode) :sql_state(SQLState), errNo(vendorCode),descr(reason)
	{
	}

	SQLWarning(const sql::SQLString& reason, const sql::SQLString& SQLState) :sql_state (SQLState), errNo(0), descr(reason)
	{
	}

	SQLWarning(const sql::SQLString& reason) : sql_state ("HY000"), errNo(0), descr(reason)
	{
	}

	SQLWarning() : sql_state ("HY000"), errNo(0) {}


	const sql::SQLString & getMessage() const
	{
		return descr;
	}


	const sql::SQLString & getSQLState() const
	{
		return sql_state;
	}

	int getErrorCode() const
	{
		return errNo;
	}

	const SQLWarning * getNextWarning() const
	{
		return next;
	}

	void setNextWarning(SQLWarning * _next)
	{
		next = _next;
	}

	virtual ~SQLWarning() throw () {};

protected:

	SQLWarning(const SQLWarning& e) : sql_state(e.sql_state), errNo(e.errNo), next(e.next), descr(e.descr) {}

	virtual SQLWarning * copy()
	{
		return new SQLWarning(*this);
	}

private:
	const SQLWarning & operator = (const SQLWarning & rhs);

};


} /* namespace sql */

#endif /* _SQL_WARNING_H_ */
