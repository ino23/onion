/*
	Onion HTTP server library
	Copyright (C) 2010 David Moreno Montero

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as
	published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#ifndef __ONION_REQUEST__
#define __ONION_REQUEST__

#include "onion_types.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @short Methods in which data can be asked.
 */
enum onion_request_flags_e{
	OR_GET=1,
	OR_POST=2,
	OR_HEAD=4,
	
	
	OR_HTTP11=0x10,
};

typedef struct onion_request_method_e onion_request_method;

/**
 * @short Basic information about a request
 */
struct onion_request_t{
	onion_server *server; /// Server original data, like write function
	onion_dict *headers;  /// Headers prepared for this response.
	int flags;            /// Flags for this response. Ored onion_request_flags_e
	char *fullpath;       /// Original path for the request
	char *path;           /// Path at this level. Its actually a pointer inside fullpath, removing the leading parts already processed by handlers
	onion_dict *query;    /// When the query (?q=query) is processed, the dict with the values @see onion_request_parse_query
	onion_write write;    /// Write function
	void *socket;         /// Write function handler
	char buffer[128];     /// Buffer for queries. This should be enough. UGLY. FIXME.
	int buffer_pos;
};



/// Creates a request
onion_request *onion_request_new(onion_server *server, void *socket);

/// Deletes a request and all its data
void onion_request_free(onion_request *req);

/// Partially fills a request. One line each time.
int onion_request_fill(onion_request *req, const char *data);

/// Reads some data from the input (net, file...) and performs the onion_request_fill
int onion_request_write(onion_request *req, const char *data, unsigned int length);

/// Parses the query. Only called when really needs the query data. LAZY.
int onion_request_parse_query(onion_request *req);

#ifdef __cplusplus
}
#endif

#endif