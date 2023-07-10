#!/usr/bin/python

from pickle import FALSE
import string
from tokenize import String
import lcm
import sys

from numpy import isin
import mars_message
import inspect


# 找出模块里所有的类名
def get_classes(arg):
    classes = []
    clsmembers = inspect.getmembers(arg, inspect.isclass)
    for (name, _) in clsmembers:
        classes.append(name)
    return classes

def usage():
    print(
        "\n"
        "usage: lcmd [OPTIONS]\n"
        "\n"
        "lcm messages publish and subscibe debug.\n"
        "\n"
        "  -h     prints this help text and exits\n"
        "  -p [topic] [type] [msg]   publish msg on topic\n"
        "  -m [topic] [type] subscibe msg on topic\n"
    )

msg_info = {}

def is_class(msg):
    if isinstance(msg, int):
        return False
    if isinstance(msg, float):
        return False
    if isinstance(msg, complex):
        return False
    if type(msg) == type('124'):
        return False
    return True

def print_list(l):
    print('[')
    for v in l:
        print_msg(v)
    print(']')
def print_msg(msg):
    if not is_class(msg):
        print(msg)
        return
    print('{')
    for attr in msg.__slots__:
        if isinstance(eval('msg.'+attr), list) or isinstance(eval('msg.'+attr), tuple):
            #print(attr + "is " + type((eval('msg.'+attr))))
            print("    " + attr + ": ")
            print_list(eval('msg.'+attr))
        elif is_class(eval('msg.'+attr)):
            #print(attr + "is " + type((eval('msg.'+attr))))
            print("    " + attr + ": ")
            print_msg(eval('msg.'+attr))
        else:
            print("  " + attr + ": " + eval('str(msg.' + attr + ')'))
    print('}')

def lcm_message_handler(channel, data):
    msg = eval('mars_message.' + msg_info[channel] + '.decode(data)')
    print_msg(msg)

def lcm_publish(lc, channel, type, data):
    msg = eval('mars_message.' + type + '()')
    lc.publish(channel, msg)

def produce_auto_complete_sh():
    pass

def main():
    lc = lcm.LCM()
    sub = False
    if(len(sys.argv) == 4):
        if(sys.argv[1] == "-m"):
            msg_info[sys.argv[2]] = sys.argv[3]
            lc.subscribe(sys.argv[2], lcm_message_handler)
            sub = True    
    elif(len(sys.argv) == 5):
        if(sys.argv[1] == '-p'):
            lcm_publish(lc, sys.argv[2], sys.argv[3], sys.argv[4])
    while sub == True:
        lc.handle()
    else:
        usage()

if __name__ == "__main__":
    main()