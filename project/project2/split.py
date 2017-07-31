import os
import shutil

output_dir = 'code_split'

if os.path.exists(output_dir):
    shutil.rmtree(output_dir, True)
os.makedirs(output_dir)


def process_file(filename):
    fin = open(filename, 'r')
    fout = 0
    depth = 0
    new_fout_name = True
    for line in fin:
        pos = 0
        while pos < len(line) and line[pos] == ' ':
            pos = pos + 1
        if line[pos:pos + 2] == "//" or line[pos] == "#" or line[pos] == "\n":
            continue

        pos2 = pos
        while pos < len(line):
            if line[pos] == '{':
                depth = depth + 1
            elif line[pos] == '}':
                depth = depth - 1
                if depth == 0:
                    new_fout_name = True
            elif line[pos] == '(' and depth == 0 and new_fout_name:
                fout_name = line[pos2 + 1:pos]
                new_fout_name = False
                if fout:
                    fout.close()
                fout = open(output_dir + '/' + fout_name + '.c', 'w')
                print(fout_name)
            elif line[pos] == ' ':
                pos2 = pos
            pos = pos + 1

        if fout:
            fout.write(line)


process_file('sha3.c')
process_file('main.c')
