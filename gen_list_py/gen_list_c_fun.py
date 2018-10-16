# term_q *l3 = create_term_str_q("3/34333", l_vars, 55, 55, 55);
# linked_list_tail_insert_q(list2, NULL, l3);
import random
import os

def poly(filename, size):
    try:
        os.remove(filename)
    except OSError:
        pass
    
    f = open(filename, "a")
    f.write("#include <stdio.h> \n #include <time.h> \n #include \"linkedlist.h\" \n")
    f.write("linked_list_q *generate_list(){\n\n")
    f.write("\tlinked_list_q *list = create_linked_list_q();\n")
    f.write("\tint m_vars = 3;\n") 
    for i in range(0, size):
        num = random.randint(-3000, 2000000)
        den = random.randint(1, 1000000)
        d1 = random.randint(1, 6000)
        d2 = random.randint(1, 6000)
        d3 = random.randint(1, 6000)
               
        f.write("\tterm_q* l" + str(i) + " = " + "create_term_str_q(" + '\"'+str(num)+'/'+str(den) +'\"' + ',' + "m_vars" + ',' + str(d1) + ','+ str(d2) + ','+ str(d3)+");")
        f.write("\n")
        f.write("\tlinked_list_tail_insert_q(" +  "list" + "," + "NULL," + "l" + str(i) + ");")
        f.write("\n")
        f.write("")
        f.write("\n")
    f.write("\treturn list;\n")
    f.write("}")
    f.close()


if __name__ == "__main__":
    poly("generate_list_fun.c", 600000)