/***********************************************************************************************************
* url_encoded_dict.h
*
* An in-memory store which stores data correspoint to a string. String preferably should be url-encoded.
* For quickly adds and retrieves data from an n-ary tree.
*
* TODO - Stored value should have a clean-up method.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __URL_ENCODED_DICT_H__
#define __URL_ENCODED_DICT_H__

#include "udef.h"

/*
* Create a dictionary to store and retrieve url-encoded string->value pair.
* @return dictionary handle
*/
url_dict create_dictionary();

/*
* Insert url-encoded key with data mapping.
* @params url_dict - dictionary handle
* @params char* - url-encoded key
* @params stored_value - value to be stored corresponding to given key.
* @return 0 if insertion successfull\
*	  1 if insertion fails\
*	  2 if key is already in the dictionary.
*/
int insert_into_dict(url_dict, char*, stored_value);

/*
* Get stored value corresponding to a key.
* @params url_dict - dictionary handle
* @params char* - url-encoded key
* @return stored value corresponding to given key. NULL if key is not present.
*/
stored_value get_from_dict(url_dict, char* );

/*
* Clears out dictionary and its stored value. 
* @param url_dict - dictionary handle
*/
void clear_dictionary(url_dict);

#endif
