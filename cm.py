#!/usr/bin/env python3

import sys
import re

replace_type = "MyClass"
wfile_text = ""
drawBSlash = False
lineWidth = 100

with open(sys.argv[1], 'r') as rfile:
    for index, line in enumerate(rfile):
        
        nline = line
        if index == 0:
            if line.find("/* Macro */") > -1:
                isMacro = True
                nline = line.replace("/* Macro */", "/* No Macro */")
            else:
                isMacro = False
                nline = line.replace("/* No Macro */", "/* Macro */")
        if isMacro:
            nline = nline.replace("// struct MyClass {", "struct MyClass {")
            nline = nline.replace("#define Deque_DEFINE", "//#define Deque_DEFINE")
            nline = nline.replace(" #TYPE", " \"" + str(replace_type) + "\"")
            nline = nline.replace("TYPE", replace_type)
            nline = nline.replace("##", "")
            nline = nline.replace(" \\", "")
            nline = nline.rstrip()
            nline = nline + "\n"
        else:
            nline = nline.replace("struct MyClass {", "// struct MyClass {")
            nline = nline.replace("_" + str(replace_type) + "_", "_##TYPE##_")
            nline = nline.replace("_" + str(replace_type), "_##TYPE")
            nline = nline.replace("\"" + str(replace_type) + "\"", "#TYPE")
            nline = nline.replace(str(replace_type), "TYPE")
            nline = nline.replace("struct TYPE {", "struct MyClass {")
            if(nline.find("//#define Deque_DEFINE") > -1):
                drawBSlash = True
                nline = nline.replace("//#define", "#define")
            if nline.find("/* End Macro */") > -1:
                drawBSlash = False
            if drawBSlash:
                # print(len(nline))
                nline = nline.replace("\n", (" " * (lineWidth - len(nline))) + " \\\n")
        wfile_text += nline
with open(sys.argv[1], 'w') as wfile:
    new_file = "".join(wfile_text)
    wfile.write(new_file)

