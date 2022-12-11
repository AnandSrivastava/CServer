'''
server_app.py 
script to add endpoint and rest handler (controller) in CServer
To register a controller
	python3 server_app.py --add-controller=<controller_name>

Add handling of the rest request in file name shown in the output.
GET @ <controller_name>_get method
POST @ <controller_name>_post method
PUT @ <controller_name>_put method
DELETE @ <controller_name>_del method
PATCH @ <controller_name>_patch method

handler is automatically registered during the build. 

To remove a controller
	python3 server_app.py --remove-controller=<controller_name>
Note - above command removes all references of given controller.

--------------------------------------------------------------------------------------------------------
After a controller is added with <controller_name> all traffic to 
"http://cserver_url:port/<controller_name>/" is handled by newly added handler.

eg - a Get request to "http://cserver:port/<controller_name>/handle.js" goes to newly added controller's
<controller_name>_get method with resource set to "handle.js"
--------------------------------------------------------------------------------------------------------

Author - Anand Kumar

'''
import sys, os, getopt

##########################################################################################################
def replace_and_copy(name, dest, src) :
	if os.path.exists(dest) :
		raise Exception(dest+" already exist. Check controller name")

	with open(src, 'r') as  in_file :
		with open(dest, 'w+') as out_file :
			for line in in_file :
				out_file.write(line.replace("{{name}}", name))

#############################################################################################################
def create_header(name) :
	replace_and_copy(name, "../app/include/"+name+"_endpoint.h", "sample/sample.h")

def create_impl(name) :
	replace_and_copy(name, "../app/"+name+"_endpoint.c", "sample/sample.c")

def update_www_resources(name) :
	if not os.path.exists("../www/"+name) :
		os.mkdir("../www/"+name)

	replace_and_copy(name, "../www/"+name+"/index.html", "sample/index.html")
	replace_and_copy(name, "../www/"+name+"/method_not_implemented.html", "sample/sample_404.html")

def update_header(name) :
	with open("../app/handlers.app", "a+") as app :
		app.write(name)
		app.write("\n");
###############################################################################################################

def controller_exists(name) :
	ret = False
	try :
		with open("../app/handlers.app","r+") as app :
			controllers = app.read().splitlines()
			for line in controllers :
				if line == name :
					ret = True
					break
	except :
		pass

	return ret

def insert_endpoint(name) :
	if not controller_exists(name) :
		try :
			create_header(name)
			create_impl(name)
			update_www_resources(name)
			update_header(name)
			sys.stdout.write("goto : app/"+name+"_endpoint.c to change rest handling of \"http://<<cserver>>:port/"+name+"\" endpoint\n")
			sys.stdout.write("resource : all resource of current controller is to be placed @ www\\"+name+"\n")
			sys.stdout.write("Please !! rebuild current project by running \"make cserver\" at the root folder of cserver\n")
		except Exception as e :
			revert_file(name)
			print(e)
	else :
		raise Exception("Controller "+name+" already exists.")

###########################################################################################################
def unregister_controller(name) :
	ret = False
	try :
		controllers = []
		with open("../app/handlers.app","r+") as app :
			controllers = app.read().splitlines()

		with open("../app/handlers.app","w+") as app :
			for controller in controllers :
				if controller == name :
					continue;
				app.write(controller)
				app.write("\n")
	except :
		pass


def remove_if_there(f) :
	if os.path.exists(f) :
		if os.path.isfile(f) :
			os.remove(f)
		else :
			os.rmdir(f)

def revert_file(name) :
	remove_if_there("../app/include/"+name+"_endpoint.h")
	remove_if_there("../app/"+name+"_endpoint.c")
	remove_if_there("../www/"+name+"/index.html")
	remove_if_there("../www/"+name+"/method_not_implemented.html")
	remove_if_there("../www/"+name)
	unregister_controller(name)
	sys.stdout.write("Please !! rebuild current project by running \"make cserver\" at the root folder of cserver\n")
################################################################################################################

if __name__ == "__main__" :
	args = sys.argv[1:]
	try :
		opts, args = getopt.getopt(args, "a:r:", ["add-controller=", "remove-controller="])
		for opt, arg in opts :
			if opt in ["--add-controller", "-a"] :
				insert_endpoint(arg)
			elif opt in ["--remove-controller", "-r"] :
				revert_file(arg)
	except Exception as e :
		print(e)
