## LAB1
# Kopiera det här programmet, du kan markera allt med C-a och kopiera med C-c och lägg det i en fil som du döper till p1.a.py och exekvera programmet med python3 p1.a.py


############################################################
#
# Labb 1
#

# global variables

url = "https://cloud.timeedit.net/kth/web/public01/ri16lXQo530Z5lQv57017QW6y5Yp80ZZqY65Y5gQ802917QZ79WQX66wPnabxWju.html"

############################################################
#
# imports and defs
#
import re, getopt, sys, urllib.request


class myclass:
    def __init__(self):
        self.string1 = ''
        self.string2 = ''
        self.string3 = ''
        self.string4 = ''
        self.list1 = []

    def __str__(self):
        s = "{ " + self.string4 + " " + self.string1 + " " + self.string3 + " " + self.string2
        if len(self.list1) > 3:
            s += " : " + self.list1[0] + " " + self.list1[1] + " " + self.list1[2] + " " + self.list1[3]
        s += " }"
        return s

    def __contains__(self, x):
        if x in self.string4:
            return True


###########################################################################
##
## parse_url_file
##
## IN
##
## OUT
##
def parse_url_file(file_content):
    vek = []

    reg_expr_w = re.compile(
        '.*?td.*?class.*?headline.*?> *([MTOFL][åinorä]) *20[12][0-9]-0?(1?[0-9])-0?([123]?[0-9])<.*weekin.*> *(v.*?)</',
        re.I)
    reg_expr_d = re.compile('.*?td.*?class.*?headline.*?>([A-Z][a-z]) *20[12][0-9]-0?(1?[0-9])-0?([123]?[0-9])</')
    reg_expr_t = re.compile('.*?td +id="time.*?>(.+?)</td')
    reg_expr_i = re.compile('.*?td.*?class.*?column[0-1].*?>(.*?)</td', re.I)

    lines = file_content.split('\n')
    qq = myclass()
    for j, line in enumerate(lines):

        m = reg_expr_i.match(line)
        if (m != None):
            qq.list1.append(m.group(1))
            next

        m = reg_expr_d.match(line)
        if (m != None):
            qq.string1 = m.group(1)
            qq.string3 = m.group(3) + "/" + m.group(2)
            next

        m = reg_expr_t.match(line)
        if (m != None):
            vek.append(qq)
            qq = myclass()
            qq.string2 = m.group(1)
            next

        m = reg_expr_w.match(line)
        if (m != None):
            qq.string4 = m.group(4)
            next

    return vek


###########################################################################
##
## get file content
##
## IN
##
## OUT
##
def get_file_content(file_name):
    infil = ''
    try:
        infil = open(file_name, 'r')
    except:
        print ("No such file", file_name, " please run with --update")
        print ("	python", sys.argv[0], "--update")
        sys.exit()

    file_content = infil.readlines()
    #file_content = infil.read()
    return file_content


###########################################################################
##
## usage
##
## IN
##
## OUT
##
def usage():
    print ("Usage example:")
    print ("python", sys.argv[0], "--update ")
    print ("	updates Time Edit schedule")
    print ("python", sys.argv[0], '--check "v 49"')
    print ("	checks schedule for week 49")
    print ("python", sys.argv[0])
    print ("	prints previously downloaded schedule")


###########################################################################
##
## parse_command_line_args
##
## IN
##
## OUT
##
def parse_command_line_args():
    try:
        opts, rest = getopt.getopt(sys.argv[1:], "hc:u", ["help", "check=", "update"])
    except getopt.GetoptError:
        # print help information and exit:
        print ("Unknown option")
        usage()
        sys.exit(2)

    todo = {}
    for option, value in opts:
        if option in ("-h", "--help"):
            usage()
            sys.exit()
        elif option in ('--check', '-c'):
            todo["check"] = value
        elif option in ('--update', '-u'):
            todo["update"] = value

    return todo


###########################################################################
##
## print_schedule
##
## IN
##
## OUT
##
def print_schedule(data):
    print ("----------- Schedule -------------")
    for item in data:
        print (item)


###########################################################################
##
## search_data
##
## IN
##
## OUT
##
def search_data(what, dataset):
    found = False
    for item in dataset:
        if (what in item):
            found = True
            print (item)
    if (found == False):
        print ("Nothing happens", what)


###########################################################################
##
## main
##
## IN
##
## OUT
##
def main():
    global url

    # get command line options
    todo = parse_command_line_args()

    # update time edit file
    if 'update' in todo:
        print ("fetching url ...")
        urllib.request.urlretrieve(url, "DD1321.htm")
        print ("         done")

    # Get schedule from disc
    filedata = get_file_content("DD1321.htm")
    sched = parse_url_file(filedata)

    # Do something
    if 'check' in todo:
        search_data(todo["check"], sched)
    else:
        print_schedule(sched)


###########################################################################

if __name__ == "__main__":
    main()


