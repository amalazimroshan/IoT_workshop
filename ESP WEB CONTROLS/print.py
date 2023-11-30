import sys

if ( len(sys.argv) > 2 ):

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(input_file,"r") as input , open(output_file,"w") as output :

        for line in input:
            modified_line = "client.println(\""+line.strip()+"\");\n"
            output.write(modified_line)



