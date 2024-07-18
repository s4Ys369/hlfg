import re

def parse_input_file(input_file):
    with open(input_file, 'r') as file:
        data = file.read()

    name_pattern = re.compile(r'const Collision (\w+)_collision\[\] = {')
    vertex_pattern = re.compile(r'COL_VERTEX\(([-\d, ]+)\)')
    tri_init_pattern = re.compile(r'COL_TRI_INIT\((\w+), (\d+)\)')
    tri_pattern = re.compile(r'COL_TRI\((\d+), (\d+), (\d+)\)')

    name_match = name_pattern.search(data)
    if not name_match:
        raise ValueError("Name not found in the input file")

    name = name_match.group(1)
    vertices = vertex_pattern.findall(data)
    tri_inits = tri_init_pattern.findall(data)
    tris = tri_pattern.findall(data)

    vertices = [tuple(map(int, v.split(', '))) for v in vertices]
    tris = [tuple(map(int, t)) for t in tris]

    surfaces = {}
    current_surface = None
    current_count = 0
    tris_index = 0

    for init in tri_inits:
        surface_type, count = init
        count = int(count)
        surface_type = surface_type.replace('SURFACE_', '')
        surfaces[surface_type] = []
        
        for _ in range(count):
            surfaces[surface_type].append(tris[tris_index])
            tris_index += 1

    return name, vertices, surfaces

def generate_c_file(name, vertices, surfaces, output_file):
    with open(output_file, 'w') as file:
        file.write('#include <libdragon.h>\n')
        file.write('#include <t3d/t3d.h>\n')
        file.write('#include <t3d/t3dmodel.h>\n')
        file.write('#include "../include/enums.h"\n')
        file.write('#include "../include/types.h"\n')
        file.write('#include "debug.h"\n')
        file.write('#include "collision.h"\n')
        file.write(f'#include "{name}.h"\n')
        file.write('#include "utils.h"\n\n')

        file.write(f'T3DMat4FP* {name}MatFP;\n')
        file.write(f'T3DModel *model{name.capitalize()};\n')
        file.write(f'rspq_block_t *dpl{name.capitalize()};\n\n')

        file.write(f'T3DVec3 {name}Verts[{len(vertices)}] =\n')
        file.write('{\n')
        for v in vertices:
            file.write(f'    {{{{{v[0]}, {v[1]}, {v[2]}}}}},\n')
        file.write('};\n\n')

        # Calculate total number of tris
        total_tris = sum(len(tris) for tris in surfaces.values())

        for surface_type, tris in surfaces.items():
            file.write(f'\nint {name}{surface_type.capitalize()}Count = {len(tris)};\n')
            file.write(f'Surface {name}{surface_type.capitalize()}[{len(tris)}];\n')

        file.write(f'\nint {name}SurfacesCount = 0;\n')
        file.write(f'Surface {name}Surfaces[{total_tris}];\n')

        file.write(f'\nvoid {name}_init(void){{\n')

        for surface_type, tris in surfaces.items():
            for i, tri in enumerate(tris):
                file.write(f'    {name}{surface_type.capitalize()}[{i}].posA = {name}Verts[{tri[0]}]; {name}{surface_type.capitalize()}[{i}].posB = {name}Verts[{tri[1]}]; {name}{surface_type.capitalize()}[{i}].posC = {name}Verts[{tri[2]}];\n')

        for surface_type, tris in surfaces.items():
            file.write(f'\n    for (int i = 0; i < {name}{surface_type.capitalize()}Count; i++) {{\n')
            file.write(f'        {name}{surface_type.capitalize()}[i].type = SURFACE_{surface_type};\n')
            file.write(f'        {name}{surface_type.capitalize()}[i].center = center;\n')
            file.write(f'        {name}{surface_type.capitalize()}[i].normal = norm;\n')
            file.write(f'        {name}{surface_type.capitalize()}[i].center = calc_surface_center({name}{surface_type.capitalize()}[i]);\n')
            file.write(f'        {name}{surface_type.capitalize()}[i].normal = calc_surface_norm({name}{surface_type.capitalize()}[i]);\n')
            file.write('    }\n')

        file.write('\n    // Combine the surfaces for collision detection\n')
        file.write('    combine_surfaces(\n')
        file.write(f'       {name}Surfaces, &{name}SurfacesCount,\n')
        for surface_type, tris in surfaces.items():
            file.write(f'       {name}{surface_type.capitalize()}, {name}{surface_type.capitalize()}Count,\n')
        file.write('    );\n')

        file.write('\n    // Allocate map\'s matrix and construct\n')
        file.write(f'    {name}MatFP = malloc_uncached(sizeof(T3DMat4FP));\n')
        file.write(f'    t3d_mat4fp_from_srt_euler({name}MatFP, (float[3]){{1.0f, 1.0f, 1.0f}}, (float[3]){{0, 0, 0}}, (float[3]){{0, 0, 0}});\n\n')

        file.write('    // Load model\n')
        file.write(f'    model{name.capitalize()} = t3d_model_load("rom:/models/{name}.t3dm");\n\n')

        file.write('    // Create map\'s RSPQ block\n')
        file.write('    rspq_block_begin();\n')
        file.write(f'        t3d_matrix_push({name}MatFP);\n')
        file.write('        matCount++;\n')
        file.write('        rdpq_set_prim_color(WHITE);\n')
        file.write(f'        t3d_model_draw(model{name.capitalize()});\n')
        file.write('        t3d_matrix_pop(1);\n')
        file.write(f'    dpl{name.capitalize()} = rspq_block_end();\n')
        file.write('}\n')

def generate_h_file(name, vertices, surfaces, output_file):
    with open(output_file, 'w') as file:
        file.write(f'#ifndef {name.upper()}_H\n')
        file.write(f'#define {name.upper()}_H\n\n')

        file.write('#include <libdragon.h>\n')
        file.write('#include <t3d/t3d.h>\n')
        file.write('#include <t3d/t3dmodel.h>\n')
        file.write('#include "../include/enums.h"\n')
        file.write('#include "../include/types.h"\n')
        file.write('#include "debug.h"\n')
        file.write('#include "collision.h"\n')
        file.write('#include "utils.h"\n\n')

        file.write(f'extern T3DVec3 {name}Verts[{len(vertices)}];\n')

        # Calculate total number of tris
        total_tris = sum(len(tris) for tris in surfaces.values())

        for surface_type, tris in surfaces.items():
            file.write(f'\nextern int {name}{surface_type.capitalize()}Count;\n')
            file.write(f'extern Surface {name}{surface_type.capitalize()}[{len(tris)}];\n')
        file.write(f'\nextern int {name}SurfacesCount;\n')
        file.write(f'extern Surface {name}Surfaces[{total_tris}];\n')
        file.write(f'\nextern T3DMat4FP* {name}MatFP;\n')
        file.write(f'extern T3DModel *model{name.capitalize()};\n')
        file.write(f'extern rspq_block_t *dpl{name.capitalize()};\n\n')

        file.write(f'void {name}_init(void);\n\n')

        file.write(f'#endif // {name.upper()}_H\n')

if __name__ == '__main__':
    input_file = 'collision.inc.c'

    name, vertices, surfaces = parse_input_file(input_file)
    c_output_file = f'{name}.c'
    h_output_file = f'{name}.h'

    generate_c_file(name, vertices, surfaces, c_output_file)
    generate_h_file(name, vertices, surfaces, h_output_file)
