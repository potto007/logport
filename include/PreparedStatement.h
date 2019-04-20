#ifndef LOGPORT_PREPARED_STATEMENT_H
#define LOGPORT_PREPARED_STATEMENT_H

#include <string>
using std::string;

#include <stdint.h>

class sqlite3_stmt;

namespace logport{

	class Database;

	class PreparedStatement{

	    public:
	    	PreparedStatement( const Database& database, const string& statement_sql );  //eg. http://www.sqlite.org/c3ref/bind_blob.html
	    	~PreparedStatement();

	    	// The leftmost SQL parameter has an offset of 1
	    	// Unbound parameters are interpreted as NULL.
			void bindInt32( int offset, int32_t value );
			void bindInt64( int offset, int64_t value );
			void bindText( int offset, const string& text );

			int step();
			int reset();
			int clearBindings();

			// gets a string type from this result offset
			// The first column has an offset of 0
			int32_t getInt32( int offset );
			int64_t getInt64( int offset );
			string getText( int offset );

			int getNumberOfColumns();


			void validateOffset( int offset ); //throws if invalid offset

			string describeColumnType( int column_type );

	    private:


	    	sqlite3_stmt *statement;
	    	sqlite3 *db;
	    	int last_step_result;
	    	int column_count;

	};

}


#endif //LOGPORT_PREPARED_STATEMENT_H
