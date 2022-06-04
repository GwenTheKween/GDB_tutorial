import gdb

def check_type(arg, accept):
    acceptable_type = gdb.lookup_type(accept)
    arg_type = arg.type.strip_typedefs()
    if(arg_type == acceptable_type.pointer()):
        arg = arg.dereference()
        arg_type = arg.type.strip_typedefs()
    if(arg_type != acceptable_type):
        raise gdb.GdbError("wrong type of variable")
    return arg

def printSingleLevel(node):
    s = ''
    while(node['right']):
        s += str(node['val']) + ' -> '
        node = node['right'].dereference()
    print(s, node['val'])

class printListLevel (gdb.Command):
    """Print all nodes of the list at the given level"""
    def __init__(self):
        super(printListLevel, self).__init__("print-level", gdb.COMMAND_USER, gdb.COMPLETE_SYMBOL)

    def invoke(self, arg, from_tty):
        if(len(arg) == 0): #Check if there is an argument
            raise gdb.GdbError("print-level takes exactly one argument")
        arg_value = gdb.parse_and_eval(arg)
        arg_value = check_type(arg_value, 'struct list_no')
        printSingleLevel(arg_value)

class printList (gdb.Command):
    """Print all levels of a list"""
    def __init__(self):
        super(printList, self).__init__("print-list", gdb.COMMAND_USER, gdb.COMPLETE_SYMBOL)

    def invoke(self, arg, from_tty):
        if(len(arg) == 0):
            raise gdb.GdbError("print-list takes exactly one argument")
        arg_value = gdb.parse_and_eval(arg)
        arg_value = check_type(arg_value, 'struct skipList')
        node = arg_value['head']
        while(node['down']):
            printSingleLevel(node)
            node = node['down'].dereference()
        printSingleLevel(node)

printList()
printListLevel()
