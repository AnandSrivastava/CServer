#include <stdio.h>

#include "url_encoded_dict.h"
#include "utils.h"
#include "logger.h"

#define VALID_CHAR_COUNT 85

//Maps a character to child-index of n-ary tree. For-invalid character it returns 162
int get_char_index(char ch) {
	static char special_char[] = {'&', '?','%','#','-','.','_','~',':','/','[',']','@','!','$','\'','(',')','*','+',',',';','='}; 

	int offset = 0, val = 100;
	if(ch >= 'a' && ch <= 'z')
		val = ch-'a';
	else if(ch >= 'A' && ch <= 'Z') {
		offset = 26;
		val = ch-'A';
	} else if(ch >= '0' && ch <= '9') {
		offset = 52;
		val = ch-'0';
	} else {
		offset = 62;
		for(int i = 0;i<sizeof(special_char)/sizeof(char);i++) {
			if(ch == special_char[i]) {
				val = i;
			}
		}
	}

	return offset+val;
}

//Rest of the world refer to it as dictionary handle. Dictionary state information is stored here.
struct url_encoded_dict {
	stored_value data;
	struct url_encoded_dict *childs[VALID_CHAR_COUNT];
};

//@see-def
url_dict create_dictionary() {
	struct url_encoded_dict *dict = (struct url_encoded_dict*)malloc_safe(sizeof(struct url_encoded_dict));
	LOG_DEBUG("Creating dictionary");
	return dict;
}

//@see-def
int insert_into_dict(url_dict t, char* hash_key, stored_value value) {
	LOG_DEBUG("inserting into dict");
	int inserted = 1;
	if(hash_key == NULL)
		return inserted;

	LOG_DEBUG(hash_key);

	struct url_encoded_dict *table = (struct url_encoded_dict*)t;
	if(table != NULL) {
		for(int i = 0;i<strlen(hash_key);i++) {
			int index = get_char_index(hash_key[i]);
			if(index < VALID_CHAR_COUNT) {
				if(table->childs[index] == NULL) {
					table->childs[index] = (struct url_encoded_dict*)malloc_safe(sizeof(struct url_encoded_dict));
				}

				table = table->childs[index];
			} else {
				break;
			}
		}

		if(table != NULL) {
			if(table->data == NULL) {
				table->data = value;
				inserted = 0;
			} else {
				inserted = 2;
			}
		}
	}

	return inserted;
}

//@see-def
stored_value get_from_dict(url_dict t, char *hash_key) {
	stored_value data = NULL;

	if(hash_key == NULL)
		return data;

	LOG_DEBUG("finding in dict");
	LOG_DEBUG(hash_key);

	struct url_encoded_dict *table = (struct url_encoded_dict*)t;
        if(table != NULL) {
                for(int i = 0;i<strlen(hash_key);i++) {
                        int index = get_char_index(hash_key[i]);
                        if(index < VALID_CHAR_COUNT)
                                table = table->childs[index];

			if(table == NULL) {
                                break;
			}
                }

                if(table != NULL && table->data != NULL)
			data = table->data;
		else
			LOG_DEBUG("entry not found");
        }

	return data;
}

//@see-def
void clear_dictionary(url_dict t) {
	if(t != NULL) {
		struct url_encoded_dict *table = (struct url_encoded_dict*)t;
		for(int i = 0;i<VALID_CHAR_COUNT;i++) {
			if(table->childs[i] != NULL)
				clear_dictionary(table->childs[i]);
		}

		free_safe(table);
	}
}
