import re

def convert_collision_file(input_file, output_file):
    # Read the input file
    with open(input_file, 'r') as file:
        collision_data = file.read()

    # Extract name
    name_pattern = re.compile(r'const Collision (\w+)_collision\[\] = {')
    name_data = name_pattern.findall(collision_data)
    for name_str in name_data:
        name = f'{name_str}'

    # Extract vertices
    vertex_pattern = re.compile(r'COL_VERTEX\((-?\d+), (-?\d+), (-?\d+)\)')
    vertices = vertex_pattern.findall(collision_data)

    # Extract triangles
    triangle_pattern = re.compile(r'COL_TRI\((\d+), (\d+), (\d+)\)')
    triangles = triangle_pattern.findall(collision_data)

    # Extract surface types and their counts
    surface_pattern = re.compile(r'COL_TRI_INIT\(SURFACE_(\w+), (\d+)\)')
    surfaces = surface_pattern.findall(collision_data)

    # Define arrays
    verts_array = "T3DVec3 verts[{}] =\n{{\n".format(len(vertices))
    for vertex in vertices:
        verts_array += "       {{" + ", ".join(vertex) + "}},\n"
    verts_array = verts_array.strip(",\n") + "\n};\n\n"

    surface_arrays = {}
    surface_counts = {}
    for surface_suffix, count in surfaces:
        surface_type = f'SURFACE_{surface_suffix}'
        surface_arrays[surface_type] = []
        surface_counts[surface_type] = int(count)

    # Assign triangles to surface arrays
    surface_index = 0
    for surface_suffix, count in surfaces:
        surface_type = f'SURFACE_{surface_suffix}'
        for i in range(int(count)):
            triangle = triangles[surface_index]
            surface_arrays[surface_type].append(triangle)
            surface_index += 1

    # Format surface arrays
    surface_definitions = ""
    for surface_type, triangles in surface_arrays.items():
        surface_name = surface_type.replace("SURFACE_", "").capitalize()
        surface_definitions += "int {}Count = {};\n".format(surface_name, len(triangles))
        surface_definitions += "Surface {}[{}];\n".format(surface_name, len(triangles))
        

    surface_init = "\nvoid {}_init(void){{\n\n".format(name)

    for surface_type, triangles in surface_arrays.items():
        surface_name = surface_type.replace("SURFACE_", "").capitalize()
        for i, triangle in enumerate(triangles):
            surface_init += "    {0}[{1}].posA = verts[{2}]; {0}[{1}].posB = verts[{3}]; {0}[{1}].posC = verts[{4}];\n".format(surface_name, i, triangle[0], triangle[1], triangle[2])
        
        surface_init += "\n    for (int i = 0; i < {}Count; i++) {{\n".format(surface_name)
        surface_init += "        {}[i].type = {};\n".format(surface_name, surface_type)
        surface_init += "        {}[i].center = center;\n".format(surface_name)
        surface_init += "        {}[i].normal = norm;\n".format(surface_name)
        surface_init += "        {}[i].center = calc_surface_center({}[i]);\n".format(surface_name, surface_name)
        surface_init += "        {}[i].normal = calc_surface_norm({}[i]);\n".format(surface_name, surface_name)
        surface_init += "    }\n\n"

    surface_init += "}"

    # Combine everything
    final_output = verts_array + surface_definitions + surface_init

    # Write the output to the new file
    with open(output_file, 'w') as file:
        file.write(final_output)

# Specify the input and output files
input_file = 'collision.inc.c'
output_file = 'gen_col.c'

# Run the conversion
convert_collision_file(input_file, output_file)
