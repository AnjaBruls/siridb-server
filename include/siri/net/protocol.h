/*
 * protocol.h - Protocol for SiriDB.
 *
 * author       : Jeroen van der Heijden
 * email        : jeroen@transceptor.technology
 * copyright    : 2016, Transceptor Technology
 *
 * changes
 *  - initial version, 17-03-2016
 *
 */
#pragma once

typedef enum
{
    CPROTO_REQ_QUERY,                           // (query, time_precision)
    CPROTO_REQ_INSERT,                          // series with points map/array
    CPROTO_REQ_AUTH,                            // (user, password, dbname)
    CPROTO_REQ_PING,                            // empty
    CPROTO_REQ_INFO,                            // empty
    CPROTO_REQ_LOADDB,                          // database path
    CPROTO_REQ_REGISTER_SERVER,                 // (uuid, host, port, pool)
    CPROTO_REQ_FILE_SERVERS,                    // empty
    CPROTO_REQ_FILE_USERS,                      // empty
    CPROTO_REQ_FILE_GROUPS,                     // empty
    CPROTO_REQ_FILE_DATABASE,                   // empty
    /* Administrative API request */
    CPROTO_REQ_ADMIN=32,                       // (user, password, request, {...})
} cproto_client_t;

typedef enum
{
    /* success */
    CPROTO_RES_QUERY,                           // {query response data}
    CPROTO_RES_INSERT,                          // {"success_msg": ...}
    CPROTO_RES_AUTH_SUCCESS,                    // empty
    CPROTO_RES_ACK,                             // empty
    CPROTO_RES_INFO,                            // [version, [dnname1, ...]]
    CPROTO_RES_FILE,                            // file content

    /* Administrative API success */
    CPROTO_ACK_ADMIN=32,                        // empty
    CPROTO_ACK_ADMIN_DATA,                      // [...]

    /* errors 64-69 are errors with messages */
    CPROTO_ERR_MSG=64,                          // {"error_msg": ...}
    CPROTO_ERR_QUERY,                           // {"error_msg": ...}
    CPROTO_ERR_INSERT,                          // {"error_msg": ...}
    CPROTO_ERR_SERVER,                          // {"error_msg": ...}
    CPROTO_ERR_POOL,                            // {"error_msg": ...}
    CPROTO_ERR_USER_ACCESS,                     // {"error_msg": ...}
    CPROTO_ERR,                                 // empty (use for unexpected errors)
    CPROTO_ERR_NOT_AUTHENTICATED,               // empty
    CPROTO_ERR_AUTH_CREDENTIALS,                // empty
    CPROTO_ERR_AUTH_UNKNOWN_DB,                 // empty
    CPROTO_ERR_LOADING_DB,                      // empty
    CPROTO_ERR_FILE,                            // empty

    /* Administrative API errors */
    CPROTO_ERR_ADMIN=96,                        // {"error_msg": ...}
    CPROTO_ERR_ADMIN_INVALID_REQUEST,           // empty
    CPROTO_DEFERRED=127                         // deferred...
} cproto_server_t;

typedef enum
{
    BPROTO_AUTH_REQUEST=128,                    /* (uuid, dbname, flags, version,
                                                min_version, dbpath, buffer_path,
                                                buffer_size, startup_time,
                                                address, port) */
    BPROTO_FLAGS_UPDATE,                        // flags
    BPROTO_LOG_LEVEL_UPDATE,                    // log_level
    BPROTO_REPL_FINISHED,                       // empty
    BPROTO_QUERY_SERVER,                        // (query, time_precision)
    BPROTO_QUERY_UPDATE,                        // (query, time_precision)
    BPROTO_INSERT_POOL,                         // {series: points, ...}
    BPROTO_INSERT_SERVER,                       // {series: points, ...}
    BPROTO_INSERT_TEST_POOL,                    // {series: points, ...}
    BPROTO_INSERT_TEST_SERVER,                  // {series: points, ...}
    BPROTO_INSERT_TESTED_POOL,                  // {series: points, ...}
    BPROTO_INSERT_TESTED_SERVER,                // {series: points, ...}
    BPROTO_REGISTER_SERVER,                     // (uuid, host, port, pool)
    BPROTO_DROP_SERIES,                         // series_name
    BPROTO_REQ_GROUPS,                          // empty
    BPROTO_ENABLE_BACKUP_MODE,                  // empty
    BPROTO_DISABLE_BACKUP_MODE,                 // empty
} bproto_client_t;

/*
 * Success and error messages are set this way so that we have one range
 * for error messages between 64.. 191.
 *
 * Client Success messages in range 0..63
 * Client Error messages in range 64..126 (127 is used as deferred)
 * Back-end Error messages in range 128..191
 * Back-end Success messages in range 192..254 (exclude 255)
 */
typedef enum
{
    /* Mappings to client protocol messages */
    /* success */
    BPROTO_RES_QUERY=CPROTO_RES_QUERY,          // {query response data}

    /* errors */
    BPROTO_ERR_QUERY=CPROTO_ERR_QUERY,          // {"error_msg": ...}
    BPROTO_ERR_SERVER=CPROTO_ERR_SERVER,        // {"error_msg": ...}
    BPROTO_ERR_POOL=CPROTO_ERR_POOL,            // {"error_msg": ...}

    /* Back-end specific protocol messages */
    /* errors */
    BPROTO_AUTH_ERR_UNKNOWN_UUID=128,           // empty
    BPROTO_AUTH_ERR_UNKNOWN_DBNAME,             // empty
    BPROTO_AUTH_ERR_INVALID_UUID,               // empty
    BPROTO_AUTH_ERR_VERSION_TOO_OLD,            // empty
    BPROTO_AUTH_ERR_VERSION_TOO_NEW,            // empty
    BPROTO_ERR_NOT_AUTHENTICATED,               // empty
    BPROTO_ERR_INSERT,                          // empty
    BPROTO_ERR_REGISTER_SERVER,                 // empty
    BPROTO_ERR_DROP_SERIES,                     // empty
    BPROTO_ERR_ENABLE_BACKUP_MODE,              // empty
    BPROTO_ERR_DISABLE_BACKUP_MODE,             // empty

    /* success */
    BPROTO_AUTH_SUCCESS=192,                    // empty
    BPROTO_ACK_FLAGS,                           // empty
    BPROTO_ACK_LOG_LEVEL,                       // empty
    BPROTO_ACK_INSERT,                          // empty
    BPROTO_ACK_REPL_FINISHED,                   // empty
    BPROTO_ACK_REGISTER_SERVER,                 // empty
    BPROTO_ACK_DROP_SERIES,                     // empty
    BPROTO_ACK_ENABLE_BACKUP_MODE,              // empty
    BPROTO_ACK_DISABLE_BACKUP_MODE,             // empty
    BPROTO_RES_GROUPS                           // [[name, series], ...]

} bproto_server_t;

#define sirinet_protocol_is_error(tp) (tp >= 64 && tp < 192)
#define sirinet_protocol_is_error_msg(tp) (tp >= 64 && tp < 70)

const char * sirinet_cproto_client_str(cproto_client_t n);
const char * sirinet_cproto_server_str(cproto_server_t n);
const char * sirinet_bproto_client_str(bproto_client_t n);
const char * sirinet_bproto_server_str(bproto_server_t n);
