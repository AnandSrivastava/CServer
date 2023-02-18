'''
pre-build-script to create auto-generated headers.
Author - Anand Kumar
'''
import os, sys

def get_absolute(p) :
	print(os.path.join(os.path.dirname(__file__), p))
	return os.path.join(os.path.dirname(__file__), p)

def get_controllers() :
	ret = False
	controllers = []
	try :
		with open(get_absolute("../app/handlers.app"),"r+") as app :
			controllers = app.read().splitlines()
	except:
		pass

	return controllers

def generate_registration_method(includes, register) :
	with open(get_absolute("sample/handlers.h"), 'r') as  in_file :
		with open(get_absolute("../app/include/handlers.h"), 'w+') as out_file :
			for line in in_file :
				line = line.replace("{{HEADERS}}", includes)
				out_file.write(line.replace("{{REGISTER}}", register))

if __name__ == "__main__" :
	controllers = get_controllers()
	includes = ""
	register = ""
	for controller in controllers :
		if len(controller) > 0 :
			includes += "#include INCLUDES("+controller+")\n";
			register += "\tREGISTER_ONE(r,"+controller+"); \\\n";

	generate_registration_method(includes, register)
