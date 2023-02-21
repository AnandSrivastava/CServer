'''
pre-build-script to create auto-generated headers for configuration read from app_config.ini
Author - Anand Kumar
'''

import os, configparser

TOP_LEVEL_CONFIG = "top_level_config"

def add_c_header(handle) :
	handle.write("#ifndef _APP_CONFIGURATION_H_\n")
	handle.write("#define _APP_CONFIGURATION_H_\n\n")
	handle.write("/**************************************(AUTO GENERATED)***************************************\n* DO NOT MODIFY\n* This file is auto-generated during compilation process which ensures that all created\n* controller is registered.\n* Author - Anand Kumar\n* Github repo - https://github.com/l1nk-0\n**********************************************************************************************/\n\n")
	handle.write("#define BEGIN_STRUCT typedef struct {\n")
	handle.write("#define END_STRUCT(x) } x;\n")
	handle.write("#define ADD_MEMBER(t, n) t n;\n")

def generate_c_struct(handle, name, members) :
	handle.write("BEGIN_STRUCT\n")
	for member in members :
		handle.write("\tADD_MEMBER("+member[0]+", "+member[1]+")\n")
	handle.write("END_STRUCT("+name+")\n")

def add_c_footer(handle, value) :
	handle.write("static "+TOP_LEVEL_CONFIG+" config = {"+value+"};\n")
	handle.write("\n#endif\n")

def to_value(data) :
	value = ""
	for d in data :
		if len(value) > 0 :
			value += ","
		value += str(d)
	value = "{"+value+"}"

	return value

def getCTypeValue(val) :
	v = val
	t = "char"
	if val.isnumeric() :
		t = "long"
		v = int(val)
	elif val.count('.') == 1 and val.replace('.', '').isnumeric() :
		t = "double"
		v = float(val)
	elif val == "true" :
		t = "short"
		v = 1
	elif val == "false" :
		t = "short"
		v = 0

	return t , v

def create_config_section(items) :
	members = []
	value = []
	for item in items :
		t,v = getCTypeValue(item[1])
		if t == 'char' :
			n = item[0]+"["+str(len(item[1])+1)+"]"
		else :
			n = item[0]

		members.append((t, n))
		value.append(v)

	return members, value

def generate_server_configuration(config) :
	with open(os.path.join(os.path.dirname(__file__),"../app/include/app_config.h"), "w") as c_file :
		add_c_header(c_file)
		top_level_config_member = []
		complete_config_value = ""
		for section in config.sections() :
			members, val = create_config_section(config.items(section))
			if len(complete_config_value) > 0 :
				complete_config_value += ","
			complete_config_value += to_value(val);
			top_level_config_member.append((section+"_config", section))
			generate_c_struct(c_file, section+"_config", members)
		generate_c_struct(c_file, TOP_LEVEL_CONFIG, top_level_config_member)
		add_c_footer(c_file, complete_config_value)

if __name__ == "__main__" :
	config = configparser.ConfigParser()
	config.read(os.path.join(os.path.dirname(__file__), "../app_config.ini"))
	generate_server_configuration(config)