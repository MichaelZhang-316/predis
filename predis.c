/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_predis.h"

/* If you declare any globals in php_predis.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(predis)
*/

/* True global resources - no need for thread safety here */
static int le_predis;

/* {{{ predis_functions[]
 *
 * Every user visible function must have an entry in predis_functions[].
 */
const zend_function_entry predis_functions[] = {
	PHP_FE(predis_connection,	NULL)
	PHP_FE_END	/* Must be the last line in predis_functions[] */
};
/* }}} */

/* {{{ predis_module_entry
 */
zend_module_entry predis_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"predis",
	predis_functions,
	PHP_MINIT(predis),
	PHP_MSHUTDOWN(predis),
	PHP_RINIT(predis),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(predis),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(predis),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_PREDIS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PREDIS
ZEND_GET_MODULE(predis)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("predis.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_predis_globals, predis_globals)
    STD_PHP_INI_ENTRY("predis.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_predis_globals, predis_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_predis_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_predis_init_globals(zend_predis_globals *predis_globals)
{
	predis_globals->global_value = 0;
	predis_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(predis)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(predis)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(predis)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(predis)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(predis)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "predis support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


PHP_FUNCTION(predis_connection)
{
  char *host=NULL;
  int host_len=0;
  int port=0;
  int failure=0;

  failure=zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sl",&host,&host_len,&port);

  if(failure==FAILURE){
    return;
  }

  struct timeval timeout={5};

  redisContext *context=NULL;
  context=redisConnectWithTimeout(host,port,timeout);
  if(context==NULL){
    RETURN_STRING("connection failure",1);
  }
  else{
    redisFree(context);
    RETURN_STRING("connection success",1);
  }
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
